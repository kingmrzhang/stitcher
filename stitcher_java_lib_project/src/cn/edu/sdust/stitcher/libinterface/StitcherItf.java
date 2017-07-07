package cn.edu.sdust.stitcher.libinterface;


import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public interface StitcherItf extends Library{
	StitcherItf instanceDll  = (StitcherItf)Native.loadLibrary("stitcher_win_lib_project",StitcherItf.class);  
	
	/**
	 * 拼接接口
	 * @param src_path	待拼接图片路径
	 * @param size	待拼接图片数量
	 * @param dst_path	拼接结果保存路径
	 * @return 拼接是否成功
	 */
	public int stitchimg_from_paths_to_path(String[] src_path,int size,String dst_path);
	/**
	 * 拼接接口
	 * @param src_path 	待拼接图片路径
	 * @param size	待拼接图片数量
	 * @param mat_rows	拼接结果行数
	 * @param mat_cols	拼接结果列数
	 * @param mat_cvtype	拼接结果类型
	 * @return	拼接结果的mat数据
	 */
	public Pointer stitchimg_from_paths_to_mat(String[] src_path,int size,int[] mat_rows, int[] mat_cols, int[] mat_cvtype);
	/**
	 * 拼接接口
	 * @param mats 	所有待拼接图片mat数据
	 * @param mats_rows	待拼接图片行数 数组
	 * @param mats_cols	待拼接图片列数 数组
	 * @param mats_cvtype	待拼接图片类型 数组
	 * @param size	待拼接图片数量
	 * @param mat_rows	拼接结果行数
	 * @param mat_cols	拼接结果列数
	 * @param mat_cvtype	拼接结果类型
	 * @return	拼接结果的mat数据
	 * 注意：图片数据拷贝后调用free_img释放内存
	 */
	public Pointer stitchimg_from_mats_to_mat(byte[] mats, int[] mats_rows, int[] mats_cols, int[] mats_cvtype, int size,
			int[] mat_rows, int[] mat_cols, int[] mat_cvtype);
	/**
	 * 显示Mat
	 * @param img_data	图片的Mat数据
	 * @param rows	图片的行数
	 * @param cols	图片的列数
	 * @param cvtype	图片的类型
	 * @param window_name	显示图片的窗体名
	 * @return	显示是否成功
	 * 注意：图片数据拷贝后调用free_img释放内存
	 */
	public int show_img(byte[] img_data,int rows,int cols,int cvtype,String window_name);
	/**
	 * 加载Mat
	 * @param img_path	图片路径
	 * @param rows	返回图片行数
	 * @param cols	返回图片列数
	 * @param cvtype	返回图片类型
	 * @return	返回图片数据指针
	 * 注意：图片数据拷贝后调用free_img释放内存
	 */
	public Pointer load_img(String img_path,int[] rows,int[] cols,int[] cvtype);
	/**
	 * 释放动态链接库 内存区域 的内存
	 * @param p_img	数据指针
	 */
	public void free_img(Pointer p_img);
}
