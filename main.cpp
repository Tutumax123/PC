#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int dx[]={1,0,-1,0};//队列读取方式
int dy[]={0,-1,0,1};
typedef struct DongDong
{
    int x;
    int y;
    int cost; //当前最低单次订单量花费
    int needed; //客户需求量
    bool barricade;//障碍物
    bool visit;//是否已访问
};
typedef struct restaurant//存储餐厅坐标
{
    int x ,y;
};
DongDong qwq[1005][1005];//声明二维数组

int n,m,k,d;
void bfs(int x, int y);
void Initialize(void);
void setvisit(void);
queue<DongDong>que;//声明队列，存储bfs访问的点

int main()
{
    cin>>n>>m>>k>>d;
    Initialize();

    restaurant r[m+1];//存储饭店的坐标
    for(int i=1;i<=m;i++)
    scanf("%d %d",&r[i].x , &r[i].y);

    restaurant client[k+1];//存客户的坐标
    for(int i=1;i<=k;i++)//标记客户需求量
    {
        int x ,y ,z;
        scanf("%d %d %d",&x,&y,&z);
        client[i].x=x;
        client[i].y=y;
        qwq[x][y].needed=z;
    }

    for(int i=1;i<=d;i++)//标记障碍物
    {
        int x, y;
        cin>>x>>y;
        qwq[x][y].barricade=true;
    }

    for(int i=1;i<=m;i++)//取餐厅的坐标
    {
        int x,y;
        x=r[i].x;
        y=r[i].y;
        //调用bfs
        bfs(x,y); //广优
        setvisit(); //重置访问标记
    }
    int cnt=0; //计数需求成本
    for(int i=1;i<=k;i++)
        cnt+=qwq[client[i].x][client[i].y].cost*qwq[client[i].x][client[i].y].needed;
    cout<<cnt<<endl;
    return 0;
}

//初始化
void Initialize(void) //初始坐标
{
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        qwq[i][j].x=i;
        qwq[i][j].y=j;
        qwq[i][j].cost=1e5;
        qwq[i][j].barricade=false;
        qwq[i][j].needed=0;
        qwq[i][j].visit=false;
    }
}

void setvisit(void)
{
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    qwq[i][j].visit=false;
}

void bfs(int x, int y)
{
    qwq[x][y].cost=0;
    qwq[x][y].visit=true;
    que.push(qwq[x][y]);//将起点加入队列
    while(!que.empty())
    {
        int nx=que.front().x;
        int ny=que.front().y;
        que.pop(); //移除头部元素
        for(int i=0;i<=3;i++)//四个方向
        {
            if(nx+dx[i]<=n && nx+dx[i]>=1 && ny+dy[i]<=n && ny+dy[i]>=1 && qwq[nx+dx[i]][ny+dy[i]].visit==false &&qwq[nx+dx[i]][ny+dy[i]].barricade==false)
            {//新点坐标在地图内,并且没走过,而且不是障碍物
                qwq[nx+dx[i]][ny+dy[i]].cost = min(qwq[nx+dx[i]][ny+dy[i]].cost , qwq[nx][ny].cost+1);
                //这里使用min函数来确保新坐标的成本是当前已知的最低成本，或者是从当前点nx, ny到新坐标的成本加1。
                que.push(qwq[nx+dx[i]][ny+dy[i]]);//新坐标加入
                qwq[nx+dx[i]][ny+dy[i]].visit=true;//标记新坐标为已访问，以避免在后续的搜索中重复访问。
            }
        }
    }
}


/*
10 2 3 3
1 1
8 8
1 5 1
2 3 3
6 7 2
1 2
2 2
6 8
*/
