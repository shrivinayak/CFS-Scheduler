// #include "rbt.cpp"
enum color {RED, BLACK};

struct rbtnode{
    
    int jobid;
    bool color;
    rbtnode *left, *right, *parent;
    heapnode* twin;

    rbtnode(int jobid){
       this->jobid = jobid;
       parent=left=right=NULL;
    }

};


// class of redblack tree
class rbt{

private:
    rbtnode *root;
protected:

    void rotateleft(rbtnode *&, rbtnode *&); // rotate left operation of rbt
    void rotateright(rbtnode *&, rbtnode *&); // rotate right operation of rbt
    void fixtree(rbtnode *&, rbtnode *&); // fix the tree to regain rbt properties
public:
    rbt(); // constructor
    rbtnode* insert(const int &n); // insert new node into the tree
    rbtnode* findnode(int jobid); // find a node in the tree 
    void nextnode(int jobid); // find the next lowest node wrt inorder traversal
    void prevnode(int jobid); // find the previous largest node wrt inorder traversal
    
    void inorder(int, int); // find a range of job id's in range low,high

    void deletenode(rbtnode*); // delete a node from tree

    void fixviolation(rbtnode*); // fix violation caused due to delete
    void rightrotate(rbtnode *p); // rotate right after delete
    void leftrotate(rbtnode *p); // rotate left after elete

};

//constructor 
rbt::rbt(){
    root = NULL;
}

