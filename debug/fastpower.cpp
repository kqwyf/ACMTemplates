//fast power for real number
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

//fast power for matrix
struct Power
{
	static const int N=100005;
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
	void powm(long long a[N][N],long long b[N][N],int x,int nn)
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
