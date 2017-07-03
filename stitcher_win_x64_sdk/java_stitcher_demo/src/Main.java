
import implementation.Stitcher;

import java.util.Scanner;

import java.lang.String;
import org.opencv.core.Mat;
import org.opencv.core.CvType;
import org.opencv.core.Scalar;
import org.opencv.highgui.Highgui;

public class Main {  
	static{ System.loadLibrary("opencv_java249"); }
    /** 
     * @param args 
     */  
    public static void main(String[] args) {  
        // TODO Auto-generated method stub  
    	test();
//    	stitchImg();

    }  
    
    public static void test(){
    	Mat image = Highgui.imread("..\\..\\Common\\images\\7-43\\img (1).jpg");
////    	Mat image = new Mat(5, 10, CvType.CV_8UC1, new Scalar(0));
    	byte buff[] = new byte[(int) (image.total() * image.channels())];
     	image.get(0,0,buff);
//     	
     	Stitcher.instanceDll.showImg(buff,image.rows(),image.cols(),image.type());
    	
//    	Mat m = new Mat(5, 10, CvType.CV_8UC1, new Scalar(0));
//        System.out.println("OpenCV Mat: " + m);
//        Mat mr1 = m.row(1);
//        mr1.setTo(new Scalar(1));
//        Mat mc5 = m.col(5);
//        mc5.setTo(new Scalar(5));
//        System.out.println("OpenCV Mat data:\n" + m.dump());
//        
//        byte buff[] = new byte[(int) (m.total() * m.channels())];
//    	m.get(0,0,buff);
//    	
//    	Stitcher.instanceDll.showImg(buff,m.total()*m.channels());
    }
    
    public static void stitchImg() {
    	Scanner in = new Scanner(System.in);
		System.out.print("Please input the number of row-picture:");
		int n = in.nextInt();
		in.close();
		
		String path[] = new String[n*2];
		for (int i = 1; i <= n; i++)
		{
			path[i*2-2] = String.format("..\\..\\Common\\images\\7-43\\img (%d).jpg",i);
			path[i*2-1] = String.format("..\\..\\Common\\images\\5-44\\img (%d).jpg", i);
		}
		
		// Check if have enough images
		int size = n*2;
		if (size < 2)
		{
			System.out.println("We need more pictures!");
			return;
		}
		//save result image to the local path
		Stitcher.instanceDll.stichimg_from_path(path,size);
		//save result image to the custom path
		Stitcher.instanceDll.stichimg_from_path_to_path(path,size,"..\\..\\Common\\images\\result.jpg");
    }
  
} 