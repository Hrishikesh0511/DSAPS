#include<iostream>
#include<cstdlib>
using namespace std;
template<typename T>
class skipList
{
    public:
    class node
    {
        public:
        T val;
        node* top;
        node* bottom; 
        node* next;
        node* prev;
        node()
        {
            this->top=NULL;
            this->bottom=NULL;
            this->next=NULL;
            this->prev=NULL;
        }
        node(T val)
        {
            this->val=val;
            this->top=NULL;
            this->bottom=NULL;
            this->next=NULL;
            this->prev=NULL;
        }
    };
    node** heads;
    int capacity;
    int level;
    int maxlevel;
    skipList()
    {
    level=0;
    capacity=1000;
    maxlevel=0;
    heads=new node*[capacity];
    node *newnode=new node();
    heads[0]=newnode;
    node *temp=newnode;
    for(int i=1;i<capacity;i++)
    {
        heads[i]=new node();
        temp->top=heads[i];
        heads[i]->bottom=temp;
        temp=heads[i];
    }
    }
    void insert(T val)
    {
        level=0;
        if(heads[0]->next==NULL)
        {
            node *newnode=new node(val);
            heads[level]->next=newnode;
            node *temp=newnode;
            level++;
            while(rand()%2==1)          //till it gives zero 
            {
                node *newnode=new node(val);
                newnode->bottom=temp;
                temp->top=newnode;
                heads[level]->next=newnode;
                level++;
                //updating the temp with newnode
                temp=newnode;
            }
            maxlevel=max(level,maxlevel);
            return;
        }
        node *it=heads[maxlevel-1];
        node *local[maxlevel]={NULL};
        int iter=maxlevel;
        while(it->bottom!=NULL)
        {
            iter--;
            local[iter]=it; 
            while(it->next && it->next->val<val)
            {
                it=it->next;
                local[iter]=it; 
            }
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        iter--;
        local[iter]=it;
        //''''''''''''''''
        node *newNode=new node(val);
        // newNode->prev=local[0];
        newNode->next=local[0]->next;
        local[0]->next=newNode;
        // cout<<level<<" ";
        level++;
        node *bottom_node=newNode;
        while(rand()%2==1)          //till it gives zero 
        {
            node *newnode=new node(val);
            if(level>maxlevel-1)
            {   
                // cout<<level<<" ";
                newnode->next=heads[level]->next;
                heads[level]->next=newnode;
                heads[level-1]->top=newnode;
                newnode->bottom=heads[level-1];
                // newnode->prev=NULL;
            }
            else{
                // cout<<level<<" ";
                newnode->next=local[level]->next;
                local[level]->next=newnode;
                local[level-1]->next->top=newnode;
                newnode->bottom=local[level-1]->next;
                // newnode->prev=local[level];
            }
                // bottom_node->top=newnode;
                // newnode->bottom=bottom_node;
                level++;
                //updating bottom_node with newnode
                // bottom_node=newnode;
        }
        // cout<<endl;
        maxlevel=max(level,maxlevel);
    }
    bool search(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        if(it->next && it->next->val==val) return true;
        else return false;
    }
    void display()
    {
        node *temp=heads[0]->next;
        while(temp)
        {
            cout<<temp->val<<" ";
            temp=temp->next;
        }
    }
    void Delete(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        if(it->next && it->next->val==val)
        {
            node *del=it->next;
            it->next=del->next;
            while(it->top!=NULL)
            {
            it=it->top;
            }
        }
    }
    // void check()
    // {
    //     node *temp=heads[1]->next->next;
    //     while(temp!=NULL)
    //     {
    //         cout<<temp->val<<endl;
    //         temp=temp->top;
    //     }
    // }
    T lower_bound(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        if(it->next==NULL) return T();
        return it->next->val;
    }
    T upper_bound(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        while(it->next && it->next->val==val) it=it->next;
        if(it->next==NULL) return T();
        return it->next->val;
    }
    T closest_element(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        if(it->next==NULL) return it->val;
        else
        {
            T a=it->val;
            if(it->next->val==val) return val;
            else
            { 
            while(it->next && it->next->val==val) it=it->next;
            if(it->next==NULL) return it->val;
            else
            {
                if(it->next->val-val<val-a)
                {
                    return it->next->val;
                }
                else
                {
                    return a;
                }
            }
            }
        }
        return T();

    }
    int count_occurences(T val)
    {
        node *it=heads[maxlevel-1];
        while(it->bottom!=NULL)
        {
            while(it->next && it->next->val<val)
            {
                it=it->next;
            }
            
            it=it->bottom;
        }
        //we will reach the bottom node
        //so search in the bottom node
        while(it->next && it->next->val<val)
        {
            it=it->next;
        }
        int cnt=0;
        while(it->next && it->next->val==val)
        {
            cnt++;
             it=it->next;
        }
        return cnt;
    }
};


int main() {
  int N;
  cin >> N;
  skipList<int> sp;
  //create skiplist

  int data, op;

  while (N > 0) {
    cin >> op;
    cin >> data;
    switch (op) {
    case 1: // insert
      sp.insert(data);
      break;
    case 2: // delete
      sp.Delete(data);
      break;
    case 3: // search
      cout<<sp.search(data);
      // print result
      cout << "\n";
      break;
    case 4: // count
      cout<<sp.count_occurences(data);
      // print result
      cout << "\n";
      break;
    case 5: // lower bound
      cout<<sp.lower_bound(data);
      // print result
      cout << "\n";
      break;
    case 6: // upper bound
      cout<<sp.upper_bound(data);
      // print result
      cout << "\n";
      break;
    case 7: // closest val
      cout<<sp.closest_element(data);
      // print result
      cout << "\n";
      break;
    }
    --N;
  }

  return 0;
}

