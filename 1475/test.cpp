#include <iostream>
#include <queue>
#include <string>
#include <stdio.h>
#include <string.h>
using namespace std;

 

const int MAX = 20 + 5;
char map[MAX][MAX];
bool visPerson[MAX][MAX];
bool visBox[MAX][MAX];
int R, C;

int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
char pushes[4] = {'E', 'W', 'S', 'N'};
char walks[4] = {'e', 'w', 's', 'n'};
string path;

 

struct NODE
{
    int br, bc;   // 箱子的位置
    int pr, pc;   // 人的位置
    string ans;   // 当前操作
};

 

bool InMap(int r, int c)
{
    return (r >= 1 && r <= R && c >= 1 && c <= C);
}

 

// 人到箱子
// (sr,sc)：人的位置
// (er,ec)：箱子的前一个位置
// (br,bc)：箱子的位置
// ans：路径
bool Bfs2(int sr, int sc, int er, int ec, int br, int bc, string & ans)
{
    memset(visPerson, false, sizeof(visPerson));
    queue<NODE> q;
    NODE node, tmpNode;
    node.pr = sr;
    node.pc = sc;
    node.ans = "";
    q.push(node);
 
    // 此处保证不从箱子上走过
    visPerson[br][bc] = true;
 
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        // 如果能够走到箱子，立即返回
        if (node.pr == er && node.pc == ec)
        {
            ans = node.ans;
            return true;
        }
        // 已访问
        if (visPerson[node.pr][node.pc])
        {
            continue;
        }
        visPerson[node.pr][node.pc] = true;
        // 向四个方向走
        for (int i=0; i<4; i++)
        {
            int nr = node.pr + dir[i][0];
            int nc = node.pc + dir[i][1];
            if (InMap(nr, nc) && !visPerson[nr][nc] && map[nr][nc] != '#')
            {
                tmpNode.pr = nr;
                tmpNode.pc = nc;
                tmpNode.ans = node.ans + walks[i]; 
                q.push(tmpNode);
            }
        }
    }
    return false;
}

 

// 箱子到终点
// (sr,sc)：人的位置
// (br,bc)：箱子的位置
bool Bfs1(int sr, int sc, int br, int bc)
{
    memset(visBox, false, sizeof(visBox));
    queue<NODE> q;
    NODE node, tmpNode;
    node.pr = sr;
    node.pc = sc;
    node.br = br;
    node.bc = bc;
    node.ans = "";
    q.push(node);
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        if (visBox[node.br][node.bc])
        {
            continue;
        }
        visBox[node.br][node.bc] = true;

        if (map[node.br][node.bc] == 'T')
        {
            path = node.ans;
            return true;
        }
        for (int i=0; i<4; i++)
        {
            // 箱子的下一个位置
            int nextr = node.br + dir[i][0];
            int nextc = node.bc + dir[i][1];
            // 箱子的前一个位置
            int backR = node.br - dir[i][0];
            int backC = node.bc - dir[i][1];
            string ans = "";
            if (InMap(backR, backC) && InMap(nextr, nextc) && map[nextr][nextc] != '#'

                && map[backR][backC] != '#' && !visBox[nextr][nextc])
            {
                if (Bfs2(node.pr, node.pc, backR, backC, node.br, node.bc, ans))
                {
                    tmpNode.pr = node.br;
                    tmpNode.pc = node.bc;
                    tmpNode.br = nextr;
                    tmpNode.bc = nextc;
                    tmpNode.ans = node.ans + ans + pushes[i];
                    q.push(tmpNode);
                }
            }
        }
    }
    return false;
}

 

int main()
{
    int sr, sc;    // 起始点
    int br, bc;    // 箱子的位置
    int cases = 1;
    while (scanf("%d%d", &R, &C) && R && C)
    {
        for (int r=1; r<=R; r++)
        {
            for (int c=1; c<=C; c++)
            {
                cin >> map[r][c];
                if (map[r][c] == 'S')
                {
                    sr = r;
                    sc = c;
                }
                else if (map[r][c] == 'B')
                {
                    br = r;
                    bc = c;
                }
            }
        }
  
        path = "";
        (Bfs1(sr, sc, br, bc)) ? cout << "Maze #" << cases << endl << path << endl :
                                 cout << "Maze #" << cases << endl << "Impossible." << endl;

        cases++;
        cout << endl;
    }
    return 0;
}
