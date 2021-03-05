#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;


const double P=3.0;//max num
int E;//fix num
int R;//item num
int N;//bucket num

int p2[35];//  p2[i]=2^i
int mask[35]; // mask[i]=p2[i]-1
bool ERROR;

string tohex(const string& str)
{
    string ret;
    static const char *hex="0123456789ABCDEF";
    for(int i=0;i!=str.size();++i)
    {
        ret.push_back(hex[(str[i]>>4)&0xf]);
        ret.push_back( hex[str[i]&0xf]);
    }
    return ret;
}

int getnum(string str)
{
    int ret = 0;
    int tempret = 0;
    for(int i=0;i<str.size();i++)
    {

        if(str[i] >= 'A' && str[i] <= 'Z')
            tempret = str[i]-'A' + 10;
        else
            tempret = str[i] -'0';

        if(i % 2 == 0)
            ret += tempret * 16;
        else
            ret += tempret;
    }
    return ret;
}

vector<string> split(string str,string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}


int make_hash(int x){
    return x*7;
}

bool hashEq(int x,int y){
    return (x&mask[E])==(y&mask[E]);
}

int currentHash(int Hash){
    Hash=Hash&mask[E];
    return Hash < N ? Hash : Hash&mask[E-1];
}

struct ListNode{
    int Hash;
    int Key;
    string Value;
    ListNode *next;
    bool flag=false;

    ListNode(){}
    ListNode(int H,int K,string V):Hash(H),Key(K),Value(V){}
};

struct List{
    ListNode *Head;
    List():Head(NULL){}
    ~List(){clear();}

    void Insert(int H,int K,string V){
        Insert(new ListNode(H,K,V));
    }
    void Insert(ListNode *temp){
        temp->next=Head;
        Head=temp;
    }

    void Transfer(int H,List *T){
        ListNode *temp,*p;
        while(Head && hashEq(Head->Hash,H)){
            temp=Head;
            Head=Head->next;
            T->Insert(temp);
        }
        p=Head;
        while(p&&p->next){
            if(hashEq(p->next->Hash,H)){
                temp=p->next;
                p->next=p->next->next;
                T->Insert(temp);
            }
            else p=p->next;
        }
    }

    string Find(int Key){
        ERROR=false;
        ListNode *temp=Head;
        if(!temp)
        {
            return "sorry";
        }
        vector<string> value = split(temp->Value,", ");
        while(temp){
            if(temp->Key==Key&&temp->flag == false) {
                temp->flag = true;
                return temp->Value;
            }

            temp=temp->next;
        }
        return "sorry";
    }

    void Show(){
        ofstream outFile;
        outFile.open("data.csv", ios::app);
        ListNode *temp=Head;
        while(temp){
            outFile << temp->Value << endl;
            cout <<temp->Value<<endl;
            temp=temp->next;
        }
        outFile.close();
    }

    void clear(){
        while(Head){
            ListNode *temp=Head;
            Head=Head->next;
            delete temp;
        }
    }
}L[100000005];

void Init(){
    p2[0]=1;
    for(int i=1;i<=32;++i) p2[i]=p2[i-1]<<1;
    for(int i=0;i<=32;++i) mask[i]=p2[i]-1;
    E=1;N=1;R=0;L[0]=List();
}

void Adjust(){
    while((double)R/N > P){
        L[N&mask[E-1]].Transfer(N,&L[N]);
        if(++N >= p2[E])  ++E;
        L[N]=List();
    }
}

void Insert(int Hash,int Key,string Value){
    L[currentHash(Hash)].Insert(Hash,Key,Value);
    ++R;
    Adjust();
}

string Find(int Hash,int Key){
    return L[currentHash(Hash)].Find(Key);
}

void FreeAll(){
    for(int i=0;i<N;++i) L[i].clear();
}

void ShowList(){
    ofstream outFile;
    outFile.open("data.csv", ios::app);
    for(int i=0;i<N;++i){
        outFile << "bucket"<< i <<":"<< endl;
        cout<<"bucket"<< i <<":"<<endl;
        L[i].Show();
    }
    outFile.close();
}

void switch_C(){
    Init();
    cout<<""<<endl;
    //C++ read
    ifstream infile;
    infile.open("Employee.csv");
    if(!infile) cout<<"error"<<endl;
    vector<string> ve;
    string line;//storing every line
    while(getline(infile,line))
    {
        ve.push_back(line);
    }

    cout<<"create index"<<endl;
    for(int i=0;i<ve.size();i++) {
        // create index
        string this_line  = ve[i];
        //cout << "this line:"<< this_line<<endl;
        vector<string> kkkey = split(ve[i],", ");
        int key = atoi(kkkey[0].c_str());
        int w  = make_hash(key);
        Insert(w,key,this_line);
    }
    ShowList();
    ve.clear();
    infile.close();
    FreeAll();
}

void switch_L(){
    Init();
    cout<<""<<endl;
    //C++ read
    ifstream infile;
    infile.open("Employee.csv");
    if(!infile) cout<<"error"<<endl;
    vector<string> ve;
    string line;//storing every line
    while(getline(infile,line))
    {
        ve.push_back(line);
    }

    cout<<"create index"<<endl;
    for(int i=0;i<ve.size();i++) {
        // create index
        string this_line  = ve[i];
        //cout << "this line:"<< this_line<<endl;
        vector<string> kkkey = split(ve[i],", ");
        int key = atoi(kkkey[0].c_str());
        int w  = make_hash(key);
        Insert(w,key,this_line);
    }
    ShowList();
    cout<<"search records:"<<endl;

    int query = make_hash(3);
    string a;
    do
    {
        cout<<"input a key:"<<endl;
        int f;
        cin >> f;
        int query = make_hash(f);
        a = Find(query,f);
        if (a!="sorry")
        {
            cout << "find:" <<endl;
            cout << a <<endl;
        }
    } while (a!="sorry");

    ve.clear();
    infile.close();
    FreeAll();
}
int main(){
    cout << "welcome, input c or l" << endl;
    cout << "switch_c can create index and provide the relationship(save in data.csv)" << endl;
    cout << "switch_l can look up with index already created only for screen" << endl;
    char s;
    cin >> s;
    if(s == 'c'){
        switch_C();
    }
    else if(s == 'l'){
        switch_L();
    }
    else{
        return 0;
    }
}