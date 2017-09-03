#include "stdalgo.cpp"
#include "graph.cpp"

//Dijkstra with adjacency matrix (no negative weight) O(v^2)
template<typename T> struct Dijkstra
{
	static const int N=100005;
	bool S[N];
	T dis[N];
	int run(int start,int end,T d[N][N],int n)
	{
		int i,j,mi;
		memset(dis,-1,sizeof dis);
		memset(S,false,sizeof S);
		S[start]=true;
		dis[start]=0;
		for(i=1;i<=n;i++)
			if(!S[i]) dis[i]=d[start][i];
		for(i=2;i<=n;i++)
		{
			mi=0;
			for(j=1;j<=n;j++)
				if((!S[j])&&repless(dis[j],dis[mi])) mi=j;
			S[mi]=true;
			if(mi==end) return dis[end];
			for(j=1;j<=n;j++)
				if(d[mi][j]!=-1&&repless(dis[mi]+d[mi][j],dis[j]))
					dis[j]=dis[mi]+d[mi][j];
		}
	}
};

//Dijkstra with adjacency list (no negative weight) O(v^2)
template<typename T> struct RDijkstra
{
	static const int N=100005;
	bool S[N];
	T dis[N];
	int run(Graph<T> *g,int start,int end,int n)
	{
		int i,j,mi,t;
		memset(dis,-1,sizeof dis);
		memset(S,false,sizeof S);
		dis[start]=0;
		S[start]=true;
		for(t=g->son[start];t!=-1;t=g->bro[t])
			dis[g->to[t]]=g->w[t];
		for(i=2;i<=n;i++)
		{
			mi=0;
			for(j=1;j<=n;j++)
				if((!S[j])&&repless(dis[j],dis[mi]))
					mi=j;
			S[mi]=true;
			if(mi==end) return dis[end];
			for(t=g->son[mi];t!=-1;t=g->bro[t])
				if(repless(dis[mi]+g->w[t],dis[g->to[t]]))
					dis[g->to[t]]=dis[mi]+g->w[t];
		}
	}
};

//Bellman Ford with adjacency list O(ve)
template<typename T> struct Bell
{
	static const int N=100005;
	Graph<T> *g;
	T dis[N];
	inline bool relax(int edge)
	{
		if(dis[g->to[edge^1]]==-1) return false;
		if(dis[g->to[edge^1]]+g->w[edge]<dis[g->to[edge]]||dis[g->to[edge]]==-1)
		{
			dis[g->to[edge]]=dis[g->to[edge^1]]+g->w[edge];
			return true;
		}
		return false;
	}
	bool run(Graph<T> *gg,int start,int n)
	{
		g=gg;
		int i,j;
		memset(dis,-1,sizeof dis);
		dis[start]=0;
		for(i=1;i<n;i++)
			for(j=0;j<g->cur;j++)
				relax(j);
		for(i=0;i<g->cur;i++)
			if(relax(i)) return false;
		return true;
	}
};

//SPFA with adjacency list O(ke) (worst O(ve))
template<typename T> struct SPFA
{
	static const int N=100005;
	bool S[N];
	int count[N];
	T dis[N];
	Graph<T> *g;
	queue<int> q;
	inline bool relax(int edge)
	{
		if(dis[g->to[edge^1]]==-1) return false;
		if(dis[g->to[edge^1]]+g->w[edge]<dis[g->to[edge]]||dis[g->to[edge]]==-1)
		{
			dis[g->to[edge]]=dis[g->to[edge^1]]+g->w[edge];
			return true;
		}
		return false;
	}
	bool run(Graph<T> *gg,int start,int n)
	{
		g=gg;
		int t;
		memset(dis,-1,sizeof dis);
		memset(count,0,sizeof count);
		memset(S,false,sizeof S);
		while(!q.empty()) q.pop();
		dis[start]=0;
		S[start]=true;
		q.push(start);
		count[start]++;
		while(!q.empty())
		{
			for(t=g->son[q.front()];t!=-1;t=g->bro[t])
				if(relax(t)&&!S[g->to[t]])
				{
					S[g->to[t]]=true;
					q.push(g->to[t]);
					if(++count[g->to[t]]>n)
						return false;
				}
			S[q.front()]=false;
			q.pop();
		}
		return true;
	}
};

//Floyd with adjacency matrix O(v^3)
template<typename T> struct Floyd
{
	static const int N=100005;
	T dis[N][N];
	inline void init()
	{
		memset(dis,-1,sizeof dis);
	}
	void run(int n)
	{
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(dis[i][k]!=-1&&dis[k][j]!=-1)
						dis[i][j]=repmin(dis[i][j],dis[i][k]+dis[k][j]);
	}
};
