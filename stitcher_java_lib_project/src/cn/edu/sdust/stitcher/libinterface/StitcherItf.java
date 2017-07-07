package cn.edu.sdust.stitcher.libinterface;


import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public interface StitcherItf extends Library{
	StitcherItf instanceDll  = (StitcherItf)Native.loadLibrary("stitcher_win_lib_project",StitcherItf.class);  
	
	/**
	 * ƴ�ӽӿ�
	 * @param src_path	��ƴ��ͼƬ·��
	 * @param size	��ƴ��ͼƬ����
	 * @param dst_path	ƴ�ӽ������·��
	 * @return ƴ���Ƿ�ɹ�
	 */
	public int stitchimg_from_paths_to_path(String[] src_path,int size,String dst_path);
	/**
	 * ƴ�ӽӿ�
	 * @param src_path 	��ƴ��ͼƬ·��
	 * @param size	��ƴ��ͼƬ����
	 * @param mat_rows	ƴ�ӽ������
	 * @param mat_cols	ƴ�ӽ������
	 * @param mat_cvtype	ƴ�ӽ������
	 * @return	ƴ�ӽ����mat����
	 */
	public Pointer stitchimg_from_paths_to_mat(String[] src_path,int size,int[] mat_rows, int[] mat_cols, int[] mat_cvtype);
	/**
	 * ƴ�ӽӿ�
	 * @param mats 	���д�ƴ��ͼƬmat����
	 * @param mats_rows	��ƴ��ͼƬ���� ����
	 * @param mats_cols	��ƴ��ͼƬ���� ����
	 * @param mats_cvtype	��ƴ��ͼƬ���� ����
	 * @param size	��ƴ��ͼƬ����
	 * @param mat_rows	ƴ�ӽ������
	 * @param mat_cols	ƴ�ӽ������
	 * @param mat_cvtype	ƴ�ӽ������
	 * @return	ƴ�ӽ����mat����
	 * ע�⣺ͼƬ���ݿ��������free_img�ͷ��ڴ�
	 */
	public Pointer stitchimg_from_mats_to_mat(byte[] mats, int[] mats_rows, int[] mats_cols, int[] mats_cvtype, int size,
			int[] mat_rows, int[] mat_cols, int[] mat_cvtype);
	/**
	 * ��ʾMat
	 * @param img_data	ͼƬ��Mat����
	 * @param rows	ͼƬ������
	 * @param cols	ͼƬ������
	 * @param cvtype	ͼƬ������
	 * @param window_name	��ʾͼƬ�Ĵ�����
	 * @return	��ʾ�Ƿ�ɹ�
	 * ע�⣺ͼƬ���ݿ��������free_img�ͷ��ڴ�
	 */
	public int show_img(byte[] img_data,int rows,int cols,int cvtype,String window_name);
	/**
	 * ����Mat
	 * @param img_path	ͼƬ·��
	 * @param rows	����ͼƬ����
	 * @param cols	����ͼƬ����
	 * @param cvtype	����ͼƬ����
	 * @return	����ͼƬ����ָ��
	 * ע�⣺ͼƬ���ݿ��������free_img�ͷ��ڴ�
	 */
	public Pointer load_img(String img_path,int[] rows,int[] cols,int[] cvtype);
	/**
	 * �ͷŶ�̬���ӿ� �ڴ����� ���ڴ�
	 * @param p_img	����ָ��
	 */
	public void free_img(Pointer p_img);
}
