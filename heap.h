// #include "heap.cpp"
struct heapnode{

	int jobID,exec_time,total_time;
	struct rbtnode* twin;

	
};

class heap{
	/*
		stores root based on executed time. (min->max)
	*/
public:

	struct heapnode* root;
	int last;
	heapnode* insert(int, int, int,rbtnode*); // insert a new node into the heap.
	struct heapnode* removeMin(); // remove the item from top of the heap ie minimum executed time.
	void swapJob(struct heapnode* a,struct heapnode* b);
	void heapify();
	void updateMin(int exec_time);
	heap(int);
	void execute(int);
	~heap(){
		delete root;
	}
};

