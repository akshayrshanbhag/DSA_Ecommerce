#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

struct location_array
{
    location_name[100];
};


struct customer_info
{
int customer_id;
char username[40];
char password[40];
int location_id;
char location[40];
};


void populate_location(struct location_array locations[SIZE])
{
    FILE *fp_location;
    int i = 0;

    fp_location = fopen("locations.txt","r");
    int dummy;

    while(!feof(fp_location))
    {
        fscanf(fp_location,"%d %s",&dummy,locations[i].location_name);
        i++;
    }

}

void customer_read(struct customer_info customers[SIZE], struct location_array locations[SIZE])
{
    FILE *fp_customer;
    fp_customer = fopen("customer.txt","r");

    int i = 0;
    int dummy;

 while(!feof(fp_customer)
    {
        fscanf(fp_customer,"%d %s %s %d",&customers[i].customer_id,customers[i].username,customers[i].password,&customers[i].location_id);
        strcpy(customers[i].location,locations[customers[i].location_id].location_name);
        i++;
    }
    fclose(fp_customer);
}


int main()
{
    struct customer_info customers[SIZE];
    struct location_array locations[SIZE];
    populate_location(locations);
    customer_read(customers, locations);
    return 0;
}

