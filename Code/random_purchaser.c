#include<stdio.h>
#include<time.h>


time_t t;



int main()
{
    int p;
    float total

    int n = rand() % 30 // Selecting a cohort of sellers

    for(i=0;i<n;i++)
    {
        int k = rand() % 30  // Randomly selecting a seller_ID
        int m = rand() % sellers[k].no_of_items;  // Selecting a cohort of items of seller_ID k
        for(j=0;j<m;j++)
        {
            int q = rand() % sellers[k].no_of_items;  // Select a item_ID q of seller_ID k
            printf("Selected Item_ID %d of Seller_ID %d\n",q,k);
            total = cart(p,k,q);// p=> Customer_ID, k=>Seller_ID, q=>Item_ID

        }
    }

}
