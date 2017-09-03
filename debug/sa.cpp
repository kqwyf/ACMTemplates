#include "stdalgo.cpp"
#include "rmq.cpp"

//suffix array rank[n]===0 sa[0]===n height[0,1]===0
template<typename T> struct SA
{
	static const int N=100005;
	int ta[N],tb[N],tc[N],rank[N],height[N];
	ST<int> rmq;
	inline int lcp(int a,int b)
	{
		a=rank[a]; b=rank[b];
		if(a>b) swap(a,b);
		return height[rmq.query(a+1,b+1)];
	}
	inline int cmp(int r[],int a,int b,int l)
	{return r[a]==r[b]&&r[a+l]==r[b+l];}
	void init(T s[],int sa[],int n,int m)
	{
		s[n++]=0;
		int i,j,p,k=0,*x=ta,*y=tb;
		for(i=0;i<m;i++) tc[i]=0;
		for(i=0;i<n;i++) tc[x[i]=s[i]]++;
		for(i=1;i<m;i++) tc[i]+=tc[i-1];
		for(i=n-1;i>=0;i--) sa[--tc[x[i]]]=i;
		for(j=1;j<=n;j<<=1)
		{
			p=0;
			for(i=n-j;i<n;i++) y[p++]=i;
			for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
			for(i=0;i<m;i++) tc[i]=0;
			for(i=0;i<n;i++) tc[x[y[i]]]++;
			for(i=1;i<m;i++) tc[i]+=tc[i-1];
			for(i=n-1;i>=0;i--) sa[--tc[x[y[i]]]]=y[i];
			swap(x,y);p=1;x[sa[0]]=0;
			for(i=1;i<n;i++) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
			if(p>=n) break;
			m=p;
		}
		for(n--,i=0;i<=n;i++) rank[sa[i]]=i;
		for(i=0;i<n;i++)
		{
			if(k) k--;
			j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
		rmq.init(height,n);
	}
};
