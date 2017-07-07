package cn.edu.sdust.stitcher;



import org.opencv.core.CvType;
import org.opencv.core.Mat;
import cn.edu.sdust.stitcher.libinterface.StitcherItf;
import com.sun.jna.Pointer;

public class Stitcher {
	/**
	 * ����ƴ������̬���ӿ� ����ͼƬ ��Mat
	 * @param path
	 * @return
	 */
	public Mat loadImg(String path)
	{
    	int rows[] = {0};
    	int cols[] = {0};
    	int cvtype[] = {0};
    	
     	Pointer p_data = StitcherItf.instanceDll.load_img(path,
     			rows,cols,cvtype);

     	int channels = CvType.channels(cvtype[0]);
     	byte[] data = p_data.getByteArray(0, rows[0]*cols[0]*channels);

     	Mat img = new Mat(rows[0],cols[0],cvtype[0]);
     	img.put(0,0, data);
     	//free the data memory in dll
     	StitcherItf.instanceDll.free_img(p_data);
     	
		return img;
	}
	
	/**
	 * ����ƴ������̬���ӿ� ��ʾ Mat
	 * @param image
	 */
    public void showImg(Mat image,String name){
    	byte buff[] = new byte[(int) (image.total() * image.channels())];
     	image.get(0,0,buff);
     	StitcherItf.instanceDll.show_img(buff,image.rows(),image.cols(),image.type(),name);
    }
    
    /**
     * ����ƴ������̬���ӿ� ƴ�Ӷ��Mat
     * @param mats
     * @return ƴ�Ӻ��Mat
     */
    public Mat stitchImg(Mat[] mats) {
		// Check if have enough images
		int size = mats.length;
		if (size < 2)
		{
			System.out.println("We need more pictures!");
			return new Mat(0,0,0);
		}
		
		int[] mats_rows = new int[size];
		int[] mats_cols = new int[size];
		int[] mats_cvtype = new int[size];
		int mats_total = 0;
		for(int i=0;i<size;i++) {
			mats_rows[i] = mats[i].rows();
	     	mats_cols[i] = mats[i].cols();
	     	mats_cvtype[i] = mats[i].type();
	     	mats_total += (mats[i].total() * mats[i].channels());
		}
		byte[] mats_data = new byte[mats_total];
		int current_offset = 0;
		for(int i=0;i<size;i++){
			byte[] img_data = new byte[(int)mats[i].total() * mats[i].channels()];
	     	mats[i].get(0,0,img_data);
	     	for(int j=0;j<img_data.length;j++) {
	     		mats_data[current_offset+j] = img_data[j];
	     	}
	     	current_offset += img_data.length;
		}
		
		int mat_rows[] = {0};
    	int mat_cols[] = {0};
    	int mat_cvtype[] = {0};
		Pointer p_data = StitcherItf.instanceDll.stitchimg_from_mats_to_mat(
				mats_data,  mats_rows,  mats_cols,  mats_cvtype, size,
				mat_rows,  mat_cols,  mat_cvtype);

     	byte[] mat_data = p_data.getByteArray(0, 
     			mat_rows[0]*mat_cols[0]* CvType.channels(mat_cvtype[0]));

     	Mat img = new Mat(mat_rows[0],mat_cols[0],mat_cvtype[0]);
     	img.put(0,0, mat_data);
     	//free the data memory in dll
     	StitcherItf.instanceDll.free_img(p_data);
     	
     	return img;
    }
    
    /**
     * ��ָ��·����ȡ��ƴ�ӵ�ͼƬ
     * @param src_paths
     * @param dst_path �������·����Ĭ��"result.jpg"
     * @return
     */
    public int stitchImg(String[] src_paths,String dst_path) {
    	if (dst_path.equals(""))
    		dst_path = "result.jpg";
    	StitcherItf.instanceDll.stitchimg_from_paths_to_path(src_paths,src_paths.length,dst_path);
    	return 0;
    }
    
    /**
     * ƴ��ͼƬ
     * @param src_path ��ƴ�ӵ�ͼƬ·��
     * @return ƴ����ɺ��Mat
     */
    public Mat stitchImg(String[] src_paths) {
		int mat_rows[] = {0};
    	int mat_cols[] = {0};
    	int mat_cvtype[] = {0};
		Pointer p_data = StitcherItf.instanceDll.stitchimg_from_paths_to_mat(
				src_paths,src_paths.length,mat_rows,mat_cols,mat_cvtype);

     	byte[] mat_data = p_data.getByteArray(0, 
     			mat_rows[0]*mat_cols[0]* CvType.channels(mat_cvtype[0]));

     	Mat img = new Mat(mat_rows[0],mat_cols[0],mat_cvtype[0]);
     	img.put(0,0, mat_data);
     	//free the data memory in dll
     	StitcherItf.instanceDll.free_img(p_data);
     	
     	return img;
    }
}
