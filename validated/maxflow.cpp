//ISAP O(mn^2)
int label[N], gap[N];
int Q[N], front, rear;
int thead[N];
int dfs(int u, int s, int t, int f) {
    if(u==t) return f;
    int flow=0;
    for(int &e=thead[u]; e!=-1; e=nxt[e]) {
        int v=to[e];
        if(label[u]!=label[v]+1||c[e]==0) continue;
        int tmp=dfs(v, s, t, min(f, c[e]));
        c[e]-=tmp; c[e^1]+=tmp;
        f-=tmp; flow+=tmp;
        if(!f) return flow;
    }
    if(--gap[label[u]]==0) label[s]=n;
    gap[++label[u]]++;
    return flow;
}
int ISAP(int s, int t) {
    memset(label, -1, sizeof label);
    memset(gap, 0, sizeof gap);
    gap[label[t]=0]++;
    Q[front=rear=0]=t;
    while(front<=rear) {
        int u=Q[front++];
        for(int e=head[u]; e!=-1; e=nxt[e]) {
            int v=to[e];
            if(label[v]!=-1) continue;
            gap[label[v]=label[u]+1]++;
            Q[++rear]=v;
        }
    }
    int ans=0;
    while(label[s]<n) {
        memcpy(thead, head, sizeof head);
        ans+=dfs(s, s, t, INF);
    }
    return ans;
}
