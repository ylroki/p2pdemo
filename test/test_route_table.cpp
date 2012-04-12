#include "route_table.h"
/* The client id is 8, the limit size of k-bucket is 4.
 * So first invoke Insert() to insert node which id is from 0 to 2.
 * Then invoke TryToInsert() to insert node which id is 3, 3, 4.
 */
int main()
{
	CRouteTable rt;
	rt.SetClientID(CUInt128::FromInteger(0LL, 8LL));
	for (UInt64 i = 0LL; i < 3LL; ++i)
	{
		TNode node;
		node.NodeID = CUInt128::FromInteger(0LL, i);
		rt.Insert(&node);
	}
	rt.Print();

	TNode node;
	node.NodeID = CUInt128::FromInteger(0LL, 3LL);
	rt.TryToInsert(&node, NULL);
	rt.Print();
	rt.TryToInsert(&node, NULL);
	rt.Print();
	node.NodeID = CUInt128::FromInteger(0LL, 4LL);
	rt.TryToInsert(&node, NULL);
	rt.Print();
	return 0;
}
