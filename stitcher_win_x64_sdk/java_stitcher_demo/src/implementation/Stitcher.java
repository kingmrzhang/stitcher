package implementation;

import org.opencv.core.Mat;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Stitcher extends Library{
	Stitcher instanceDll  = (Stitcher)Native.loadLibrary("stitcher_win_lib_project",Stitcher.class);  
	Mat stitchImg(char[][] path, int size);
	public int Add(int a,int b);  
	public Mat Stitcher_stitchImg(char[][] path, int size);
	public int stichImg_by_path(String[] path,int size);
}
