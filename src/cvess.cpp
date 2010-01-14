#include "cvess.h"

void cvExtractESS( const CvArr* _img, const CvArr* _mask,
				   CvSeq** _keypoints, CvSeq** _descriptors,
				   CvMemStorage* storage, CvESSParams params )
{
	CvMat imghdr, *img = cvGetMat(_img, &imghdr);
	CvMat maskhdr, *mask = _mask ? cvGetMat(_mask, &maskhdr) : 0;
	CvSeq* keypoints = *_keypoints;
	int x, y, k, dx, dy, r0 = params.large_patch / 2, r1 = params.small_patch / 2;
	CvMat* lp = cvCreateMat(params.large_patch + params.small_patch - 1, params.large_patch + params.small_patch - 1, CV_8UC1);
	CvMat* ssd = cvCreateMat(params.large_patch, params.large_patch, CV_32FC1);
	double trfp[6];
	CvMat trf = cvMat(2, 3, CV_64FC1, trfp);
	for (k = 0; k < keypoints->total; ++k)
	{
		(CvESSPoint*) kp = (CvESSPoint*)cvGetSeqElem(keypoints, k);
		cvmSet(trf, 0, 0, cos(kp->dir) * kp->scale);
		cvmSet(trf, 0, 1, sin(kp->dir) * kp->scale);
		cvmSet(trf, 1, 0, -sin(kp->dir) * kp->scale);
		cvmSet(trf, 1, 1, cos(kp->dir) * kp->scale);
		cvmSet(trf, 0, 2, kp->pt.x);
		cvmSet(trf, 1, 2, kp->pt.y);
		cvGetQuadrangleSubPix(img, lp, trf);
		float* ssdptr = ssd->data.fl;
		for (y = 0; y < lp->rows; ++y, ssdptr += ssd->cols)
			for (x = 0; x < lp->cols; ++x)
			{
				int sum = 0;
				uchar* lptr = lp->data.ptr + lp->step * (r1 + y) + r1 + x;
				uchar* sptr = lp->data.ptr + lp->step * r0 + r0;
				for (dy = -r1; dy < r1; ++dy, sptr += lp->step, lptr += lp->step)
				{
					for (dx = -r1; dx < r1; ++dx)
					{
						int t = sptr[dx] - lptr[dx];
						sum += t * t;
					}
				}
				ssdptr[x] = sum / (params.small_patch * params.small_patch);
			}
	}
	cvReleaseMat(&ssd);
	cvReleaseMat(&large_patch);
}

