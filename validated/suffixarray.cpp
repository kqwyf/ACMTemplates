// Double Array O(nlogn)
int sa[N], rk[N], ht[N];
int t1[N], t2[N], tt[N];
inline bool cmpSA(int *y, int i, int j, int l) {
    return y[i]==y[j]&&y[i+l]==y[j+l];
}
void buildSA(char s[], int n, int m) {
    int *x=t1, *y=t2;
    memset(tt, 0, sizeof tt);
    for(int i=0; i<n; i++) tt[x[i]=s[i]]++;
    for(int i=1; i<m; i++) tt[i]+=tt[i-1];
    for(int i=n-1; i>=0; i--) sa[tt[x[i]]--]=i;
    for(int j=1, p; j<n; j<<=1, m=p+1) {
        p=1;
        for(int i=n-j; i<n; i++) y[p++]=i;
        for(int i=1; i<=n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        memset(tt, 0, sizeof tt);
        for(int i=0; i<n; i++) tt[x[i]]++;
        for(int i=1; i<m; i++) tt[i]+=tt[i-1];
        for(int i=n; i>0; i--) sa[tt[x[y[i]]]--]=y[i];
        p=1; swap(x, y); x[sa[1]]=1;
        for(int i=2; i<=n; i++) x[sa[i]]=cmpSA(y, sa[i], sa[i-1], j)?p:++p;
        if(p>n) break;
    }
    for(int i=1; i<=n; i++) rk[sa[i]]=i;
    for(int i=0, p=0, j; i<n; i++) {
        if(rk[i]==1) continue;
        for(j=sa[rk[i]-1]; s[i+p]==s[j+p]; p++);
        ht[rk[i]]=p;
        if(p>0) p--;
    }
}
