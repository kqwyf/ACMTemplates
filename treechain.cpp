#include "stdalgo.cpp"
#include "graph.cpp"

//Tree Chain Subdivision
template<typename T> struct TChain
{
	static const int N=100005;
	Graph<T> *g;
	int s[N],dep[N],hvy[N],out[N],in[N],pa[N],top[N];
	int cnt;
	void predfs(int u,int p)
	{
		s[u]=1;
		pa[u]=p;
		hvy[u]=-1;
		dep[u]=dep[p]+1;
		for(int t=g->son[u];t!=-1;t=g->bro[t])
		{
			int v=g->to[t];
			if(v==p) continue;
			predfs(v,u);
			if(hvy[u]==-1||s[v]>s[hvy[u]]) hvy[u]=v;
			s[u]+=s[v];
		}
	}
	void dfs(int u)
	{
		if(hvy[u]!=-1)
		{
			in[cnt]=hvy[u];
			out[hvy[u]]=cnt++;
			top[hvy[u]]=top[u];
			dfs(hvy[u]);
		}
		for(int t=g->son[u];t!=-1;t=g->bro[t])
		{
			int v=g->to[t];
			if(v==hvy[u]||v==pa[u]) continue;
			in[cnt]=v;
			out[v]=cnt++;
			top[v]=v;
			dfs(v);
		}
	}
	inline void init(Graph<T> *gg,int root,T l[],int start)
	{
		g=gg;
		cnt=start;

		top[N-1]=N-1;
		dep[N-1]=-1;
		top[root]=root;
		in[cnt]=root;
		out[root]=cnt++;
		
		memset(s,0,sizeof s);
		predfs(root,N-1);
		dfs(root);
		for(int i=start;i<start+cnt;i++)
			l[i]=g->w[in[i]];
	}
	inline void updateans(int l,int r,T d,T &ans)
	{
		ans+=r+1-l+d;
	}
	T path(int u,int v,T d)
	{
		T ans=0;
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]])
			{
				updateans(out[top[v]],out[v],d,ans);
				v=pa[top[v]];
			}
			else
			{
				updateans(out[top[u]],out[u],d,ans);
				u=pa[top[u]];
			}
		}
		updateans(out[u],out[v],d,ans);
		return ans;
	}
};
