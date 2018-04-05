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
    void rotateleft(rbtnode *&, rbtnode *&);
    void rotateright(rbtnode *&, rbtnode *&);
    void fixtree(rbtnode *&, rbtnode *&);
public:
    rbt();
    rbtnode* insert(const int &n);
    rbtnode* findnode(int jobid);
    void nextnode(int jobid);
    void prevnode(int jobid);
    
    void inorder(int, int);

    void deletenode(rbtnode*);
    void fixviolation(rbtnode*);
    void rightrotate(rbtnode *p);
    void leftrotate(rbtnode *p);

};

//constructor 
rbt::rbt(){
    root = NULL;
}

