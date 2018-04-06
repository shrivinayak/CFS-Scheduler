#include <iostream>
// #include "Timer.h"
#include <fstream>
#include <sys/time.h>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


#define BUFFER_SIZE 1000


ofstream fout;
#include "heap.h"
#include "rbt.h"
#include "heap.cpp"
#include "rbt.cpp"




class scheduler{
private:
	int counter;
	rbt* myrbt;
	heap* myheap;
protected:

public:
	void printjob(int JobID); //Print(jobID,executed_time,total_time) for given jobID
	void printjob(int JobIDlow,int JobIDhigh); //Print(jobID,executed_time,total_time) for given range of jobIDs

	void nextjob(int JobID); //Print the NextJob(jobID,executed_time,total_time) for next greatest job id
	void prevjob(int JobID); 
	void insert(int JobID, int time);
	scheduler();
	void syncTime(int time);
	int dispatch(int);
	int ifjob();

};

int scheduler::dispatch(int x){
	int retval = 0;

	heapnode* thisnode = &(myheap->root[1]);
	
	
	
	thisnode->exec_time+=x;
	// cout<<"dispatch "<<thisnode->jobID<<" totaltime="<<thisnode->total_time<<" exec_time"<<thisnode->exec_time<<endl;
	if(thisnode->total_time-thisnode->exec_time<=0){
		retval = thisnode->exec_time-thisnode->total_time;
		
		// cout<<"removed node: jobID="<<thisnode->jobID<<" total_time="<<thisnode->total_time<<" exec_time="<<thisnode->exec_time<<endl;
		// cout<<"retval="<<retval<<" total time="<<thisnode->total_time<<" exec_time="<<thisnode->exec_time<<endl;
		
		//overflow 
		//remove from rbt
		myrbt->deletenode(thisnode->twin);
		// myrbt->inorder(0,10000);
		//remove from heap
		struct heapnode* temp = myheap->removeMin();
		
	}
	// fout<<"Dispatched: "<<thisnode->jobID<<endl;
	// if(retval)
	myheap->heapify();
	
	return retval;
}
void scheduler::syncTime(int time){
	int param,remain;
	while(time>counter){
		// cout<<"time="<<time<<" counter="<<counter<<endl;
		if(time-counter < 5)
			param = time-counter;
		else
			param = 5;
		// param = (time-counter)<5?(time-counter):5;
		
		if(ifjob()){
			remain = dispatch(param);
			counter+=param-remain;
		}
		else
			counter=time;
		// if(remain !=0)
			// cout<<"scheduled for ="<<5-remain<<endl;
		
	}
	// fout<<"syncTime complete: time="<<time<<" count="<<counter<<endl;
}
scheduler::scheduler(){
		counter=0;
		myheap = new heap(BUFFER_SIZE);
		myrbt = new rbt;
		//create rbt
	}
void scheduler::printjob(int JobID){
	// fout<<"printjob1"<<JobID;

	myrbt->findnode(JobID);
}

void scheduler::printjob(int JobIDlow,int JobIDhigh){
	// fout<<"printjob2"<<JobIDlow<<" "<<JobIDhigh;
	myrbt->inorder(JobIDlow,JobIDhigh);
	
}

void scheduler::nextjob(int JobID){

	// fout<<"nextjob";
	myrbt->nextnode(JobID);

}

int scheduler::ifjob(){
	return myheap->last;
}

void scheduler::prevjob(int JobID){

	// fout<<"prevjob ";
	myrbt->prevnode(JobID);

}

void scheduler::insert(int JobID,int totaltime){

	// cout<<"inserting node: jobID="<<JobID<<" totaltime="<<totaltime<<endl;
	//insert into rbt
	rbtnode* temp2 = myrbt->insert(JobID);

	//insert into heap
	heapnode* temp = myheap->insert(JobID,0,totaltime,temp2);

	//store pointers
	// temp->twin = temp2;

	//store ptr in heap
	// fout<<"temp: "<<temp<<endl;
	// temp2->twin = temp;


	// fout<<"insertjob\n";
	// fout<<"heap:"<<temp2->twin<<" rbt:"<<temp2<<endl;
}

int main(int argc, char** arg){

	scheduler myscheduler; // create a scheduler object

	char *ptr,*ptr1,buff[100];
	int num;
	ifstream file; 
	file.open("sample.txt"); 
	fout.open("output_file.txt");
	// fout<<"line: ";
	for( std::string line; getline( file, line, '\n'); ){    
		// fout<<"line: "<<line<<endl;
		int temp1,temp2;
		ptr = strcpy(buff,line.c_str());
		ptr = strtok(ptr,":");
		num = atoi(ptr);

		// fout<<"t"<<num<<" :";
		myscheduler.syncTime(num);

        // std::fout << ptr;
        ptr = strtok(NULL,"(");
        // fout << ++ptr<<endl;

        if(strcmp(ptr+1,"Insert")==0){
        	// fout<<"enterer print2";
        	ptr = strtok(NULL,",");
        	temp1 = atoi(ptr);
        	ptr = strtok(NULL,")");
        	temp2 = atoi(ptr);
        	myscheduler.insert(temp1,temp2);
        }
        else if(strcmp(ptr+1,"PrintJob")==0){
        	// fout<<"enterer print1";
        	ptr = strtok(NULL,")");
        	int i,flag=0;
        	// fout<<"strlen="<<strlen(ptr)<<endl;
        	for(i=0;i<strlen(ptr);i++){
        		if(ptr[i]==',') {
        			flag=1;
        			break;
        		}
        	}

   	     		// fout<<"here"<<endl;
   	     	if(flag==1){
   	     		ptr1 = strtok(ptr,",");
   	     		ptr += strlen(ptr1)+1;
				myscheduler.printjob(atoi(ptr1),atoi(ptr));

        	}
        	else{

   	     		// fout<<"here2"<<ptr<<endl;
        		myscheduler.printjob(atoi(ptr));
        	}


   	     		// fout<<"here3"<<endl;
   //      	ptr1 = strtok(ptr,",");
   //      	fout<<"\n----------------------ptr:"<<ptr<<"ptr1:"<<ptr1<<endl;
   //      	if(ptr1==NULL)
			// 	myscheduler.printjob(atoi(ptr));
			// else
			// 	myscheduler.printjob(atoi(ptr1),atoi(ptr+strlen(ptr1)+1));
         }

        else if(strcmp(ptr+1,"NextJob")==0)
        	myscheduler.nextjob(atoi(strtok(NULL,")")));
        else if(strcmp(ptr+1,"PreviousJob")==0)
        	myscheduler.prevjob(atoi(strtok(NULL,")")));
        else
        	fout<<"unknown operation"<<endl;

    }

    while(myscheduler.ifjob()){
    	// cout<<"last:"<<myscheduler.ifjob()<<endl;
    	myscheduler.dispatch(100);
    }
    
    // fout<<"end of program"<<endl;
	file.close();
	fout.close();

	return 0;

}