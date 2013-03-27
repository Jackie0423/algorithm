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
/*01��������
mΪ��¼���� m[i][j]������ʣ��j�����������£���i��ʼ�������Ʒ�п���ȡ�õ�����ֵ
wΪ�������飬vΪ��ֵ����
nΪ��Ʒ������cΪ��ʼ����
��m[1][c]���˱�����ʢ�µ�����ֵ
*/
void knapsack(int **m,const int n,const int c,const int *w,const int *v)
{
	/*
	m[n][j]���ȼ���
	m[n][j]����˼������Ϊj ���ŵ�n����Ʒ����ȡ�õ�����ֵ����Ȼ��j�ȴ���Ʒ������Сʱ��װ���£�m[n][j]Ϊ0
	��j�ȴ���Ʒ������ʱ����ȡ�õ�����ֵ����v[n]
	*/
	for(int i=0;i<w[n]&&i<=c;i++)
		m[n][i]=0;
	for(i=w[n];i<=c;i++)
		m[n][i]=v[n];
	/*
		������m[n][1��2��3����]�� �Ϳ����õ��ƹ�ʽ
	*/
	/*����Ѿ�֪��m[i+1][j] (j=1~c)��ֵ�ˣ���ôm[i][j]��ֵҪô��m[i+1][j] */
	/*�����i����Ʒ��Ҫ�ˣ�ʡ�¿ռ��֮�����Ʒ*/
	/*Ҫô����m[i+1][j-w[i]]+v[i]���������ƷҪ�ˣ�ռ����w[i]�ռ䣬������v[i]��ֵ*/
	for(i=n-1;i>1;i--){
		for(int j=0;j<w[i]&&j<=c;j++)
			m[i][j] = m[i+1][j];
		for(j=w[i];j<=c;j++)        /*Ӧ����m[i+1][j-w[i]]+v[i])*/
			m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
	}

	//�߽紦��
	m[1][c]=max(m[2][c],m[2][c-w[1]]+v[1]);
	
}
/*�������ҳ����Ž⣬Ҳ����Ҫ�ĸ���Ҫ�ĸ�*/
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

	//�߽紦��
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
    cout<<"������������,"<<N<<"��"<<endl;
	for(i=1;i<=N;i++)
		cin>>w[i];
	cout<<"�����ֵ����,"<<N<<"��"<<endl;
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