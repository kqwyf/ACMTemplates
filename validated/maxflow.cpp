//ISAP O(mn^2)
int label[N], gap[N];
int Q[N], front, rear;
int thead[N];
ll dfs(int u, int s, int t, ll f) {
    if(u==t) return f;
    ll flow=0;
    for(int &e=thead[u]; e!=-1; e=nxt[e]) {
        int v=to[e];
        if(c[e]==0||label[u]!=label[v]+1) continue;
        ll tmp=dfs(v, s, t, min(f, c[e]));
        c[e]-=tmp; c[e^1]+=tmp;
        f-=tmp; flow+=tmp;
        if(!f) return flow;
    }
    if(--gap[label[u]]==0) label[s]=n; // number of points
    gap[++label[u]]++;
    return flow;
}
ll ISAP(int s, int t) {
    memset(label, -1, sizeof label);
    memset(gap, 0, sizeof gap);
    gap[label[t]=0]++;
    Q[front=rear=0]=t;
    while(front<=rear) {
        int u=Q[front++];
        for(int e=head[u]; e!=-1; e=nxt[e]) {
            int v=to[e];
            if(c[e]!=0||label[v]!=-1) continue;
            gap[label[v]=label[u]+1]++;
            Q[++rear]=v;
        }
    }
    ll ans=0;
    while(label[s]<n) { // number of points
        memcpy(thead, head, sizeof head);
        ans+=dfs(s, s, t, INF);
    }
    return ans;
}

//Minimum Cost Max Flow O(mnF)
int pre[N], dis[N];
bool vis[N];
bool spfa(int s, int t) {
    memset(pre, -1, sizeof pre);
    memset(vis, false ,sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    queue<int> q;
    q.push(s);
    vis[s]=true;
    pre[s]=-1;
    dis[s]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int e=head[u]; e!=-1; e=nxt[e]) {
            int v=to[e];
            if(c[e]&&dis[v]>dis[u]+w[e]) {
                dis[v]=dis[u]+w[e];
                pre[v]=e;
                if(!vis[v]) {
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return pre[t]!=-1;
}
int MCMF(int s, int t) {
    int ans=0;
    while(spfa(s, t)) {
        int f=INF;
        for(int e=pre[t]; e!=-1; e=pre[to[e^1]])
            f=min(f, c[e]);
        for(int e=pre[t]; e!=-1; e=pre[to[e^1]]) {
            c[e]-=f; c[e^1]+=f;
            ans+=f*w[e];
        }
    }
    return ans;
}

//Minimum Cost Max Flow O(mnF)
int pre[N], dis[N];
bool vis[N];
bool spfa(int s, int t) {
    memset(pre, -1, sizeof pre);
    memset(vis, false ,sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    queue<int> q;
    q.push(s);
    vis[s]=true;
    pre[s]=-1;
    dis[s]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int e=head[u]; e!=-1; e=nxt[e]) {
            int v=to[e];
            if(c[e]&&dis[v]>dis[u]+w[e]) {
                dis[v]=dis[u]+w[e];
                pre[v]=e;
                if(!vis[v]) {
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return pre[t]!=-1;
}
int MCMF(int s, int t) {
    int ans=0;
    while(spfa(s, t)) {
        int f=INF;
        for(int e=pre[t]; e!=-1; e=pre[to[e^1]])
            f=min(f, c[e]);
        for(int e=pre[t]; e!=-1; e=pre[to[e^1]]) {
            c[e]-=f; c[e^1]+=f;
            ans+=f*w[e];
        }
    }
    return ans;
}
