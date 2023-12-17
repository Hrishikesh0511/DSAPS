//Priority Queue
#include <iostream>
using namespace std;
class maxpriority_queue
{
    int sizevar=0;
    int *arr;
    public:
        void heapify(int p)
        {
                int c1=2*p+1;
                int c2=2*p+2;
                int maxindx=p;
                if(c1<=sizevar && arr[c1]>arr[maxindx])
                {
                    maxindx=c1;
                }
                if(c2<=sizevar && arr[c2]>arr[maxindx]){
                    maxindx=c2;
                }
                if(p!=maxindx)
                {
                    swap(arr[p],arr[maxindx]);
                    heapify(maxindx);
                }
        }
        maxpriority_queue()
        {
            sizevar=0;
            arr=new int[100000];
        }
        int size()
        {
            return (sizevar);
        }
        void push(int ele)
        {
            sizevar++;
            arr[sizevar-1]=ele;
            int c=sizevar-1;
            while (c != 0 && arr[(c-1)/2] < arr[c])
            {
            swap(arr[c], arr[(c-1)/2]);
            c = (c-1)/2;
            }
        }
        void pop()
        {
            if(sizevar==1) 
            {
                sizevar--;
                return;
            }
            arr[0]=arr[sizevar-1];
            sizevar--;
            heapify(0);
        }
        int top()
        {
            return arr[0];
        }
        bool empty()
        {
            if(sizevar<1)
            {
                return true;
            }
            return false;
        }
};
class minpriority_queue
{
    int sizevar=0;
    int *arr;
    public:
        void heapify(int p)
        {
                int c1=2*p+1;
                int c2=2*p+2;
                int maxindx=p;
                if(c1<=sizevar && arr[c1]>arr[maxindx])
                {
                    maxindx=c1;
                }
                if(c2<=sizevar && arr[c2]>arr[maxindx]){
                    maxindx=c2;
                }
                if(p!=maxindx)
                {
                    swap(arr[p],arr[maxindx]);
                    heapify(maxindx);
                }
        }
        minpriority_queue()
        {
            sizevar=0;
            arr=new int[100000];
        }
        int size()
        {
            return (sizevar);
        }
        void push(int ele)
        {
            ele=-ele;
            sizevar++;
            arr[sizevar-1]=ele;
            int c=sizevar-1;
            while (c != 0 && arr[(c-1)/2] < arr[c])
            {
            swap(arr[c], arr[(c-1)/2]);
            c = (c-1)/2;
            }
        }
        void pop()
        {
            if(sizevar==1) 
            {
                sizevar--;
                return;
            }
            arr[0]=arr[sizevar-1];
            sizevar--;
            heapify(0);
        }
        int top()
        {
            return -arr[0];
        }
        bool empty()
        {
            if(sizevar<1)
            {
                return true;
            }
            return false;
        }
};
int main()
{
    maxpriority_queue pq=maxpriority_queue();
    minpriority_queue pq=minpriority_queue();
}