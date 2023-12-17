#include<iostream>
#include<vector>
#include<string>
#include<utility>
using namespace std;
template<class T1,class T2>
class ordered_map{
    public:
        class avlnode{
            public:
                avlnode *left;
                avlnode *right;
                T1 key;
                T2 value;
                int height;
                avlnode(avlnode *left,avlnode *right,T1 key,T2 value,int height){
                    this->left = left;
                    this->right = right;
                    this->key = key;
                    this->value = value;
                    this->height=height;
                }
        };
        avlnode *root=NULL;
        int mpsize=0;
        int height(avlnode *node){
            if(node==NULL){
                return 0;
            }
            return node->height;
        }
        bool insert(T1 key,T2 value){
            if(searchForKey(root,key)) return false;
            else{
                mpsize++;
                root=insertNode(root,key,value);
                return true;
            }
            
        }
        int getBalanceFactor(avlnode *node){
            if(!node){
                return 0;
            }
            else{
                return(height(node->left)-height(node->right));
            }
        }
         bool contains(T1 key){
           return searchForKey(root,key);
        }
        bool searchForKey(avlnode *root,T1 key){
            if(root==NULL) return false;
            else if(root->key<key) return searchForKey(root->right,key);
            else if(key<root->key) return searchForKey(root->left,key);
            else return true;
            // return false;
        }
        avlnode *insertNode(avlnode *root,T1 key,T2 value){
            if(root==NULL){
                avlnode *node =new avlnode(NULL,NULL,key,value,1);
                return node;
            }
            else if(root->key<key){
                root->right=insertNode(root->right,key,value);
            }
            else if(key<root->key){
                root->left=insertNode(root->left,key,value);
            }
            root->height=1+max(height(root->left),height(root->right));
            int bf=getBalanceFactor(root);
            if(1<bf && root->left&& key<root->left->key){
                //right rotate
                // cout<<"right rotate"<<endl;
                return rightrotate(root);
            }
            else if(bf<-1 &&root->right&& key>root->right->key){
                //left rotate
                // cout<<"left rotate"<<endl;
                return leftrotate(root);
            }
            else if(1<bf &&root->left&& key>root->left->key){
                // cout<<"left-right"<<key<<endl;
                //left-right rotate
                root->left=leftrotate(root->left);
                return rightrotate(root);
            }
            else if(bf<-1 &&root->right&& key<root->right->key){
                // cout<<"right-left"<<endl;
                //right-left rotate
                root->right= rightrotate(root->right);
                return leftrotate(root);
            }
            return root;
        }
        bool erase(T1 key){
            if(!searchForKey(root,key)){
                return false;
            }
            mpsize--;
            root=eraseNode(root,key);
            return true;
        }
        avlnode *inorderPredeccessor(avlnode *root){
            avlnode* curr=root;
            while(curr->right){
                curr=curr->right;
            }
            return curr;
        }
        avlnode *eraseNode(avlnode *root,T1 key){
            if (root == NULL){
            return root;}
             if (root->key<key){
            root->right = eraseNode(root->right, key);}
            else if (key < root->key){
            root->left = eraseNode(root->left, key);}
            else
            { 
            if(root->left!=NULL && root->right!=NULL){
                //if both children are available
                avlnode *temp=inorderPredeccessor(root->left);
                root->key=temp->key;
                root->left=eraseNode(root->left,temp->key);
            }
            else{
                avlnode *temp;
                if(root->left==NULL){
                    temp=root->right;
                }
                else if(root->right==NULL){
                    temp=root->left;
                }
                if(temp==NULL){
                    temp=root;
                    root=NULL;    
                }
                else{
                    *root=*temp;
                }
                free(temp);
            }
            }
            if(root==NULL){return NULL;}
            root->height=1+max(height(root->left),height(root->right));
            int bf=getBalanceFactor(root);
            if(1<bf && getBalanceFactor(root->left) >= 0){
                //right rotate
                return rightrotate(root);
            }
            else if(bf<-1 && getBalanceFactor(root->right) <= 0){
                //left rotate
                return leftrotate(root);
            }
            else if(1<bf && getBalanceFactor(root->left) < 0){
                //left-right rotate
                root->left=leftrotate(root->left);
                return rightrotate(root);
            }
            else if(bf<-1 && getBalanceFactor(root->right) > 0){
                //right-left rotate
                root->right= rightrotate(root->right);
                return leftrotate(root);
            }
            return root;
            }

        T2& operator[](T1 key){
        T2 t=T2();
            if(!contains(key)){
                insert(key,T2());
                avlnode *temp=root;
                while(temp!=NULL){
                    if(temp->key<key){
                        temp=temp->right;
                    }
                    else if(key<temp->key){
                        temp=temp->left;
                    }
                    else{
                        return temp->value;
                    }
                }
            }
            else{
                avlnode *temp=root;
                 while(temp!=NULL){
                    if(temp->key<key){
                        temp=temp->right;
                    }
                    else if(key<temp->key){
                        temp=temp->left;
                    }
                    else{
                        return temp->value;
                    }
                }
            }
            return t;
        }
        avlnode *leftrotate(avlnode *root){
            avlnode *y=root->right;
            avlnode *x=root;
            avlnode* temp=y->left;
            y->left=x;
            x->right=temp;
            //heights
            x->height=1+max(height(x->left),height(x->right));
            y->height=1+max(height(y->left),height(y->right));
            return y;
        }
        avlnode *rightrotate(avlnode *root){
            avlnode *z=root;
            avlnode *y=root->left;
            avlnode *temp=y->right;
            y->right=z;
            z->left=temp;
            //heights
            z->height=1+max(height(z->left),height(z->right));
            y->height=1+max(height(y->left),height(y->right));
            return y;
        }
        void inOrder(avlnode *root,vector<T1 > &res)  
        {
        if(root != NULL)  
        {   
        inOrder(root->left,res);
         res.push_back(root->key); 
        inOrder(root->right,res);  
        }  
        }
        void postOrderDelete(avlnode *root){
            if(root==NULL) return ;
            postOrderDelete(root->left);
            postOrderDelete(root->right);
            delete root;
        }
        int size(){
            return mpsize;
        }
        bool empty(){
            return (mpsize==0);
        }
        void clear(){
            postOrderDelete(root);
            (root)=NULL;
            mpsize=0;
        }
        vector<T1> keys(){
            vector<T1> res;  
            inOrder(root,res);
            return res;
        }
        pair<bool, T1> lower_bound(T1 key){
            avlnode *temp=root;
                T1 res=T1();
                 while(temp!=NULL){
                    if(temp->key<key){
                        temp=temp->right;
                    }
                    else if(key<temp->key){
                         res=temp->key;
                        temp=temp->left;
                    }
                    else{
                        return  {true,temp->key};
                    }
                }
                if(res==T1()){
                    return {false,T1()};
                }
                return {true,res};
        }
        pair<bool,T1> upper_bound(T1 key){
            avlnode *temp=root;
            avlnode *res=NULL;
                 while(temp!=NULL){
                    if(temp->key<key){
                        temp=temp->right;
                    }
                    else if(key<temp->key){
                        res=temp;
                        temp=temp->left;
                    }
                    else{
                        temp=temp->right;
                    }
                }
                if(res==NULL){
                    return {false,T1()};
                }
                return {true,res->key};
        }
};


int main(){
    ordered_map<int,int> mp;
    int choice=1;
    int key;
    int value;
    int flag=0;
    vector<int> arr;
    pair<bool,int> p;
    while(choice){
        cin>>choice;
        switch(choice){
            case 1:
                cout<<boolalpha<<mp.empty()<<endl;
                break;
            case 2:
                cout<<mp.size()<<endl;
                break;
            case 3:
                cin>>key;
                cout<<boolalpha<<mp.contains(key)<<endl;
                break;
            case 4:
                cin>>key>>value;
                cout<<boolalpha<<mp.insert(key,value)<<endl;
                break;
            case 5:
                cin>>key;
                cout<<boolalpha<<mp.erase(key)<<endl;
                break;
            case 6:
                cin>>key;
                cout<<mp[key]<<endl;
                break;
            case 7:
                mp.clear();
                break;
            case 8:
                arr=mp.keys();
                for(auto key:arr){
                    cout<<key<<endl;
                }
                break;
            case 9:
                cin>>key;
                p=mp.lower_bound(key);
                if(p.first){
                    cout<<boolalpha<<p.first<<endl;
                    cout<<p.second<<endl;
                }
                else{
                    cout<<boolalpha<<p.first<<endl;
                }
                break;
            case 10:
                cin>>key;
                p=mp.upper_bound(key);
                if(p.first){
                    cout<<boolalpha<<p.first<<endl;
                    cout<<p.second<<endl;
                }
                else{
                    cout<<boolalpha<<p.first<<endl;
                }
                break;
            default:
               flag=1;
               break; 
        }
        if(flag)    
        {
            break;
        }
        }
}
