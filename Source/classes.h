#include <iostream>
#include "text.h"
#include <stdio.h>
#include <stdlib.h> 

using namespace std;

//////////////////////////////////////////////CREATURE CLASS////////////////////////////////////////////////////////////

class creature{
private:
	string name;			//name of creature
	int lifespan;			//Default health of creature
	int location;			//Location of the creature in the society(in the array of creatures)
	creature*** SocietyPtr;		//Pointer to the society that the creature belongs
public:
	creature(string i, int j,int k,creature*** l):name(i),lifespan(j),location(k),SocietyPtr(l){
		cout<<"Creature "<<name<<location<<" (HP:"<<lifespan<<")"<<" created!"<<endl;
	}
	virtual ~creature(){};

	string return_name(){ return name; }		///////////////////
	int return_lifespan(){ return lifespan; }	//    ACCESSORS  //
	int return_location(){ return location; }	///////////////////
	void raise_lifespan(){ lifespan+=1; }
	creature*** return_SocietyPtr(){ return SocietyPtr; }

	void print_name(void){ cout<<name<<location<<" (HP:"<<lifespan<<")"<<endl; };
	virtual creature* clone(creature** arrayptrtocreatures)=0;
	virtual bool is_a_good(void)=0;				//Returns sign that creature is good or bad
	virtual bool is_healthy(void)=0;			//Returns sign that creature is healthy or not (HP>threshold)
	bool is_a_zombie(void){					//Returns sign that creature is a zombie or not
		if(lifespan<=0) return 1;
		else return 0; }		
	void beat(void){ 
		if(!is_a_zombie()){ 
			lifespan-=1;
			cout<<"Creature "<<name<<location<<" has just been beat!"<<endl;
		}	
	}
	virtual void bless(void)=0;
};

/////////////////////////////////////////////GOOD CREATURE CLASS//////////////////////////////////////////////////////////////

class good_creature:public creature{
private:
	int threshold;
public:
	good_creature(string i, int j,int good_thrsh,int k,creature*** l):creature(i,j,k,l),threshold(good_thrsh){};
	//Copy constructor of good creature:
	good_creature( good_creature& p2):creature(p2.return_name(),p2.return_lifespan(),p2.return_location()+1,p2.return_SocietyPtr()){}; 
	~good_creature(){cout<<"Destroying "<<return_name()<<return_location()<<" creature!"<<endl;};

	creature* clone(creature** arrayptrtocreatures){
		int temp=return_location()+1;	
		delete arrayptrtocreatures[temp];			//Deleting next creature..
		arrayptrtocreatures[temp]=new good_creature(*this);	//Cloning this creature..
		return arrayptrtocreatures[temp];
	}

	void bless(void){
		if(!is_a_zombie()){	
			raise_lifespan();
			cout<<"Creature "<<return_name()<<return_location()<<" has just been blessed!"<<endl;
		}
	}
	bool is_healthy(void){ if(return_lifespan()>threshold) return 1; else return 0; }
	bool is_a_good(void){return true;} 
};

///////////////////////////////////////////////BAD CREATURE CLASS/////////////////////////////////////////////////////////////

class bad_creature:public creature{
private:
	int threshold;
public:
	bad_creature(string i,int j,int bad_thrsh,int k,creature*** l):creature(i,j,k,l),threshold(bad_thrsh){};
	//Copy constructor of bad creature:
	bad_creature( bad_creature& p2):creature(p2.return_name(),p2.return_lifespan(),p2.return_location()+1,p2.return_SocietyPtr()){}; 
	~bad_creature(){cout<<"Destroying "<<return_name()<<return_location()<<" creature!"<<endl;};
	
	creature* clone(creature** arrayptrtocreatures){
		int temp=return_location()+1;
		delete arrayptrtocreatures[temp];		//Deleting next creature..
		arrayptrtocreatures[temp]=new bad_creature(*this);//Cloning this creature..
		return arrayptrtocreatures[temp];
	}

	void bless(void){
		if(!is_a_zombie()){
			this->raise_lifespan();
			cout<<"Creature "<<return_name()<<return_location()<<" has just been blessed!"<<endl;
		}
	}
	bool is_healthy(void){ if(return_lifespan()>threshold) return 1; else return 0; }
	bool is_a_good(void){return false;}

};

//////////////////////////////////////////////CREATURE SOCIETY CLASS///////////////////////////////////////////////////////////

class creature_society{
private:
	int slots;				//Creature seats in society
	creature* ptr;				//pointer to a creature
	creature** arrayptrtocreatures;		//array of pointers to creatures
	creature*** QQ;				//Pointer to society
	int numberofactions;			//Number of actions
public:
	creature_society(int N,int M,int L,int good_thrsh,int bad_thrsh):slots(N),numberofactions(M){
		QQ=&arrayptrtocreatures;
		int a;
		arrayptrtocreatures=new creature* [slots];
		for(int i=0;i<slots;i++){
			a=rand()%2;			//Creating randomly good or bad creature
			if(a==0) ptr=new good_creature(GoodNames[(rand() % 10)],L,good_thrsh,i,QQ);
			else ptr=new bad_creature(BadNames[(rand() % 10)],L,bad_thrsh,i,QQ);
			arrayptrtocreatures[i]=ptr;	//Inserting every pointer to creature to the array(society)
		}
		cout<<"\nCreature society created!\n"<<endl;
	};
	~creature_society(){ 
		for(int i=0;i<slots;i++){		//Freeing the array of pointers to creatures at the end of the program
			delete arrayptrtocreatures[i];
		}	
		delete arrayptrtocreatures;
	};

	void print_society(void){
		for(int i=0;i<slots;i++){
			arrayptrtocreatures[i]->print_name();
		}
	}
	void hit_creature(creature *y){   y->beat(); }; 
	void bless_creature(creature *y){ y->bless(); };
	void clone_next(creature *y){ 	  y=y->clone(arrayptrtocreatures); };
	void clone_zombies(creature *y,int i){
		while(i!=slots-1){	
			if(arrayptrtocreatures[i+1]->is_a_zombie()) clone_next(y);	//While next creature is in zombie mode , keep cloning
			i++;
		}
	}

	int no_of_good(void){	//Determing number of good creatures
		int sum=0;
		for(int i=0;i<slots;i++){
			if(arrayptrtocreatures[i]->is_a_good()) sum+=1; 
		}
		return sum;
	}
	
	int no_of_bad(void){	//Determining number of bad creatures
		int sum=0;
		for(int i=0;i<slots;i++){
			if(!(arrayptrtocreatures[i]->is_a_good())) sum+=1;
		}
		return sum;
	}	

	int no_of_zombies(void){//Determing number of zombies
		int sum=0;
		for(int i=0;i<slots;i++){
			if(arrayptrtocreatures[i]->is_a_zombie()) sum+=1;
		}
		return sum;
	}

	void action(void){	
		int a=0;
		for(int i=0;i<numberofactions;i++){
			a=rand()%2;		//50% hit, 50% bless
			int b=rand()%slots;	//Action affects a random creature in the society
			if(a==0) hit_creature(arrayptrtocreatures[b]);
			else {
				bless_creature(arrayptrtocreatures[b]);
				if(b!=slots-1){	//If creature isn't at the end , clone it properly
					if(arrayptrtocreatures[b]->is_a_good() && arrayptrtocreatures[b]->is_healthy()) 
					clone_next(arrayptrtocreatures[b]);
					else if(!(arrayptrtocreatures[b]->is_a_good()) && arrayptrtocreatures[b]->is_healthy()) 					clone_zombies(arrayptrtocreatures[b],b);
				}
			}
				
		}
		cout<<endl;	
		print_society();
		cout<<endl;
	}
	
};
	
	
