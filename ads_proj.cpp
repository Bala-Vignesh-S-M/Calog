#include<bits/stdc++.h>
using namespace std;
class Time
{
    int hr,min;
public:
    Time(int h=0,int m=0);
    Time(const Time &t);
    bool operator <(Time &t);
    bool operator >(Time &t);
    bool operator ==(Time &t);
    friend ostream& operator <<(ostream &out,const Time &t);
    int isNull();
    void get_time();
};
Time::Time(int h,int m)
{
    hr=h;
    min=m;
}
Time::Time(const Time &t)
{
    hr=t.hr;
    min=t.min;
}
bool Time::operator<(Time &t)
{
    if(hr<t.hr)
        return true;
    else if(min<t.min)
        return true;
    else
        return false;
}
bool Time::operator>(Time &t)
{
    if(hr>t.hr)
        return true;
    else if(min>t.min)
        return true;
    else
        return false;
}
bool Time::operator==(Time &t)
{
    if((hr==t.hr)&&(min==t.min))
        return true;
    else
        return false;
}
ostream& operator <<(ostream &out,const Time &t)
{
    out<<t.hr<<':'<<setw(2)<<t.min<<' ';
    return out;
}
int Time::isNull()
{
    if(this->hr==0&&this->min==0)
        return 1;
    else
        return 0;
}
void Time::get_time()
{
    int h,m;
    do
    {
        cout<<"Enter hours: ";
        cin>>h;
        if(h>23||h<0)
            cout<<"Enter valid hours\n";
    }while(h>24||h<0);
    do
    {
        cout<<"Enter minutes: ";
        cin>>m;
        if(m>59||m<0)
                cout<<"Enter valid hours\n";
    }while(m>59||m<0);
    hr=h;
    min=m;
}
struct node
{
    string name,number;
    Time time_of;
    node *left, *right;
};
node* newNode(string num,string nam,Time t)
{
    node* Node = new node();
    Node->name = nam;
    Node->number=num;
    Node->time_of = t;
    Node->left = Node->right = NULL;
    return (Node);
}
node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
node *splay(node *root, Time t)
{
    if (root == NULL || root->time_of == t)
        return root;
    if (root->time_of > t)
    {
        if (root->left == NULL)
            return root;

        if (root->left->time_of > t)
        {
            root->left->left = splay(root->left->left, t);
            root = rightRotate(root);
        }
        else if (root->left->time_of < t)
        {
            root->left->right = splay(root->left->right, t);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL)? root: rightRotate(root);
    }
    else
    {
        if (root->right == NULL)
            return root;

        if (root->right->time_of > t)
        {
            root->right->left = splay(root->right->left, t);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->time_of < t)
        {
            root->right->right = splay(root->right->right, t);
            root = leftRotate(root);
        }
        return (root->right == NULL)? root: leftRotate(root);
    }
}
node *insert(node *root, string num, string nam, Time t)
{
    if (root == NULL)
        return newNode(num,nam,t);
    root = splay(root, t);
    if (root->time_of == t)
        return root;
    node *newnode = newNode(num,nam,t);
    if (root->time_of > t)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
    return newnode;
}
struct node* delete_key(struct node *root, Time t)
{
    struct node *temp;
    if (!root)
        return NULL;
    root = splay(root, t);
    if (!(t == root->time_of))
        return root;
    if (!root->left)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splay(root->left, t);
        root->right = temp->right;
    }
    free(temp);
    return root;

}
void InOrder(node *root)
{
    if (root != NULL)
    {
        InOrder(root->left);
        cout<<setw(12)<<root->number<<" "<<setiosflags(ios::left)<<setw(20)<<root->name<<" "<<root->time_of<<endl;
        InOrder(root->right);
    }
}
Time search_by_num(node *root, string key)
{
    stack<node *> s;
    node *curr=root;
    Time t;
    while (curr!=NULL||s.empty()==false)
    {
        while (curr!=NULL)
        {
            s.push(curr);
            curr=curr->left;
        }
        curr=s.top();
        s.pop();
        if(curr->number==key)
            t=curr->time_of;
        curr=curr->right;
    }
    return t;
}
Time search_by_name(node *root, string nam)
{
    stack<node *> s;
    node *curr=root;
    Time t;
    while (curr!=NULL||s.empty()==false)
    {
        while (curr!=NULL)
        {
            s.push(curr);
            curr=curr->left;
        }
        curr=s.top();
        s.pop();
        if(curr->name==nam)
            t=curr->time_of;
        curr=curr->right;
    }
    return t;
}
int invalidName(string name)
{
    for(int i=0;i<int(name.length());i++)
    {
        if((!isalpha(name[i]))&&(name[i]!=' '))
            return 1;
    }
    return 0;
}
int main()
{
    node *root=NULL;
    string no;
    int c;
    Time t;
    string name;
    cout<<"CALL LOG MENU"<<endl<<endl;
    char m='Y';
    while(m=='Y'||m=='y')
    {
        cout<<"1. Add New Log\n2. Search for a Log"<<endl;
        cout<<"3. Delete a Log\n4. List the Call Log"<<endl;
        cout<<"5. Exit\n";
        cout<<"Enter option: ";
        cin>>c;
        switch (c)
        {
            case 1:
                {
                    cout<<"Enter the phone number"<<endl;
                    cin>>no;
                    do
                    {
                        cout<<"Enter the name of the contact"<<endl;
                        fflush(stdin);
                        getline(cin,name);
                        if(invalidName(name))
                            cout<<"Enter valid name\n";
                    }while(invalidName(name));
                    cout<<"Enter time of call:\n";
                    t.get_time();
                    root=insert(root,no,name,t);
                }
                break;
            case 2:
                {
                    cout<<"Choose method to search"<<endl;
                    cout<<"1. According to Contact Number\n2. According to Name of the Contact"<<endl;
                    int cho;
                    cin>>cho;
                    if(cho==1)
                    {
                        cout<<"Enter the Contact Number to search: ";
                        cin>>no;
                        t=search_by_num(root,no);
                        if(t.isNull())
                        {
                            cout<<"Log Not Found\n";
                            break;
                        }
                        root=splay(root,t);
                        cout<<"Contact Number:      "<<root->number<<endl;
                        cout<<"Name of the Contact: "<<root->name<<endl;
                        cout<<"Time of last call: "<<root->time_of<<endl;
                    }
                    else if(cho==2)
                    {
                        cout<<"Enter the Name of the Contact: ";
                        cin>>name;
                        t=search_by_name(root,name);
                        if(t.isNull())
                        {
                            cout<<"Log Not Found\n";
                            break;
                        }
                        root=splay(root,t);
                        cout<<"Contact Number:      "<<root->number<<endl;
                        cout<<"Name of the Contact: "<<root->name<<endl;
                        cout<<"Time of last call: "<<root->time_of<<endl;
                    }
                }
                break;
            case 3:
                {
                    cout<<"Choose method to delete"<<endl;
                    cout<<"1. According to Contact Number\n2. According to Name of the Contact"<<endl;
                    int cho;
                    cin>>cho;
                    if(cho==1)
                    {
                        cout<<"Enter the Contact Number to delete: ";
                        cin>>no;
                        t=search_by_num(root,no);
                        if(t.isNull())
                        {
                            cout<<"Log Not Found\n";
                            break;
                        }
                        root=splay(root,t);
                        root=delete_key(root,root->time_of);
                        cout<<"Log deleted.\n";
                    }
                    else if(cho==2)
                    {
                        cout<<"Enter the Name of the Contact: ";
                        cin>>name;
                        t=search_by_name(root,name);
                        if(t.isNull())
                        {
                            cout<<"Log Not Found\n";
                            break;
                        }
                        root=splay(root,t);
                        root=delete_key(root,root->time_of);
                        cout<<"Log deleted.\n";
                    }
                }
                break;
            case 4:
                {
                    cout<<"Call Log:"<<endl;
                    cout<<setw(12)<<"Phone Number"<<" "<<setiosflags(ios::left);
                    cout<<setw(20)<<"Name"<<" "<<"Time\n";
                    if(root!=NULL)
                        InOrder(root);
                    else
                        cout<<"Log is empty.\n";
                }
                break;
            case 5:exit(0);

        }
        cout<<"Do you want to continue in main menu?(y/n) ";
        cin>>m;
    }
    return 0;
}
