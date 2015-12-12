#include <iostream>
#include <vector>
using namespace std;

class base{
public:
	base() { cout<<"construct"<<endl; }
	base(const base& rhs) { cout<<"rhsc"<<endl; *this = rhs; }
	~base() { cout<<"destroy"<<endl; }
};
void f(base b) {
}
class big_block{
public:
	int n[40000];
}temp;
int main() {
	vector<big_block> v;
	cout<<sizeof(big_block)<<endl;
	for(int i = 0; i < 1000; i++)
		v.push_back(temp);
	for(int i = 0; i < 1000; i++)
		v.pop_back();
	cout << v.size()<<endl;
	cout << v.capacity()<<endl;
	for(int i = 0; i < 1000; i++)
		v.push_back(temp);
	cout << v.size()<<endl;
	cout << v.capacity()<<endl;
	while(1) {
	}
}
