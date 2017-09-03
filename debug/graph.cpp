#include "stdalgo.cpp"

//Adjacency List
template<typename T> struct Graph
{
	static const int N=100005;
	static const int M=100005;
	int son[N],to[2*M],bro[2*M],cur;
	T w[2*M];
	void init()
	{
		memset(son,-1,sizeof son);
		cur=0;
	}
	void add(int u,int v,T ww)
	{
		to[cur]=v;
		w[cur]=ww;
		bro[cur]=son[u];
		son[u]=cur++;
	}
};
