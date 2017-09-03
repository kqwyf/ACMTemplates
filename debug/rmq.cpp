#include "stdalgo.cpp"

//Range Minimum Query ST O(nlogn)
template<typename T> struct ST
{
	static const int N=100005;
	int mm[N],best[30][N];
	T *s;
	void init(T *ss,int n)
	{
		s=ss;
		mm[0]=-1;
		for(int i=1;i<=n;i++)
			mm[i]=mm[i-1]+((i&(i-1))==0);
		for(int i=1;i<=n;i++) best[0][i]=i;
		for(int i=1;i<=mm[n];i++)
			for(int j=1;j+(1<<i)-1<=n;j++)
			{
				int a=best[i-1][j];
				int b=best[i-1][j+(1<<(i-1))];
				if(s[a]<s[b]) best[i][j]=a;
				else best[i][j]=b;
			}
	}
	int query(int a,int b)
	{
		if(a>b) swap(a,b);
		int t=mm[b-a];
		b-=(1<<t);
		a=best[t][a];
		b=best[t][b];
		return s[a]<s[b]?a:b;
	}
};
