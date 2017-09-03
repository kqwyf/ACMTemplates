#include "stdalgo.cpp"
using namespace std;

//Trie child starts from 0
struct Trie
{
	static const int N=100005;
	static const int M=26;
	int root,cur,ch[N][M],end[N];
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
	void insert(char s[])
	{
		int t=root;
		for(int i=0,l=strlen(s);i<l;t=ch[t][s[i++]])
			if(ch[t][s[i]]==-1)
				ch[t][s[i]]=newnode();
		end[t]++;
	}
	int query(char s[])
	{
		int t=root;
		for(int i=0,l=strlen(s);t!=-1&&i<=l;t=ch[t][s[i++]])
			if(i==l) return end[t];
		return 0;
	}
};

//AC automaton child starts from 0
struct ACTrie
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
	void insert(char s[])
	{
		int t=root;
		for(int i=0,l=strlen(s);i<l;t=ch[t][s[i++]])
			if(ch[t][s[i]]==-1)
				ch[t][s[i]]=newnode();
		end[t]++;
	}
	void buildac()
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
	int query(char s[])
	{
		int ans=0;
		for(int t=root,i=0,l=strlen(s);i<=l;t=ch[t][s[i++]])
			for(int tmp=t;tmp!=root;tmp=fail[tmp])
				ans+=end[tmp],end[tmp]=0;
		return ans;
	}
};
