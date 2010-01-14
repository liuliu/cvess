#ifndef _GUARD_cvess_h_
#define _GUARD_cvess_h_

typedef struct CvESSPoint
{
	CvPoint2D32f pt;
	float scale;
	float dir;
} CvSSDPoint;

typedef struct CvESSParams
{
	int large_patch;
	int small_patch;
} CvESSParams;

void cvExtractESS( const CvArr* image, const CvArr* mask, CvSeq** keypoints, CvSeq** descriptors, CvMemStorage* storage, CvESSParams params );

#endif
