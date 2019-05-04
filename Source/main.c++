#include <iostream>
#include "classes.h"
#include "text.h"

using namespace std;

int main(void){
	int N,M,L,good_thrsh,bad_thrsh;
	srand( time(NULL) ); 					//Randomize seed initialization
	cout<<"Enter number of creatures per society:"<<endl;
	cin>>N;
	if(N<=0){
		cout<<"Please enter positive number.."<<endl;
		cin>>N;
	}
	cout<<"Enter number of battle actions:"<<endl;
	cin>>M;
	cout<<"Enter creature lifespan:"<<endl;
	cin>>L;
	if(L<=0){
		cout<<"Please enter positive number.."<<endl;
		cin>>L;
	}
	cout<<"Enter healthy condition for good creatures:"<<endl;
	cin>>good_thrsh;
	cout<<"Enter healthy condition for bad creatures:"<<endl;
	cin>>bad_thrsh;
	
	creature_society MinasTirith(N,M,L,good_thrsh,bad_thrsh);	//Build society
	MinasTirith.action();						//Run society
	if(MinasTirith.no_of_good() == N && MinasTirith.no_of_zombies()!=MinasTirith.no_of_good()) cout<<"\nGood Dominates in the World!\n"<<endl;	
	else if(MinasTirith.no_of_zombies() == N) cout<<"This is a dead society.\n"<<endl;
	else cout<<"Try again to improve the world!\n"<<endl;	
	
return 0;
}
