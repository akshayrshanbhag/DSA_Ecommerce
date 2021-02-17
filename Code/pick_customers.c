#include<stdio.h>
#include<time.h>

time_t t;


int pick_customer()
{
    return(rand()%500);
}



int main()
{   int i;
    srand((unsigned) time(&t));
    int n = rand()% 100; // We are randomly choosing n no. of customers where  n<100
    for(i=0;i<n;i++)
    {
        int p = pick_customer(); //We are picking a random customer_ID p from the range of (0,499), i.e 500  customers
        authenticate(p);
    }
}
