#include <stdio.h>

int main()
{
    int ch;
    int b = 1;

    while(b = 1)
   {
    printf("\nEnter\n1\tTo Register a new customer");
    printf("\n2\tTo login with already available customers");
    printf("\n3\To Exit");


    scanf("%d",&ch);

    switch(ch){

    case 1: register();
            break;
    case 2: login();
            break;
    case 3: b=0;
            break;
    default: printf("\nPlease Enter the Right Choice!\n");

    }

   }

    return(0);
}
