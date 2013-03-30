#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*下面定义结点的类型*/
#define Min(a,b) ((a>b)?b:a)
//宏定义的操作符Min作用 取最小值; 
const int MAX=1010;
//解答树的结点最多 
typedef struct Node
{
	int v[3];//三个杯子的剩余水量;
	int fa;//第一次访问到这个结点是的前一个结点的下标；
	//通过下标可以随机访问真不错; 
	int last_op;//记录从上个结点到这个结点的变化方式
	//last_op认为是两位数字,第一位表示往外倒水的杯子
	//的编号,第二位表示被倒入水的杯子; 
	int  deepth;
	//记录从原始状态到这个状态变化的最少的步数;也就是解答树的深度； 
}Node; 
int cup_capacity[3];//存储三个杯子的容量； 
int water_to_get; //存储要量出的水量; 
Node  q[MAX*MAX]; //定义这么多个状态组成的数组; 用这个数组来表示队列真不错; 
int vis[MAX][MAX];//两个下标分别是中杯的余量和小杯的余量; 
void print_path(int destination);//函数的作用是输出从下标为0到下标为destination的结点的路径; 
void bfs();//breath-first-search;广度优先遍历 ;
int main()
{
	/*首先读入三个杯子的容量和要量出的水量*/
	scanf("%d%d%d%d",&cup_capacity[0],&cup_capacity[1],&cup_capacity[2],&water_to_get);
	/*进行遍历搜索*/
	memset(vis,0,sizeof vis);//sizeof 对于变量名可以不用括号 表明 它并不是一个函数 ;
							 /*
							 memset()起初是为字符数组赋值的所以需要包含头文件string.h，
							 但是它可以为结构体，一维数组，二维数组等赋值了 ;
							 这里其实并不需要赋值，因为全局变量已经被初始化了; 
							*/ 
	bfs();
	return 0;
} 
void bfs()
{
	q[0].v[0]=cup_capacity[0];
	q[0].v[1]=q[0].v[2]=0;
	q[0].fa=0;//因为第一个结点没有父节点了; 
	q[0].deepth=0;//也可以不写这些0;因为全局变量会自动初始化; 
	q[0].last_op=0;//因为是第一个结点 ;
	vis[q[0].v[1]][q[0].v[2]]=1;//表示这个结点已经在队列里了
	//如果在遇到它就不再将它放进队列了; 
	//上个句子也可以这么写vis[0][0]=1; 
	int front=0,rear=1;//模拟队列;可以实现广度优先遍历; 
	while(front<rear)
	{
		Node N=q[front];//当前队列中将要访问的变量;
		if(N.v[0]==water_to_get||N.v[1]==water_to_get||N.v[2]==water_to_get)
		{//如果当前结点正好就是要访问的,那么就来输出它的路径; 
			//首先输出需要的步数;
			printf("%d\n",N.deepth);
			//然后调用递归函数依次输出各个中间状态;
			print_path(front); 
			return;
		}
		for(int i=0;i<3;i++)//往外倒水的杯子进行枚举;
		{
			
			for(int j=0;j<3;j++)//被倒入水的杯子的枚举;
			{//i！=j;是避免了那些自己往自己里面倒水的情况发生; 
				Node &IN=q[rear];
				if(i==j)continue;
				int amount=Min(N.v[i],cup_capacity[j]-N.v[j]);//这个是用来决定倒出水的多少
				//要么倒水的杯子倒完；要么被倒入的杯子被倒满; 
				for (int k=0;k<3;k++)
				{
					IN.v[k]=N.v[k];
				}
				IN.v[i]=N.v[i]-amount;//从i杯倒出amount量的水； 
				IN.v[j]=N.v[j]+amount;//倒入j杯amou量的水;
				//至此就产生了一个状态；然后就要看它是否已经存在于队列里面了; 
				if(!vis[IN.v[1]][IN.v[2]])
				{
					vis[IN.v[1]][IN.v[2]]=1;
					IN.fa=front;//设置父节点的下标；
					IN.deepth=N.deepth+1;//设置最少步骤数；
					IN.last_op=10*i+j;//记录变换的方法;
					
					rear++; 
				}//if
			} //for(j)
		} //for(i)
		front++;//从队列的下一个结点向下一次考察; 
		
	}//while
}
void print_path(int destination)
{
	if(q[destination].fa!=destination)
	{
		print_path(q[destination].fa);//先找到原始的元素;递归栈机制可以记得路径 
		int from=q[destination].last_op/10,to=q[destination].last_op%10;
		int num=q[q[destination].fa].v[from]-q[destination].v[from];
		printf("cup %d (-%d)->cup %d\n",from,num,to); 
	}
	printf("(%d,%d,%d)\n",q[destination].v[0],q[destination].v[1],q[destination].v[2]);
	
}