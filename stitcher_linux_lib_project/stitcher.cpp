#include "stitcher.h"



Stitcher::Stitcher()
{


}

Mat Stitcher::stichImg(vector<Mat> full_img)
{
    cv::setBreakOnError(true);
    // Check if have enough images
    int num_images = static_cast<int>(full_img.size());
    if (num_images < 2)
    {
        cout<<"需要更多图片"<<endl;
        return -1;
    }

    //若按原图片大小进行拼接时，会在曝光补偿时造成内存溢出，所以在计算时缩小图像尺寸变为work_megapix*10000
    double work_scale = 1, seam_scale = 1, compose_scale = 1;
    bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

    cout<<"寻找特征点..."<<endl;
#if ENABLE_LOG
    int64 t = getTickCount();
#endif

    Ptr<FeaturesFinder> finder;
    finder = new SurfFeaturesFinder();//使用surf方法进行特征点检测

    vector<Mat> img(num_images);
    vector<ImageFeatures> features(num_images);
    vector<Mat> images(num_images);
    vector<Size> full_img_sizes(num_images);
    double seam_work_aspect = 1;
    #pragma omp parallel for
    for (int i = 0; i < num_images; ++i)
    {
        full_img_sizes[i] = full_img[i].size();
       //计算work_scale，将图像resize到面积在work_megapix*10^6以下
        work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img[i].size().area()));

        resize(full_img[i], img[i], Size(), work_scale, work_scale);
        //将图像resize到面积在work_megapix*10^6以下
        seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img[i].size().area()));
        seam_work_aspect = seam_scale / work_scale;
        // 计算图像特征点，以及计算特征点描述子，并将img_idx设置为i
        (*finder)(img[i], features[i]);
        features[i].img_idx = i;
        cout << "Features in image #" << i + 1 << ": " << features[i].keypoints.size() << endl;
        //将源图像resize到seam_megapix*10^6，并存入image[]中
        resize(full_img[i], img[i], Size(), seam_scale, seam_scale);
        images[i] = img[i].clone();

        resize(full_img[i], img[i], Size(), seam_scale, seam_scale);
        images[i] = img[i].clone();
    }

    finder->collectGarbage();
    //cout<<"寻找特征点所用时间: " << ((getTickCount() - t) / getTickFrequency()) << " sec"<<endl;
    //对图像进行两两匹配
    //cout << "两两匹配" << endl;
    //t = getTickCount();
    //使用最近邻和次近邻匹配，对任意两幅图进行匹配
    vector<MatchesInfo> pairwise_matches;
    BestOf2NearestMatcher matcher(try_gpu, match_conf);

    matcher(features, pairwise_matches);//对pairwise_matches中大于0的进行匹配
    matcher.collectGarbage();
    //cout<<"两两匹配所用时间: " << ((getTickCount() - t) / getTickFrequency()) << " sec"<<endl;
    for(int i=0;i<num_images * num_images;++i)
    {
        if(pairwise_matches[i].confidence==0)
            pairwise_matches[i].confidence=-1;

    }

    //将置信度高于设置门限的留下来，其他的删除
    vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);//留下来的序号
    vector<Mat> img_subset;
    vector<Size> full_img_sizes_subset;
    for (size_t i = 0; i < indices.size(); ++i)
    {
        img_subset.push_back(images[indices[i]]);
        full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
    }

    images = img_subset;
    full_img_sizes = full_img_sizes_subset;

    num_images = static_cast<int>(img_subset.size());
    if (num_images < 2)
    {
        cout<<"需要更多图片"<<endl;
        return -1;
    }

    HomographyBasedEstimator estimator;//基于单应性矩阵H的估计量
    vector<CameraParams> cameras;//相机参数
    estimator(features, pairwise_matches, cameras);

    //计算出R矩阵
    for (size_t i = 0; i < cameras.size(); ++i)
    {
        Mat R;
        cameras[i].R.convertTo(R, CV_32F);
        cameras[i].R = R;
        cout << "Initial intrinsics #" << indices[i] + 1 << ":\n" << cameras[i].K() << endl;
    }
    //捆绑调整方法精确求取变换参数
    Ptr<detail::BundleAdjusterBase> adjuster;
     adjuster = new detail::BundleAdjusterRay();//使用光束法平差对所有相机参数矫正

    adjuster->setConfThresh(conf_thresh);//设置阈值
    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
    if (ba_refine_mask[0] == 'x') refine_mask(0, 0) = 1;
    if (ba_refine_mask[1] == 'x') refine_mask(0, 1) = 1;
    if (ba_refine_mask[2] == 'x') refine_mask(0, 2) = 1;
    if (ba_refine_mask[3] == 'x') refine_mask(1, 1) = 1;
    if (ba_refine_mask[4] == 'x') refine_mask(1, 2) = 1;
    adjuster->setRefinementMask(refine_mask);
    (*adjuster)(features, pairwise_matches, cameras);//cameras存储求精后的变换参数

    // Find median focal length

    vector<double> focals;//存入相机像素
    for (size_t i = 0; i < cameras.size(); ++i)
    {
        cout<<"Camera #" << indices[i] + 1 << ":\n" << cameras[i].K()<<endl;
        focals.push_back(cameras[i].focal);
    }

    sort(focals.begin(), focals.end());
    float warped_image_scale;
    if (focals.size() % 2 == 1)
        warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
    else
        warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;


        vector<Mat> rmats;
        for (size_t i = 0; i < cameras.size(); ++i)
            rmats.push_back(cameras[i].R);
        waveCorrect(rmats, wave_correct);//波形矫正
        for (size_t i = 0; i < cameras.size(); ++i)
            cameras[i].R = rmats[i];
        for (int i = 0; i < num_images; i++)
        cout << "R " << i <<":"<<cameras[i].R <<endl;

    cout << "弯曲图像 ... " << endl;
#if ENABLE_LOG
    t = getTickCount();
#endif

    vector<Point> corners(num_images);//统一坐标后的顶点
    vector<Mat> masks_warped(num_images);
    vector<Mat> images_warped(num_images);
    vector<Size> sizes(num_images);
    vector<Mat> masks(num_images);//融合掩码

    // 准备图像融合掩码
    for (int i = 0; i < num_images; ++i)
    {
        masks[i].create(images[i].size(), CV_8U);//masks为模，和图像一样大小，设置为白色，在上面进行融合
        masks[i].setTo(Scalar::all(255));
    }

    //弯曲图像和融合掩码

    Ptr<WarperCreator> warper_creator;
    warper_creator = new cv::SphericalWarper();//球面拼接

    vector<Mat> images_warped_f(num_images);
    Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));//warped_image_scale焦距中值;
    #pragma omp parallel for
    for (int i = 0; i < num_images; ++i)
    {
        Mat_<float> K;
        cameras[i].K().convertTo(K, CV_32F);
        float swa = (float)seam_work_aspect;
        K(0,0) *= swa; K(0,2) *= swa;
        K(1,1) *= swa; K(1,2) *= swa;
        corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
        cout << "k"<<i<<":" << K << endl;
        sizes[i] = images_warped[i].size();
        cout << "size" << i << ":" << sizes[i] << endl;
        cout << "corner" << i << ":" << corners[i] << endl;
        warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);//膜进行变换
        images_warped[i].convertTo(images_warped_f[i], CV_32F);
    }


    //cout<<"球面变换耗时" << ((getTickCount() - t) / getTickFrequency()) << " sec"<<endl;

    //查找图片之间的接缝
    Ptr<SeamFinder> seam_finder;
    seam_finder = new detail::GraphCutSeamFinder(GraphCutSeamFinderBase::COST_COLOR);
    seam_finder->find(images_warped_f, corners, masks_warped);

    //释放未使用内存
    images.clear();
    images_warped.clear();
    images_warped_f.clear();
    masks.clear();

    //////图像融合
    cout << "图像融合..." << endl;
#if ENABLE_LOG
    t = getTickCount();
#endif

    Mat img_warped, img_warped_s;
    Mat dilated_mask, seam_mask, mask, mask_warped;
    Ptr<Blender> blender;
    //double compose_seam_aspect = 1;
    double compose_work_aspect = 1;
    #pragma omp parallel for
    for (int img_idx = 0; img_idx < num_images; ++img_idx)
    {
        LOGLN("Compositing image #" << indices[img_idx] + 1);

        //重新计算

        if (!is_compose_scale_set)
        {
            if (compose_megapix > 0)
                compose_scale = min(1.0, sqrt(compose_megapix * 1e6 / full_img[img_idx].size().area()));
            is_compose_scale_set = true;


            compose_work_aspect = compose_scale / work_scale;


        // 更新弯曲图像比例
            warped_image_scale *= static_cast<float>(compose_work_aspect);
            warper = warper_creator->create(warped_image_scale);

            //更新 corners and sizes
            for (int i = 0; i < num_images; ++i)
            {
                // 更新相机属性
                cameras[i].focal *= compose_work_aspect;
                cameras[i].ppx *= compose_work_aspect;
                cameras[i].ppy *= compose_work_aspect;

                //更新 corner and size
                Size sz = full_img_sizes[i];
                if (std::abs(compose_scale - 1) > 1e-1)
                {
                    sz.width = cvRound(full_img_sizes[i].width * compose_scale);
                    sz.height = cvRound(full_img_sizes[i].height * compose_scale);
                }
                //corners和sizes
                Mat K;
                cameras[i].K().convertTo(K, CV_32F);
                Rect roi = warper->warpRoi(sz, K, cameras[i].R);
                corners[i] = roi.tl();
                sizes[i] = roi.size();
            }
        }
        if (abs(compose_scale - 1) > 1e-1)
            resize(full_img[img_idx], img[img_idx], Size(), compose_scale, compose_scale);
        else
            img = full_img;
        full_img[img_idx].release();
        Size img_size = img[img_idx].size();

        Mat K;
        cameras[img_idx].K().convertTo(K, CV_32F);

        // 扭曲当前图像
        warper->warp(img[img_idx], K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

        // 扭曲当图像掩模
        mask.create(img_size, CV_8U);
        mask.setTo(Scalar::all(255));
        warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

        // 曝光补偿


        img_warped.convertTo(img_warped_s, CV_16S);
        img_warped.release();
        img[img_idx].release();
        mask.release();

        dilate(masks_warped[img_idx], dilated_mask, Mat());
        resize(dilated_mask, seam_mask, mask_warped.size());
        mask_warped = seam_mask & mask_warped;
        //初始化blender

        if (blender.empty())
        {
            blender = Blender::createDefault(blend_type, try_gpu);
            Size dst_sz = resultRoi(corners, sizes).size();
            float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;

            if (blend_width < 1.f)
                blender = Blender::createDefault(Blender::NO, try_gpu);

            else
            {
                MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(static_cast<Blender*>(blender));
                mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));

            }

        //根据corners顶点和图像的大小确定最终全景图的尺寸
            blender->prepare(corners, sizes);
        }

        // 融合当前图像
        blender->feed(img_warped_s, mask_warped, corners[img_idx]);
    }

    Mat result, result_mask;
    blender->blend(result, result_mask);
    result.convertTo(result, (result.type() / 8) * 8);
    //imwrite(result_name, result);
    //cout<<"程序运行时间为: " << ((getTickCount() - app_start_time) / getTickFrequency()) << " 秒"<<endl;
    cout << "succeed" << endl;
    return result;
}
