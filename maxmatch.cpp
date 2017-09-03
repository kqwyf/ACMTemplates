#include "graph1.cpp"
#include "stdalgo.cpp"

//Hungary with adjacency matrix O(v^3)
struct Hungary
{
	static const int N=100005;
	int matching[2*N],pre[2*N];
	bool used[2*N];
	queue<int> q;
	int run(bool e[N][N],int n)
	{
		int ans=0;
		memset(matching,-1,sizeof matching);
		for(int i=1;i<=n;i++)
		{
			if(matching[i]!=-1) continue;
			memset(used,false,sizeof used);
			while(!q.empty()) q.pop();
			q.push(i);
			used[i]=true;
			pre[i]=-1;
			bool flag=false;
			while(!q.empty()&&!flag)
			{
				int u=q.front();
				q.pop();
				for(int t=N+1;t<=N+n;t++)
				{
					if(!e[u][t-N]||used[t]) continue;
					used[t]=true;
					if(matching[t]!=-1)
					{
						pre[matching[t]]=u;
						q.push(matching[t]);
					}
					else
					{
						flag=true;
						int s=u,e=t,tmp=matching[s];
						matching[e]=s;
						matching[s]=e;
						while(s!=-1)
						{
							e=tmp;
							s=pre[s];
							if(s==-1) break;
							tmp=matching[s];
							matching[e]=s;
							matching[s]=e;
						}
						break;
					}
				}
			}
			if(flag) ans++;
		}
		return ans;
	}
};

//Hungary with adjacency list O(ve)
struct RHungary
{
	static const int N=100005;
	int matching[N],pre[N];
	bool used[N];
	queue<int> q;
	int run(Graph<int> *g,int n)
	{
		int ans=0;
		memset(matching,-1,sizeof matching);
		for(int i=1;i<=n;i++)
		{
			if(matching[i]!=-1) continue;
			memset(used,false,sizeof used);
			while(!q.empty()) q.pop();
			q.push(i);
			used[i]=true;
			pre[i]=-1;
			bool flag=false;
			while(!q.empty()&&!flag)
			{
				int u=q.front();
				q.pop();
				for(int t=g->son[u];t!=-1;t=g->bro[t])
				{
					if(used[g->to[t]]) continue;
					used[g->to[t]]=true;
					if(matching[g->to[t]]!=-1)
					{
						pre[matching[g->to[t]]]=u;
						q.push(matching[g->to[t]]);
					}
					else
					{
						flag=true;
						int s=u,e=g->to[t],tmp=matching[s];
						matching[e]=s;
						matching[s]=e;
						while(s!=-1)
						{
							e=tmp;
							s=pre[s];
							if(s==-1) break;
							tmp=matching[s];
							matching[e]=s;
							matching[s]=e;
						}
						break;
					}
				}
			}
			if(flag) ans++;
		}
		return ans;
	}
};

//HK with adjacency list O(esqrt(v))
struct HK
{
};

//KM with adjacency matrix O(v^3)
template<typename T> struct KM
{
	static const int N=100005;
	static const int M=100005;
	int matching[M];
	T lx[M],ly[N],slack[M];
	bool usedx[M],usedy[N];
	int n,m;
	bool augment(T e[M][N],int u)
	{
		usedx[u]=true;
		for(int i=1;i<=n;i++)
		{
			if(usedy[i]) continue;
			int t=lx[u]+ly[i]-e[u][i];
			if(t==0)
			{
				usedy[i]=true;
				if(matching[i]==-1||augment(e,matching[i]))
				{
					matching[i]=u;
					return true;
				}
			}
			else if(slack[i]>t)
				slack[i]=t;
		}
		return false;
	}
	T run(T e[M][N],int nn,int mm)
	{
		n=nn;
		m=mm;
		int i,j;
		memset(matching,-1,sizeof matching);
		memset(ly,0,sizeof ly);
		for(i=1;i<=m;i++)
			for(j=1,lx[i]=0;j<=n;j++)
				lx[i]=max(lx[i],e[i][j]);
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=n;j++)
				slack[j]=INF;
			for(;;)
			{
				memset(usedx,false,sizeof usedx);
				memset(usedy,false,sizeof usedy);
				if(augment(e,i))
					break;
				T d=INF;
				for(j=1;j<=n;j++)
					if(!usedy[j]&&d>slack[j])
						d=slack[j];
				for(j=1;j<=m;j++)
					if(usedx[j])
						lx[j]-=d;
				for(j=1;j<=n;j++)
					if(usedy[j])
						ly[j]+=d;
					else
						slack[j]-=d;
			}
		}
		T ans=0;
		for(i=1;i<=n;i++)
			if(matching[i]!=-1)
				ans+=e[matching[i]][i];
		return ans;
	}
};
