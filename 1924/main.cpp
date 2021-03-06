#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
const int maxn = 105;
char map[maxn][maxn];
int dir[8][2] = {{0,1},{1,1},{1,0},{0,-1},{-1,-1},{-1,0},{-1,1}};
int R,C;
bool vis[maxn][maxn];
class pos
{
public:
	int x,y;
	pos(){}
	pos(int i,int j):x(i),y(j){}
};
bool inmap(int x, int y)
{
	if(x>=0 && x < R && y >= 0 && y < C)
		return true;
	return false;
}
class monster
{
public:
	int type;
	pos mpos[maxn];
	int s;
	void clear(int i)
	{
		pos temp = mpos[i%s];
		map[temp.x][temp.y] = '.';
		if(type)
		{	
			int x,y;
			for(int i = 0; i < 8; i++)
			{
				x = temp.x+dir[i][0];
				y = temp.y+dir[i][1];
				if(inmap(x,y)&&map[x][y] != '#')
					map[x][y] = '.';
			}
		}
	}
	void set(int i)
	{
		pos temp = mpos[i%s];
		map[temp.x][temp.y] = 'a';
		if(type)
		{
			int x,y;
			for(int i = 0; i < 8; i++)
			{
				x = temp.x+dir[i][0];
				y = temp.y+dir[i][1];
				if(inmap(x,y)&&map[x][y] != '#')
					map[x][y] = 'a';
			}
		}
	}
}m[maxn];
class ppos :public pos
{
public:
	int time;
	ppos(){}
	ppos(int x,int y,int t):pos(x,y),time(t) {}
}q[maxn*maxn*maxn];
void start()
{
	int tx,ty,p,s,sx,sy;
	bool f = false;
	while(cin>>R>>C&&R&&C)
	{	
		if(f) cout<<endl;
		f = true;
		//queue<ppos> q;
		int head = 0,tail = 0;
		memset(vis,false, sizeof(vis));
		for(int i = 0; i < R; i++)
			cin>>map[i];
		for(int i = 0; i < R; i++)
			for(int j = 0; j < C; j++)
			{
				if(map[i][j] == 't')
					tx=i,ty=j;
				else if(map[i][j] == 'p')
					//q.push(ppos(i,j,0));
					q[head++] = ppos(i,j,0);
			}
		cin>>p;
		for(int i =0; i < p; i++)
		{
			cin>>s;
			m[i].s = s;
			for(int j =0; j < s; j++)
			{
				cin>>sx>>sy;
				sx--,sy--;
				//m[i].mpos[j]= pos(sx,sy);
				m[i].mpos[j].x = sx, m[i].mpos[j].y = sy;
				if(j == 0)
					m[i].type = (map[sx][sy] == 'a'? 1:0);
			}
		}
		ppos t,node;
		int answer = 0;
		while(head > tail)
		{
			//t = q.front();
			//q.pop();
			t = q[tail++];
			vis[t.x][t.y] = true;
			if((t.x == tx && t.y == ty) || t.time >100)
			{			
				break;
			}
			if(t.time >= answer)
			{
				answer++;
				for(int i = 0; i < p; i++)
				{
					m[i].clear(answer-1);
					m[i].set(answer);
					//cout<<m[i].type<<'\t'<<m[i].mpos[0].x<<'\t'<<m[i].mpos[0].y<<endl;
				}
			}
			//for(int i = 0; i < R; i++)
				//cout<<map[i]<<endl;
			int nextx,nexty;
			for(int i =0; i < 8; i++ )
			{
				nextx = t.x+dir[i][0];
				nexty = t.y+dir[i][1];
				if(inmap(nextx,nexty) && map[nextx][nexty] !='#' && map[nextx][nexty] != 'a' )
				{
					node.x=nextx,node.y=nexty,node.time = t.time+1;
					if(!vis[nextx][nexty]) q[head++] = node;
					nextx += dir[i][0];
					nexty += dir[i][1];
					if(inmap(nextx,nexty) && map[nextx][nexty] !='#' && map[nextx][nexty] != 'a' && !vis[nextx][nexty])
					{
						node.x=nextx,node.y=nexty,node.time = t.time+1;
						//q.push(node);
						q[head++] = node;
					}
				}
			}
			if(t.time < answer && map[t.x][t.y] != 'a')
			{
				t.time++;
				q[head++] = t;				
				//q.push(t);
			}
		}
		if(t.time <= 100) cout<<t.time<<endl;
		else cout<<"impossible\n";
	}
}
int main()
{
	start();
}
