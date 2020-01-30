#include<bits/stdc++.h>
#include <conio.h>
using namespace std;

/////////////////////////Dijkstra-start/////////////////////

map<string,int> m;

int matrix[100][100];
int d[100];
int n,x;
int employee_id=500001;
int customer_id=100001;
int prev[100];

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

void graph()
{
    ifstream in;
    in.open("weight.txt");

    string s;

    getline(in,s);
    n=atoi(s.c_str());

     x=1;

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
}

////////////////////////////////Dijkstra End////////////////////////////

void front_page()
{
    cout<<"......................................................."<<endl;
    cout<<"\t\t\t FOOD PANDA"<<endl;
    cout<<"\t\t      Aftab Nagar,Dhaka"<<endl;
    cout<<"......................................................."<<endl<<endl;;
    cout<<"\t1 . Take Order "<<endl;
    cout<<"\t2 . Registration "<<endl;
    cout<<"\t3 . Search Location"<<endl;
    cout<<"\t4 . Restaurants Information"<<endl;
    cout<<"\t5 . Users Information"<<endl;
    cout<<"\t6 . Employees Information"<<endl;
    cout<<"\t7 . Exit"<<endl;
}
void employee_front_page()
{
    cout<<"......................................................."<<endl;
    cout<<"\t\tEmployee Section"<<endl;
    cout<<"......................................................."<<endl<<endl;
    cout<<"\t1 . Add Employe"<<endl;
    cout<<"\t2 . Employee List"<<endl;
    cout<<"\t3 . Employee Status"<<endl;
    cout<<"\t4 . Edit"<<endl;

    cout<<endl<<"\tPress 0 to back to main menu"<<endl;
}
struct resturent
{
    string name;
    string location;
    string contact;
};
vector<resturent> r;

struct employee
{
    string name;
    int id;
    string contact;
    string location;
    string status;
};
vector<employee> e;

struct customer
{
    string name;
    string contact;
    string location;
    string exact_location;
    string password;
    int id;

};
vector<customer> c;

struct order
{
    string name;
    int id;
    string contact;
    string location;
    string exact_location;
    string resturent;
    vector<string> food;
};

void resturent_input()
{
    ifstream in;
    in.open("resturent.txt");

    string s,a,b,c;

    getline(in,s);
    int t=atoi(s.c_str());

    resturent temp;

    for(int i=0;i<t;i++)
    {
        getline(in,temp.name);
        getline(in,temp.location);
        getline(in,temp.contact);
        r.push_back(temp);
    }
}

void employee_input()
{
    ifstream in;
    in.open("employee.txt");

    string s,a,b,c;

    getline(in,s);
    int t=atoi(s.c_str());

    employee temp;

    for(int i=0;i<t;i++)
    {
        getline(in,temp.name);
        getline(in,temp.contact);
        temp.status="Free";
        temp.location="Office";
        temp.id=employee_id;
        employee_id++;
        e.push_back(temp);
    }
}

string string_converter(string name)
{
    if(name[0]>96)
    {
        name[0]=name[0]-32;
    }
    for(int i=1;i<name.length()-1;i++)
    {
        if(name[i]==' ')
        {
            if(name[i+1]>96)
            {
                name[i+1]=name[i+1]-32;
            }
        }
    }
    return name;
}
int search_location(string name)
{
    if(m.find(name)==m.end())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void print_order_memo(string source,string resturent_location,string destination,string resturent,order temp)
{
     system("CLS");
     cout<<"......................................................."<<endl;
     cout<<"\t\tOrder Information : "<<endl;
     cout<<"......................................................."<<endl<<endl;
     cout<<"Name : "<<temp.name<<endl;
     cout<<"Contact : "<<temp.contact<<endl;
     cout<<"Address : "<<temp.location<<endl;
     cout<<"Exact Address : "<<temp.exact_location<<endl;
     cout<<"Food Item : ";

     for(int i=0;i<temp.food.size();i++)
     {
         if(i!=temp.food.size()-1)
         {
              cout<<temp.food[i]<<" , ";
         }
         else
         {
             cout<<temp.food[i]<<endl;
         }
     }
     cout<<"Cost 50/="<<endl;

     cout<<"Path For Delivery: "<<endl;
     cout<<"(Office) ";
     dijkstra(m[source]);
     print_path(m[resturent_location]);
     dijkstra(m[resturent_location]);
     cout<<"("<<resturent<<")";
     print_path(m[destination]);
     cout<<destination<<"(Delivery Location)"<<endl;

     cout<<endl<<"Path For Come Back At Office : "<<endl;
     dijkstra(m[destination]);
     print_path(m[source]);
     cout<<source<<" (Office)"<<endl;
}
string create_password()
{
    char pass[32];
    string password;
    int i = 0;
    char a;

    for(i=0;;)
    {
        a=getch();
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
        {
            pass[i]=a;
            password=password+a;
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(a=='\r')
        {
            pass[i]='\0';
            break;
        }
    }

    return password;
}
int main()
{
    resturent_input();
    employee_input();

    graph();
    string choice;

    while(1)
    {
        front_page();

        cout<<endl<<"\tEnter Choice : ";
        cin>>choice;
        cin.ignore();

        if(choice=="1")
        {
            system("CLS");
            cout<<endl<<"\tOrder Info "<<endl<<endl;
            int t=0;
            for(int i=0;i<e.size();i++)
            {
                if(e[i].status=="Free")
                {
                    t++;
                    break;
                }
            }
            if(t==0)
            {
                cout<<"\tSorry All employees are busy "<<endl<<endl;
                system("Pause");
                system("CLS");
                continue;
            }

            order temp;

            cout<<"\tName : ";
            getline(cin,temp.name);
            cout<<"\tIs Member ? (y/n) :"<<endl;
            cout<<"\tEnter Choice : ";
            cin>>choice;
            if(choice=="y")
            {
                cout<<"\tEnter Id : ";
                cin>>temp.id;
                int t=0;
                for(int i=0;i<c.size();i++)
                {
                    if(c[i].id==temp.id)
                    {
                        temp.contact=c[i].contact;
                        temp.location=c[i].location;
                        temp.exact_location=c[i].exact_location;
                        cin.ignore();
                        t++;
                        break;
                    }
                }
                if(t==0)
                {
                    cout<<"\t Invalid Id"<<endl<<endl;
                    system("Pause");
                    system("CLS");
                    continue;
                }
            }
            else
            {
                cin.ignore();
                cout<<"\tMobile Number : ";
                getline(cin,temp.contact);
                cout<<"\tCustomer Location : ";
                getline(cin,temp.location);
                cout<<"\tExact Location : ";
                getline(cin,temp.exact_location);
            }

            if(!search_location(temp.exact_location))
            {
                cout<<endl<<"\tSorry! We Dont Cover this Location"<<endl<<endl;

            }
            else
            {
                cout<<"\tRestaurant name : ";
                getline(cin,temp.resturent);
                int t=0;
                for(int i=0;i<r.size();i++)
                {
                    if(r[i].name==temp.resturent)
                    {
                        t++;
                    }
                }
                if(t==0)
                {
                      cout<<endl<<"\tSorry! This restaurant is not availabe"<<endl<<endl;
                }
                else
                {
                    while(1)
                    {
                        cout<<"\tFood Item : ";
                        string food;
                        getline(cin,food);
                        temp.food.push_back(food);

                        cout<<"\tDo you want to add more food item? (y/n) ";
                        cin>>choice;
                        cin.ignore();
                        if(choice=="y")
                        {
                            continue;
                        }
                        else if(choice=="n")
                        {
                            cout<<"\tOrder Done!"<<endl<<endl;
                            string source="Aftab Nagar",destination=temp.exact_location,resturent,resturent_location;

                            int min=1000000;

                            for(int i=0;i<r.size();i++)
                            {
                                if(r[i].name==temp.resturent)
                                {
                                    int sum=0;
                                    dijkstra(m[source]);
                                    sum=sum+d[m[r[i].location]];
                                    dijkstra(m[r[i].location]);
                                    sum=sum+d[m[destination]];

                                    if(sum<min)
                                    {
                                        min=sum;
                                        resturent=r[i].name;
                                        resturent_location=r[i].location;
                                    }
                                }
                            }
                            system("Pause");
                            print_order_memo(source,resturent_location,destination,resturent,temp);
                            for(int i=0;i<e.size();i++)
                            {
                                if(e[i].status=="Free")
                                {
                                    cout<<endl<<"Employee "<<e[i].name<<" is selected for this delivery"<<endl<<endl;
                                    e[i].status="Busy";
                                    e[i].location="Outside";
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            system("Pause");
            system("CLS");
        }
        else if(choice=="2")
        {
            system("CLS");
            cout<<"......................................................."<<endl;
            cout<<"\t\tCustomer Registration "<<endl;
            cout<<"......................................................."<<endl<<endl;
            customer temp;

            cout<<"\tEnter name : ";
            getline(cin,temp.name);
            cout<<"\tEnter Address : ";
            getline(cin,temp.location);
            cout<<"\tExact Address : ";
            getline(cin,temp.exact_location);

            if(!search_location(temp.exact_location))
            {
                cout<<endl<<"\tSorry We dont cover this location"<<endl<<endl;
                system("Pause");
                system("CLS");
            }
            else
            {
                cout<<"\tContact : ";
                getline(cin,temp.contact);
                cout<<"\tEnter a Password : ";
                temp.password=create_password();
                cout<<endl;
                temp.id=customer_id;
                cout<<"\tId of "<<temp.name<<" is "<<temp.id<<endl;
                customer_id++;
                c.push_back(temp);
                cout<<endl<<"\tRegistration Done!"<<endl<<endl;
                system("Pause");
                system("CLS");
            }
        }
        else if(choice=="3")
        {
            system("CLS");
            while(1)
            {
                 cout<<"......................................................."<<endl;
                 cout<<"\t\tLocations Info "<<endl;
                 cout<<"......................................................."<<endl<<endl;
                 cout<<"\t1 . All Locations We Cover"<<endl;
                 cout<<"\t2 . Search Specific Location"<<endl;
                 cout<<endl<<"\tPress 0 to back to main menu"<<endl;
                 cout<<endl<<"\tEnter Choice : ";
                 cin>>choice;
                 cin.ignore();

                 if(choice=="1")
                 {
                     system("CLS");
                     cout<<endl<<"\tLocations We Cover  "<<endl<<endl;
                     for(map<string,int>:: iterator it=m.begin();it!=m.end();it++)
                     {
                         cout<<"\t"<<it->first<<endl;
                     }
                     cout<<endl;
                     system("PAUSE");
                     system("CLS");
                 }
                 else if(choice=="2")
                 {
                     system("CLS");
                     cout<<endl<<"\tSearch"<<endl<<endl;
                     cout<<"\tEnter Name : ";
                     string name;
                     getline(cin,name);

                     if(!search_location(name))
                     {
                         cout<<"\tNot found"<<endl;
                     }
                     else
                     {
                         cout<<"\tYes"<<endl<<endl;
                     }
                     system("PAUSE");
                     system("CLS");
                 }
                 else if(choice=="0")
                 {
                     system("CLS");
                     break;
                 }
                 else
                 {
                     system("CLS");
                     continue;
                 }
            }
        }
        else if(choice=="4")
        {
             system("CLS");

             while(1)
             {
                  cout<<"......................................................."<<endl;
                  cout<<"\t\tRestaurants  Information "<<endl;
                  cout<<"......................................................."<<endl<<endl;
                  cout<<"\t1 . Restaurants List"<<endl;
                  cout<<"\t2 . Add New Restaurant"<<endl;
                  cout<<endl<<"\tPress 0 to back to main menu"<<endl;
                  cout<<endl<<"\tEnter Choice : ";
                  cin>>choice;
                  cin.ignore();

                  if(choice=="1")
                  {
                      for(int i=0;i<r.size();i++)
                      {
                          cout<<"\t"<<r[i].name<<endl<<"\t"<<r[i].location<<endl<<"\t"<<r[i].contact<<endl<<endl;
                      }
                      system("PAUSE");
                      system("CLS");
                  }
                  else if(choice=="2")
                  {

                      system("CLS");
                      cout<<endl<<"\tRestaurant Add"<<endl<<endl;
                      cout<<"\tEnter Name : ";
                      resturent temp;
                      getline(cin,temp.name);
                      temp.name=string_converter(temp.name);
                      cout<<"\tEnter Location : ";
                      getline(cin,temp.location);
                      temp.location=string_converter(temp.location);

                      if(!search_location(temp.location))
                      {
                          cout<<endl<<"\tSorry We Dont Cover This Location"<<endl<<endl;
                          system("PAUSE");
                          system("CLS");
                      }
                      else
                      {
                          cout<<"\tEnter Contact : ";
                          getline(cin,temp.contact);
                          r.push_back(temp);
                          cout<<endl<<"\tAdded succesfully"<<endl<<endl;
                          system("PAUSE");
                          system("CLS");
                      }
                  }
                  else if(choice=="0")
                  {
                      system("CLS");
                      break;
                  }
                  else
                  {
                      system("CLS");
                      continue;
                  }
             }
        }
        else if(choice=="5")
        {
            system("CLS");

            while(1)
            {
                cout<<"......................................................."<<endl;
                cout<<"\t\tCustomer Informations"<<endl;
                cout<<"......................................................."<<endl<<endl;
                cout<<"\t1 . Customer List"<<endl;
                cout<<"\t2 . Edit Information"<<endl;
                cout<<endl<<"\tPress 0 to back to main menu"<<endl;
                cout<<endl<<"\tEnter Choice : ";
                cin>>choice;

                if(choice=="1")
                {
                    system("CLS");
                    cout<<endl<<"\tCustomer List"<<endl<<endl;

                    if(c.size()==0)
                    {
                        cout<<"\tNo One Register Yet"<<endl<<endl;
                    }
                    else
                    {
                        for(int i=0;i<c.size();i++)
                        {
                            cout<<"\tName : "<<c[i].name<<endl<<"\tId : "<<c[i].id<<endl;
                            cout<<"\tAddress : "<<c[i].location<<endl;
                            cout<<"\tExact Address : "<<c[i].exact_location<<endl<<"\tContact : "<<c[i].contact<<endl<<endl;
                        }
                    }
                    system("Pause");
                    system("CLS");
                }
                else if(choice=="2")
                {
                    system("CLS");

                    if(c.size()==0)
                    {
                        cout<<endl<<"\tEdit Option"<<endl<<endl;
                        cout<<"\t"<<"No customer register yet"<<endl<<endl;
                        system("Pause");
                        system("CLS");
                    }
                    else
                    {
                        cout<<endl<<"\tEdit Option"<<endl<<endl;
                        cout<<"\tEnter ID : ";
                        int id;
                        cin>>id;

                        int t=0;

                        for(int i=0;i<c.size();i++)
                        {
                            if(id==c[i].id)
                            {
                                t++;
                                cout<<"\tEnter Password : ";
                                string password;
                                password=create_password();

                                if(password==c[i].password)
                                {
                                    while(1)
                                    {
                                        system("CLS");
                                        cout<<endl<<"\tEdit Option"<<endl<<endl;
                                        cout<<"\t1 . Edit Location"<<endl;
                                        cout<<"\t2 . Edit Contact"<<endl;
                                        cout<<endl<<"\tPress 0 to back to main menu"<<endl;
                                        cout<<endl<<"\tEnter choice : ";
                                        cin>>choice;
                                        cin.ignore();

                                        if(choice=="1")
                                        {
                                            system("CLS");
                                            cout<<endl<<"\tEdit Location"<<endl<<endl;
                                            cout<<"\tCurrent Location of "<<c[i].name<<" is "<<c[i].location<<endl;
                                            cout<<endl<<"\tNew Location : ";
                                            string location,exact_location;
                                            getline(cin,location);
                                            cout<<endl<<"\tCurrent Exact Location of "<<c[i].name<<" is "<<c[i].exact_location<<endl;
                                            cout<<endl<<"\tNew Exact Location : ";
                                            getline(cin,exact_location);

                                            if(!search_location(exact_location))
                                            {
                                                cout<<"\tSorry This Location Is Not Coverable"<<endl;
                                                system("PAUSE");
                                                system("CLS");
                                            }
                                            else
                                            {
                                                c[i].location=location;
                                                c[i].exact_location=exact_location;
                                                cout<<endl<<"\tSuccessfully Changed!"<<endl<<endl;
                                                system("PAUSE");
                                                system("CLS");
                                            }
                                        }
                                        else if(choice=="2")
                                        {
                                            system("CLS");
                                            cout<<endl<<"\tEdit Contatact"<<endl<<endl;
                                            cout<<"\tCurrent Contact of "<<c[i].name<<" is "<<c[i].contact<<endl<<endl;
                                            cout<<"\tEnter New Contact : ";
                                            string contact;
                                            cin>>contact;
                                            c[i].contact=contact;
                                            cout<<endl<<"\tSuccessfully Changed!"<<endl<<endl;
                                            system("PAUSE");
                                            system("CLS");
                                        }
                                        else if(choice=="0")
                                        {
                                            system("CLS");
                                            break;
                                        }
                                        else
                                        {
                                            system("CLS");
                                            continue;
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    cout<<endl<<endl<<"\tWrong Password"<<endl<<endl;
                                    system("Pause");
                                    system("CLS");
                                    break;
                                }
                            }
                        }
                        if(t==0)
                        {
                            cout<<endl<<"\tInvalid ID"<<endl<<endl;
                            system("PAUSE");
                            system("CLS");
                        }
                    }
                }
                else if(choice=="0")
                {
                    system("CLS");
                    break;
                }
                else
                {
                    system("CLS");
                    continue;
                }
            }
        }
        else if(choice=="6")
        {
            system("CLS");

            while(1)
            {
                employee_front_page();

                cout<<endl<<"\tEnter Choice : ";
                cin>>choice;
                cin.ignore();

                if(choice=="1")
                {
                    system("CLS");

                    cout<<endl<<"\tEmployee Inforamtion "<<endl<<endl;

                    employee temp;

                    cout<<"\tName : ";
                    getline(cin,temp.name);
                    temp.name=string_converter(temp.name);
                    cout<<"\tMobile Number : ";
                    getline(cin,temp.contact);
                    temp.status="Free";
                    temp.location="Office";
                    temp.id=employee_id;
                    employee_id++;
                    cout<<"\tId of "<<temp.name<<" is : "<<temp.id<<endl<<endl;
                    e.push_back(temp);
                    cout<<endl<<"\tRegistration done"<<endl<<endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if(choice=="2")
                {
                    system("CLS");

                    cout<<endl<<"\tEmployee List "<<endl<<endl;

                    for(int i=0;i<e.size();i++)
                    {
                        cout<<"\tName : "<<e[i].name<<endl;
                        cout<<"\tId : "<<e[i].id<<endl;
                        cout<<"\tContact: "<<e[i].contact<<endl;
                        cout<<"\tLocation : "<<e[i].location<<endl;
                        cout<<"\tStatus : "<<e[i].status<<endl<<endl;

                    }
                    system("PAUSE");
                    system("CLS");
                }
                else if(choice=="3")
                {
                    system("CLS");
                    cout<<endl<<"\tEmployee Status "<<endl<<endl;

                    for(int i=0;i<e.size();i++)
                    {
                        cout<<"\t"<<e[i].name<<" : "<<e[i].status<<endl;
                    }
                    cout<<endl;
                    system("Pause");
                    system("CLS");
                }
                else if(choice=="4")
                {
                    system("CLS");

                    while(1)
                    {
                        cout<<endl<<"\tEdit Option "<<endl<<endl;
                        cout<<"\t1.Edit Status"<<endl;
                        cout<<"\t2.Edit Location"<<endl;
                        cout<<endl<<"\tPress 0 to back to main menu"<<endl;
                        cout<<endl<<"\tEnter Choice : ";
                        cin>>choice;
                        cin.ignore();
                        if(choice=="1")
                        {
                            system("CLS");
                            cout<<endl<<"\tEdit Status "<<endl<<endl;
                            cout<<"\tEnter Employee Name : ";
                            string name,status;
                            getline(cin,name);
                            int t=0;
                            for(int i=0;i<e.size();i++)
                            {
                                if(e[i].name==name)
                                {
                                    cout<<endl<<"\tCurrent Status Of "<<e[i].name<<" is "<<e[i].status<<endl;
                                    cout<<endl<<"\tNew Status : ";
                                    getline(cin,status);
                                    e[i].status=status;
                                    t++;
                                }
                            }
                            if(t==0)
                            {
                                cout<<endl<<"\tSorry This Employee doesn't Exist"<<endl<<endl;
                            }
                            system("Pause");
                            system("CLS");
                        }
                        else if(choice=="2")
                        {
                            system("CLS");
                            cout<<endl<<"\tEdit Location "<<endl<<endl;
                            cout<<"\tEnter Employee Name : ";
                            string name,location;
                            getline(cin,name);
                            int t=0;
                            for(int i=0;i<e.size();i++)
                            {
                                if(e[i].name==name)
                                {
                                    cout<<endl<<"\tCurrent Location Of "<<e[i].name<<" is "<<e[i].location<<endl;
                                    cout<<endl<<"\tNew Location : ";
                                    getline(cin,location);
                                    e[i].location=location;
                                    t++;
                                }
                            }
                            if(t==0)
                            {
                                cout<<endl<<"\tSorry This Employee doesn't Exist"<<endl<<endl;
                            }
                            system("Pause");
                            system("CLS");
                        }
                        else if(choice=="0")
                        {
                            system("CLS");
                            break;
                        }
                        else
                        {
                            system("CLS");
                            continue;
                        }
                    }
                }
                else if(choice=="0")
                {
                    system("CLS");
                    break;
                }
                else
                {
                    system("CLS");
                    continue;
                }
            }
        }
        else if(choice=="7")
        {
            cout<<endl<<"\t|| Thank You ||"<<endl;
            exit(1);
        }
        else
        {
            system("CLS");
            continue;
        }
    }
    return 0;
}
