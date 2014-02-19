#include "imageHandler.h"
#define SQRT2 1.414213562373095
#define INV_SQRT2 0.7071067811865475
#define SQRT3 1.732050807568877
double filters[8][9] = {
	// link 0
	{0.0, 0.25, 0.25,
	 0.0, 0.0, 0.0, 
	 0.0, -0.25, -0.25},
	 // link 1
	{0.0, -INV_SQRT2, 0.0,
	 0.0, 0.0, INV_SQRT2,
	 0.0, 0.0, 0.0},
	 // link 2
	{0.25, 0.0, -0.25,
	 0.25, 0.0, -0.25,
	 0.0, 0.0, 0.0},
	 // link 3
	{0.0, INV_SQRT2, 0.0,
	 -INV_SQRT2, 0.0, 0.0,
	 0.0, 0.0, 0.0},
	 // link 4
	{0.25, 0.25, 0.0,
	 0.0, 0.0, 0.0,
	 -0.25, -0.25, 0.0},
	 // link 5
	{0.0, 0.0, 0.0,
	 -INV_SQRT2, 0.0, 0.0,
	 0.0, INV_SQRT2, 0.0},
	 // link 6
	{0.0, 0.0, 0.0,
	 0.25, 0.0, -0.25,
	 0.25, 0.0, -0.25},
	 // link 7
	{0.0, 0.0, 0.0,
	 0.0, 0.0, -INV_SQRT2,
	0.0, INV_SQRT2, 0.0}
};

double ImageHandler::computeEdgeDerivative(int i, int j, int linkIndex) {
	
	// Current pixel RGB tuple is Img(i, j)
	cv::Vec3d D_link;
	D_link = filters[linkIndex][0]*origImg.at<cv::Vec3b>(i-1, j-1) +
		             filters[linkIndex][1]*origImg.at<cv::Vec3b>(i, j-1) +
					 filters[linkIndex][2]*origImg.at<cv::Vec3b>(i+1, j-1) +
					 filters[linkIndex][3]*origImg.at<cv::Vec3b>(i-1, j) +
					 filters[linkIndex][4]*origImg.at<cv::Vec3b>(i, j) +
					 filters[linkIndex][5]*origImg.at<cv::Vec3b>(i+1, j) +
					 filters[linkIndex][6]*origImg.at<cv::Vec3b>(i-1, j+1) +
					 filters[linkIndex][7]*origImg.at<cv::Vec3b>(i, j+1) +
					 filters[linkIndex][8]*origImg.at<cv::Vec3b>(i+1, j+1);

	double dlink = norm(D_link)/SQRT3; 
	return dlink;
}

void ImageHandler::refineEdgeCost(PixelNode &pn, double factor)
{
	for(int i=0; i<8; i++) {
		pn.linkCost[i] = (factor - pn.linkCost[i])*(i%2 == 0? 1:SQRT2);
	}
}

void ImageHandler::InitializeCostGraph()
{
	// initialize data structure
	double MaxD = 0.0;
	for(int i=1; i<width()-1; i++) {
		for(int j=1; j<height()-1; j++) {
			PixelNode tem(0, 0.0, NULL, i, j);
			for(int k=0; k<8; k++) {
				tem.linkCost[k] = computeEdgeDerivative(i, j, k);
				if(tem.linkCost[k] > MaxD) MaxD = tem.linkCost[k];
			}
			graph.push_back(tem);
		}
	}
	
	for(int i=0; i<graph.size(); i++) {
		refineEdgeCost(graph[i], MaxD);
	}
	//
}