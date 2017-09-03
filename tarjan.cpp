#include "stdalgo.cpp"
#include "graph.cpp"

//Tarjan O(v+e)
struct Tarjan
{
	static const int N=100005;
	Graph<int> *g;
	int dfn[N],low[N],curdfn;
	bool vis[N],ins[N];
	stack<int> tars;
	void inittarjan(Graph<int> *gg)
	{
		g=gg;
		curdfn=0;
		memset(vis,false,sizeof vis);
		while(!tars.empty()) tars.pop();
	}
	void tarjan(int st)
	{
		vis[st]=true;
		dfn[st]=low[st]=curdfn++;
		tars.push(st);
		ins[st]=true;
		for(int t=g->son[st];t!=-1;t=g->bro[t])
		{
			if(!vis[g->to[t]])
			{
				tarjan(g->to[t]);
				low[st]=min(low[st],low[g->to[t]]);
			}
			else if(ins[g->to[t]])
			{
				low[st]=min(low[st],dfn[g->to[t]]);
			}
		}
		if(dfn[st]==low[st])
		{
			int tmp;
			do
			{
				tmp=tars.top();
				tars.pop();
				ins[tmp]=false;
			}while(tmp!=st);
		}
	}
};
