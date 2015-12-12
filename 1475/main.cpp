#include <iostream>
#include <string.h>
#include <string>
#include <queue>
using namespace std;
const int maxn=21;
bool visbox[maxn][maxn],visper[maxn][maxn];
char map[maxn][maxn];
int dir[4][2] = { {0,1} , { 1, 0}, { 0, -1}, {-1, 0}};
char push[4] = {'E', 'S', 'W', 'N'};
char walk[4] = {'e', 's', 'w', 'n'};
int R,C,tr,tc;
class Node{
public:
	int pr,pc;
	int br,bc;
	string path;
};
bool inmap(int x,int y)
{
	if(x >=0 && x < R && y >= 0 && y < C && map[x][y] != '#')
		return true;
	return false;
}
bool bfs1(int pr, int pc, int br, int bc, int bbr, int bbc,string &path)
{
	queue<Node> q;
	Node node,tmp;
	node.pr = pr, node.pc = pc, node.br = br, node.bc = bc, node.path = "";
	q.push(node);
	memset(visper, false, sizeof(visper));
	while( !q.empty())
	{
		tmp = q.front();
		q.pop();
		if(visper[tmp.pr][tmp.pc]) continue;
		visper[tmp.pr][tmp.pc] = true;
		if(tmp.pr == bbr && tmp.pc == bbc) 
		{
			path = tmp.path;
			return true;
		}
		for(int i =0; i < 4; i++)
		{
			int nextpr = tmp.pr+dir[i][0],nextpc = tmp.pc+dir[i][1];
			if(inmap(nextpr, nextpc) && (nextpr != br || nextpc != bc) && !visper[nextpr][nextpc])
			{
				node.pr = nextpr,node.pc = nextpc;
				node.path = tmp.path + walk[i];
				q.push(node);
			}
		}
	}
	return false;
}
bool bfs2(int pr, int pc, int br, int bc, string &path)
{
	queue<Node> q;
	Node node, tmp;
	node.pr = pr, node.pc = pc, node.br = br, node.bc = bc, node.path = "";
	q.push(node);
	memset(visbox, false, sizeof(visbox));
	while(!q.empty())
	{
		tmp = q.front();
		q.pop();
		if(visbox[tmp.br][tmp.bc]) continue;
		visbox[tmp.br][tmp.bc] = true;
		if(tmp.br == tr && tmp.bc == tc)
		{
			path = tmp.path;
			return true;
		}
		for(int i = 0; i < 4; i++)
		{
			int nextbr = tmp.br + dir[i][0], nextbc = tmp.bc + dir[i][1];
			int backbr = tmp.br - dir[i][0], backbc = tmp.bc - dir[i][1];
			if(inmap(nextbr,nextbc)&&inmap(backbr,backbc)&&!visbox[nextbr][nextbc])
			{
				if(bfs1(tmp.pr, tmp.pc, tmp.br, tmp.bc,backbr, backbc, node.path))
				{
					node.pr = tmp.br, node.pc = tmp.bc;
					node.br = nextbr, node.bc = nextbc;
					node.path = tmp.path + node.path + push[i];
					q.push(node);
				}
			}
		}
	}
	return false;
}
int main()
{
	int pr,pc,br,bc;
	string path;
	cin>>R>>C;
	for(int i = 0; i < R ; i ++ )
		cin >> map[i];
	for(int i = 0; i < R ; i ++ )
		for(int j = 0; j < C; j++ )
		{
			if(map[i][j] == 'T')
			{
				tr = i,tc = j;
			}
			else if(map[i][j] == 'S')
			{
				pr = i, pc = j;
			}
			else if(map[i][j] == 'B')
			{
				br = i, bc = j;
			}
		}
	bfs2(pr, pc, br, bc, path)?cout<<path<<endl:cout<<"Impossible\n";
}
