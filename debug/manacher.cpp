#include "stdalgo.cpp"

//Manacher - the longest palindrome substring O(n)
struct Manacher
{
	static const int N=100005;
	int maxright,maxmid,myl[2*N+2];
	char mys[2*N+2];
	int manacher(char s[])
	{
		int i,j,l,ans=0;
		memset(mys,'$',sizeof mys);
		for(i=0;s[i]!='\0';i++)
			mys[2*i+1]=s[i];
		l=2*i;
		myl[0]=1;
		myl[1]=2;
		maxright=maxmid=1;
		for(i=2;i<l;i++)
		{
			if(maxright>=i) myl[i]=min(myl[2*maxmid-i],maxright-i+1);
			else myl[i]=1;
			for(j=i+myl[i];2*i-j>=0&&mys[j]==mys[2*i-j];) j++;
			myl[i]=j-i;
			if(j>maxright)
			{
				maxright=j-1;
				maxmid=i;
			}
			if(myl[i]>myl[ans]||(myl[i]==myl[ans]&&mys[i]!='$'))
				ans=i;
		}
		return myl[ans]-1<1?1:myl[ans]-1;
	}
};
