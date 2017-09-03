#include "stdalgo.cpp"

//Tree Array
template<typename T> struct TA
{
	static const int N=100005;
	int n;
	bool simple;
	T sum[N],d[N],di[N],t[N],td[N],tdi[N];
	inline int lowbit(int a) {return a&-a;}
	inline int left(int i) {return i-lowbit(i)+1;}
	inline int parent(int i) {return i+lowbit(i);}
	void build(T a[],T t[])
	{
		int i;
		sum[0]=0;
		for(i=1;i<=n;i++)
			sum[i]=sum[i-1]+a[i];
		for(i=1;i<=n;i++)
			t[i]=sum[i]-sum[left(i)-1];
	}
	T ksum(T t[],int k)
	{
		T ans=0;
		for(int i=k;i>0;i=left(i)-1)
			ans+=t[i];
		return ans;
	}
	T dksum(int k)
	{
		return (k+1)*ksum(td,k)-ksum(tdi,k);
	}
	void add(T t[],int k,int d)
	{
		for(int i=k;i<=n;i=parent(i))
			t[i]+=d;
	}
	inline T query(int l,int r)
	{
		if(l>r) swap(l,r);
		return simple?ksum(t,r)-ksum(t,l-1):dksum(r)-dksum(l-1);
	}
	inline T query(int index)
	{
		if(!simple) return query(index,index);
		T ans=t[index];
		for(int i=index-1;left(i)>=left(index);i=left(i)-1)
			ans-=t[i];
		return ans;
	}
	inline void add(int k,int d)
	{
		for(int i=k;i<=n;i=parent(i))
			t[i]+=d;
	}
	inline void add(int l,int r,int d)
	{
		if(l>r) swap(l,r);
		add(td,l,d);
		add(tdi,l,l*d);
		add(td,r+1,-d);
		add(tdi,r+1,-(r+1)*d);
	}
	inline void simpinit(T a[],int nn)
	{
		n=nn;
		build(a,t);
		simple=true;
	}
	inline void stdinit(T a[],int nn)
	{
		n=nn;
		a[0]=0;
		for(int i=1;i<=n;i++)
			d[i]=a[i]-a[i-1];
		build(d,td);
		for(int i=1;i<=n;i++)
			di[i]=i*d[i];
		build(di,tdi);
		simple=false;
	}
};
