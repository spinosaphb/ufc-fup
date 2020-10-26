#include <iostream>

int main(){
    int a,b;
    std::cin >> a >> b;
    a-=b;
    a= a & a >> 31;
    std::cout << a << std::endl;
    a+=b;
    std::cout << a;
}