#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int dx[]={1,0,-1,0};//���ж�ȡ��ʽ
int dy[]={0,-1,0,1};
typedef struct DongDong
{
    int x;
    int y;
    int cost; //��ǰ��͵��ζ���������
    int needed; //�ͻ�������
    bool barricade;//�ϰ���
    bool visit;//�Ƿ��ѷ���
};
typedef struct restaurant//�洢��������
{
    int x ,y;
};
DongDong qwq[1005][1005];//������ά����

int n,m,k,d;
void bfs(int x, int y);
void Initialize(void);
void setvisit(void);
queue<DongDong>que;//�������У��洢bfs���ʵĵ�

int main()
{
    cin>>n>>m>>k>>d;
    Initialize();

    restaurant r[m+1];//�洢���������
    for(int i=1;i<=m;i++)
    scanf("%d %d",&r[i].x , &r[i].y);

    restaurant client[k+1];//��ͻ�������
    for(int i=1;i<=k;i++)//��ǿͻ�������
    {
        int x ,y ,z;
        scanf("%d %d %d",&x,&y,&z);
        client[i].x=x;
        client[i].y=y;
        qwq[x][y].needed=z;
    }

    for(int i=1;i<=d;i++)//����ϰ���
    {
        int x, y;
        cin>>x>>y;
        qwq[x][y].barricade=true;
    }

    for(int i=1;i<=m;i++)//ȡ����������
    {
        int x,y;
        x=r[i].x;
        y=r[i].y;
        //����bfs
        bfs(x,y); //����
        setvisit(); //���÷��ʱ��
    }
    int cnt=0; //��������ɱ�
    for(int i=1;i<=k;i++)
        cnt+=qwq[client[i].x][client[i].y].cost*qwq[client[i].x][client[i].y].needed;
    cout<<cnt<<endl;
    return 0;
}

//��ʼ��
void Initialize(void) //��ʼ����
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
    que.push(qwq[x][y]);//�����������
    while(!que.empty())
    {
        int nx=que.front().x;
        int ny=que.front().y;
        que.pop(); //�Ƴ�ͷ��Ԫ��
        for(int i=0;i<=3;i++)//�ĸ�����
        {
            if(nx+dx[i]<=n && nx+dx[i]>=1 && ny+dy[i]<=n && ny+dy[i]>=1 && qwq[nx+dx[i]][ny+dy[i]].visit==false &&qwq[nx+dx[i]][ny+dy[i]].barricade==false)
            {//�µ������ڵ�ͼ��,����û�߹�,���Ҳ����ϰ���
                qwq[nx+dx[i]][ny+dy[i]].cost = min(qwq[nx+dx[i]][ny+dy[i]].cost , qwq[nx][ny].cost+1);
                //����ʹ��min������ȷ��������ĳɱ��ǵ�ǰ��֪����ͳɱ��������Ǵӵ�ǰ��nx, ny��������ĳɱ���1��
                que.push(qwq[nx+dx[i]][ny+dy[i]]);//���������
                qwq[nx+dx[i]][ny+dy[i]].visit=true;//���������Ϊ�ѷ��ʣ��Ա����ں������������ظ����ʡ�
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
