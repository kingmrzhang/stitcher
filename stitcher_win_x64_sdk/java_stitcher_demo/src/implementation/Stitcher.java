package implementation;


import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Stitcher extends Library{
	Stitcher instanceDll  = (Stitcher)Native.loadLibrary("stitcher_win_lib_project",Stitcher.class);  
	public int stichImg_by_path(String[] path,int size);
}
