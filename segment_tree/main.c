#include <stdio.h>
#define N 10

//N sets the no. of levels in the tree
int A[1 << (N + 1)];

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void precompute(int start)
{
	int i;
	for (i = start; i > 0; i--)
	{
		A[i] = max(A[2 * i], A[2 * i + 1]);
	}
}

void update(int idx, int val)
{
	int t = idx / 2;
	A[idx] += val;
	while (t)
	{
		A[t] = max(A[2 * t], A[2 * t + 1]);
		t /= 2;
	}
}

int query(int node, int l, int r, int tl, int tr)
{
	int t = tl + (tr - tl) / 2;
	//printf("%d %d %d %d %d\n",node,l,r,tl,tr);
	if (tl >= l && tr <= r)
		return A[node];
	else if (tl > r || tr < l)
		return 0;
	else
		return max(query(2 * node, l, r, tl, t), query(2 * node + 1, l, r, t + 1, tr));
}

int main()
{
	int i, l, r, idx, val, start = (1 << N);

	for (i = 0; i < (1 << N); i++)
	{
		A[start + i] = i + 1;
	}

	precompute(start - 1);

	/*for(i=1;i<2048;i++){
		printf("%d\n",A[i]);
	}*/
	while (scanf("%d %d %d%d", &idx, &val, &l, &r))
	{
		//Increase value in idx by val and query between l and r
		update((1 << N) + idx - 1, val);
		printf("%d\n", query(1, (start) + l - 1, start + r - 1, start, 2 * start - 1));
	}

	return 0;
}