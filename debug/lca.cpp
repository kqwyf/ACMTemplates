#include "stdalgo.cpp"
#include "rmq.cpp"
#include "graph.cpp"

//Least Common Ancestors Online O(n)
struct LCA
{
	static const int N=100005;
	ST<int> rmq; //IMPORTANT: N times 2 for ST
	Graph<int> *g;
	int d[2*N],dfn[2*N],p[N],cnt;
	void dfs(int u,int pa,int dep)
	{
		dfn[++cnt]=u;
		d[cnt]=dep;
		p[u]=cnt;
		for(int t=g->son[u];t!=-1;t=g->bro[t])
		{
			int v=g->to[t];
			if(v==pa) continue;
			dfs(v,u,dep+1);
			dfn[++cnt]=u;
			d[cnt]=dep;
		}
	}
	void init(Graph<int> *gg,int root,int n)
	{
		g=gg;
		cnt=0;
		dfs(root,root,0);
		rmq.init(d,2*n-1);
	}
	inline int query(int u,int v)
	{
		if(u==v) return u;
		return dfn[rmq.query(p[u],p[v])];
	}
};

//Least Common Ancestors Offline

