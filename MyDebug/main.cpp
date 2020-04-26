#include <iostream>

using namespace std;

int main()
{
    int sum=0;

    int A[]={1,26,87,5,69};

    for(auto x:A)
    {
        sum=sum+x;
    }

    cout<<sum;
    return 0;
}
