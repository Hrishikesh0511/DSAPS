//look at slice()
//clear()
//upper_bound()
//merge()
//indexOf()
//count()
//to_array()
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#define endl '\n'
using namespace std;

template<typename T>
class Treap {
public:
    class node {
    public:
        T key;
        int priority;
        node* left;
        node* right;
        int size;
        node(T data) {
            this->key = data;
            this->priority = rand() % 10000;
            this->left = NULL;
            this->right = NULL;
            this->size = 1;
        }
    };

    node* root;

    Treap() {
        root = NULL;
    }

    bool empty() {
        return (root == NULL);
    }

    int size() {
        if (root == NULL) return 0;
        return root->size;
    }
    void clear(node* root) {
         //deleting all nodes by post order traversal
        if(!root){
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }
    void clear() {
        // Implement this to release all the memory allocated and clear the treap.
        clear(root);
        root=NULL;
    }

    int insert(T val) {
        //find the index at which you need to insert
        //Split the treap at that index into two treaps
        //Merge the left treap with newnode 
        //now merge the resultant treap with right treap
        int index = lower_bound(val);   //because this gives the all numbers less than the value which is my index
        auto parts = split(index);
        node* newnode = new node(val);
        node* t1 = parts.first;
        node* t2 = parts.second;
        root = merge(merge(t1, newnode), t2);
        return index;
    }
    bool erase(int index){
        if(index<0 || index>=size()){
            return T();
        }
        //split the node at that index
        //now split the right part by 1 index
        //now merge left part and second part of right part
        //free that first part of rightpart
        auto parts=split(index);
        auto rightpart=split_tree(parts.second,1);
        root=merge(parts.first,rightpart.second);
        delete rightpart.first;
        return true;
    }
    int indexOf(T val){
        //get some index using lower_bound
        //check if that index contains the actual value by using atIndex function
        //else return -1
        if(!root) return -1;
        int trialIndex=lower_bound(val);
        if(val==atIndex(trialIndex)){
            return trialIndex;
        }
        return -1;
    }
    T atIndex(int index){
        if(index<0 || index>=size()){
            return T();
        }
        //split the node at that index
        //now split the right part by index
        //get the value and merge them again
        auto parts=split(index);
        auto rightpart=split_tree(parts.second,1);
        int value=rightpart.first->key;
        root=merge(parts.first,merge(rightpart.first,rightpart.second));
        return value;
    }
    int lower_bound(T val) {
        return lower_bound(root, val);
    }

    int lower_bound(node* current, T val) {
        if (!current) {
            return 0;
        }
        if (val>current->key) {
            return 1 + getSize(current->left) + lower_bound(current->right, val);
        }
        else {
            return lower_bound(current->left, val);
        }
    }
    int upper_bound(T val){
        return upper_bound(root, val);
    }
    int upper_bound(node *current,T val){
        if(!current){
            return 0;
        }
        if (val>=current->key) {
            return 1 + getSize(current->left) + upper_bound(current->right, val);
        }
        else {
            return upper_bound(current->left, val);
        }
    }
    bool erase(int first,int last){
        if(first<0 || last<0 || first>last || first>=size() || last>=size()){
            return false;
        }
        //split the treap by first index
        //now take the rightpart 
        //split rightpart by last index()
        //now take the second part and merge it with left part of the treap
        auto parts1=split(first);
        auto parts2=split_tree(parts1.second,last-first+1);
        root=merge(parts1.first,parts2.second);
        return true;
    }
    pair<node*, node*> split(int index) {
        return split_tree(root, index);
    }

    pair<node*, node*> split_tree(node* Root, int index) {
        if (Root==NULL) {
            return {NULL,NULL};
        }

        if (getSize(Root->left)>=index) {
            auto subTrees=split_tree(Root->left, index);
            Root->left=subTrees.second;
            updateSize(Root);
            return {subTrees.first,Root};
        }
        else {
            auto subTrees=split_tree(Root->right,index-getSize(Root->left)-1);
            Root->right=subTrees.first;
            updateSize(Root);
            return {Root,subTrees.second};
        }
    }
    Treap *slice(int first,int last){
         if(first<0 || last<0 || first>last || first>=size() || last>=size()){
            return NULL;
        }
        auto parts1=split(first);
        auto parts2=split_tree(parts1.second,last-first+1);
        Treap *newTreap=new Treap();
        newTreap->root=parts2.first;
        root=parts2.first;
        return newTreap;
    }
    node* merge(node* t1, node* t2) {
        if (!t1) {
            return t2;
        }
        if (!t2) {
            return t1;
        }
        //if t1 priority is more merge t2 with t1, root is (t1)
        if (t1->priority>t2->priority) {
            t1->right = merge(t1->right, t2);
            updateSize(t1);
            return t1;
        }
        //else merge t1 with t2,root is t2
        else {
            t2->left = merge(t1, t2->left);
            updateSize(t2);
            return t2;
        }
    }
    // void print_treap(node *root){
    //     if(!root) return;
    //     print_treap(root->left);
    //     cout<<root->key<<" ";
    //     print_treap(root->right);
    // }
    // void print(){
    //     print_treap(root);
    // }
    int getSize(node* node) {
        if (!node) return 0;
        return node->size;
    }
    int count(T val) {
        return count(root,val);
    }
    int count(node *root,T val){
        if(!root){
            return 0;
        }
        int cnt= count(root->left,val)+count(root->right,val);
         if(root->key==val){
            cnt++;
        }
        return cnt;
    }
    void inorder(node* root,vector<int> &res){
        if(!root) return ;
        inorder(root->left,res);
        res.push_back(root->key);
        inorder(root->right,res);
    }
    vector<T> to_array(){
        vector<T> res;
        inorder(root,res);
        return res;
    }
    void updateSize(node* current) {
        if (current != NULL) {
            current->size = 1 + getSize(current->left) + getSize(current->right);
        }
    }
};

int main() {
        ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    Treap<int> t;
    int choice=1;
    int val;
    int index,first,last;
    while (choice){
        cin>>choice;
        switch (choice) {
            case 1:
                cout<<boolalpha<<t.empty()<<endl;
                break;
            case 2:
                cout<<t.size()<<endl;
                break;
            case 3:
                t.clear();
                break;
            case 4:
                cin>>val;
                cout<<t.insert(val)<<endl;
                break;
            case 5:
                cin>>index;
                cout<<boolalpha<<t.erase(index)<<endl;
                break;
            case 6:
                cin>>val;
                cout<<t.indexOf(val)<<endl; 
                break;
            case 7:
                cin>>index;
                cout<<t.atIndex(index)<<endl;
                break;
            case 10:
                cin>>first>>last;
                cout<<boolalpha<<t.erase(first,last)<<endl;
                break;
            case 11:
                cin>>first>>last;
                Treap<int> *temp;
                temp=t.slice(first,last);
                break;
            case 12:
                cin>>val;
                cout<<t.lower_bound(val)<<endl;
                break;
            case 13:
                cin>>val;
                cout<<t.upper_bound(val)<<endl;
                break;
            case 14:
                cin>>val;
                 cout<<t.count(val)<<endl;
                break;
            case 15:
                vector<int> res(t.to_array());
                for(auto it:res){
                    cout<<it<<" ";
                }
                cout<<endl;
                break;
        }

    } 

    return 0;
}


