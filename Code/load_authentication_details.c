#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

struct authenticate_info
{
int customer_id;
char username[40];
char password[40];
};


void authentication_load(struct authenticate_info authentications[SIZE])
{
    FILE *fp_customer;
    fp_customer = fopen("customer.txt","r");

    int i = 0;


 while(!feof(fp_customer)
    {
        fscanf(fp_customer,"%d %s %s",&authentications[i].customer_id,authentications[i].username,authentications[i].password);
        i++;
    }
    fclose(fp_customer);
}


int main()
{
    struct authenticate_info authentications[SIZE];

    authentication_load(authentications);
    return 0;
}

