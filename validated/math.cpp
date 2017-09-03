#include "stdalgo.cpp"

//扩展欧几里得算法 - 解方程 ax+by=gcd(a,b) 形式1
int exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	int q=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return q;
}

//扩展欧几里得算法 - 解方程 ax+by=gcd(a,b) 形式2
void exgcd(int a,int b,int &d,int &x,int &y)
{
    if(b==0) {x=1; y=0; d=a; return;}
    exgcd(b,a%b,d,y,x);
    y-=a/b*x;
}

/*
 * 实数快速幂
 * long long可改为其它数值类型
 * 取模时将ans*=a与a*=a改为b=(b*a)%MOD型即可
 */
long long pow(long long a,int x)
{
	long long ans=1;
	while(x)
	{
		if(x&1) ans*=a;
		x>>=1;
		a*=a;
	}
	return ans;
}

/*
 * 矩阵快速幂
 * usage: pow()
 */
struct Power
{
	static const int N=105; //矩阵各维长度
	int n;
	long long eax[N][N],ebx[N][N];
	void clrm(long long a[N][N])
	{
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				a[i][j]=0;
	}
	void cpym(long long a[N][N],long long b[N][N])
	{
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				b[i][j]=a[i][j];
	}
	void mulm(long long a[N][N],long long b[N][N])
	{
		int i,j,k;
		clrm(ebx);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					ebx[i][j]+=a[i][k]*b[k][j];
		cpym(ebx,b);
	}
	void pow(long long a[N][N],long long b[N][N],int x,int nn)
	{
		n=nn;
		int i;
		clrm(b);
		for(i=0;i<n;i++)
			b[i][i]=1;
		cpym(a,eax);
		while(x)
		{
			if(x&1) mulm(eax,b);
			mulm(eax,eax);
			x>>=1;
		}
	}
};

//素数筛 - 求(1,N)间素数
struct Prime
{
	static const int N=100005; //求(1,N)间素数
	int cur;
	bool p[N];
	void run(int prime[])
	{
		memset(p,true,sizeof p);
		p[0]=p[1]=false;
		cur=0;
		for(int i=2;i<N;i++)
			if(p[i])
			{
				prime[cur++]=i;
				for(int j=i*2;j<N;j+=i)
					p[j]=false;
			}
	}
};

//素数线性筛 - 求(1,N)间素数
struct LPrime
{
	static const int N=100005; //求(1,N)间素数
	void run(int prime[])      //IMPORTANT: prime长度>=N
	{
		memset(prime,0,sizeof(int)*N);
		for(int i=2;i<N;i++)
		{
			if(!prime[i]) prime[++prime[0]]=i;
			for(int j=1;j<=prime[0]&&prime[j]<=N/i;j++)
			{
				prime[prime[j]*i]=1;
				if(i%prime[j]==0) break;
			}
		}
	}
};

/*
 * 欧拉函数
 * 性质：a^phi(n)=1 mod n
 */
int phi(int n)
{
	int ans=n;
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
		{
			ans=ans/i*(i-1);
			for(;n%i==0;n/=i);
		}
	if(n!=1) ans=ans/n*(n-1);
	return ans;
}

//欧拉函数筛 - 求[1,N)的欧拉函数值
struct Euler
{
	static const int N=100005;
	void run(int phi[])
	{
		memset(phi,0,sizeof(int)*N);
		phi[1]=1;
		for(int i=2;i<N;i++)
			if(!phi[i])
				for(int j=i;j<N;j+=i)
				{
					if(!phi[j]) phi[j]=j;
					phi[j]=phi[j]/i*(i-1);
				}
	}
};
