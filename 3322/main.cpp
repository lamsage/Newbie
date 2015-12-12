#include <iostream>
#include <queue>
using namespace std;
const int maxn = 500;
char map[maxn][maxn];
bool visit[3][maxn][maxn];
class node
{
public:
	int x,y;
	int status;
	int step;
	node(){}
	node(int x,int y, int status, int step):x(x),y(y),status(status),step(step){}
}nodes[maxn*maxn*3];
node create(int x, int y, int status, int step)
{
	node temp;
	temp.x = x,temp.y = y, temp.status = status, temp.step = step;
	return temp;
}
bool can1(int x,int y)
{
	if(map[x][y] == '.' || map[x][y] == 'O' || map[x][y] == 'X' )
		return true;
	return false;
}
bool can2(int x1,int y1, int x2, int y2 )
{
	if((map[x1][y1] == '.'||map[x1][y1] == 'E' || map[x1][y1] =='O' || map[x1][y1] == 'X' ) &&(map[x2][y2] == '.'||map[x2][y2] == 'E' || map[x2][y2] =='O' || map[x2][y2] == 'X' ))
		return true;
	return false;
}
int main()
{
	int R,C;
	//queue<node> nodes;
	while(1)
	{
	cin>>R>>C;
	if(R == 0 && C ==0)
		break;
	//while(!nodes.empty()) nodes.pop();
	int head = 0, tail = 0;
	for(int i = 0; i < R; i++)
	{
		int j;
		for(j = 0; j < C; j++)
		{
			cin>> map[i][j];
			for(int k = 0; k < 3; k++)
				visit[k][i][j] = false;
		}
		map[i][j] = '\0';
	}
	int tx,ty;
	for(int i = 0; i < R; i++)
	{
		int j;
		for(j = 0; j < C; j++)
		{
			if(map[i][j] == 'X' && tail == head)
			{
				if(j < C-1 && map[i][j+1] == 'X')
					//nodes.push(create(i,j,1,0));
					nodes[head++] = node(i,j,1,0);
				else if(i < R-1 && map[i+1][j] =='X')
					//nodes.push(create(i,j,2,0));
					nodes[head++] = node(i,j,2,0);
				else 
					//nodes.push(create(i,j,0,0));
					nodes[head++] = node(i,j,0,0);
				visit[0][i][j] = true;
			}
			if(map[i][j] == 'O')
				tx = i, ty =j;
		}
	}
	//cout<<tx<<'\t'<<ty<<endl;
	int best = 0;
	while(head > tail)
	{
		node t = nodes[tail++];
		//nodes.pop();
		//cout<< t.x<<'\t'<<t.y<<'\t'<<t.status<<'\t'<<t.step<<endl;
		if(t.x == tx && t.y == ty && t.status == 0)
		{
			best = t.step;
			break;
		}
		if(t.status == 0)
		{
			if(t.y+2 < C && can2(t.x, t.y+1, t.x, t.y+2) && !visit[1][t.x][t.y+1])
			{
				visit[1][t.x][t.y+1] = true;
				//nodes.push(create(t.x, t.y+1, 1, t.step+1));
				nodes[head++] = node(t.x,t.y+1,1,t.step+1);
			}
			if(t.y-2 >= 0 && can2(t.x, t.y-1, t.x, t.y-2) && !visit[1][t.x][t.y-2])
			{
				visit[1][t.x][t.y-2] = true;
				//nodes.push(create(t.x, t.y-2, 1, t.step+1));
				nodes[head++] = node(t.x,t.y-2,1,t.step+1);
			}
			if(t.x-2 >= 0 && can2(t.x-2, t.y, t.x-1, t.y) && !visit[2][t.x-2][t.y])
			{
				visit[2][t.x-2][t.y] = true;
				//nodes.push(create(t.x-2, t.y, 2, t.step+1));
				nodes[head++] = node(t.x-2,t.y,2,t.step+1);
			}
			if(t.x+2 < R && can2(t.x+1, t.y, t.x+2, t.y) && !visit[2][t.x+1][t.y])
			{
				visit[2][t.x+1][t.y] = true;
				//nodes.push(create(t.x+1, t.y, 2, t.step+1));
				nodes[head++] = node(t.x+1,t.y,2,t.step+1);
			}
		}
		else if(t.status == 1)
		{
			if(t.y+2 < C && can1(t.x, t.y+2) && !visit[0][t.x][t.y+2])
			{
				visit[0][t.x][t.y+2] = true;
				//nodes.push(create(t.x, t.y+2, 0, t.step+1));
				nodes[head++] = node(t.x,t.y+2,0,t.step+1);
			}
			if(t.y-1 >= 0 && can1(t.x, t.y-1) && !visit[0][t.x][t.y-1])
			{
				visit[0][t.x][t.y-1] = true;
				//nodes.push(create(t.x, t.y-1, 0, t.step+1));
				nodes[head++] = node(t.x,t.y-1,0,t.step+1);
			}
			if(t.x-1 >= 0 && can2(t.x-1, t.y, t.x-1, t.y+1) && !visit[1][t.x-1][t.y])
			{
				visit[1][t.x-1][t.y] = true;
				//nodes.push(create(t.x-1, t.y, 1, t.step+1));
				nodes[head++] = node(t.x-1,t.y,1,t.step+1);
			}
			if(t.x+1 < R && can2(t.x+1, t.y, t.x+1, t.y+1) && !visit[1][t.x+1][t.y])
			{
				visit[1][t.x+1][t.y] = true;
				//nodes.push(create(t.x+1, t.y, 1, t.step+1));
				nodes[head++] = node(t.x+1,t.y,1,t.step+1);
			}
		}
		else if(t.status == 2)
		{
			if(t.y+1 < C && can2(t.x, t.y+1, t.x+1, t.y+1) && !visit[2][t.x][t.y+1])
			{
				visit[2][t.x][t.y+1] = true;
				//nodes.push(create(t.x, t.y+1, 2, t.step+1));
				nodes[head++] = node(t.x,t.y+1,2,t.step+1);
			}
			if(t.y-1 >= 0 && can2(t.x, t.y-1, t.x+1, t.y-1) && !visit[2][t.x][t.y-1])
			{
				visit[2][t.x][t.y-1] = true;
				//nodes.push(create(t.x, t.y-1, 2, t.step+1));
				nodes[head++] = node(t.x,t.y-1,2,t.step+1);
			}
			if(t.x-1 >= 0 && can1(t.x-1, t.y) && !visit[0][t.x-1][t.y])
			{
				visit[0][t.x-1][t.y] = true;
				//nodes.push(create(t.x-1, t.y, 0, t.step+1));
				nodes[head++] = node(t.x-1,t.y,0,t.step+1);
			}
			if(t.x+2 < R && can1(t.x+2, t.y) && !visit[0][t.x+2][t.y])
			{
				visit[0][t.x+2][t.y] = true;
				//nodes.push(create(t.x+2, t.y, 0, t.step+1));
				nodes[head++] = node(t.x+2,t.y,0,t.step+1);
			}
		}
	}
	if(best)
		cout << best << endl;
	else
		cout << "Impossible" <<endl;
	}
}
