#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
template <class T1, class T2>

class unordered_map
{
public:
    class hashnode
    {
    public:
        T1 key;
        T2 value;
        hashnode *next;
        hashnode(T1 key, T2 value, hashnode *next)
        {
            this->key = key;
            this->value = value;
            this->next = next;
        }
    };
    hashnode *hashtable[100000];
    int tablesize = 0;
    int arr[100000];
    int k = 0;
    // constructor
    unordered_map()
    {
        for (int i = 0; i < 100000; i++)
        {
            hashtable[i] = NULL;
        }
    }
    int hash(T1 key)
    {
        stringstream ss;
         ss << key;
        string keyhash=ss.str();
        int p = 107897;
        int q = 1;
        int m = 100000;
        int final_hash = 0;
        for (int i = 0; i < keyhash.size(); i++)
        {
            final_hash += ((int(keyhash[i]) * p) % m + q % m) % m;
            q = (q + 11) % m;
        }
        return final_hash;
    }
    bool insert(T1 key, T2 value)
    {
        int indx = hash(key);
        hashnode *node = new hashnode(key, value, NULL);
        // stores all the indices which have the keys
        arr[k++] = indx;
        if (hashtable[indx] == NULL)
        {
            hashtable[indx] = node;
        }
        else
        {
            hashnode *temp = hashtable[indx];
            while (temp->next != NULL)
            {
                if (temp->key == key)
                    return false;
                temp = temp->next;
            }
            if (temp->key == key)
                return false;
            temp->next = node;
        }
        tablesize++;
        return true;
    }
    bool erase(T1 key)
    {
        int indx = hash(key);
        if (hashtable[indx] == NULL)
        {
            return false;
        }
        else
        {
            hashnode *temp = hashtable[indx];
            if (temp->key == key)
            {
                tablesize--;
                hashtable[indx] = NULL;
                free(temp);
                return true;
            }
            while (temp->next != NULL && temp->next->key != key)
            {
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                return false;
            } // the key doesn't exist
            hashnode *temp2 = temp->next;
            temp->next = temp->next->next;
            free(temp2);
            tablesize--;
            return true;
        }
    }
    bool contains(T1 key)
    {
        int indx = hash(key);
        if (hashtable[indx] == NULL)
        {
            return false;
        }
        else
        {
            hashnode *temp = hashtable[indx];
            if (temp->key == key)
            {
                return true;
            }
            while (temp->next != NULL && temp->next->key != key)
            {
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                return false;
            } // the key doesn't exist
            return true;
        }
    }
    T2 &operator[](T1 key)
    {
        int indx = hash(key);
        if (hashtable[indx] == NULL)
        {
            hashtable[indx]= new hashnode(key, T2(), NULL);
            arr[k++]=indx;
            tablesize++;
            return hashtable[indx]->value;
        }
        hashnode *temp = hashtable[indx];
        while (temp != NULL && temp->next != NULL)
        {
            if (temp->key == key)
            {
                return temp->value;
            }
            temp = temp->next;
        }
        if (temp->key == key)
        {
            return temp->value;
        }
        temp->next = new hashnode(key, T2(), NULL);
        arr[k++]=indx;
        tablesize++;
        return temp->next->value;
    }
    void clear()
    {
        for (int i = 0; i <= k; i++)
        {
            if (hashtable[arr[i]]== NULL)
                continue;
            hashnode *temp = hashtable[arr[i]];
            while (temp != NULL)
            {
                hashnode *x = temp;
                temp = temp->next;
                delete x;
            }
            hashtable[arr[i]] = NULL;
        }
        tablesize=0;
    }
    int size()
    {
        return tablesize;
    }
    bool empty()
    {
        return (tablesize == 0);
    }
    vector<T1> keys()
    {
        vector<T1> arr1;
        for (int i = 0; i <= k; i++)
        {
            // cout<<hashtable[arr[i]]<<endl;
            if ( hashtable[arr[i]]== NULL)
                continue;
            hashnode *temp = hashtable[arr[i]];
            while (temp != NULL)
            {
                arr1.push_back(temp->key);
                temp = temp->next;
            }
        }
        return arr1;
    }
};

int main()
{
    unordered_map<int, int> mp;
    int choice=1;
    int key;
    int value;
    vector<int> arr;
    while(choice){
        cin>>choice;
        switch(choice){
            case 1:
                 cin>>key>>value;
                cout<<boolalpha<<mp.insert(key,value)<<endl;
                break;
            case 2:
                cin>>key;
                cout<<boolalpha<<mp.erase(key)<<endl;
                break;
               
            case 3:
                cin>>key;
                cout<<boolalpha<<mp.contains(key)<<endl;
                break;
            case 4:
                cin>>key;
                cout<<mp[key]<<endl;
                break;
            case 5:
                mp.clear();
                break;
            case 6:
                cout<<mp.size()<<endl;
                break;
            case 7:
                cout<<boolalpha<<mp.empty()<<endl;
                break;
            case 8:
                arr=mp.keys();
                for(auto key:arr){
                    cout<<key<<endl;
                }
                break;
        }    
        }
}
