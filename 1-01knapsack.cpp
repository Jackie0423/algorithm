#include <iostream>
#include <iomanip>
using namespace std;

const int C=6;
const int N=3;
template <class T>
T max(const T a,const T b)
{
	return a>b?a:b;
}
/*01背包问题
m为记录数组 m[i][j]代表在剩有j容量的条件下，从i开始往后的物品中可以取得的最大价值
w为质量数组，v为价值数组
n为物品个数，c为开始容量
则m[1][c]即此背包能盛下的最大价值
*/
void knapsack(int **m,const int n,const int c,const int *w,const int *v)
{
	/*
	m[n][j]首先计算
	m[n][j]的意思是容量为j ，放第n个物品可以取得的最大价值，当然当j比此物品的重量小时，装不下，m[n][j]为0
	当j比此物品重量大时，能取得的最大价值就是v[n]
	*/
	for(int i=0;i<w[n]&&i<=c;i++)
		m[n][i]=0;
	for(i=w[n];i<=c;i++)
		m[n][i]=v[n];
	/*
		计算完m[n][1，2，3……]后 就可以用递推公式
	*/
	/*如果已经知道m[i+1][j] (j=1~c)的值了，那么m[i][j]的值要么是m[i+1][j] */
	/*即这第i个物品不要了，省下空间给之后的物品*/
	/*要么就是m[i+1][j-w[i]]+v[i]，即这个物品要了，占用了w[i]空间，增加了v[i]价值*/
	for(i=n-1;i>1;i--){
		for(int j=0;j<w[i]&&j<=c;j++)
			m[i][j] = m[i+1][j];
		for(j=w[i];j<=c;j++)        /*应该是m[i+1][j-w[i]]+v[i])*/
			m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
	}

	//边界处理
	m[1][c]=max(m[2][c],m[2][c-w[1]]+v[1]);
	
}
/*最后就是找出最优解，也就是要哪个不要哪个*/
void traceback(int **m,int n,int c,int *x,int *w)
{
	for(int i=1;i<n;i++)
	{
		if(m[i][c]==m[i+1][c])x[i]=0;
		else
		{
			x[i]=1;
			c-=w[i];
		}
	}

	//边界处理
	x[n]=(m[n][c]==0)?0:1;
}
int main()
{
	int *v=new int[N+1];
	int *w=new int[N+1];
	int **m=new int*[N+1];
	int *x=new int [N+1];
	for(int i=0;i<N+1;i++)
	{
		m[i]=new int[C+1];
	}
    cout<<"输入质量序列,"<<N<<"个"<<endl;
	for(i=1;i<=N;i++)
		cin>>w[i];
	cout<<"输入价值序列,"<<N<<"个"<<endl;
	for(i=1;i<=N;i++)
		cin>>v[i];
	knapsack(m,N,C,w,v);
	traceback(m,N,C,x,w);
	
	cout<<m[1][C]<<endl;
    for(i=1;i<=N;i++)
		cout<<x[i];
	cout<<endl;
	
	for(i=0;i<N+1;i++)
	{
		delete [C+1]m[i];
	}
	delete [N+1] m;
	return 1;
}