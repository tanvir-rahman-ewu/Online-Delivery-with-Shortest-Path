#include<bits/stdc++.h>
using namespace std;

char grid[10][10];
int t=0,count=0;

void printGrid()
{
    cout<<"\t\t\t\t\t   Chip Star Game"<<endl;
    cout<<endl<<"                            1      2       3       4       5       6       7"<<endl<<endl;

    for(int i=1;i<=6;i++)
    {
        for(int j=1;j<=7;j++)
        {
            if(j==1)
            {
                cout<<"\t\t\t|";
            }
            cout<<"  "<<grid[i][j]<<"  "<<" | ";
        }

        cout<<endl;

        cout<<"\t\t\t";

        for(int j=0;j<56;j++)
        {
            cout<<"=";
        }

        cout<<endl;
    }
}

int input(int c,int p)
{
    int x=6,y=p;

    while(x)
    {
        if(grid[x][y]==' ')
        {
            if(t==0)
            {
                grid[x][y]='X';
                t=1;
                system("CLS");
                printGrid();
                break;
            }
            else
            {
                grid[x][y]='0';
                t=0;
                system("CLS");
                printGrid();
                break;
            }
        }
        else
        {
            x--;
        }
    }

    if(x==0)
    {
        system("CLS");
        printGrid();
        cout<<endl<<" \t\t\tSorry! Stack is full!"<<endl;
    }
    return t;
}
void is_game(int x,int y)
{

}
int main()
{
    for(int i=1;i<=6;i++)
    {
        for(int j=1;j<=7;j++)
        {
            grid[i][j]=' ';
        }
    }

    printGrid();
    char c;

    while(1)
    {
        if(t==0)
        {
            cout<<endl<<" \t\t\tPlayer 1 :";
            cin>>c;
        }
        else
        {
            cout<<endl<<" \t\t\tPlayer 2 :";
            cin>>c;
        }

        if(c=='1')
        {
            t=input(1,1);
        }
        else if(c=='2')
        {
            t=input(2,2);
        }
        else if(c=='3')
        {
            t=input(3,3);
        }
        else if(c=='4')
        {
            t=input(4,4);
        }
        else if(c=='5')
        {
            t=input(5,5);
        }
        else if(c=='6')
        {
            t=input(6,6);
        }
        else if(c=='7')
        {
            t=input(7,7);
        }
        else
        {
            system("CLS");
            printGrid();
            cout<<endl<<" \t\t\tSorry! Wrong place!"<<endl;
        }
    }
}
