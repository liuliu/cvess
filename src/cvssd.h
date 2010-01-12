#ifndef _GUARD_cvssd_h_
#define _GUARD_cvssd_h_

typedef struct CvSSDPoint
{
	CvPoint2D32f pt;
	int size;
	float dir;
} CvSSDPoint;

typedef struct CvSSDParams
{
	int large_patch;
	int small_patch;
} CvSSDParams;

void cvExtractSSD( const CvArr* image, const CvArr* mask, CvSeq** keypoints, CvSeq** descriptors, CvMemStorage* storage, CvSSDParams params );

#endif
