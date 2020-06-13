#include <iostream>
using namespace std;

int n;

void printStars(int line)
{
    for(int j=0;j<line;++j)
        cout<<" ";
    for(int stars=line*2;stars<(n*2)-1;++stars)
        cout<<"*";
    cout<<endl;
}

int main()
{
    cin>>n;
    
    for(int line=0;line<n;++line)
        printStars(line);
    for(int line=n-2;line>=0;--line)
        printStars(line);
    return 0;
}
