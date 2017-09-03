#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int n,m;

struct Euler
{
	static const int N=101;
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

Euler euler;
int phi[100005];

int main()
{
	int i,j,T,t;
	euler.run(phi);
	for(i=1;i<=101;i++)
		printf("%d ",phi[i]);
	puts("");
	return 0;
}
