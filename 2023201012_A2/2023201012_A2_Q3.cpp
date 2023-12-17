#include<iostream>
#define mod 1000000007
using namespace std;
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int dp[n];
    long long int cnt[n];
    for(int i=0;i<n;i++)
    { 
        cnt[i]=1;
        dp[i]=1;
    }
    int maxlen=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[i]>=arr[j])
            {
                if(dp[i]<1+dp[j])
                {
                    cnt[i]=cnt[j];
                    dp[i]=1+dp[j];
                }
                else if(dp[i]==1+dp[j]) cnt[i]=(cnt[i]+cnt[j])%mod;
            }
        }
        if(maxlen<dp[i])
        {
            maxlen=dp[i];
        }
    }
    long long int t=0;
    for(int i=0;i<n;i++)
    {
        if(dp[i]==maxlen)
        {
            t=(t+cnt[i])%mod;
        }
    }
    cout<<t<<endl;
}
#include<iostream>
#define mod 1000000007
using namespace std;
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int dp[n];
    long long int cnt[n];
    for(int i=0;i<n;i++)
    { 
        cnt[i]=1;
        dp[i]=1;
    }
    int maxlen=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[i]>=arr[j])
            {
                if(dp[i]<1+dp[j])
                {
                    cnt[i]=cnt[j];
                    dp[i]=1+dp[j];
                }
                else if(dp[i]==1+dp[j]) cnt[i]=(cnt[i]+cnt[j])%mod;
            }
        }
        if(maxlen<dp[i])
        {
            maxlen=dp[i];
        }
    }
    long long int t=0;
    for(int i=0;i<n;i++)
    {
        if(dp[i]==maxlen)
        {
            t=(t+cnt[i])%mod;
        }
    }
    cout<<t<<endl;
}
#include<iostream>
#define mod 1000000007
using namespace std;
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int dp[n];
    long long int cnt[n];
    for(int i=0;i<n;i++)
    { 
        cnt[i]=1;
        dp[i]=1;
    }
    int maxlen=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[i]>=arr[j])
            {
                if(dp[i]<1+dp[j])
                {
                    cnt[i]=cnt[j];
                    dp[i]=1+dp[j];
                }
                else if(dp[i]==1+dp[j]) cnt[i]=(cnt[i]+cnt[j])%mod;
            }
        }
        if(maxlen<dp[i])
        {
            maxlen=dp[i];
        }
    }
    long long int t=0;
    for(int i=0;i<n;i++)
    {
        if(dp[i]==maxlen)
        {
            t=(t+cnt[i])%mod;
        }
    }
    cout<<t<<endl;
}

