#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #define MAX 1000000
 typedef struct Node
 {
     int state[9];//��ű�״̬����λ�õ�����ֵ��
     int fa;//��¼���ڵ���±�;
     int deepth;
     int last_x;
     int last_y;
 
 }Node;
 Node q[MAX];//����״̬����;
 typedef struct Vis
 {
     int sequeue[9];//��¼9�������λ��;
     int visited;
 
 }Vis;
 Vis vis[MAX];//�ж��Ƿ���ʹ�;
 int vis_cur=0;//��¼vis����ĵ�ǰ����λ��;
 const int dx[4]={-1,1,0,0};//��������;
 const int dy[4]={0,0,-1,1};
 //bool has_vis(const int * state_to_decide);
 int has_vis=0;
 int bfs();//��������ҵ�Ŀ��״̬;
 void print_path(int founded);//����fa��Ա��ͨ���ݹ鼼��ʵ��״̬�������;
 Node destination;//�洢Ŀ��״̬;
 int i,j,k;
 int main()
 {
     /*����������ʼ״̬��Ŀ��״̬*/
     memset(q,0,sizeof q);
     for(i=0;i<9;i++)
     {
         scanf("%d",&(q[0].state[i]));
     }
     for(i=0;i<9;i++)
     {
         scanf("%d",&destination.state[i]);
     }
         memset(vis,0,sizeof vis);
     
     /*Ȼ��������������*/
     int founded=bfs();
     if(founded)
         print_path(founded);
     else
         printf("-1\n");
     system("pause");
     return 0;
 }
 int bfs()
 {
     memcpy(vis[0].sequeue,q[0].state,sizeof q[0].state);
     int front=0,rear=1;//����ģ����е��Ƚ��ȳ�,�ﵽ������ȵ�Ŀ��;
     vis[0].visited=1;//��һ�������ʣ�
     vis_cur++;
     while (front<rear)
     {
         Node &first=q[front];
         if (memcmp(first.state,destination.state,sizeof destination.state)==0)
         {//�ҵ���Ŀ��״̬;
             return front;
         }
         for(i=0;i<9;i++)
             if (!first.state[i])
             {//�ҵ��ո�;
                 break;
             }
 
         for(j=0;j<4;j++)
         {//���ĸ��������ת��;
             Node &new_Node=q[rear];
             memcpy(new_Node.state,first.state,sizeof first.state);
             int new_x=i%3+1+dx[j];
             int new_y=i/3+1+dy[j];
             
             if (new_x>0&&new_y>0&&new_x<4&&new_y<4)
             {
                 //λ�úϷ�
                 new_Node.state[i]=new_Node.state[i+dx[j]+3*dy[j]];//�ո�λ�ã�
                 new_Node.state[i+dx[j]+3*dy[j]]=0;//�µ�״̬�γ���;
                 has_vis=0;
                 for(k=0;k<vis_cur;k++)//���ﲻ��i,j��Ϊi,j��ȫ�ֱ����ұ���������ѭ�������;
                 {
                     if((memcmp(vis[k].sequeue,new_Node.state,sizeof vis[k].sequeue))==0)
                     {
                         has_vis=1;
                         break;
                     }
                 }
                 if(!has_vis)//û�б����ʣ�
                 {
                     new_Node.fa=front;
                     new_Node.deepth=first.deepth+1;
                     new_Node.last_x=dx[j];
                     new_Node.last_y=dy[j];
                     memcpy(vis[vis_cur].sequeue,new_Node.state,sizeof new_Node.state);
                     vis[vis_cur].visited=1;
                     vis_cur++;
                     rear++;
                 }//if
                 
             }//if
         }//for
         front++;
         printf("%d %d\n",front,q[front].deepth);
     }//while
     return 0;
 }
 void print_path(int founded)
 {
     if(q[founded].fa!=founded)
     {
         print_path(q[founded].fa);
     }
     for(i=0;i<3;i++)
     {
         for(j=0;j<3;j++)
         {
             printf("%d ",q[founded].state[3*i+j]);
         }
         printf("\n");
     }
     printf("\n");
 }
 /*bool has_vis(const int * state_to_decide)
 {
     for(k=0;k<vis_cur;k++)//���ﲻ��i,j��Ϊi,j��ȫ�ֱ����ұ���������ѭ�������;
     {
         if(memcmp(vis[k].sequeue,state_to_decide,sizeof vis[k].sequeue)==0)
             return true;
     }
     return false;
 }*/