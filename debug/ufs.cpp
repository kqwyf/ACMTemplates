#include "stdalgo.cpp"

//Union Find Set
struct UFS
{
	static const int N=100005;
	int pre[N],rank[N];
	void init()
	{
		memset(rank,0,sizeof(rank));
		for(int i=0;i<N;i++) pre[i]=i;
	}
	int parent(int k)
	{
		if(pre[k]==k) return k;
		return pre[k]=parent(pre[k]);
	}
	bool join(int p,int q)
	{
		p=parent(p);
		q=parent(q);
		if(p==q) return false;
		if(rank[p]>rank[q]) pre[q]=p;
		else
		{
			if(rank[p]==rank[q]) rank[q]++;
			pre[p]=q;
		}
		return true;
	}
};
