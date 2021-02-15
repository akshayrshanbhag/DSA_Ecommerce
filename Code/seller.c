#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int count;

struct articles
{
char article_name[100];
float cost;
};


struct seller_info
{
int seller_id;
char name[40];
char location[20];
struct articles items[100];
};


void seller_write(struct seller_info sellers[SIZE])
{
    char temp[SIZE];
    FILE *fp;

    fp = fopen("seller.txt","a");
    count++;
    sellers[count].seller_id = count;
    fprintf(fp,"\n%d\t",sellers[count].seller_id);
    printf("Enter Seller Name : ");
    scanf("%s", sellers[count].name);
    fprintf(fp,"%s",sellers[count].name);
    printf("Enter Seller Location: Mumbai/ Bangalore/ New Delhi/ Pune/ Chennai/ Vishakapatnam/ Chandigarh: \n");
    scanf("%s",&sellers[count].location);
    fprintf(fp,"\t%s",sellers[count].location);

    printf("Your Seller ID is %d\n",sellers[count].seller_id);
    fclose(fp);
}

void display(struct seller_info sellers[SIZE])
{
    int i;
    printf("SELLER_ID\tNAME\tLOCATION\n");
    for(i = 0; i < count; i++)
    {
        printf("%d\t\t%s\t%s\n",sellers[i+1].seller_id,sellers[i+1].name,sellers[i+1].location);
    }

}

int main()
{

    count = 0;
    struct seller_info sellers[SIZE];

    seller_write(sellers);
    display(sellers);

    return 0;
}
