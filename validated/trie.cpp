#include "stdalgo.cpp"

/*
 * Trie (字典树) - 单词出现次数查询
 * 字符类型T
 * usage: init() -> insert()*n -> query()
 */
template<typename T> struct Trie
{
	static const int N=100005; //最大节点数=关键词数*单词平均字符数
	static const int M=26;     //字符取值范围开区间右端点
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
	void insert(T s[],int l)
	{
		int t=root;
		for(int i=0;i<l;t=ch[t][s[i++]])
			if(ch[t][s[i]]==-1)
				ch[t][s[i]]=newnode();
		end[t]++;
	}
	int query(T s[],int l)
	{
		int t=root;
		for(int i=0;t!=-1&&i<=l;t=ch[t][s[i++]])
			if(i==l) return end[t];
		return 0;
	}
};
