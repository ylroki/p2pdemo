#include "route_table.h"
/* The client id is 0, the limit size of k-bucket is 4.
 * Split depth limit is 1.
 * So first invoke Insert() to insert node which id is from 0 to 3.
 * Then invoke Insert() to insert node which id is 3, 3, 4.
 */
int main()
{
	CRouteTable rt(NULL, CUInt128::FromInteger(0LL, 0LL), 0, true);
	for (UInt64 i = 0LL; i < 4LL; ++i)
	{
		TNode* node = new TNode;
		node->NodeID = CUInt128::FromInteger(0LL, i);
		rt.Insert(node);
	}
	printf("case 1\n");
	rt.Print();
//////////////////////////////////////////////
	CUInt128 big = CUInt128::FromInteger((1LL<<63), 0LL);

	TNode* node = new TNode;
	node->NodeID = big;
	rt.Insert(node);
	printf("case 2\n");
	rt.Print();
/////////////////////////////////////////////
	for (UInt64 i = 1LL; i < 4LL; ++i)
	{
		node = new TNode;
		big = CUInt128::FromInteger((1LL<<63), i);
		node->NodeID = big;
		rt.Insert(node);
	}
	printf("case 3\n");
	rt.Print();
/////////////////////////////////////////////
	node = new TNode;
	big = CUInt128::FromInteger((1LL<<63), 4LL);
	node->NodeID = big;
	rt.Insert(node);
	printf("case 4\n");
	rt.Print();
//////////////////////////////////////////////
	node = new TNode;
	node->NodeID = CUInt128::FromInteger(0LL, 3LL);
	rt.Insert(node);
	printf("case 5\n");
	rt.Print();
//////////////////////////////////////////////
	node = new TNode;
	node->NodeID = CUInt128::FromInteger((1LL<<62), 0LL);
	rt.Insert(node);
	printf("case 6\n");
	rt.Print();
/////////////////////////////////////////////

// GetCloseTo
	std::list<TNode> tempList;
	std::list<TNode>::iterator it;
	tempList.clear();
	rt.GetCloseTo(CUInt128::FromInteger(0LL, 0LL), &tempList);
	for (it = tempList.begin(); it != tempList.end(); ++it)
		it->NodeID.Print();
	// 0 to 3


	tempList.clear();
	rt.GetCloseTo(CUInt128::FromInteger((1LL<<62), 0LL), &tempList);
	for (it = tempList.begin(); it != tempList.end(); ++it)
		it->NodeID.Print();


	return 0;
}
