// 主席树/可持久化线段树 操作时间O(logn)，空间复杂度O(n+qlogn)
// 使用闭区间，使用前需初始化
// 示例为区间第k小
int root[N], tot;
struct node {int num, l, r;} T[N*26];
void init() {tot=0;}
void update(int& u, int v, int L, int R, int x) {
    T[u=++tot]=T[v];
    T[u].num++;
    if(L==R) return;
    if(x>(L+R)/2) update(T[u].r, T[v].r, (L+R)/2+1, R, x);
    else update(T[u].l, T[v].l, L, (L+R)/2, x);
}
int query(int l, int r, int L, int R, int k) {
    if(L==R) return L;
    int d=T[T[r].l].num-T[T[l].l].num;
    if(k>d) return query(T[l].r, T[r].r, (L+R)/2+1, R, k-d);
    else return query(T[l].l, T[r].l, L, (L+R)/2, k);
}
