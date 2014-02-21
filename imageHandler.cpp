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
	double R_D =     filters[linkIndex][0]*(int)origImg.at<cv::Vec3b>(j-1, i-1)[0] +
		             filters[linkIndex][1]*(int)origImg.at<cv::Vec3b>(j-1, i)[0] +
					 filters[linkIndex][2]*(int)origImg.at<cv::Vec3b>(j-1, i+1)[0] +
					 filters[linkIndex][3]*(int)origImg.at<cv::Vec3b>(j, i-1)[0] +
					 filters[linkIndex][4]*(int)origImg.at<cv::Vec3b>(j, i)[0] +
					 filters[linkIndex][5]*(int)origImg.at<cv::Vec3b>(j, i+1)[0] +
					 filters[linkIndex][6]*(int)origImg.at<cv::Vec3b>(j+1, i-1)[0] +
					 filters[linkIndex][7]*(int)origImg.at<cv::Vec3b>(j+1, i)[0] +
					 filters[linkIndex][8]*(int)origImg.at<cv::Vec3b>(j+1, i+1)[0];

	double G_D =	 filters[linkIndex][0]*(int)origImg.at<cv::Vec3b>(j-1, i-1)[1] +
		             filters[linkIndex][1]*(int)origImg.at<cv::Vec3b>(j-1, i)[1] +
					 filters[linkIndex][2]*(int)origImg.at<cv::Vec3b>(j-1, i+1)[1] +
					 filters[linkIndex][3]*(int)origImg.at<cv::Vec3b>(j, i-1)[1] +
					 filters[linkIndex][4]*(int)origImg.at<cv::Vec3b>(j, i)[1] +
					 filters[linkIndex][5]*(int)origImg.at<cv::Vec3b>(j, i+1)[1] +
					 filters[linkIndex][6]*(int)origImg.at<cv::Vec3b>(j+1, i-1)[1] +
					 filters[linkIndex][7]*(int)origImg.at<cv::Vec3b>(j+1, i)[1] +
					 filters[linkIndex][8]*(int)origImg.at<cv::Vec3b>(j+1, i+1)[1];

	double B_D =	 filters[linkIndex][0]*(int)origImg.at<cv::Vec3b>(j-1, i-1)[2] +
		             filters[linkIndex][1]*(int)origImg.at<cv::Vec3b>(j-1, i)[2] +
					 filters[linkIndex][2]*(int)origImg.at<cv::Vec3b>(j-1, i+1)[2] +
					 filters[linkIndex][3]*(int)origImg.at<cv::Vec3b>(j, i-1)[2] +
					 filters[linkIndex][4]*(int)origImg.at<cv::Vec3b>(j, i)[2] +
					 filters[linkIndex][5]*(int)origImg.at<cv::Vec3b>(j, i+1)[2] +
					 filters[linkIndex][6]*(int)origImg.at<cv::Vec3b>(j+1, i-1)[2] +
					 filters[linkIndex][7]*(int)origImg.at<cv::Vec3b>(j+1, i)[2] +
					 filters[linkIndex][8]*(int)origImg.at<cv::Vec3b>(j+1, i+1)[2];
	
	//double dlink = cv::norm(D_link)/SQRT3; 
	double dlink = sqrt((R_D*R_D + G_D*G_D + B_D*B_D)/3);
	//return G_D;

	/*
	// using ptr to access image
	unsigned char *input = (unsigned char*)(origImg.data);
	double R_D = filters[linkIndex][0]*input[origImg.cols * (j-1) + (i-1)]
				+filters[linkIndex][1]*input[origImg.cols * (j-1) + (i)]
				+filters[linkIndex][2]*input[origImg.cols * (j-1) + (i+1)];
				+filters[linkIndex][3]*input[origImg.cols * (j) + (i-1)]
				+filters[linkIndex][4]*input[origImg.cols * (j) + (i)]
	*/
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
	//for(int i=1; i<5; i++) {
		//for(int j=1; j<2; j++) {
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
}
