

//Treap
template<typename T> struct Treap
{
	static const int N=100005;
	struct node
	{
		T v;
		int l,r,s,n;//left,right,size,num
		int rnd;
	}mem[N];
	int treapcur,root;
	inline void init()
	{
		treapcur=1;
		root=0;
	}
	inline void lturn(int &in)
	{
		int t=mem[in].r;
		mem[in].r=mem[t].l;
		mem[t].l=in;
		mem[t].s=mem[in].s;
		mem[in].s=mem[mem[in].l].s+mem[in].n+mem[mem[in].r].s;
		in=t;
	}
	inline void rturn(int &in)
	{
		int t=mem[in].l;
		mem[in].l=mem[t].r;
		mem[t].r=in;
		mem[t].s=mem[in].s;
		mem[in].s=mem[mem[in].l].s+mem[in].n+mem[mem[in].r].s;
		in=t;
	}
	bool _insert(int &in,T x)
	{
		bool res=true;
		if(in==0)
		{
			in=treapcur++;
			mem[in].l=mem[in].r=0;
			mem[in].n=mem[in].s=1;
			mem[in].v=x;
			return false;
		}
		mem[in].s++;
		if(mem[in].v==x) mem[in].n++;
		else if(x<mem[in].v)
		{
			res=_insert(mem[in].l,x);
			if(mem[mem[in].l].rnd<mem[in].rnd) rturn(in);
		}
		else
		{
			res=_insert(mem[in].r,x);
			if(mem[mem[in].r].rnd<mem[in].rnd) lturn(in);
		}
		return res;
	}
	inline bool insert(T x)
	{return _insert(root,x);}
	bool _del(int &in,T x)
	{
		if(!in) return false;
		if(mem[in].v==x)
		{
			if(mem[in].n>1)
				mem[in].n--,mem[in].s--;
			else if(!mem[in].l||!mem[in].r)
				in=mem[in].l+mem[in].r;
			else if(mem[mem[in].l].rnd<mem[mem[in].r].rnd)
				rturn(in),_del(in,x);
			else
				lturn(in),_del(in,x);
			return true;
		}
		else if(x<mem[in].v)
			return _del(mem[in].l,x)?(mem[in].s--,true):false;
		else
			return _del(mem[in].r,x)?(mem[in].s--,true):false;
	}
	inline bool del(T x)
	{return _del(root,x);}
	int _getrank(int in,T v)
	{
		if(!in) return 0;
		if(v==mem[in].v) return mem[mem[in].l].s+1;
		else if(v<mem[in].v) return _getrank(mem[in].l,v);
		else return mem[mem[in].l].s+mem[in].n+_getrank(mem[in].r,v);
	}
	inline int getrank(T v)
	{return _getrank(root,v);}
	T _getv(int in,int rank)
	{
		if(!in) return 0;
		if(mem[mem[in].l].s<rank&&rank<=mem[mem[in].l].s+mem[in].n) return mem[in].v;
		else if(rank<=mem[mem[in].l].s) return _getv(mem[in].l,rank);
		else return _getv(mem[in].r,rank-mem[mem[in].l].s-mem[in].n);
	}
	inline T getv(int rank)
	{return _getv(root,rank);}
	void _getpre(int in,T x,int &ans)
	{
		if(!in) return;
		if(mem[in].v<x)
			ans=in,_getpre(mem[in].r,x,ans);
		else
			_getpre(mem[in].l,x,ans);
	}
	inline T getpre(T x)
	{int ans=0;_getpre(root,x,ans);return mem[ans].v;}
	void _getsub(int in,T x,int &ans)
	{
		if(!in) return;
		if(mem[in].v>x)
			ans=in,_getsub(mem[in].l,x,ans);
		else
			_getsub(mem[in].r,x,ans);
	}
	inline T getsub(T x)
	{int ans=0;_getsub(root,x,ans);return mem[ans].v;}
};
