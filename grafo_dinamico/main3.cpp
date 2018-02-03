#include<iostream>
#include<map>


using namespace std;




class label{
public:
	int dato;
	int index;
	label():index(-1),dato(-2){}


};


int main(){
	map <int, label* > m;

	label a0,a1,a2;
	a0.dato=33;
	a1.dato=44;
	a2.dato=66;

	a0.index=0;
	a1.index=1;
	a2.index=2;
	m.insert(make_pair(0,&a0));
	m.insert(make_pair(1,&a1));
	m.insert(make_pair(2,&a2));
	
	typename map<int, label* >::iterator it;
	
	for(it=m.begin();it!=m.end();it++){
		cout<<it->first<<"--"<<it->second->index<<endl;
	}

	
	typename map<int, label* >::iterator it_1=m.find(1);
	typename map<int, label* >::iterator it_2=m.find(2);
	label *temp;
	
	temp=it_1->second;
	it_1->second=it_2->second;
	it_2->second=temp;
	
	
	for(it=m.begin();it!=m.end();it++){
		cout<<it->first<<"--"<<it->second->index<<endl;
	}



}
