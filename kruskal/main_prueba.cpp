#include <iostream>

#include<set>


using namespace std;

struct x{
	int a;
};

int main(){
	
	set<int> a;
	a.insert(5);
	a.insert(15);
	a.insert(25);
	bool c= a.find(15)!=a.end();
	cout<<c<<endl;
	
}
