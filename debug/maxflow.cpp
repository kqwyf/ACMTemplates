#include "graph.cpp"
#include "stdalgo.cpp"

//Dinic sup O(ev^2)
template<typename T> struct Dinic
{
	static const int N=100005;
	int level[N],tson[N];
	queue<int> q;
	Graph<T> *g;
	bool bfs(int s,int e)
	{
		memset(level,-1,sizeof level);
		level[s]=0;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int t=g->son[u];t!=-1;t=g->bro[t])
				if(level[g->to[t]]==-1&&g->w[t]>0)
				{
					level[g->to[t]]=level[u]+1;
					q.push(g->to[t]);
				}
		}
		return level[e]!=-1;
	}
	T dfs(int s,int e,T f)
	{
		if(s==e||f==0) return f;
		for(int &t=tson[s];t!=-1;t=g->bro[t])
		{
			if(g->w[t]<=0||level[g->to[t]]<=level[s]) continue;
			long long d=dfs(g->to[t],e,min(f,g->w[t]));
			if(d)
			{
				g->w[t]-=d;
				g->w[t^1]+=d;
				return d;
			}
		}
		level[s]=-1;
		return 0;
	}
	T dinic(Graph<T> *gg,int s,int e)
	{
		g=gg;
		long long ans=0,f;
		while(bfs(s,e))
		{
			memcpy(tson,g->son,sizeof g->son);
			while((f=dfs(s,e,INF))>0) ans+=f;
		}
		return ans;
	}
};

//MCMF - Minimum Cost Maximum Flow
template<typename T> struct MCMF
{
	static const int N=100005;
	bool S[N];
	int dis[N],pre[N];
	long long maxf;
	queue<int> q;
	Graph<T> *g;
	bool relax(int edge)
	{
		if(dis[g->to[edge^1]]==-1) return false;
		if(dis[g->to[edge^1]]+g->c[edge]<dis[g->to[edge]]||dis[g->to[edge]]==-1)
		{
			dis[g->to[edge]]=dis[g->to[edge^1]]+g->c[edge];
			return true;
		}
		return false;
	}
	bool spfa(int s,int e)
	{
		int t;
		memset(dis,-1,sizeof dis);
		memset(pre,-1,sizeof pre);
		memset(S,false,sizeof S);
		while(!q.empty()) q.pop();
		dis[s]=0;
		S[s]=true;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			S[u]=false;
			for(t=g->son[u];t!=-1;t=g->bro[t])
				if(g->w[t]&&relax(t))
				{
					pre[g->to[t]]=t;
					if(!S[g->to[t]])
					{
						q.push(g->to[t]);
						S[g->to[t]]=true;
					}
				}
		}
		return pre[e]!=-1;
	}
	T mcmf(Graph<T> *gg,int s,int e)
	{
		g=gg;
		T ans=0;
		maxf=0;
		while(spfa(s,e))
		{
			T f=INF;
			for(int i=e;i!=s;i=g->to[pre[i]^1])
				f=min(f,g->w[pre[i]]);
			for(int i=e;i!=s;i=g->to[pre[i]^1])
			{
				g->w[pre[i]]-=f;
				g->w[pre[i]^1]+=f;
			}
			maxf+=f;
			ans+=f*dis[e];
		}
		return ans;
	}
};
