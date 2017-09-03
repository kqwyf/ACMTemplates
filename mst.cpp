#include "stdalgo.cpp"
#include "graph.cpp"
#include "ufs.cpp"

//Prim with adjacency list O(elogv)
Graph<int> *Pg;
struct Primcmp
{
	bool operator () (int a,int b)
	{return Pg->w[a]>Pg->w[b];}
};
priority_queue<int,vector<int>,Primcmp> q;
template<typename T> struct Prim
{
	static const int N=100005;
	bool used[N];
	Graph<T> *g;
	inline int getfront()
	{
		while((!q.empty())&&used[g->to[q.top()]]) q.pop();
		if(q.empty()) return -1; else return q.top();
	}
	T run(Graph<T> *gg,int start)
	{
		Pg=g=gg;
		T ans=0;
		while(!q.empty()) q.pop();
		memset(used,false,sizeof used);
		used[start]=true;
		for(int t=g->son[start];t!=-1;t=g->bro[t])
			q.push(t);
		while(!q.empty())
		{
			int mi=getfront();
			if(mi==-1) break;
			q.pop();
			used[g->to[mi]]=true;
			ans+=g->w[mi];
			for(int t=g->son[g->to[mi]];t!=-1;t=g->bro[t])
				if(!used[g->to[t]]) q.push(t);
		}
		return ans;
	}
};

//Prim with adjacency matrix O(v^2)
template<typename T> struct RPrim
{
	static const int N=100005;
	bool used[N];
	T newd[N];
	T run(T d[N][N],int start,int n)
	{
		int i,j,mi;
		T ans=0;
		memset(used,false,sizeof used);
		memset(newd,-1,sizeof newd);
		used[start]=true;
		for(i=1;i<=n;i++)
			newd[i]=d[start][i];
		for(i=1;i<n;i++)
		{
			mi=0;
			for(j=1;j<=n;j++)
				if((!used[j])&&repless(newd[j],newd[mi]))
					mi=j;
			used[mi]=true;
			ans+=newd[mi];
			for(j=1;j<=n;j++)
				if((!used[j])&&repless(d[mi][j],newd[j]))
					newd[j]=d[mi][j];
		}
		return ans;
	}
};

//Kruskal with adjacency list O(eloge)
template<typename T> struct Kruskal
{
	static const int N=100005;
	static const int M=100005;
	struct edge
	{
		int u,v;
		T w;
		bool operator <(edge a) const
		{return w<a.w;}
	}edges[M];
	bool ac[M];
	UFS ufs;
	Graph<T> *g;
	T run(Graph<T> *gg,int n)
	{
		g=gg;
		T ans=0;
		memset(ac,false,sizeof ac);
		for(int i=0;i<g->cur;i+=2)
		{
			edges[i/2].u=g->to[i^1];
			edges[i/2].v=g->to[i];
			edges[i/2].w=g->w[i];
		}
		sort(edges,edges+g->cur/2);
		ufs.init();
		for(int i=0,k=1;i<g->cur/2&&k<n;i++)
			if(ufs.parent(edges[i].u)!=ufs.parent(edges[i].v))
			{
				ufs.join(edges[i].u,edges[i].v);
				ans+=edges[i].w;
				ac[i*2]=ac[i*2+1]=true;
				k++;
			}
		return ans;
	}
};
