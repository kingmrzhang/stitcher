package implementation;


import com.sun.jna.Library;
import com.sun.jna.Native;
import org.opencv.core.Mat;
public interface Stitcher extends Library{
	Stitcher instanceDll  = (Stitcher)Native.loadLibrary("stitcher_win_lib_project",Stitcher.class);  
	public int stichimg_from_path(String[] src_path,int size);
	public int stichimg_from_path_to_path(String[] src_path,int size,String dst_path);
	public int showImg(byte[] img_data,int rows,int cols,int cvtype);
}
