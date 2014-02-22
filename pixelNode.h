#include "fibheap.h"
class PixelNode : public FibHeapNode{

public:
	double linkCost[8];
	// 0 for initial; 1 for active; 2 for expanded;
	int state;
	double totalCost; // The key of fibHeapNode
	PixelNode *prevNode;
	int column, row;
public:
	PixelNode(int state, double totalCost, PixelNode *pre, int column, int row) : FibHeapNode() {
		this->state = state;
		this->totalCost = totalCost;
		this->prevNode = pre;
		this->column = column;
		this->row = row;
	}
	
	virtual void operator =(FibHeapNode& RHS);
    virtual int  operator ==(FibHeapNode& RHS);
    virtual int  operator <(FibHeapNode& RHS);

    virtual void operator =(float NewKeyVal);
    virtual void Print();
    //float GetKeyValue() { return Key; };
    //void SetKeyValue(float inkey) { Key = inkey; };
};