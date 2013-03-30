#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #define MAX 1000000
 typedef struct Node
 {
     int state[9];//存放本状态各个位置的数码值；
     int fa;//记录父节点的下标;
     int deepth;
     int last_x;
     int last_y;
 
 }Node;
 Node q[MAX];//构成状态数组;
 typedef struct Vis
 {
     int sequeue[9];//记录9个数码的位置;
     int visited;
 
 }Vis;
 Vis vis[MAX];//判断是否访问过;
 int vis_cur=0;//记录vis数组的当前索引位置;
 const int dx[4]={-1,1,0,0};//左右上下;
 const int dy[4]={0,0,-1,1};
 //bool has_vis(const int * state_to_decide);
 int has_vis=0;
 int bfs();//广度优先找到目标状态;
 void print_path(int founded);//根据fa成员，通过递归技术实现状态依次输出;
 Node destination;//存储目标状态;
 int i,j,k;
 int main()
 {
     /*首先输入起始状态和目标状态*/
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
     
     /*然后进行搜索并输出*/
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
     int front=0,rear=1;//用来模拟队列的先进先出,达到广度优先的目的;
     vis[0].visited=1;//第一个结点访问；
     vis_cur++;
     while (front<rear)
     {
         Node &first=q[front];
         if (memcmp(first.state,destination.state,sizeof destination.state)==0)
         {//找到了目标状态;
             return front;
         }
         for(i=0;i<9;i++)
             if (!first.state[i])
             {//找到空格处;
                 break;
             }
 
         for(j=0;j<4;j++)
         {//向四个方向进行转换;
             Node &new_Node=q[rear];
             memcpy(new_Node.state,first.state,sizeof first.state);
             int new_x=i%3+1+dx[j];
             int new_y=i/3+1+dy[j];
             
             if (new_x>0&&new_y>0&&new_x<4&&new_y<4)
             {
                 //位置合法
                 new_Node.state[i]=new_Node.state[i+dx[j]+3*dy[j]];//空格位置；
                 new_Node.state[i+dx[j]+3*dy[j]]=0;//新的状态形成了;
                 has_vis=0;
                 for(k=0;k<vis_cur;k++)//这里不用i,j因为i,j是全局变量且本函数是在循环里面的;
                 {
                     if((memcmp(vis[k].sequeue,new_Node.state,sizeof vis[k].sequeue))==0)
                     {
                         has_vis=1;
                         break;
                     }
                 }
                 if(!has_vis)//没有被访问；
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
     for(k=0;k<vis_cur;k++)//这里不用i,j因为i,j是全局变量且本函数是在循环里面的;
     {
         if(memcmp(vis[k].sequeue,state_to_decide,sizeof vis[k].sequeue)==0)
             return true;
     }
     return false;
 }*/