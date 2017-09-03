//extended GCD solving ax+by=gcd(a,b)
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

void exgcd(int a,int b,int &d,int &x,int &y)
{
	if(b==0) {x=1; y=0; d=a; return;}
	exgcd(b,a%b,d,y,x);
    y-=a/b*x;
}
