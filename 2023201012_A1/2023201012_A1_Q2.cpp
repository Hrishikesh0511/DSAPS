//Deque implementation
#include<iostream>
#include<string>
using namespace std;
// defining a template so that it can be used to all datatypes
template<typename T>
class MyDeque
{
        int frontele=0,rear=-1,sizevar=0,cap=0;
        T *arr=new T[cap];
        
    public:
        //this function just doubles the size of old array
        T *doubleArray()
        {
            cap*=2;
                T *newarr=new T[cap];
                for(int i=frontele;i<=rear;i++)
                {
                    newarr[i%cap]=arr[i%cap];
                }
                //frees all the memory allocated to the arr by new
                delete[] arr;
                return newarr;
        }
        // 1 Initialization of an empty deque
        MyDeque()
        {
            cap=0;
            arr=new T[cap];
            frontele=0;
            rear=-1;
            sizevar=0;
        }
        // 2 Initialization with some default values
        MyDeque(int n)
        {
            //so this will initialize the deque with size 'n' with default values
            arr=new T[n]();
            frontele=0,rear=n-1;
            cap=n;
            sizevar=n;
        }
        //3 Initialization with some given value 
        MyDeque(int n,T x)
        {
            arr=new T[n]();
            frontele =0,rear=n-1;
            cap=n;
            sizevar=n;
            for(int i=frontele;i<=rear;i++) arr[i]=x;
        }
        //4
        bool push_back(T x)
        {
            
            if(capacity()==0) cap++;
            
            //if size equals capacity means the current arr is full just double it
            if(sizevar==capacity())
            {
                arr=doubleArray();
            }
            if(sizevar==0)
            {
                arr=new T[cap];
            }
            //In normal case it just increases rear
            //assign the value
            arr[(++rear)%cap]=x;
            sizevar++;
            return true;
        }
        
        // 5
        bool pop_back()
        {
            if(empty())
            {
                //when it is really empty
                return false;
            }
            rear=(cap+(rear-1))%cap;
            sizevar--;
            return true;
        }
        //6
        bool push_front(T x)
        {
            if(capacity()==0) cap++;
            //if size equals capacity means the current arr is full just double it
            if(size()==capacity())
            {
                arr=doubleArray();
            }
            if(sizevar==0) arr=new T[cap];
            frontele=(cap+(frontele))%cap;
            sizevar++;
            arr[frontele]=x;
            return true;
        }
        //7
        bool pop_front()
        {
            if(empty()) return false;
            frontele=(frontele+1)%cap;
            sizevar--;
            return true;
        }
        //8
        T front()
        {
            if(empty()) return T();
            return arr[frontele%cap];
        }
        //9
        T back()
        {
            if(empty()) return T(); 
            return arr[rear%cap];
        }
        //10
        int operator[](size_t n) {
        return getn(n);
        }
        T getn(int n)
        {
            if(n>=sizevar || n<-1*sizevar) return T();
            //i th element
            if(n<0)
            {
                return arr[((rear+n)+cap)%cap];
            }
            return arr[(frontele+n)%cap];
        }
        //11
        bool empty()
        {
            if(sizevar==0) return true;
            return false;
        }
        //12
        int size()
        {
            if(empty()) return 0;
            return sizevar;
        }
        //13
        void resize(int n)
        {
            //resize
                T* newarr=new T[n]();
                //this will initialise all with default values
                int j=0;
                //this will ensure both conditions
                for(int i=frontele;j<sizevar && j<n;i++)
                {
                    newarr[j++]=arr[i%cap];
                    //this will replace all the values with old array
                }
                frontele =0,rear=n-1;
                sizevar=n;
                delete[] arr;
                arr=newarr;
                if(n>cap) cap=n;
                //change the capacity if only n is greater than cap
        }
        //14
        void resize(int n,T d)
        {
            //resize
            T* newarr=new T[n]();
                //this will initialise all with default values
                for(int i=0;i<n;i++)
                {
                    //we replace the value with d
                    newarr[i]=d;
                }
                int j=0;
                //this will ensure both conditions
                for(int i=frontele;i<sizevar && j<n;i++)
                {
                    newarr[j++]=arr[i%cap];
                    //this will replace all the values with old array
                }
                frontele =0,rear=n-1;
                sizevar=n;
                delete[] arr;
                arr=newarr;
                //change the capacity if only n is greater than cap
                if(n>cap) cap=n;
        }
        //15
        void reserve(int n)
        {
            //reserve
            if(n>sizevar)
            {
                 T* newarr=new T[n]();
                //this will initialise all with default values
                int j=0;
                //this will ensure both conditions
                for(int i=frontele;j<sizevar;i++)
                {
                    newarr[j++]=arr[i%cap];
                    //this will replace all the values with old array
                }
                frontele=0,rear=sizevar-1;
                delete[] arr;
                arr=newarr;
                cap=n;
            }
        }
        //16
        void shrink_to_fit()
        {
            //shrink
             T* newarr=new T[sizevar]();
                //this will initialise all with default values
                int j=0;
                for(int i=frontele;j<sizevar;i++)
                {
                    newarr[j++]=arr[i%cap];
                    //this will replace all the values with old array
                }
                delete[] arr;
                arr=newarr;
                cap=sizevar;
        }
        //17
        void clear()
        {
            //clear
            frontele=0,rear=-1;
            sizevar=0;
            //capacity should remain same
        }
        //18
        int capacity()
        {
            return cap;
        }
};
int main()
{
MyDeque<int> sample;
int choice=1;
int n;
int x;
while(choice)
{
    cin>>choice;
    switch(choice)
    {
        case 1:
            sample=MyDeque<int>();
            break;
        case 2:
            cin>>n;
            sample=MyDeque<int>(n);
            // sample.print();
            break;
        case 3:
            cin>>n>>x;
            sample=MyDeque<int>(n,x);
            // sample.print();
             break;
        case 4:
            cin>>x;
            cout<<boolalpha<<sample.push_back(x)<<endl;
            // sample.print();
            break;
        case 5:
            cout<<boolalpha<<sample.pop_back()<<endl;
            // sample.print();
            break;
        case 6:
            cin>>x;
            cout<<boolalpha<<sample.push_front(x)<<endl;
            // sample.print();
            break;
        case 7:
            cout<<boolalpha<<sample.pop_front()<<endl;
            // sample.print();
            break;
        case 8:
            cout<<sample.front()<<endl;
            break;
        case 9:
            cout<<sample.back()<<endl;
            break;
        case 10:
            // int n;
            cin>>n;
            cout<<sample[n]<<endl;
            break;
        case 11:
            cout<<sample.empty()<<endl;
            break;
        case 12: 
            cout<<sample.size()<<endl;
            break;
        case 13:
            // int n;
            cin>>n;
            sample.resize(n);
            // sample.print();
            break;
        case 14:
            // int n,T d;
            cin>>n;
            cin>>x;
            sample.resize(n, x);
            // sample.print();
            break;
        case 15: 
            // int n;
            cin>>n;
            sample.reserve(n);
            // sample.print();
            break;
        case 16:
             sample.shrink_to_fit();
            //  sample.print();
             break;
        case 17: 
            sample.clear();
            // sample.print();
            break;
        case 18:
            cout<<sample.capacity()<<endl;
            break;
        default:
        break;
    }
}
}
