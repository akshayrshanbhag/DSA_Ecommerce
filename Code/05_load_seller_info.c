#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000



struct articles
{
char article_name[100];
float cost;
float discount;
};


struct seller_info
{
int seller_id;
char username[40];
int no_of_items;
int location_id;
struct articles items[100];
};


void seller_read(struct seller_info sellers[SIZE])
{
    char temp[SIZE];
    FILE *fp_seller;
    FILE *fp_items;

    fp_seller = fopen("seller.txt","r");
    fp_items  = fopen("items.txt","r");
    int i=0;
    int dummy;

 while(!feof(fp_seller) && !feof(fp_items))
    {
        fscanf(fp_seller,"%d %s %d %d",&sellers[i].seller_id,sellers[i].username,&sellers[i].no_of_items,&sellers[i].location_id);
        int j;
        for(j=0; j<sellers[i].no_of_items; j++)
            fscanf(fp_items,"%d %s %d %f %f",&dummy,sellers[i].items[j].article_name,&sellers[i].items[j].cost,&sellers[i].items[j].discount);
        i++;
    }
    fclose(fp_seller);
    fclose(fp_items);

    return i;
}

/*void display(struct seller_info sellers[SIZE],int count)
{
    int i;
    printf("SELLER_ID\tNAME\tNo.of Items\tLocation_ID\n");
    for(i = 0; i < count; i++)
    {
       printf("%d\t%s\t%d\t%d\n",sellers[i].seller_id,sellers[i].username,sellers[i].no_of_items,sellers[i].location_id);
    }

}
*/
int main()
{


    struct seller_info sellers[SIZE];

    seller_read(sellers);

   // display(sellers,k);

    return 0;
}
