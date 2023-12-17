//Sparse Matrix operations
#include<iostream>
#include<algorithm>
using namespace std;
// Define a Mat datatype storing row, col, and val;
template <typename T>
class ll{
    public:
    class MatrixNode
{
    public:
    int row;                   //row number
    int col;                   //column number
    T val;                   //value 
    MatrixNode *next;          //pointer to next node 


    MatrixNode(int row, int col, T val,MatrixNode *next)  
    {
        this->row=row;
        this->col=col;
        this->val=val;
        this->next=next;
    }
};
void printMatrix(MatrixNode *head,int rows,int cols)
{
    MatrixNode *temp=head;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(temp!=NULL && temp->row==i && temp->col==j)
            {
                cout<<temp->val<<" ";
                temp=temp->next;
            }
            else{
                cout<<"0"<<" ";
            }
        }
        cout<<endl;
    }
}
MatrixNode *reverse(MatrixNode * head)
{
    MatrixNode* curr=head;
    MatrixNode* next=NULL;
    MatrixNode* prev=NULL;
    while(curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return prev;
}
MatrixNode *mergeLists(MatrixNode* l1,MatrixNode* l2)
{
  MatrixNode *temp=new MatrixNode(-1,-1,0,NULL); //temporary node
  MatrixNode *curr=temp;
  while(l1!=NULL && l2!=NULL)
  {
    if(l1->row<l2->row || (l1->row==l2->row && l1->col<=l2->col))
    {
      curr->next=l1;
      l1=l1->next;
    }
    else
    {
      curr->next=l2;
      l2=l2->next;
    }
    curr=curr->next;
  }
  while(l1!=NULL)
  {
    curr->next=l1;
    l1=l1->next;
    curr=curr->next;
  }
  while(l2!=NULL)
  {
    curr->next=l2;
    l2=l2->next;
    curr=curr->next;
  }
  return temp->next;
}
MatrixNode* sort(MatrixNode* head) {
      if(head==NULL || head->next==NULL) return head;
        MatrixNode* slow=head;
        MatrixNode* fast=head;
        MatrixNode *temp=NULL;
        while(fast!=NULL && fast->next!=NULL)
        {
          //finding the middle node
          temp=slow;
          slow=slow->next;
          fast=fast->next->next;
        }   
        temp->next=NULL;  //dividing the linked list
        MatrixNode *l1=sort(head);
        MatrixNode *l2=sort(slow);
        return mergeLists(l1,l2);
    }
void addMatrices()
{
    int n1,m1; //rows and columns of first matrix
    cin>>n1>>m1;
    MatrixNode *mat1=NULL;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<m1;j++)
        {
            T val;
            cin>>val;
            if(val!=0)
            {
                //every non zero node is inserted at the start of list
                MatrixNode *node = new MatrixNode(i,j,val,mat1);
                mat1=node;
            }
        }
    }
    mat1=reverse(mat1);
    int n2,m2; //rows and columns of second matrix 
    cin>>n2>>m2;
    MatrixNode *mat2=NULL;
    for(int i=0;i<n2;i++)
    {
        for(int j=0;j<m2;j++)
        {
            T val;
            cin>>val;
            if(val!=0)
            {
                //every non zero node is inserted at the start of list
                MatrixNode *node = new MatrixNode(i,j,val,mat2);
                mat2=node;
            }
        }
    }
    mat2=reverse(mat2);
    MatrixNode *head1=mat1;
    MatrixNode *head2=mat2;
    MatrixNode *res=NULL;
    while(head1!=NULL && head2!=NULL)
    {
    if(head1->row==head2->row && head1->col==head2->col)
    {
        MatrixNode *node = new MatrixNode(head1->row,head1->col,head1->val+head2->val,res);
        res=node;
        head1=head1->next;
        head2=head2->next;
    }
    else if(head1->row>head2->row ||(head1->row==head2->row && head1->col>head2->col))
    {
        MatrixNode *node = new MatrixNode(head2->row,head2->col,head2->val,res);
        res=node;
        head2=head2->next;
    }
    else 
    {
        MatrixNode *node = new MatrixNode(head1->row,head1->col,head1->val,res);
        res=node;
        head1=head1->next;
    }
    }
    while(head1!=NULL)
    {
        MatrixNode *node = new MatrixNode(head1->row,head1->col,head1->val,res);
        res=node;
        head1=head1->next;
    }
    while(head2!=NULL)
    {
        MatrixNode *node = new MatrixNode(head2->row,head2->col,head2->val,res);
        res=node;
        head2=head2->next;
    }
    res=reverse(res);
    printMatrix(res,n1,m1);
}
MatrixNode * merge(MatrixNode *list)
{
    MatrixNode* temp=list;
    while(temp!=NULL && temp->next!=NULL)
    {
        if(temp->row==temp->next->row && temp->col==temp->next->col)
        {
            temp->val+=temp->next->val;
            temp->next=temp->next->next;   
        }
        else{
        temp=temp->next;
        }
    }
    return list;
}
void mulMatrices()
{
    int n1,m1; //rows and columns of first matrix
    cin>>n1>>m1;
    MatrixNode *mat1=NULL;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<m1;j++)
        {
            T val;
            cin>>val;
            if(val!=0)
            {
                //every non zero node is inserted at the start of list
                MatrixNode *node = new MatrixNode(i,j,val,mat1);
                mat1=node;
            }
        }
    }
    mat1=reverse(mat1);
    int n2,m2; //rows and columns of second matrix 
    cin>>n2>>m2;
    MatrixNode *mat2=NULL;
    for(int i=0;i<n2;i++)
    {
        for(int j=0;j<m2;j++)
        {
            T val;
            cin>>val;
            if(val!=0)
            {
                //every non zero node is inserted at the start of list
                MatrixNode *node = new MatrixNode(i,j,val,mat2);
                mat2=node;
            }
        }
    }
    mat2=reverse(mat2);
    MatrixNode* head1=mat1;
    MatrixNode *res=NULL;
    while(head1!=NULL)
    {
        MatrixNode* head2=mat2;
        while(head2!=NULL)
        {
            if(head1->col==head2->row)
            {
                MatrixNode* node=new MatrixNode(head1->row,head2->col,head1->val*head2->val,res);
                res=node;
            }
            head2=head2->next;
        }
        head1=head1->next;
    }
    res=sort(res);
    MatrixNode *temp=res;
    res=merge(res);
    printMatrix(res,n1,m2);

}
void Transpose()
{
    int n1,m1; //rows and columns of first matrix
    cin>>n1>>m1;
    MatrixNode *mat1=NULL;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<m1;j++)
        {
            T val;
            cin>>val;
            if(val!=0)
            {
                //every non zero node is inserted at the start of list
                MatrixNode *node = new MatrixNode(i,j,val,mat1);
                mat1=node;
            }
        }
    }
    mat1=reverse(mat1);
    MatrixNode* temp=mat1;
    while(temp!=NULL)
    {
        swap(temp->row,temp->col);
        temp=temp->next;
    }
    mat1=sort(mat1);
    printMatrix(mat1,m1,n1);
}
};
template <typename T>
class ar
{
    public:
    class Mat
    {
    public:
    int row;
    int col;
    T val;
    };
   static bool compare(Mat m1, Mat m2) {
   if(m1.row<m2.row || (m1.row==m2.row && m1.col <= m2.col)) {
      return true;
   } return false;
}
 void addMatrices()
    {
    int n1, m1; // rows and columns of the first matrix
    cin >> n1 >> m1;
    int size1 = 10;
    Mat *mat1 = new Mat[size1];
    int cnt = 0;
    
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m1; j++)
        {
            T val;
            cin >> val;
            if(val != 0)
            {
                if (cnt >= size1)
                {
                    size1*= 2;
                    Mat *temp = new Mat[size1];
                    for(int k = 0; k < cnt; k++)
                    {
                        temp[k] = mat1[k];
                    }
                    delete[] mat1;
                    mat1 = temp;
                } 
                mat1[cnt].row = i;
                mat1[cnt].col = j;
                mat1[cnt].val = val;
                cnt++;
            }
        }
    }
    size1=cnt;
    int n2, m2; // rows and columns of the second matrix 
    cin >> n2 >> m2;
    int size2 = 10;
    Mat *mat2 = new Mat[size2];
    cnt = 0;
    
    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            T val;
            cin >> val;
            if(val != 0)
            {
                if (cnt >= size2)
                {
                    size2*= 2;
                    Mat *temp = new Mat[size2];
                    for(int k = 0; k < cnt; k++)
                    {
                        temp[k] = mat2[k];
                    }
                    delete[] mat2;
                    mat2 = temp;
                } 
                mat2[cnt].row = i;
                mat2[cnt].col = j;
                mat2[cnt].val = val;
                cnt++;
            }
        }
    }
    size2=cnt;
   Mat *res=new Mat[size1+size2];
    int r=0,i=0,j=0;
    while(i<size1 && j<size2)
    {
    if(mat1[i].row==mat2[j].row && mat1[i].col==mat2[j].col)
    {
        res[r].row=mat1[i].row;
        res[r].col=mat1[i].col;
        res[r].val=mat1[i].val+mat2[j].val;
        r++;
        i++;
        j++;
    }
    else if(mat1[i].row>mat2[j].row ||(mat1[i].row==mat2[j].row && mat1[i].col>mat2[j].col))
    {
        res[r].row=mat2[j].row;
        res[r].col=mat2[j].col;
        res[r].val=mat2[j].val;
        r++;
        j++;
    }
    else 
    {
        res[r].row=mat1[i].row;
        res[r].col=mat1[i].col;
        res[r].val=mat1[i].val;
        r++;
        i++;
    }
    }
    while(i<size1)
    {
        res[r].row=mat1[i].row;
        res[r].col=mat1[i].col;
        res[r].val=mat1[i].val;
        r++;
        i++;
    }
    while(j<size2)
    {
        res[r].row=mat2[j].row;
        res[r].col=mat2[j].col;
        res[r].val=mat2[j].val;
        r++;
        j++;
    } 
    printMat(res,n1,m1);
}
void mulMatrices()
{
    int n1, m1; // rows and columns of the first matrix
    cin >> n1 >> m1;
    int size1 = 10;
    Mat *mat1 = new Mat[size1];
    int cnt = 0;
    
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m1; j++)
        {
            T val;
            cin >> val;
            if(val != 0)
            {
                if (cnt >= size1)
                {
                    size1*= 2;
                    Mat *temp = new Mat[size1];
                    for(int k = 0; k < cnt; k++)
                    {
                        temp[k] = mat1[k];
                    }
                    delete[] mat1;
                    mat1 = temp;
                } 
                mat1[cnt].row = i;
                mat1[cnt].col = j;
                mat1[cnt].val = val;
                cnt++;
            }
        }
    }
    size1=cnt;
    int n2, m2; // rows and columns of the second matrix 
    cin >> n2 >> m2;
    int size2 = 10;
    Mat *mat2 = new Mat[size2];
    cnt = 0;
    
    for(int i = 0; i < n2; i++)
    {
        for(int j = 0; j < m2; j++)
        {
            T val;
            cin >> val;
            if(val != 0)
            {
                if (cnt >= size2)
                {
                    size2*= 2;
                    Mat *temp = new Mat[size2];
                    for(int k = 0; k < cnt; k++)
                    {
                        temp[k] = mat2[k];
                    }
                    delete[] mat2;
                    mat2 = temp;
                } 
                mat2[cnt].row = i;
                mat2[cnt].col = j;
                mat2[cnt].val = val;
                cnt++;
            }
        }
    }
    size2=cnt;
    Mat *res=new Mat[size1+size2];
    int i=0;
    int k=0;
    while(i<size1)
    {
        int j=0;
        while(j<size2)
        {
            if(mat1[i].col==mat2[j].row)
            {
                res[k].row=mat1[i].row;
                res[k].col=mat2[j].col;
                res[k].val=mat1[i].val*mat2[j].val;
                k++;
            }
            j++;
        }
        i++;
    }
    sort(res,res+k,compare);
    //Need to merge
    int mergedCnt = 0;
    for (int i = 1; i < k; i++) {
        if (res[i].row == res[mergedCnt].row && res[i].col == res[mergedCnt].col) {
            res[mergedCnt].val += res[i].val;
        } else {
            mergedCnt++;
            res[mergedCnt]=res[i];
            res[i].val=T();
        }
    }
    printMat(res,n1,m2);
}
void transpose()
{
    int n1,m1;
    cin>>n1>>m1;
    int size1 = 10;
    Mat *mat1 = new Mat[size1];
    int cnt = 0;
    
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < m1; j++)
        {
            T val;
            cin >> val;
            if(val != 0)
            {
                if (cnt >= size1)
                {
                    size1*= 2;
                    Mat *temp = new Mat [size1];
                    for(int k = 0; k < cnt; k++)
                    {
                        temp[k] = mat1[k];
                    }
                    delete[] mat1;
                    mat1 = temp;
                } 
                mat1[cnt].row = i;
                mat1[cnt].col = j;
                mat1[cnt].val = val;
                cnt++;
            }
        }
    }
    size1=cnt;
    int i=0;
    while(i<size1)
    {
        swap(mat1[i].row,mat1[i].col);
        i++;
    }
    sort(mat1,mat1+size1,compare);
    printMat(mat1,m1,n1);
}
void printMat(Mat matrix[],int rows,int cols)
{
    int k=0;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(matrix[k].row==i && matrix[k].col==j)
            {
                cout<<matrix[k].val<<" ";
                k++;
            }
            else{
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
}

};
int main()
{
    int t;
    cin>>t;
    while(t--){
    int type;
    cin>>type;
    int op;
    cin>>op;
    if(type==2)
    {
    ll <int> obj;
    if(op==1)
    {
    obj.addMatrices();
    }
    else if(op==2)
    {
    obj.Transpose();
    }
    else{
    obj.mulMatrices();
    }
    }
    else{
    ar<int> obj;
    if(op==1)
    {
    obj.addMatrices();
    }
    else if(op==2)
    {
    obj.transpose();
    }
    else{ 
    obj.mulMatrices();
    }
    }
    }
    return 0;
}
