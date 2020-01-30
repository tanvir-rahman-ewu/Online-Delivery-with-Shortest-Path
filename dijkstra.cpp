#include<bits/stdc++.h>
using namespace std;

map<string,int> m;

int matrix[100][100];
int d[100];
int prev[100];
int n;

struct edge
{
    int name;
    int distance;

    bool operator < (const edge& p) const
    {
        return distance>p.distance;
    }
};

void dijkstra(int source)
{

    priority_queue<edge> p;

    for(int i=1;i<=n;i++)
    {
        d[i]=1000000;
        prev[i]=-1;
    }

    d[source]=0;

    edge temp;

    temp.distance=0;
    temp.name=source;

    p.push(temp);

    while(!p.empty())
    {
        temp=p.top();
        p.pop();

        for(int i=1;i<=n;i++)
        {
            if(matrix[temp.name][i]!=0)
            {
                edge t;

                t.name=i;
                t.distance=d[temp.name]+matrix[temp.name][i];

                if(d[i]>t.distance)
                {
                    prev[i]=temp.name;
                    d[i]=t.distance;
                    p.push(t);
                }
            }
        }
    }
}
void print_place(int a)
{
    for(map<string,int>:: iterator it=m.begin();it!=m.end();it++)
    {
        if(a==it->second)
        {
            cout<<it->first<<" -> ";
        }
    }
}
void print_path(int i)
{
    if(prev[i]==-1)
    {
        return;
    }
    else
    {
        print_path(prev[i]);

        print_place(prev[i]);
    }
}


int main()
{
    ifstream in;
    in.open("weight.txt");

    string s;

    getline(in,s);
    n=atoi(s.c_str());

    int x=1;

    for(int i=0;i<n;i++)
    {
        string a,b,c;
        int w;

        getline(in,a);

        getline(in,b);

        getline(in,c);

        w=atoi(c.c_str());

        if(m[a]==0)
        {
            m[a]=x;
            x++;
        }

        if(m[b]==0)
        {
            m[b]=x;
            x++;
        }

        matrix[m[a]][m[b]]=w;
        matrix[m[b]][m[a]]=w;

    }

    while(1)
    {
        cout<<"Enter Source : ";
        string source;
        getline(cin,source);
        dijkstra(m[source]);
        cout<<"Enter destination : ";
        string destination;
        getline(cin,destination);
        cout<<d[m[destination]]<<endl;;
    }
}
