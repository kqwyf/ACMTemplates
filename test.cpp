#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


template<typename T> struct ACTrie
{
	static const int N=500005;
	static const int M=26;
	int root,cur,ch[N][M],fail[N],end[N];
	inline int newnode()
	{
		for(int i=0;i<M;i++)
			ch[cur][i]=-1;
		end[cur]=0;
		return cur++;
	}
	inline void init()
	{
		cur=0;
		root=newnode();
	}
	void insert(T s[],int l)
	{
		int t=root;
		for(int i=0;i<l;t=ch[t][s[i++]])
			if(ch[t][s[i]]==-1)
				ch[t][s[i]]=newnode();
		end[t]++;
	}
	void build()
	{
		queue<int> q;
		fail[root]=root;
		for(int i=0;i<M;i++)
			if(ch[root][i]==-1)
				ch[root][i]=root;
			else
			{
				fail[ch[root][i]]=root;
				q.push(ch[root][i]);
			}
		while(!q.empty())
		{
			int t=q.front();
			q.pop();
			for(int i=0;i<M;i++)
				if(ch[t][i]==-1)
					ch[t][i]=ch[fail[t]][i];
				else
				{
					fail[ch[t][i]]=ch[fail[t]][i];
					q.push(ch[t][i]);
				}
		}
	}
	int query(T s[],int l)
	{
		int ans=0;
		for(int t=root,i=0;i<=l;t=ch[t][s[i++]])
			for(int tmp=t;tmp!=root;tmp=fail[tmp])
				ans+=end[tmp],end[tmp]=0;
		return ans;
	}
};

ACTrie<char> trie;

int n,m;

char s[1000005];
int main()
{
	int i,j,T,t;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		trie.init();
		while(n--)
		{
			scanf("%s",s);
			m=strlen(s);
			for(i=0;i<m;i++)
				s[i]-='a';
			trie.insert(s,m);
		}
		trie.build();
		scanf("%s",s);
		m=strlen(s);
		for(i=0;i<m;i++)
			s[i]-='a';
		printf("%d\n",trie.query(s,m));
	}
	return 0;
}
