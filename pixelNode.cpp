#include "pixelNode.h"

void PixelNode::Print()
{
	FibHeapNode::Print();
}

void PixelNode::operator =(float NewKeyVal)
{
	PixelNode Temp(this->state, this->totalCost, this->prevNode, this->column, this->row);

     Temp.totalCost = totalCost = NewKeyVal;
     FHN_Assign(Temp);
}

void PixelNode::operator =(FibHeapNode& RHS)
{
     FHN_Assign(RHS);
     totalCost = ((PixelNode&) RHS).totalCost;
}

int  PixelNode::operator ==(FibHeapNode& RHS)
{
     if (FHN_Cmp(RHS)) return 0;
     return totalCost == ((PixelNode&) RHS).totalCost ? 1 : 0;
}

int  PixelNode::operator <(FibHeapNode& RHS)
{
int X;

     if ((X=FHN_Cmp(RHS)) != 0)
	  return X < 0 ? 1 : 0;

     return totalCost < ((PixelNode&) RHS).totalCost ? 1 : 0;
};