class PixelNode {

public:
	double linkCost[8];
	// 0 for initial; 1 for active; 2 for expanded;
	int state;
	double totalCost;
	PixelNode *prevNode;
	int column, row;
public:
	PixelNode(int state, double totalCost, PixelNode *pre, int column, int row){
		this->state = state;
		this->totalCost = totalCost;
		this->prevNode = pre;
		this->column = column;
		this->row = row;
	}

};