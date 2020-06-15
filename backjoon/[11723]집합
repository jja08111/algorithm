#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int testCase,s=0,x;
    char operation[10];
    
    scanf("%d",&testCase);
    while(testCase--)
    {
        
        scanf("%s",operation);
        //all
        if(operation[0]=='a' && operation[1]=='l')
            s=(1<<21)-1;
        //empty
        else if(operation[0]=='e')
            s=0;
        else
        {
            scanf("%d",&x);
            //add
            if(operation[0]=='a')
                s |= (1<<x);
            //remove
            else if(operation[0]=='r')
                s &= ~(1<<x);
            //check
            else if(operation[0]=='c')
                printf("%d\n",(s&(1<<x) ? 1 : 0));
            //toggle
            else if(operation[0]=='t')
                s ^= (1<<x);
        }
    }
    return 0;
}
