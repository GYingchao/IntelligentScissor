#ifndef IMAGE_HANDLER_H_H
#define IMAGE_HANDLER_H_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "pixelNode.h"

using namespace std;

/*
// basic data structure to handle pixel by pixel cost
struct PixelNode {
	double linkCost[8];
	int state;
	double totalCost;
	PixelNode *prevNode;
	int column, row;
};
*/

class ImageHandler
{
private:
	cv::Mat origImg;
	vector<PixelNode> graph;
	int cur_si, cur_sj;
public:
	ImageHandler(cv::Mat img) {
		origImg = img;
	}
	~ImageHandler(){}
	int width() { return origImg.cols;}
	int height() {return origImg.rows;}
	bool isEmpty() {return origImg.data == NULL;}
	void InitializeCostGraph();
	void LiveWireDP(int si, int sj);
	void setSeed(int si, int sj) {cur_si = si; cur_sj = sj;}
	//cv::Mat& printImg(cv::Mat pImg);
private:
	double computeEdgeDerivative(int i, int j, int linkIndex);
	void refineEdgeCost(PixelNode &pn, double factor);
};
#endif;