#include <queue>
#include <iostream>
#include <unistd.h>
using namespace std;
class t
{
public:
	int i;
	t(){}
	t(int ii):i(ii) {}
};
int main()
{
	queue<t*> q;
	for(int i =0; i < 50000; i++)
	{
		for(int j = 0; j < 10000; j++)
			{
				q.push(new t(1));
			}
		usleep(1);
		for(int j = 0; j < 10000; j++)
		{
				//usleep(1);
				t *tp = q.front();
				q.pop();
				delete tp;
		}
	}
	cout<<"finish\n";
}
