//Hopcroft Karp O(sqrt(n)e)
int maxdis;
int dis[N], match[N];
bool bfs() {
	memset(dis, -1, sizeof dis);
	maxdis=INF;
	queue<int> q;
	for(int i=0; i<n; i++)
		if(match[i]==-1) {
			q.push(i);
			dis[i]=0;
		}
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		if(dis[u]>maxdis) break;
		for(int t=head[u]; t!=-1; t=adj[t]) {
			int v=to[t];
			if(dis[v]!=-1) continue;
			dis[v]=dis[u]+1;
			if(match[v]==-1) {
				maxdis=dis[v];
			}
			else {
				dis[match[v]]=dis[v]+1;
				q.push(match[v]);
			}
		}
	}
	return maxdis!=INF;
}

bool vis[N];
bool dfs(int u) {
	for(int t=head[u]; t!=-1; t=adj[t]) {
		int v=to[t];
		if(vis[v]||dis[v]!=dis[u]+1) continue;
		vis[v]=true;
		if(match[v]!=-1&&dis[v]==maxdis) continue;
		if(match[v]==-1||dfs(match[v])) {
			match[u]=v;
			match[v]=u;
			return true;
		}
	}
	return false;
}

int maxmatch() {
	int ans=0;
	memset(match, -1, sizeof match);
	while(bfs()) {
		memset(vis, false, sizeof vis);
		for(int i=0; i<n; i++)
			if(match[i]==-1&&dfs(i))
				ans++;
	}
	return ans;
}
