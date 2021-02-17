#include<stdio.h>
#include<time.h>


time_t t;



int main()
{
    int p,i,j,z,y;
    float total;
    int array_item_ID[30][10];

    for(z=0;z<30;z++)
    {
        for(y=0;y<10;y++)
        {
           array_item_ID[z][y] = 0;
        }
    }

    int n = rand() % 30; // Selecting a cohort of sellers

    for(i=0;i<n;i++)
    {
        int k = rand() % 30;  // Randomly selecting a seller_ID
        int m = rand() % sellers[k].no_of_items;  // Selecting a cohort of items of seller_ID k
        for(j=0;j<m;j++)
        {
            int q = rand() % sellers[k].no_of_items;  // Select a item_ID q of seller_ID k
            array_item_ID[i][j] = q;
            printf("Selected Item_ID %d of Seller_ID %d\n",q,k);
            sort_n_display(array_item_ID);
            total = cart(p,k,q);// p=> Customer_ID, k=>Seller_ID, q=>Item_ID

        }
    }

}
