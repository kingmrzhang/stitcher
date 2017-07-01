
import implementation.Stitcher;

import java.util.Scanner;
import org.opencv.core.Core;
import org.opencv.core.CvType;  
import org.opencv.core.Mat; 
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Platform;

import java.lang.String;

public class Main {  
    /** 
     * @param args 
     */  
    public static void main(String[] args) {  
        // TODO Auto-generated method stub  
    	System.loadLibrary("opencv_java249");
    	
    	Scanner in = new Scanner(System.in);
		System.out.print("Please input the number of row-picture:");
		int n = in.nextInt();
		in.close();
		
		String path[] = new String[n*2];
		for (int i = 1; i <= n; i++)
		{
			path[i*2-2] = String.format("..\\..\\Common\\images\\7-43\\img (%d).jpg",i);
//			System.out.println(path[i*2-2]);
			path[i*2-1] = String.format("..\\..\\Common\\images\\5-44\\img (%d).jpg", i);
//			System.out.println(path[i*2-1]);
		}
		
		// Check if have enough images
		int size = n*2;
		if (size < 2)
		{
			System.out.println("We need more pictures!");
			return;
		}
		
		Stitcher.instanceDll.stichImg_by_path(path,size);
		//System.out.println(Stitcher.instanceDll.Add(1, 2));
		//Mat result = Stitcher.instanceDll.Stitcher_stitchImg(path, size);
		
		//Imgproc.resize(result, result, new Size(640, 480));
		//ImageViewer imageViewer = new ImageViewer(mat, "µÚÒ»·ùÍ¼Æ¬");
    }  
  
} 