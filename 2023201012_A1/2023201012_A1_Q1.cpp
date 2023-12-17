//need to recheck gcd
// Big Integer Problem
#include<iostream>
#include<string>
using namespace std;
//stack implementation
template<typename T>
class stack
{
    private:
    T arr[20000];
    int ptr=-1;

    public:
    void push(T a)
    {
        arr[++ptr]=a; 
    }
    void pop()
    {
        ptr--;
    }
    T top()
    {
        return arr[ptr];
    }
    bool isEmpty()
    {
        return (ptr==-1);
    }
};
//returns the precedence
int precedence(char oper)
{
    switch (oper)
    {
        case '+':
            return 1;
        case '-':
            return 1;
        case 'x':
            return 2;
        case '/':
            return 2;
    }
    return 0;
}
void convertToPostfix(string s,string resArr[])
{
    stack<char> st;
    //it temporarily stores the number
    string number="";
    //convertToPostfix
    int i=0;
    for(auto it:s)
    {
        if(it>='0' && it<='9')
        {
            number+=it;
        }
        else
        {
            resArr[i++]=number;
            number=""; 
            if(st.isEmpty())
            {
                st.push(it);
            }
            else
            {
                if(precedence(it)>precedence(st.top()))
                {
                    st.push(it);
                }
                else{
                while(precedence(it)<=precedence(st.top()))
                {
                    resArr[i++]=st.top();
                    st.pop();
                }
                //converting string to char bcoz the precedence function accepts char only
                st.push(it);
                }
            }
              
        }
        
    }
    resArr[i++]=number;
    //all the remaining operators are popped from the stack
    while(!st.isEmpty())
    {
        resArr[i++]=st.top();
        st.pop();
    }
}
bool isop(string a)
{
    if(a=="+"||a=="-"||a=="x"||a=="/") return true;
    return false;
}
string reverse(string s)
{
    int start=0,end=s.size()-1;
    while(start<end)
    {
        swap(s[start++],s[end--]);
    }
    return s;
}
string add(string s1,string s2)
{
    //addition
    string res="";
    int carry=0;
    int sum=0;
    int m=s1.size()-1; int n=s2.size()-1;
    while(m>=0 && n>=0)
    {
        int sum=(int)(s1[m--]-'0')+(int)(s2[n--]-'0')+carry;
        res+=char((sum%10)+'0');
        carry=sum/10;
    }
    while(m>=0)
    {
        sum=(int)(s1[m--]-'0')+carry;
        res+=char((sum%10)+'0');
        carry=sum/10;
    }
    while(n>=0)
    {
        sum=(int)(s2[n--]-'0')+carry;
        res+=char((sum%10)+'0');
        carry=sum/10;
    }
    if(carry>0)
    {
        res+=char(carry+48);
    }
    res=reverse(res);

    return res;
}
string subtract(string s1,string s2)
{
    //subtract
    //s1-s2
    string res="";
    int borrow=0;
    int sub=0;
    int m=s1.size()-1,n=s2.size()-1;
    while(m>=0 && n>=0)
    {
    int d1=(int)(s1[m--]-'0');
    int d2=(int)(s2[n--]-'0');
    //If there is any borrow it is subtracted at first
    if(borrow>0)
    {
    d1=d1-borrow;
    borrow--;
    }
    if(d1<d2) 
    {
        borrow++;
        d1+=10;
    }
    res+=char((d1-d2)+'0');
    }
    while(m>=0)
    {
        int d1=(int)(s1[m--]-'0');
        if(borrow>0)
        {
        d1=d1-borrow;
        borrow--;
        }
        if(d1<0)
        {
            borrow++;
            d1+=10;
        }
        res+=char((d1)+'0');
    }
    res=reverse(res);
    // if(negflag) res="-"+res;
    //removing leading zeroes
    while(res[0]=='0')
    {
        res.erase(res.begin());
    }
    if(res=="") return "0";
   return res;
}
string multiply(string s1,string s2)
{
    //multiply
    //if any number is zero we return 0;
    if (s1 == "0" || s2 == "0") return "0";
        int m=s1.size(),n=s2.size();
        int res[m+n];
        //created a result array
        for(int i=0;i<m+n;i++) res[i]=0;
        for (int i = m-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                res[i + j + 1] += (s1[i]-'0') * (s2[j]-'0');
                //every time storing carry at the last
                res[i + j] += res[i + j + 1] / 10;
                res[i + j + 1] %= 10;
            }
        }
        int i = 0;
        string s = "";
        while (res[i] == 0) i++;
        while (i < s1.size()+s2.size()) 
        {
            s += to_string(res[i++]);
        }
        return s;
}
bool checkIfgreater(string s1,string s2)
{
    if(s1.size()!=s2.size()) return (s1.size()>s2.size());
    return (s1>s2);
}
string divide(string num,string divisor)
{
    string res="";
    //to increase the indx while the numbr is still less than the divisor
    int indx=0;
    //taking the first place value
    string temp="";
    temp+=num[indx];
    while(checkIfgreater(divisor,temp))
    {
        //so we will increase the temp till it becomes larger than the divisor
        temp+=num[++indx];
    }
    //do this whole process till the index exceeds our number size
    
    //when it becomes larger than the temp just divide it with div and add it to the res
    //need to find the multiple under that is just less than 10
    while(num.size()>indx)
    {
    indx++;
    for(int i=0;i<10;i++)
    {
        string mul=to_string(i+1);
        string mult=multiply(divisor,mul);
        // cout<<mult<<endl;
        if(checkIfgreater(mult,temp))
        {
            res+=char(i+48);
            temp=subtract(temp,multiply(divisor,to_string(i)));
            if(temp=="0") temp="";
            temp+=num[indx];
            break;
        }   
    }
    }
    if(res=="") return "0"; 
    return res;
    }
string eval(string postfix[])
{
    stack<string> st;
    int i=0;
    while(postfix[i]!="$")
    {
        if(!isop(postfix[i]))
        {
            st.push(postfix[i]);
        }
        else{
            string op1=st.top();
            // cout<<op1;
            st.pop();
            string op2=st.top();
            // cout<<op2;
            st.pop();
            if(postfix[i]=="+")
            {
                st.push(add(op2,op1));
            }
            else if(postfix[i]=="-")
            {
                st.push(subtract(op2,op1));
            }
            else if(postfix[i]=="x")
            {
                st.push(multiply(op2,op1));
            }
            else{
                st.push(divide(op2,op1));
            }
        }
        i++;
    }
    return st.top();
}
void Arithmetic()
{
    string expr;
    cin>>expr;
    string postfix[100];
    for(int i=0;i<100;i++)
    {
        postfix[i]="$";
    }
    convertToPostfix(expr,postfix);
    cout<<eval(postfix)<<endl;
}
string Mod(string s1,string s2)
{
    string quotient=divide(s1,s2);
    string temp=multiply(quotient,s2);
    string remainder=subtract(s1,temp);
    return remainder;
}
string findGcd(string a,string b)
{
    //need to recheck
    if(Mod(a,b)=="0") return b;
    else return findGcd(b,Mod(a,b));
}
string power(string a,string b)
{
    if(b=="0") return "1";
    string t=power(a,divide(b,"2"));   
    if(Mod(b,"2")=="0") return multiply(t,t);
    else return multiply(a,power(a,subtract(b,"1")));
}

void Exponent()
{
    //Exponent
    string s1,s2;
    cin>>s1>>s2;
    cout<<power(s1,s2)<<endl;
} 
void Gcd()
{
    //Gcd
    string s1;
    string s2;
    cin>>s1;
    cin>>s2;
    string maxi=checkIfgreater(s1,s2)?s1:s2;
    string mini=checkIfgreater(s1,s2)?s2:s1;
    cout<<findGcd(maxi,mini)<<endl;
}
void Factorial()
{
    // Factorial
    string s;
    cin>>s;
    string res="1";
    while(s!="1"&&s!="0")
    {
        res=multiply(res,s);
        s=subtract(s,"1");
    }
    cout<<res<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    int n;
    cin>>n;
    switch(n)
    {
        case 1:
            Arithmetic();
            break;
        case 2:
            Exponent();
            break;
        case 3:
            Gcd();
            break;
        case 4:
            Factorial();
            break;
    }
    }
}
