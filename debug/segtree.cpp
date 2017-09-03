#include "stdalgo.cpp"

//Segment Tree 1-Dimension
template<typename T> struct SegTree
{
	static const int N=100005;
	struct seg
	{
		int l,r;
		T v,toadd;
		int L,R;
	}mem[3*N];
	int segcur;
	int newseg(int L,int R)
	{
		if(L==R) return 0;
		int cur=segcur++;
		mem[cur].L=L;
		mem[cur].R=R;
		if(L+1<R)
		{
			mem[cur].l=newseg(L,(R+L)/2);
			mem[cur].r=newseg((R+L)/2,R);
		}
		else
			mem[cur].l=mem[cur].r=0;
		mem[cur].toadd=mem[cur].v=0;
		return cur;
	}
	inline void init(int l)
	{
		segcur=1;
		newseg(0,l);
	}
	long long _query(int in,int L,int R)
	{
		if(!in) return 0;
		if(mem[in].R<=L||mem[in].L>=R) return 0;
		if(mem[in].toadd)
		{
			mem[in].v+=mem[in].toadd*(mem[in].R-mem[in].L);
			if(mem[in].l) mem[mem[in].l].toadd+=mem[in].toadd;
			if(mem[in].r) mem[mem[in].r].toadd+=mem[in].toadd;
			mem[in].toadd=0;
		}
		if(mem[in].L>=L&&mem[in].R<=R) return mem[in].v;
		return _query(mem[in].l,L,R)+_query(mem[in].r,L,R);
	}
	inline long long query(int l,int r)
	{return _query(1,l,r);}
	void _modify(int in,int L,int R,long long toadd)
	{
		if(!in) return;
		if(mem[in].L>=L&&mem[in].R<=R)
		{
			mem[in].toadd+=toadd;
			return;
		}
		if(mem[in].R<=L||mem[in].L>=R) return;
		mem[in].v+=toadd*(min(R,mem[in].R)-max(L,mem[in].L));
		_modify(mem[in].l,L,R,toadd);
		_modify(mem[in].r,L,R,toadd);
	}
	inline void modify(int l,int r,long long toadd)
	{_modify(1,l,r,toadd);}
};

//Segment Tree 2-Dimension (4-child)
struct SegTree2
{
	static const int N=100005;
	struct seg
	{
		int lu,ld,ru,rd,v;
		int L,R,U,D;
		int toadd;
	}mem[N];
	int segcur;
	int newseg(int L,int R,int U,int D)
	{
		if(L==R||U==D) return 0;
		int cur=segcur++;
		mem[cur].L=L;
		mem[cur].R=R;
		mem[cur].U=U;
		mem[cur].D=D;
		if(L+1<R||U+1<D)
		{
			mem[cur].lu=newseg(L,(R+L)/2,U,(U+D)/2);
			mem[cur].ld=newseg(L,(R+L)/2,(U+D)/2,D);
			mem[cur].ru=newseg((R+L)/2,R,U,(U+D)/2);
			mem[cur].rd=newseg((R+L)/2,R,(U+D)/2,D);
		}
		else
			mem[cur].lu=mem[cur].ld=mem[cur].ru=mem[cur].rd=0;
		mem[cur].toadd=mem[cur].v=0;
		return cur;
	}
	inline void init(int w,int h)
	{
		segcur=1;
		newseg(0,w,0,h);
	}
	int _query(int in,int L,int R,int U,int D)
	{
		if(!in) return 0;
		if(mem[in].R<=L||mem[in].L>=R||mem[in].U>=D||mem[in].D<=U) return 0;
		if(mem[in].toadd)
		{
			mem[in].v+=mem[in].toadd*(mem[in].R-mem[in].L)*(mem[in].D-mem[in].U);
			if(mem[in].lu) mem[mem[in].lu].toadd+=mem[in].toadd;
			if(mem[in].ld) mem[mem[in].ld].toadd+=mem[in].toadd;
			if(mem[in].ru) mem[mem[in].ru].toadd+=mem[in].toadd;
			if(mem[in].rd) mem[mem[in].rd].toadd+=mem[in].toadd;
			mem[in].toadd=0;
		}
		if(mem[in].L>=L&&mem[in].R<=R&&mem[in].U>=U&&mem[in].D<=D) return mem[in].v;
		return _query(mem[in].lu,L,R,U,D)
			+_query(mem[in].ld,L,R,U,D)
			+_query(mem[in].ru,L,R,U,D)
			+_query(mem[in].rd,L,R,U,D);
	}
	inline int query(int l,int r,int u,int d)
	{return _query(1,l,r,u,d);}
	void _modify(int in,int L,int R,int U,int D,int toadd)
	{
		if(!in) return;
		if(mem[in].L>=L&&mem[in].R<=R&&mem[in].U>=U&&mem[in].D<=D)
		{
			mem[in].toadd+=toadd;
			return;
		}
		if(mem[in].R<=L||mem[in].L>=R||mem[in].D<=U||mem[in].U>=D) return;
		mem[in].v+=toadd*(min(R,mem[in].R)-max(L,mem[in].L))*(min(D,mem[in].D)-max(U,mem[in].U));
		_modify(mem[in].lu,L,R,U,D,toadd);
		_modify(mem[in].ld,L,R,U,D,toadd);
		_modify(mem[in].ru,L,R,U,D,toadd);
		_modify(mem[in].rd,L,R,U,D,toadd);
	}
	inline void modify(int l,int r,int u,int d,int toadd)
	{_modify(1,l,r,u,d,toadd);}
};
