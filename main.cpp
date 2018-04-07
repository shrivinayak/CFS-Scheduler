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
		
		myrbt->deletenode(thisnode->twin);
		myheap->removeMin();
		
	}
	myheap->heapify();
	
	return retval;
}
void scheduler::syncTime(int time){
	int param,remain;
	while(time>counter){
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
		
	}
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

	rbtnode* temp2 = myrbt->insert(JobID);

	//insert into heap
	myheap->insert(JobID,0,totaltime,temp2);

}

int main(int argc, char** argv){

	scheduler myscheduler; // create a scheduler object

	char *ptr,*ptr1,buff[100];
	int num;
	ifstream file; 

	//some book keeping
	if(argc<2){
		cout<<"Error: Not enough arguments"<<endl;
		exit(1);
	}

	file.open(argv[1]); // open input file 
	fout.open("output_file.txt"); //open output file
	


	for( std::string line; getline( file, line, '\n'); ){    


		//variables for string parsing
		int temp1,temp2;
		ptr = strcpy(buff,line.c_str());
		ptr = strtok(ptr,":");
		num = atoi(ptr);


		//schedule jobs until counter = command time
		myscheduler.syncTime(num);

        ptr = strtok(NULL,"(");

        // Insert new job
        if(strcmp(ptr+1,"Insert")==0){
        	ptr = strtok(NULL,",");
        	temp1 = atoi(ptr);
        	ptr = strtok(NULL,")");
        	temp2 = atoi(ptr);
        	myscheduler.insert(temp1,temp2);
        }

        // print jobs
        else if(strcmp(ptr+1,"PrintJob")==0){
        	ptr = strtok(NULL,")");
        	int i,flag=0;
        	for(i=0;i<strlen(ptr);i++){
        		if(ptr[i]==',') {
        			flag=1;
        			break;
        		}
        	}

   	     	if(flag==1){
   	     		// print range of jobs
   	     		ptr1 = strtok(ptr,",");
   	     		ptr += strlen(ptr1)+1;
				myscheduler.printjob(atoi(ptr1),atoi(ptr));

        	}
        	else{
        		// print single job
   	    		myscheduler.printjob(atoi(ptr));
        	}


         }
         // print next job
        else if(strcmp(ptr+1,"NextJob")==0)
        	myscheduler.nextjob(atoi(strtok(NULL,")")));

        // print previous job
        else if(strcmp(ptr+1,"PreviousJob")==0)
        	myscheduler.prevjob(atoi(strtok(NULL,")")));
        //error case
        else
        	fout<<"unknown operation"<<endl;


    }

    // End of input file. schedule all the pending jobs
    while(myscheduler.ifjob()){
    	myscheduler.dispatch(100);
    }
    

    //close file handlers
	file.close();
	fout.close();

	return 0;

}