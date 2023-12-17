#include <iostream>
#include <string>
#include <vector>
using namespace std;
class trienode
{
public:
    bool flag;
    trienode *node[26];
    trienode()
    {
        flag = false;
        for (int i = 0; i < 26; i++)
        {
            node[i] = NULL;
        }
    }
};
class trie
{
public:
    trienode *root;
    trie()
    {
        root = new trienode();
    }
    void insert(string s)
    {
        trienode *temp = root;
        int i = 0;
        while (temp->node[int(s[i] - 'a')] != NULL)
        {
            /// traverse till the prefix matches
            temp = temp->node[int(s[i++] - 'a')];
            if (i == s.size())
                temp->flag = true;
        }
        for (int j = i; j < s.size(); j++)
        {
            trienode *ptr = new trienode();
            temp->node[int(s[j] - 'a')] = ptr;
            temp = ptr;
            if (j == s.size() - 1)
                temp->flag = true;
        }
    }
    bool search(string s)
    {
        trienode *temp = root;
        int i = 0;
        while (i < s.size() && temp->node[int(s[i] - 'a')] != NULL)
        {
            /// traverse till the prefix matches
            temp = temp->node[int(s[i++] - 'a')];
        }
        return (temp->flag && i == s.size());
    }
    vector<string> autocomplete(string s)
    {
        vector<string> res;
        trienode *temp = root;
        int i = 0;
        while (i < s.size() && temp->node[int(s[i] - 'a')] != NULL)
        {
            /// traverse till the prefix matches
            temp = temp->node[int(s[i++] - 'a')];
        }
        if (i == s.size())
        {
            if (temp->flag == true)
            {
                res.push_back(s);
            }
            for (int i = 0; i < 26; i++)
            {
                if (temp->node[i] != NULL)
                {
                    s += char('a' + i);
                    getwords(temp->node[i], res, s);
                    s.pop_back();
                }
            }
        }
        return res;
    }
    void getwords(trienode *temp, vector<string> &res, string &s)
    {
        if (temp->flag == true)
            res.push_back(s);
        for (int i = 0; i < 26; i++)
        {
            if (temp->node[i] != NULL)
            {
                s += char('a' + i);
                getwords(temp->node[i], res, s);
                s.pop_back();
            }
        }
    }
    int finddist(int indx1,int indx2,string &word1,string &word2,vector<vector<int>> &dp)
    {
        // why the base case is this ? => imagine a situation where one index got to zero and there is still characters to insert or delete
        if(indx1==0) return indx2;
        if(indx2==0) return indx1;
        if(dp[indx1][indx2]!=-1) return dp[indx1][indx2];
        if(word1[indx1-1]==word2[indx2-1]) return dp[indx1][indx2]=finddist(indx1-1,indx2-1,word1,word2,dp);
        return dp[indx1][indx2]=1+min(finddist(indx1-1,indx2-1,word1,word2,dp),min(finddist(indx1,indx2-1,word1,word2,dp),finddist(indx1-1,indx2,word1,word2,dp)));
    }
    int LevinshteinDistance(string word1, string word2) {
        int n1=word1.size(),n2=word2.size();
        vector<vector<int>> dp(n1+1,vector<int> (n2+1,-1));
        return finddist(n1,n2,word1,word2,dp);
    }
    vector<string> autocorrect(string s)
    {
        trienode *temp=root;
        vector<string> words;
        string s1="";
        for (int i = 0; i < 26; i++)
        {
            if (temp->node[i] != NULL)
            {
                    s1 += char('a' + i);
                    getwords(temp->node[i], words, s1);
                    s1.pop_back();
            }
        }
        vector<string> res;
        for(auto word:words){
            if(LevinshteinDistance(s,word)<=3)
            {
                res.push_back(word);
            }
        }
        return res;
    }
};
// Driver code
int main()
{
    int n, q;
    cin >> n >> q;
    trie *t = new trie();
    while (n--)
    {
        string s;
        cin >> s;
        t->insert(s);
    }
    while (q--)
    {
        int ai;
        string ti;
        cin>>ai;
        cin>>ti;
        if(ai==1){
            cout<<t->search(ti)<<endl;
        }
        else if(ai==2) {
            vector<string> autoCompleteWords(t->autocomplete(ti));
            cout<<autoCompleteWords.size()<<endl;
            for(auto it:autoCompleteWords) cout<<it<<endl;
        }
        else if(ai==3) {
            vector<string> autoCorrectWords(t->autocorrect(ti));
            cout<<autoCorrectWords.size()<<endl;
            for(auto it:autoCorrectWords) cout<<it<<endl;
        }
    }
}
