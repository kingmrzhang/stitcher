
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
		
		// Check if have enough images
		int size = n*2;
		if (size < 2)
		{
			System.out.println("We need more pictures!");
			return;
		}
		
		Stitcher stitcher = new Stitcher();
		String path[] = new String[size];
		Mat mats[] = new Mat[size];
		for (int i = 1; i <= n; i++)
		{
			path[i*2-2] = String.format("..\\..\\Common\\images\\7-43\\img (%d).jpg",i);
			mats[i*2-2] = stitcher.loadImg(path[i*2-2]);
			path[i*2-1] = String.format("..\\..\\Common\\images\\5-44\\img (%d).jpg", i);
			mats[i*2-1] = stitcher.loadImg(path[i*2-1]);
		}
		
		Mat rul = stitcher.stitchImg(mats);
		
		Imgproc.resize( rul, rul, new Size(640,480) );
		stitcher.showImg(rul);

    }  
   
 
  
} 