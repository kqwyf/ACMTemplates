#include "stdalgo.cpp"

/*
 * AC自动机 - 多关键词搜索
 * 字符类型T
 * usage: init() -> insert()*n -> build() -> query()
 */
template<typename T> struct ACTrie
{
	static const int N=100005; //最大节点数=关键词数*单词平均字符数
	static const int M=26;     //字符取值范围开区间右端点
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
	void insert(T s[],int l) //向字典树插入新关键词s，长度l
	{
		int t=root;
		for(int i=0;i<l;t=ch[t][s[i++]])
			if(ch[t][s[i]]==-1)
				ch[t][s[i]]=newnode();
		end[t]++;
	}
	void build() //由字典树建立fail[]数组
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
	int query(T s[],int l) //对长度l的字符串s搜索 WARNING:将破坏字典树单词计数
	{
		int ans=0;
		for(int t=root,i=0;i<=l;t=ch[t][s[i++]])
			for(int tmp=t;tmp!=root;tmp=fail[tmp])
				ans+=end[tmp],end[tmp]=0;
		return ans;
	}
};

