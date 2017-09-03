//KMP O(m+n)
struct KMP
{
	static const int N=100005;
	int fail[N];
	void init(const char p[],int l)
	{
		fail[0]=-1;
		for(int i=0,j=-1;i<l;i++)
		{
			while(j!=-1&&p[i]!=p[j]) j=fail[j];
			fail[i+1]=++j;
		}
	}
	int query(const char s[],const char p[],int ls,int lp)
	{
		int ans=0;
		for(int i=0,j=0;i<ls;i++)
		{
			while(j!=-1&&s[i]!=p[j]) j=fail[j];
			if(++j>=lp) ans++,j=fail[j];
		}
		return ans;
	}
};
