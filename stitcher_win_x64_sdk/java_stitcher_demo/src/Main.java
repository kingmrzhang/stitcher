
import java.util.Scanner;

import java.lang.String;
import org.opencv.core.Mat;
import org.opencv.core.CvType;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.highgui.Highgui;
import org.opencv.imgproc.Imgproc;

import cn.edu.sdust.stitcher.Stitcher;
import cn.edu.sdust.stitcher.libinterface.StitcherItf;

import com.sun.jna.Pointer;

public class Main {  
	static{ System.loadLibrary("opencv_java249"); }
    /** 
     * @param args 
     */  
    public static void main(String[] args) {  
        // TODO Auto-generated method stub 
     	
    	Scanner in = new Scanner(System.in);
		System.out.print("Please input the number of row-picture:");
		int n = in.nextInt();
		in.close();
		
		int size = n*2;
		Stitcher stitcher = new Stitcher();
		String paths[] = new String[size];
		Mat mats[] = new Mat[size];
		for (int i = 1; i <= n; i++)
		{
			paths[i*2-2] = String.format("..\\..\\Common\\images\\7-43\\img (%d).jpg",i);
			mats[i*2-2] = stitcher.loadImg(paths[i*2-2]);
			paths[i*2-1] = String.format("..\\..\\Common\\images\\5-44\\img (%d).jpg", i);
			mats[i*2-1] = stitcher.loadImg(paths[i*2-1]);
		}
		
		Mat result_from_mats = stitcher.stitchImg(mats);
		Imgproc.resize( result_from_mats, result_from_mats, new Size(640,480) );
		stitcher.showImg(result_from_mats,"result from mats");

		Mat result_from_paths = stitcher.stitchImg(paths);
		Imgproc.resize( result_from_paths, result_from_paths, new Size(640,480) );
		stitcher.showImg(result_from_paths,"result from paths");
    } 
} 