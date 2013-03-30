#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*���涨���������*/
#define Min(a,b) ((a>b)?b:a)
//�궨��Ĳ�����Min���� ȡ��Сֵ; 
const int MAX=1010;
//������Ľ����� 
typedef struct Node
{
	int v[3];//�������ӵ�ʣ��ˮ��;
	int fa;//��һ�η��ʵ��������ǵ�ǰһ�������±ꣻ
	//ͨ���±������������治��; 
	int last_op;//��¼���ϸ���㵽������ı仯��ʽ
	//last_op��Ϊ����λ����,��һλ��ʾ���⵹ˮ�ı���
	//�ı��,�ڶ�λ��ʾ������ˮ�ı���; 
	int  deepth;
	//��¼��ԭʼ״̬�����״̬�仯�����ٵĲ���;Ҳ���ǽ��������ȣ� 
}Node; 
int cup_capacity[3];//�洢�������ӵ������� 
int water_to_get; //�洢Ҫ������ˮ��; 
Node  q[MAX*MAX]; //������ô���״̬��ɵ�����; �������������ʾ�����治��; 
int vis[MAX][MAX];//�����±�ֱ����б���������С��������; 
void print_path(int destination);//������������������±�Ϊ0���±�Ϊdestination�Ľ���·��; 
void bfs();//breath-first-search;������ȱ��� ;
int main()
{
	/*���ȶ����������ӵ�������Ҫ������ˮ��*/
	scanf("%d%d%d%d",&cup_capacity[0],&cup_capacity[1],&cup_capacity[2],&water_to_get);
	/*���б�������*/
	memset(vis,0,sizeof vis);//sizeof ���ڱ��������Բ������� ���� ��������һ������ ;
							 /*
							 memset()�����Ϊ�ַ����鸳ֵ��������Ҫ����ͷ�ļ�string.h��
							 ����������Ϊ�ṹ�壬һά���飬��ά����ȸ�ֵ�� ;
							 ������ʵ������Ҫ��ֵ����Ϊȫ�ֱ����Ѿ�����ʼ����; 
							*/ 
	bfs();
	return 0;
} 
void bfs()
{
	q[0].v[0]=cup_capacity[0];
	q[0].v[1]=q[0].v[2]=0;
	q[0].fa=0;//��Ϊ��һ�����û�и��ڵ���; 
	q[0].deepth=0;//Ҳ���Բ�д��Щ0;��Ϊȫ�ֱ������Զ���ʼ��; 
	q[0].last_op=0;//��Ϊ�ǵ�һ����� ;
	vis[q[0].v[1]][q[0].v[2]]=1;//��ʾ�������Ѿ��ڶ�������
	//������������Ͳ��ٽ����Ž�������; 
	//�ϸ�����Ҳ������ôдvis[0][0]=1; 
	int front=0,rear=1;//ģ�����;����ʵ�ֹ�����ȱ���; 
	while(front<rear)
	{
		Node N=q[front];//��ǰ�����н�Ҫ���ʵı���;
		if(N.v[0]==water_to_get||N.v[1]==water_to_get||N.v[2]==water_to_get)
		{//�����ǰ������þ���Ҫ���ʵ�,��ô�����������·��; 
			//���������Ҫ�Ĳ���;
			printf("%d\n",N.deepth);
			//Ȼ����õݹ麯��������������м�״̬;
			print_path(front); 
			return;
		}
		for(int i=0;i<3;i++)//���⵹ˮ�ı��ӽ���ö��;
		{
			
			for(int j=0;j<3;j++)//������ˮ�ı��ӵ�ö��;
			{//i��=j;�Ǳ�������Щ�Լ����Լ����浹ˮ���������; 
				Node &IN=q[rear];
				if(i==j)continue;
				int amount=Min(N.v[i],cup_capacity[j]-N.v[j]);//�����������������ˮ�Ķ���
				//Ҫô��ˮ�ı��ӵ��ꣻҪô������ı��ӱ�����; 
				for (int k=0;k<3;k++)
				{
					IN.v[k]=N.v[k];
				}
				IN.v[i]=N.v[i]-amount;//��i������amount����ˮ�� 
				IN.v[j]=N.v[j]+amount;//����j��amou����ˮ;
				//���˾Ͳ�����һ��״̬��Ȼ���Ҫ�����Ƿ��Ѿ������ڶ���������; 
				if(!vis[IN.v[1]][IN.v[2]])
				{
					vis[IN.v[1]][IN.v[2]]=1;
					IN.fa=front;//���ø��ڵ���±ꣻ
					IN.deepth=N.deepth+1;//�������ٲ�������
					IN.last_op=10*i+j;//��¼�任�ķ���;
					
					rear++; 
				}//if
			} //for(j)
		} //for(i)
		front++;//�Ӷ��е���һ���������һ�ο���; 
		
	}//while
}
void print_path(int destination)
{
	if(q[destination].fa!=destination)
	{
		print_path(q[destination].fa);//���ҵ�ԭʼ��Ԫ��;�ݹ�ջ���ƿ��Լǵ�·�� 
		int from=q[destination].last_op/10,to=q[destination].last_op%10;
		int num=q[q[destination].fa].v[from]-q[destination].v[from];
		printf("cup %d (-%d)->cup %d\n",from,num,to); 
	}
	printf("(%d,%d,%d)\n",q[destination].v[0],q[destination].v[1],q[destination].v[2]);
	
}