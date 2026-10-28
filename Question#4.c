#include <stdio.h>
int main(void){
    int number_of_days;
    while(1){
        printf("Enter Number of Days: ");
        scanf("%d",&number_of_days);
        if(number_of_days>=1 && number_of_days<=7){
            break;
        }
        
    }
    return 0;
}