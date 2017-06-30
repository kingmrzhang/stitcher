#pragma once

#ifdef STITCHER_WIN_LIB_PROJECT
#define EXPORTS_STITCHER _declspec( dllexport )
#else
#define EXPORTS_STITCHER _declspec(dllimport)
#endif
class EXPORTS_STITCHER Stitcher
{
public:
	Stitcher();
	~Stitcher();
	int Add(int a, int b);
};

