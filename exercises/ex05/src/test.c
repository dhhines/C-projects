#include <stdlib.h>
#include <stdio.h>

int main()
{
    
    double d = -1;

    long l = -1;

    if (d == l){
        printf("Equal ");
        printf("%lf\n%ld", d, l);
    } 
    else {
        printf("not equal ");
        printf("%lf\n%ld", d, l);
    }

    return 0;
}
