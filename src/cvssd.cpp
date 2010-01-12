#include "cvssd.h"

void cvExtractSSD( const CvArr* _img, const CvArr* _mask,
				   CvSeq** _keypoints, CvSeq** _descriptors,
				   CvMemStorage* storage, CvSSDParams params )
{
	CvMat imghdr, *img = cvGetMat(_img, &imghdr);
	CvMat maskhdr, *mask = _mask ? cvGetMat(_mask, &maskhdr) : 0;
	
}

