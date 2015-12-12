#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<iostream>
using namespace std;

const int maxn = 110;

int vis[maxn][maxn][maxn];

char map[maxn][maxn];
bool mon_vis[maxn][maxn][maxn];
int n,m;
int cnt;
int sx,sy,ex,ey;


struct point
{
    int x,y;
};

struct monster
{
    int num;
    point p[maxn];
    bool is_agg;
}mon[maxn];

struct node
{
    int time;
    int x,y;
};

int fang[9][2] = {1,1,1,-1,-1,-1,-1,1,0,1,0,-1,1,0,-1,0,0,0};

void judge_mon_yuchuli()
{
    memset(mon_vis,false,sizeof(mon_vis));
    for(int i=0;i<=100;i++)
    {
        for(int j=0;j<cnt;j++)
        {
            int x = mon[j].p[i%mon[j].num].x;
            int y = mon[j].p[i%mon[j].num].y;
            mon_vis[x][y][i] = true;
            if(mon[j].is_agg)
            {
                for(int k=0;k<8;k++)
                {
                    int fx=x+fang[k][0];
                    int fy=y+fang[k][1];
                    mon_vis[fx][fy][i] = true;
                }
            }
        }
    }
}


bool judge_bianjie(node next)
{
    if(next.x < 1 || next.x > n || next.y < 1 || next.y > m || map[next.x][next.y] == '#')
        return false;
    return true;
}

bool judge_isfree(node next)
{
    return vis[next.x][next.y][next.time] == false ;
}

bool judge_mon(node next)
{
    return mon_vis[next.x][next.y][next.time] == false;
}


void solve()
{
    memset(vis,false,sizeof(vis));
    judge_mon_yuchuli();
    queue<node> q;

    int ans = -1;

    node start;
    start.x = sx;
    start.y = sy;
    start.time = 0;
    vis[sx][sy][0] = true;
    q.push(start);

    int c=1;
    while(!q.empty())
    {
        node cur = q.front();
        q.pop();
        if(cur.x==ex && cur.y==ey)
        {
            ans = cur.time;
            break;
        }

        if(cur.time >= 100)
            break;
        for(int i=0;i<8;i++)
        {
            node next;
            for(int j=0;j<=2;j++)
            {
                next.x = cur.x+j*fang[i][0];
                next.y = cur.y+j*fang[i][1];
                next.time = cur.time+1;
                if(!judge_mon(next) || !judge_bianjie(next))
                    break;
                if(!judge_isfree(next))
                    continue;
                vis[next.x][next.y][next.time] = true;
                q.push(next);
            }
        }
    }

    if(ans == -1)
        printf("impossible\n");
    else
        printf("%d\n",ans);

}



int main()
{
    bool f=false;
    while(cin>>n>>m&& n+m)
    {
        if(f)
            printf("\n");
        f=true;

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>map[i][j];
                if(map[i][j] == 'p')
                {
                    sx=i,sy=j;
                }
                if(map[i][j] == 't')
                {
                    ex=i,ey=j;
                }
            }
        }

        scanf("%d",&cnt);
        int x,y;
        for(int i=0;i<cnt;i++)
        {
            scanf("%d",&mon[i].num);
            for(int j=0;j<mon[i].num;j++)
            {
                scanf("%d%d",&x,&y);
                mon[i].p[j].x = x;
                mon[i].p[j].y = y;
                if(j==0)
                {
                    if(map[x][y] =='a')
                        mon[i].is_agg = true;
                    else
                        mon[i].is_agg = false;
                }
            }
        }

        solve();

    }
    return 0;
}

