#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define chunksize 10000

class minpriority_queue
{
    struct node{
        long long value;
        int indx;
    };
    int sizevar=0;
    node *arr;
    public:
        void heapify(int p)
        {
                int c1=2*p+1;
                int c2=2*p+2;
                int maxindx=p;
                if(c1<=sizevar && arr[c1].value>arr[maxindx].value)
                {
                    maxindx=c1;
                }
                if(c2<=sizevar && arr[c2].value>arr[maxindx].value){
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
            arr=new node[100000];
        }
        int size()
        {
            return (sizevar);
        }
        void push(long long ele,int indx)
        {
            ele=-ele;
            sizevar++;
            arr[sizevar-1].value=ele;
            arr[sizevar-1].indx=indx;
            int c=sizevar-1;
            while (c != 0 && arr[(c-1)/2].value < arr[c].value)
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
        node top()
        {
            arr[0].value=-arr[0].value;
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
int main(int argc, char** argv){
fstream strm;
string inputfilepath=argv[1];
string outputfilepath=argv[2];
high_resolution_clock::time_point start_time = high_resolution_clock::now();
strm.open(inputfilepath,ios_base::in);          //in for reading and out for writing
if(!strm.is_open()){
    cout<<"Can't open input file"<<endl;
    exit(1);
}
vector<fstream> temp_opfiles;
int op_file_indx=0;
while(1){
    int i=0;
    vector<long long> temp;
    while(i<chunksize && !strm.eof()){
        string a;
        strm>>a;
        temp.emplace_back(stoll(a));
        i++;
    }
    sort(temp.begin(),temp.end());
    fstream tempfile(to_string(op_file_indx),ios_base::out);
    for(int j=0;j<temp.size();j++){
        tempfile<<(to_string(temp[j])+" ");
    }
    tempfile.close();
    temp_opfiles.push_back(move(tempfile));
    op_file_indx++;
    if(strm.eof()){
        break;
    }
}
strm.close();
minpriority_queue pq=minpriority_queue();
strm.open(outputfilepath,ios_base::out);
if(!strm.is_open()){
    cout<<"Can't open output file"<<endl;
    exit(1);
}
// vector<int> file_identifiers(temp_opfiles.size(),0);
int partitions=temp_opfiles.size();

for(int i=0;i<temp_opfiles.size();i++){
    string a;
    temp_opfiles[i].open(to_string(i),ios_base::in);
    string value;
    temp_opfiles[i]>>value;
    pq.push(stoll(value),i);
}
while(!pq.empty()){
strm<<(to_string(pq.top().value)+" ");
int indx=pq.top().indx;
pq.pop();
// if(temp_opfiles[indx].eof()){
//     temp_opfiles[indx].close();
//     int flag=1;
//     for(int i=0;i<temp_opfiles.size();i++){
//         if(!temp_opfiles[i].eof()){
//             indx=i;
//             flag=0;
//             break;
//         }
//     }
//     if(flag){
//         continue;
//     }
// }
string temp_push_value;
if(temp_opfiles[indx]>>temp_push_value){
// cout<<temp_push_value<<endl;
pq.push(stoll(temp_push_value),indx);
}
else{
    temp_opfiles[indx].close();
    const char* filename = to_string(indx).c_str();
        remove(filename);
}
}
strm.close();
high_resolution_clock::time_point end_time = high_resolution_clock::now();
duration<double> duration_sec = duration_cast<duration<double>>(end_time - start_time);
cout << "Time taken: " << duration_sec.count() << " seconds" << endl;
cout<< "Number of partitions: "<<partitions<<endl;
cout<<"Partition Size: "<<chunksize<<endl;
}
