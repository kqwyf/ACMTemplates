#include "stdalgo.cpp"
#include "vec.cpp"

//Graham solving Convex Hull O(nlogn)
vec2<int> p0;
template<typename T> bool ldcmp(vec2<T> a,vec2<T> b)
{
	vec2<T> ta=a-p0,tb=b-p0;
	T tmp=ta/tb;
	return tmp>0||(tmp==0&&ta.l()<tb.l());
}
template<typename T> struct Graham
{
	static const int N=1005;
	int s[N],top;
	void run(vec2<T> p[],int n)
	{
		int t=0;
		for(int i=1;i<n;i++)
			if(p[i].y<p[t].y||(p[i].y==p[t].y&&p[i].x<p[t].x))
				t=i;
		swap(p[t],p[0]);
		p0=p[0];
		sort(p+1,p+n,ldcmp<T>);
		for(top=0;top<2&&top<n;top++)
			s[top]=top;
		if(n<=2) return;
		for(int i=2;i<n;i++)
		{
			while(top>1&&(p[s[top-1]]-p[s[top-2]])/(p[i]-p[s[top-2]])<=0)
				top--;
			s[top++]=i;
		}
	}
};
//Rotating Calipers
int rc(vec2<int> p[],int n)
{
	int ans=0;
	for(int i=0,cur=1;i<n;i++)
	{
		vec2<int> t=p[i]-p[(i+1)%n];
		while(t/(p[(cur+1)%n]-p[cur])<0) cur=(cur+1)%n;
		ans=max(ans,max((p[i]-p[cur]).l2(),(p[(i+1)%n]-p[(cur+1)%n]).l2()));
	}
	return ans;
}
