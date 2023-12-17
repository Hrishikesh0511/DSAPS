//Priority Queue
#include <iostream>
using namespace std;
class maxheap
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
        maxheap()
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
class minheap
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
        minheap()
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
    int n,k;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int xtra[100000]={0};
    maxheap maxh=maxheap();
    int maxhsize=1;
    minheap minh=minheap();
    int minhsize=0;
    maxheap tmaxh=maxheap();
    minheap tminh=minheap();
    tmaxh.push(arr[0]);
    double median=arr[0];
    maxh.push(arr[0]);
    double winMedian=arr[0];
    int winStart=0;
    int days=0;
    for(int i=1;i<n;i++)
    {
        if(arr[i]>=median+winMedian && i>=k) 
        {
            //check previous median and previous winMedian are less than today's sales
            days++;
        }
        //window Median
        if(i-winStart>=k)
        {
        //need to remove the element at window start
        // instead we'll just increment the count
        if(maxhsize!=0 && arr[winStart]>winMedian)
        {
            minhsize--;
        }
        else
        {
            maxhsize--;
        }
        xtra[arr[winStart]]++;
        winStart++;
        
        }
        while(minhsize!=0 &&xtra[minh.top()]) //whenever top is redundant we'll just pop it
        {
            xtra[minh.top()]--;
            // minhsize--;
            minh.pop();
        }
        while(maxhsize!=0 &&xtra[maxh.top()]) //whenever top is redundant we'll just pop it
        {
            xtra[maxh.top()]--;
            // maxhsize--;
            maxh.pop();
        }
        if(arr[i]>winMedian)
        { 
            minh.push(arr[i]);
            minhsize++;
        }
        else{
            maxh.push(arr[i]);
            maxhsize++;
        }
        while(minhsize!=0 && xtra[minh.top()]) //whenever top is redundant we'll just pop it
        {
            xtra[minh.top()]--;
            // minhsize--;
            minh.pop();
        }
        while(maxhsize!=0 && xtra[maxh.top()]) //whenever top is redundant we'll just pop it
        {
            xtra[maxh.top()]--;
            // maxhsize--;
            maxh.pop();
        }
        if(maxhsize-minhsize>1) // resize the above changes
        {
        minh.push(maxh.top());
        minhsize++;
        maxhsize--;
        maxh.pop();
        }
        else if(minhsize>maxhsize) //resize the above changes
        {
        maxh.push(minh.top());
        maxhsize++;
        minhsize--;
        minh.pop();
        }
        // cout<<maxhsize<<" "<<minhsize<<" "<<maxh.top()<<" "<<minh.top()<<endl;
        winMedian=((maxhsize+minhsize)%2==0)?maxh.top()+abs(maxh.top()-minh.top())/2.0:maxh.top();
        //total running median
        if(arr[i]>median)
        {
            tminh.push(arr[i]);
        }
        else if(arr[i]<median)
        {
            tmaxh.push(arr[i]);
        }
        if(tmaxh.size()-tminh.size()>1)
        {
            tminh.push(tmaxh.top());
            tmaxh.pop();
        }
        else if(tminh.size()>tmaxh.size())
        {
            tmaxh.push(tminh.top());
            tminh.pop();
        }
        if((tmaxh.size()+tminh.size())%2==0) 
        {
            median=(tmaxh.top()+tminh.top())/2.0;
        }
        else 
        {
            median=tmaxh.top();
        }
    }
    cout<<days<<endl;
}
