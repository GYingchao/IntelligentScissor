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
					int r = (r_c+i-1)*(height()-2)+r_r+j-1;
					
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
			min = dynamic_cast<PixelNode*>(pq->ExtractMin());
		}
		//cout << (graph[(si-1)*(height()-2)+sj-1].column == si) << endl;
		//cout << (graph[(si-1)*(height()-2)+sj-1].row == sj) << endl;
		// for test
		//printTree();
	} else {
		cout << "Invalid seed point input !!!" << endl;
	}
}

// get the pixel path from current seed to pixel(i, j)
void ImageHandler::getPath(int i, int j, vector<vec2i>& container) 
{
	container.clear();
	// Check the validity of the image index
	if(i>=1 && i<(width()-1) && j>=1 && j<(height()-1)) {
		vec2i t;
		t.pos[0] = i;
		t.pos[1] = j;
		container.push_back(t);
		// locate pixel(i, j) in the cost graph
		int ni = i; 
		int nj = j;
		PixelNode* ancestor = graph[(ni-1)*(height()-2)+nj-1].prevNode;
		while(ancestor != NULL) {
			ni = ancestor->column;
			nj = ancestor->row;
			vec2i n;
			n.pos[0] = ni;
			n.pos[1] = nj;
			container.push_back(n);
			ancestor = graph[(ni-1)*(height()-2)+nj-1].prevNode;
		}
		// Assert
		//if(ancestor->column != cur_si || ancestor->row != cur_sj) cout << "Computing Path Error!!!" << endl;
		//graph[(i-1)*(height()-2)+j-1].
		//return tem;
	// return empty vector;
	} //else {return tem;}
}

void ImageHandler::printTree()
{
	for(int j=1; j<height()-1; j++) {
		for(int i=1; i<width()-1; i++) {
			PixelNode* tem = graph[(i-1)*(height()-2)+j-1].prevNode;
			if(tem != NULL) {
				cout << " (" << tem->column << ", " << tem->row << ")";
			} else {
				cout << " seed";
			}
		}
		cout << endl;
	}
}

cv::Mat ImageHandler::ComputePixelNodeGraph()
{
	// Before invoke this method, graph should be assigned valid data ahead
	int png_rows = (height()-2)*3;
	int png_cols = (width()-2)*3;
	cv::Mat png(png_rows, png_cols, CV_8UC3);

	// rescale the link cost
	double max_cost = 0.0;
	for(int i=0; i<graph.size(); i++) {
		for(int j=0; j<8; j++) {
			if(max_cost < graph[i].linkCost[j]) max_cost = graph[i].linkCost[j];
		}
	}

	for(int i=0; i<width()-2; i++) {
		for(int j=0; j<height()-2; j++) {
			//cost(link 0)
			png.at<cv::Vec3b>(1+j*3, 2+i*3)[0] = graph[i*(height()-2)+j].linkCost[0]/max_cost*255;
			png.at<cv::Vec3b>(1+j*3, 2+i*3)[1] = graph[i*(height()-2)+j].linkCost[0]/max_cost*255;
			png.at<cv::Vec3b>(1+j*3, 2+i*3)[2] = graph[i*(height()-2)+j].linkCost[0]/max_cost*255;
			// cost(link 1)
			png.at<cv::Vec3b>(j*3, 2+i*3)[0] = graph[i*(height()-2)+j].linkCost[1]/max_cost*255;
			png.at<cv::Vec3b>(j*3, 2+i*3)[1] = graph[i*(height()-2)+j].linkCost[1]/max_cost*255;
			png.at<cv::Vec3b>(j*3, 2+i*3)[2] = graph[i*(height()-2)+j].linkCost[1]/max_cost*255;
			//cost(link 2)
			png.at<cv::Vec3b>(j*3, 1+i*3)[0] = graph[i*(height()-2)+j].linkCost[2]/max_cost*255;
			png.at<cv::Vec3b>(j*3, 1+i*3)[1] = graph[i*(height()-2)+j].linkCost[2]/max_cost*255;
			png.at<cv::Vec3b>(j*3, 1+i*3)[2] = graph[i*(height()-2)+j].linkCost[2]/max_cost*255;
			//cost(link 3)
			png.at<cv::Vec3b>(j*3, i*3)[0] = graph[i*(height()-2)+j].linkCost[3]/max_cost*255;
			png.at<cv::Vec3b>(j*3, i*3)[1] = graph[i*(height()-2)+j].linkCost[3]/max_cost*255;
			png.at<cv::Vec3b>(j*3, i*3)[2] = graph[i*(height()-2)+j].linkCost[3]/max_cost*255;
			//cost(link 4)
			png.at<cv::Vec3b>(1+j*3, i*3)[0] = graph[i*(height()-2)+j].linkCost[4]/max_cost*255;
			png.at<cv::Vec3b>(1+j*3, i*3)[1] = graph[i*(height()-2)+j].linkCost[4]/max_cost*255;
			png.at<cv::Vec3b>(1+j*3, i*3)[2] = graph[i*(height()-2)+j].linkCost[4]/max_cost*255;
			//cost(link 5)
			png.at<cv::Vec3b>(2+j*3, i*3)[0] = graph[i*(height()-2)+j].linkCost[5]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, i*3)[1] = graph[i*(height()-2)+j].linkCost[5]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, i*3)[2] = graph[i*(height()-2)+j].linkCost[5]/max_cost*255;
			//cost(link 6)
			png.at<cv::Vec3b>(2+j*3, 1+i*3)[0] = graph[i*(height()-2)+j].linkCost[6]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, 1+i*3)[1] = graph[i*(height()-2)+j].linkCost[6]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, 1+i*3)[2] = graph[i*(height()-2)+j].linkCost[6]/max_cost*255;
			//cost(link 7)
			png.at<cv::Vec3b>(2+j*3, 2+i*3)[0] = graph[i*(height()-2)+j].linkCost[7]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, 2+i*3)[1] = graph[i*(height()-2)+j].linkCost[7]/max_cost*255;
			png.at<cv::Vec3b>(2+j*3, 2+i*3)[2] = graph[i*(height()-2)+j].linkCost[7]/max_cost*255;
			//png.at<cv::Vec3b>(1+j*3, 2+i*3) = graph[i*(height()-2)+j].linkCost[0];

			png.at<cv::Vec3b>(1+3*j, 1+3*i) = origImg.at<cv::Vec3b>(j+1, i+1);
		}
	}
	//cout << "png channels: " << png.channels() << endl;
	//cout << "png cols: " << png.cols << endl;
	//cout << "width: " << width() << endl;
	return png;
}

void ImageHandler::saveMask(vector<vector<vec2i>> contour, QString filename)
{
	if(contour.empty()) {
		cout << "Nothing to save.." << endl;
		return;
	} else {
		if(!filename.endsWith(".bmp")) filename.append(".bmp");
		// Update pixelNode inContour attribute
		for(int i=0; i<graph.size(); i++) {
			graph[i].inContour = false;
		}
		for(int p=0; p<contour.size(); p++) {
			for(int q=0; q<contour[p].size(); q++) {
				int i = contour[p][q].pos[0];
				int j = contour[p][q].pos[1];
				graph[(i-1)*(height()-2)+j-1].inContour = true;
			}
		}
		/*
		// Create the mask image
		cv::Mat mask(height()-2, width()-2, CV_8UC3);
		//cv::Vec2b blank(255, 255, 255);
		bool controller = false;
		for(int i=1; i<height()-1; i++) {
			controller = false;
			for(int j=1; j<width()-1; j++) {

				if(graph[(j-1)*(height()-2)+i-1].inContour && !controller) controller = true;
				else if(graph[(j-1)*(height()-2)+i-1].inContour && controller) controller = false;
				else if(!graph[(j-1)*(height()-2)+i-1].inContour && controller) controller = true;
				else controller = false;

				if(controller) {
					mask.at<cv::Vec3b>(i-1, j-1) = origImg.at<cv::Vec3b>(i, j);
				} else {
					mask.at<cv::Vec3b>(i-1, j-1)[0] = 255;
					mask.at<cv::Vec3b>(i-1, j-1)[1] = 255;
					mask.at<cv::Vec3b>(i-1, j-1)[2] = 255;
				}
			}
		}
		*/

		// Another way..test
		// convert contour to cv::points set
		vector<cv::Point> set;
		// one way of reordering
		/*
		for(int i=0; i<graph.size(); i++) {
			if(graph[i].inContour) {

				set.push_back(cv::Point(graph[i].column, graph[i].row));
			}
		}
		*/
		// another way of reordering
		for(int p=contour.size()-1; p>=0; p--) {
			for(int q=0; q<contour[p].size(); q++) {
				set.push_back(cv::Point(contour[p][q].pos[0], contour[p][q].pos[1]));
			}
		}
		vector<vector<cv::Point>> contours;
		contours.push_back(set);

		cv::Mat mask = origImg.clone();
		//drawContours(mask, contours, -1, cvScalarAll(0), 0);
		
		vector<cv::Point> tmp = contours.at(0);
		const cv::Point* ppt[1] = {&tmp[0]};
		int npts = tmp.size();
		fillPoly(mask, ppt, &npts, 1, cvScalarAll(0), 8);


		// Get the mask image
		cv::Mat mask_img = origImg - mask;
		//cv::Mat mask_img;
		//cv::subtract(mask, origImg, mask_img);

		cv::cvtColor(mask_img, mask_img, CV_RGB2BGR);
		if(cv::imwrite(filename.toStdString().data(), mask_img)) cout << "mask saved.. " << endl;
	}
}

void ImageHandler::saveContour(vector<vector<vec2i>> contour, QString filename)
{
	if(contour.empty()) {
		cout << "Nothing to save.." << endl;
		return;
	} else {
		if(!filename.endsWith(".bmp")) filename.append(".bmp");
		// Update pixelNode inContour attribute
		for(int i=0; i<graph.size(); i++) {
			graph[i].inContour = false;
		}
		for(int p=0; p<contour.size(); p++) {
			for(int q=0; q<contour[p].size(); q++) {
				int i = contour[p][q].pos[0];
				int j = contour[p][q].pos[1];
				graph[(i-1)*(height()-2)+j-1].inContour = true;
			}
		}

		// Create the with contour image
		cv::Mat with_contour(height()-2, width()-2, CV_8UC3);
		for(int i=1; i<height()-1; i++) {
			for(int j=1; j<width()-1; j++) {
				if(graph[(j-1)*(height()-2)+i-1].inContour) {
					with_contour.at<cv::Vec3b>(i-1, j-1)[0] = 0;
					with_contour.at<cv::Vec3b>(i-1, j-1)[1] = 255;
					with_contour.at<cv::Vec3b>(i-1, j-1)[2] = 0;
				} else {
					with_contour.at<cv::Vec3b>(i-1, j-1) = origImg.at<cv::Vec3b>(i, j);
					//mask.at<cv::Vec3b>(j-1, i-1)[1] = origImg.at<cv::Vec3b>(j, i)[1];
					//mask.at<cv::Vec3b>(j-1, i-1)[2] = origImg.at<cv::Vec3b>(j, i)[2];
				}
			}
		}
		cv::cvtColor(with_contour, with_contour, CV_RGB2BGR);
		if(cv::imwrite(filename.toStdString().data(), with_contour)) cout << "contour saved.. " << endl;
	}
}