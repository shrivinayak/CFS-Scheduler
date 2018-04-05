// #include "heap.h"


heap::heap(int size){
	root = new heapnode[size];
	last = 0;
}


void heap::execute(int x){

	root[1].exec_time+=x;
	
	heapify();
}
void heap::swapJob(struct heapnode* a,struct heapnode* b){

	int jobID,exec_time,total_time;
	rbtnode *tmp1,*tmp2;
	// heapnode* tmp;
	jobID = a->jobID;
	a->jobID = b->jobID;
	b->jobID = jobID;

	exec_time = a->exec_time;
	a->exec_time = b->exec_time;
	b->exec_time = exec_time;

	total_time = a->total_time;
	a->total_time = b->total_time;
	b->total_time = total_time;

	tmp1 = a->twin;
	tmp2 = b->twin;

	tmp1->twin = b;
	tmp2->twin = a;

	tmp1 = a->twin;
	a->twin = b->twin;
	b->twin = tmp1;

	//yet to swap twin pointer
}

heapnode* heap::insert(int jobID,int exec_time,int total_time,rbtnode* p){
	
	int ptr = ++last;

	// rbtnode* temp;
	root[last].jobID = jobID;
	root[last].exec_time = exec_time;
	root[last].total_time = total_time;
	root[last].twin = p;

	// temp = root[ptr].twin;
	// temp->twin = &root[ptr];
	p->twin = &root[ptr];
	// fout<<"twin:"<<temp->twin<<endl;
	

	while(ptr>1){
		if(root[ptr].exec_time < root[ptr/2].exec_time){
			swapJob(&root[ptr],&root[ptr/2]);
			ptr = ptr/2;
			// fout<<"exchange"<<endl;
		}
		else
			break;
	}
	// printf("%d %d %d\n",jobID,exec_time,total_time);
	// fout<<"inserted at "<<last<<" shifted to "<<pos;
	return &root[ptr];
}

void heap::updateMin(int exec_time){
	root[1].exec_time = exec_time;
	heapify();
}

void heap::heapify(){
	int i=1,j;
	while(1){
		if(i*2>last )
			break;
		if(i*2+1>last)
			j=i*2;
		else
			j = root[i*2].exec_time < root[i*2+1].exec_time ? i*2:i*2+1; 


		if(root[j].exec_time < root[i].exec_time){
			swapJob(&root[i],&root[j]);
			i = j;
		}
		else
			break;
		
	}
	// if(i==1)
	// 	fout<<"heapified"<<endl;
}

struct heapnode* heap::removeMin(){
	int i=1;

	struct heapnode *result = new heapnode;

	result->jobID = root[i].jobID;
	result->exec_time = root[i].exec_time;
	result->total_time = root[i].total_time;

	root[i].jobID = root[last].jobID;
	root[i].exec_time = root[last].exec_time;
	root[i].total_time = root[last].total_time;

	last--;
	heapify();
	return result;
}