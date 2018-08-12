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
		for(int t=head[u]; t!=-1; t=nxt[t]) {
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
	for(int t=head[u]; t!=-1; t=nxt[t]) {
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

//Kuhn Munkras (O(n^3))
int w[N][N];
int match[2][N], label[2][N], slack[N];
bool vis[2][N];

bool dfs(int u) {
    vis[0][u]=true;
    for(int i=0; i<n; i++) {
        if(vis[1][i]) continue; 
        int tmp=label[0][u]+label[1][i]-w[u][i];
        if(tmp==0) {
            vis[1][i]=true;
            if(match[1][i]==-1||dfs(match[1][i])) {
                match[0][u]=i;
                match[1][i]=u;
                return true;
            }
        } else if(tmp<slack[i]) {
            slack[i]=tmp;
        }
    }
    return false;
}

int KM() {
    memset(match, -1, sizeof match);
    memset(label[1], 0, sizeof label[1]);
    for(int i=0; i<n; i++)
    {
        label[0][i]=-INF;
        for(int j=0; j<n; j++)
            label[0][i]=max(label[0][i], w[i][j]);
    }
    for(int i=0; i<n; i++) {
        memset(slack, 0x3f, sizeof slack);
        while(memset(vis, false, sizeof vis), !dfs(i)) {
            int d=INF;
            for(int j=0; j<n; j++)
                if(!vis[1][j]) d=min(d, slack[j]);
            for(int j=0; j<n; j++)
                if(vis[0][j]) label[0][j]-=d;
            for(int j=0; j<n; j++)
                if(vis[1][j]) label[1][j]+=d;
                else slack[j]-=d;
        }
    }
    int ans=0;
    for(int i=0; i<n; i++)
        if(match[0][i]!=-1)
            ans+=w[i][match[0][i]];
    return ans;
}
