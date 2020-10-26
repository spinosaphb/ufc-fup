#include <iostream>

int main(){
    int n, x, y, s;
    char c;
    scanf("%d%d%d %c %d", &n, &x, &y, &c, &s);
    if(!(c-'U') || !(c-'D'))
        y = (c=='U')?(((y-s)%n)+n)%n:(((y+s)%n)+n)%n;
    else
        x = (c=='L')?(((x-s)%n)+n)%n:(((x+s)%n)+n)%n;
    printf("%d %d", x, y);

    return 0;
}