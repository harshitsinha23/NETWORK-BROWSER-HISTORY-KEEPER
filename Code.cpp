#include<bits/stdc++.h>
#define int long long int
#define inf 100000000000000
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
int mod=1000000007;
int cnt=0;
vector<string> URL;
vector<string> prefix;
class multilist{
public:
    string data;
    multilist *next;
    multilist *child;

    multilist(string str)
    {
        data=str;
        next=NULL;
    }
};

multilist *createlist(vector<string> str, int n)
{
    multilist*head=NULL;


    for(int i=0;i<n;i++)
    {
        multilist*p=new multilist(str[i]);
        p->next=head;
        head=p;
    }

    return head;

}

void printmultilist(multilist *head)
{
    while(head!=NULL)
    {
        cout<<head->data<<endl;
        head=head->next;
    }
    cout<<endl;
}

class node{
public:
    char data;
    bool terminal;
    map<char,node*> children;

    node(char data)
    {
        this->data=data;
        this->terminal = false;
    }

};

class trie{
public:
    node*root;
    int count;

    trie()
    {
        this->root=new node('\0');
        this->count=0;
    }



void addword(string str)
{
    node*temp=root;

    for(int i=0;i<str.size();i++)
    {
        char ch=str[i];
        if(temp->children.count(ch))
        {
            temp=temp->children[ch];
        }
        else
        {
            node*n=new node(ch);
            temp->children[ch]=n;
            temp=n;
        }
    }
    temp->terminal=true;
}

bool search(string str)
{
    node*temp=root;

    for(int i=0;i<str.size();i++)
    {
        char ch=str[i];

        if(temp->children.count(ch))
        {
            temp=temp->children[ch];
        }
        else
        {
            return false;
        }
    }
    if(temp->terminal==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check(node*root)
{
    node*temp=root;
    for(int i=0;i<256;i++)
    {
        char ch=i;
        if(temp->children.count(ch))
        {
            return 0;
        }
    }
    return 1;
}

void suggestURL(node*root,string str)
{
    if(root->terminal)
    {
       prefix.push_back(str);
    }

    if(check(root))
    {
        return;
    }

    for(int i=0;i<256;i++)
    {
        char ch=i;
        if(root->children.count(ch))
        {
            str.push_back(ch);
            suggestURL(root->children[ch],str);
            str.pop_back();
        }
    }
}

int printURL(const string str)
{
    node*temp=root;

    for(int i=0;i<str.size();i++)
    {
        char ch=str[i];
        if(!temp->children.count(ch))
        {
            return 0;
        }
        temp=temp->children[ch];
    }

    if((temp->terminal==true) && check(temp))
    {
        cout<<str<<endl;
        return -1;
    }

    if(!check(temp))
    {
        string p=str;
        suggestURL(temp,p);
        return 1;
    }

}
};
int32_t main()
{
    trie root;
    root.addword("godaddy.com");
    root.addword("google.com");
    root.addword("hackerearth.com");
    root.addword("facebook.com");
	root.addword("faceapp.com");
	root.addword("youtube.com");
	root.addword("whatsapp.com");
	root.addword("imdb.com");
	root.addword("codeforces.com");
	root.addword("codechef.com");
    while(true)
    {
        cout<<"Press 1 to search a URL"<<endl;
        cout<<"Press 2 to exit"<<endl;
        cout<<"Press 3 to print the browser history"<<endl<<endl;
        int a;
        cin>>a;

        if(a==1)
        {
         	prefix.resize(0);
            cout<<"Please enter any prefix of your URL"<<endl;
            string s;
            cin>>s;
           // URL.push_back(s);
            //cnt++;
            int c=root.printURL(s);

            if(c==0)
            {
            	string s1;
                cout<<"No URL found , enter your URL"<<endl;
                cin>>s1;
                root.addword(s1);
                URL.push_back(s1);
                cnt++;
            }
            else
            {
            	int t;
            	cout<<"Select the URL you want to search by entering the index no. , Enter anything else to enter your URL"<<endl;
            	for( int i=0;i<prefix.size();i++)
            	{
            		
            		cout<<prefix[i]<<" "<<i<<endl;
				}
				cin>>t;
				if(t>=0 && t<prefix.size())
				{
					URL.push_back(prefix[t]);
					cnt++;
				}
				else
				{
					string s2;
					cout<<"Enter your URL"<<endl;
					cin>>s2;
					root.addword(s2);
                    URL.push_back(s2);
                    cnt++;
					
					
				}
			}
             

        }
        else
        {
            if(a==2)
            {
                break;
            }
            else
            {
                if(a==3)
                {
                    cout<<endl;

                    multilist*head=createlist(URL,cnt);
                    printmultilist(head);
                }
                else
                {
                    cout<<"Wrong Input"<<endl;
                }

            }
        }
    }

    return 0;
}
