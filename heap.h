
//structure declaration for heap nodes.
struct heapnode{

	int jobID,exec_time,total_time;
	struct rbtnode* twin;	
};


//Class of heap data structure

class heap{
	public:
	struct heapnode* root;
	int last; // keeps track of last element in the heap array
	int size; // keeps track of total size allocated for heap array

	heapnode* insert(int, int, int,rbtnode*); // insert a new node into the heap.

	struct heapnode* removeMin(); // remove the item from top of the heap ie minimum executed time.

	void swapJob(struct heapnode* a,struct heapnode* b); // swap two nodes of the heap
	
	void heapify(); // regain heap property

	void updateMin(int exec_time); // update exec_time of root node and heapify the structure

	heap(int); // constructor declaration
	
	void execute(int); // execute a job
	
	~heap(){ // destructor declaration
		delete root;
	}
};

