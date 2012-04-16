#include "route_table.h"
/* The client id is 8, the limit size of k-bucket is 4.
 * So first invoke Insert() to insert node which id is from 0 to 2.
 * Then invoke Insert() to insert node which id is 3, 3, 4.
 */
int main()
{
	CRouteTable rt(NULL, CUInt128::FromInteger(0LL, 8LL), 0, true);
	for (UInt64 i = 0LL; i < 3LL; ++i)
	{
		TNode* node = new TNode;
		node->NodeID = CUInt128::FromInteger(0LL, i);
		rt.Insert(node);
	}
	rt.Print();

	return 0;
}
