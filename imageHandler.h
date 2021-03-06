#ifndef IMAGE_HANDLER_H_H
#define IMAGE_HANDLER_H_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "pixelNode.h"
#include <QString>
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
struct vec2i{
	int pos[2];
};

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
	void getPath(int i, int j, vector<vec2i>& container);
	cv::Mat ComputePixelNodeGraph();
	void saveMask(vector<vector<vec2i>> contour, QString filename);
	void saveContour(vector<vector<vec2i>> contour, QString filename);
private:
	double computeEdgeDerivative(int i, int j, int linkIndex);
	void refineEdgeCost(PixelNode &pn, double factor);
	//For debug
	void printTree();
};
#endif;