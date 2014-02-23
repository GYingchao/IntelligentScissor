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

static int which_link(int offset_i, int offset_j) {
	if		 (offset_i == 1 && offset_j == 0) {
		return 0;
	} else if(offset_i == 1 && offset_j == -1) {
		return 1;
	} else if(offset_i == 0 && offset_j == -1) {
		return 2;
	} else if(offset_i == -1 && offset_j == -1) {
		return 3;
	} else if(offset_i == -1 && offset_j == 0) {
		return 4;
	} else if(offset_i == -1 && offset_j == 1) {
		return 5;
	} else if(offset_i == 0 && offset_j == 1) {
		return 6;
	} else if(offset_i == 1 && offset_j == 1) {
		return 7;
	} else {
		return -1;
	}
}

// The seed pixel is at Index(si, sj)
void ImageHandler::LiveWireDP(int si, int sj) 
{
	// legal seed point
	if(si>0 && si < (width()-1) && sj>0 && sj < (height()-1)) {
		// Initialize the priority queue pq to be empty
		FibHeap *pq = new FibHeap;

		// Initialize each node to the INITIAL state
		for(int i=0; i<graph.size(); i++) {
			graph[i].state = 0;
		}

		// set the totalCost of seed to be zero
		int seed = (si-1)*(height()-2)+sj-1;
		graph[seed].totalCost = 0.0;
		// make the seed the root of the minimum path tree
		graph[seed].prevNode = NULL;
		// insert seed into pq
		pq->Insert(&graph[seed]);

		
		PixelNode *min = dynamic_cast<PixelNode*>(pq->ExtractMin());
		while(min != NULL) {
			// mark it as expanded
			min->state = 2;
			
			// find the legal neighbor
			for(int i=-1; i<=1; i++) {
				for(int j=-1; j<=1; j++) {
					if(i==0 && j==0) continue;
					//each neigbor node r of min
					int r_c = min->column;
					int r_r = min->row;
					// illegal neighbos dose not count
					if((r_c+i<1) || (r_c+i>width()-2) || (r_r+j<1) || (r_r+j>height()-2)) continue;
					// index the legal neighbor
					int r = (r_c+i-1)*(height()-2)+r_r-1;
					
					if(graph[r].state != 2) {
						// if r has not been expanded
						if(graph[r].state == 0) {
							// if r is still initial
							// make min be the predecessor of r
							graph[r].prevNode = min;
							// update r's totalCost
							graph[r].totalCost = min->totalCost + min->linkCost[which_link(i, j)];
							// mark r as active
							graph[r].state = 1;
							// insert r into pq
							pq->Insert(&graph[r]);
						} else {
							// if r is active(already in the queue)
							if((min->totalCost)+(min->linkCost[which_link(i, j)]) < graph[r].totalCost) {
								// set min to be the predecessor of r
								graph[r].prevNode = min;
								// update r's totalCost
								graph[r].totalCost = (min->totalCost)+(min->linkCost[which_link(i, j)]);
							}
						}
					}
				}
			}
		}
		//cout << (graph[(si-1)*(height()-2)+sj-1].column == si) << endl;
		//cout << (graph[(si-1)*(height()-2)+sj-1].row == sj) << endl;
	}
}