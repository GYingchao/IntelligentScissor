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
public:
	ImageHandler(cv::Mat img) {
		origImg = img;
	}
	~ImageHandler(){}
	int width() { return origImg.cols;}
	int height() {return origImg.rows;}
	bool isEmpty() {return origImg.data == NULL;}
	void InitializeCostGraph();
private:
	double computeEdgeDerivative(int i, int j, int linkIndex);
	void refineEdgeCost(PixelNode &pn, double factor);
};