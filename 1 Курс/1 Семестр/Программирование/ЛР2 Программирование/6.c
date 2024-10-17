#include <stdio.h>
#include <stdlib.h>

int main(){
    int h=6,m=0,len=25;
    while (h<23){
        printf("%i:%i\n", h, m);
        m+=len;
        if(m>=60) {
            h+=m/60; 
            m=m-60;
            
        }
    }
    system("pause");
    return 0;
}
