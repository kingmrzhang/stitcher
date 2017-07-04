package cn.edu.sdust.stitcher;

import java.util.Scanner;

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
    public void showImg(Mat image){
    	byte buff[] = new byte[(int) (image.total() * image.channels())];
     	image.get(0,0,buff);
     	StitcherItf.instanceDll.show_img(buff,image.rows(),image.cols(),image.type());
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
		
		byte[][] mats_data = new byte[size][];
		int[] mats_rows = new int[size];
		int[] mats_cols = new int[size];
		int[] mats_cvtype = new int[size];
		for(int i=0;i<size;i++){
			mats_data[i] = new byte[(int) (mats[i].total() * mats[i].channels())];
	     	mats[i].get(0,0,mats_data[i]);
	     	mats_rows[i] = mats[i].rows();
	     	mats_cols[i] = mats[i].cols();
	     	mats_cvtype[i] = mats[i].type();
		}
		
		int mat_rows[] = {0};
    	int mat_cols[] = {0};
    	int mat_cvtype[] = {0};
		Pointer p_data = StitcherItf.instanceDll.stichimg_from_mats_to_mat(
				mats_data,  mats_rows,  mats_cols,  mats_cvtype, size,
				 mat_rows,  mat_cols,  mat_cvtype);

     	byte[] mat_data = p_data.getByteArray(0, 
     			mat_rows[0]*mat_cols[0]* CvType.channels(mat_cvtype[0]));

     	Mat img = new Mat(mat_rows[0],mat_cols[0],mat_cvtype[0]);
     	img.put(0,0, mat_data);
     	//free the data memory in dll
     	StitcherItf.instanceDll.free_img(p_data);
     	
     	return img;
		//save result image to the local path
//		StitcherItf.instanceDll.stichimg_from_path(path,size);
		//save result image to the custom path
//		StitcherItf.instanceDll.stichimg_from_path_to_path(path,size,"..\\..\\Common\\images\\result.jpg");
    }
}
