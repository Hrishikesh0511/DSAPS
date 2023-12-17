#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
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

    void clear() {
        // Implement this to release all the memory allocated and clear the treap.
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
        int index = lower_bound(val);
        return index;
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
        return lower_bound_recursive(root, val);
    }

    int lower_bound_recursive(node* current, T val) {
        if (current == NULL) {
            return 0;
        }
        if (val > current->key) {
            return 1 + getSize(current->left) + lower_bound_recursive(current->right, val);
        }
        else {
            return lower_bound_recursive(current->left, val);
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
        if (Root == NULL) {
            return {NULL, NULL};
        }

        if (getSize(Root->left) >= index) {
            auto subTrees = split_tree(Root->left, index);
            Root->left = subTrees.second;
            updateSize(Root);
            return {subTrees.first, Root};
        }
        else {
            auto subTrees = split_tree(Root->right, index - getSize(Root->left) - 1);
            Root->right = subTrees.first;
            updateSize(Root);
            return {Root, subTrees.second};
        }
    }
    node* merge(node* t1, node* t2) {
        if (t1 == NULL) {
            return t2;
        }
        if (t2 == NULL) {
            return t1;
        }
        //if t1 priority is more merge t2 with t1, root(t1)
        if (t1->priority > t2->priority) {
            t1->right = merge(t1->right, t2);
            updateSize(t1);
            return t1;
        }
        //else merge t1 with t2,t2 as root
        else {
            t2->left = merge(t1, t2->left);
            updateSize(t2);
            return t2;
        }
    }

    int getSize(node* node) {
        if (!node) return 0;
        return node->size;
    }

    void updateSize(node* current) {
        if (current != NULL) {
            current->size = 1 + getSize(current->left) + getSize(current->right);
        }
    }
};
class Solution {
public:
    void reverse(vector<int> &res,int start,int end){
        while(start<end){
            swap(res[start++],res[end--]);
        }
    }
    vector<int> countSmaller(vector<int>& nums) {
        srand(time(NULL));
        Treap<int> t;
        vector<int> res;
        for (int i=nums.size()-1;i>=0;i--){
            t.insert(nums[i]);
            res.push_back(t.lower_bound(nums[i]));
        }
        reverse(res,0,res.size()-1);
        return res;
    }
};