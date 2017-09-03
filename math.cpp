//Prime numbers from 1 to M
int pr[M],pcur;
bool pl[N];
void prime()
{
	memset(pl,true,sizeof pl);
	pl[0]=pl[1]=false;
	pcur=0;
	for(int i=2;i<N;i++)
		if(pl[i])
		{
			pr[pcur++]=i;
			for(int j=i*2;j<N;j+=i)
				pl[j]=false;
		}
}

//Prime numbers Linear Algorithm
int pr[M];
void prime()
{
	memset(pr,0,sizeof pr);
	for(int i=2;i<M;i++)
	{
		if(!pr[i]) pr[++pr[0]]=i;
		for(int j=1;j<=pr[0]&&pr[j]<=M/i;j++)
		{
			pr[pr[j]*i]=1;
			if(i%pr[j]==0) break;
		}
	}
}

//Miller Rabin prime test
bool mr(int p)
{}

//Euler Phi Function
//a^phi(n)=1 mod n
int phi(int n)
{
	int res=n;
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
		{
			res=res/i*(i-1);
			for(;n%i==0;n/=i);
		}
	if(n!=1) res=res/n*(n-1);
	return res;
}

//Phi numbers from 1 to M
int phi[M];
void euler()
{
	memset(phi,0,sizeof phi);
	phi[1]=1;
	for(int i=2;i<M;i++)
		if(!phi[i])
			for(int j=i;j<m;j+=i)
			{
				if(!phi[j]) phi[j]=j;
				phi[j]=phi[j]/i*(i-1);
			}
}

//

