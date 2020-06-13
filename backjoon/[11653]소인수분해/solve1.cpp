#include <iostream>
using namespace std;

void printResult(int n)
{
    for(int i=2;i<n;++i)
        while(n%i==0)
        {
            n/=i;
            cout<<i<<endl;
        }
        
    if(n>1)
        cout<<n<<endl;
}

int main()
{
    int n;
    cin>>n;
    
    printResult(n);

    return 0;
}
