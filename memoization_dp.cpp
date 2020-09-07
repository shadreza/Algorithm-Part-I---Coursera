#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
long long int a[1000000]={0};
long long int fib(long long int x){
    if(a[x]==0){
        if(x==0){
            a[x]=0;
        }
        else if(x==1){
            a[x]=1;
        }
        else{
            a[x]=fib(x-1)+fib(x-2);
        }
    }
    return a[x];
}
int main(){
    cout<<fib(50)<<endl;
}
