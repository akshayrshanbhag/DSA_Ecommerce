#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define V 50
#define INF 99999


char temp_username[100], temp_password[100];
int ch;

time_t t;

int one_day_count = -1;
int priority_count = -1;
int normal_count = -1;


int count = -1;


int dist[V][V];


struct articles
{
int item_ID;
char article_name[100];
float cost;
int discount;
int popularity;
};


struct seller_info
{
int seller_id;
char username[40];
int no_of_items;
int location_id;
struct articles items[100];
};



struct location_array
{
    char location_name[100];
};


struct customer_info
{
int customer_id;
char username[40];
char password[40];
int location_id;
char location[40];
};


struct authenticate_info
{
int customer_id;
char username[40];
char password[40];
};



struct purchase_items
{
    int seller_ID;
    int item_ID;
};



struct purchase_table
{
    int hash_value;
    int customer_ID;
    struct purchase_items items_purchase[SIZE];
    int delivery_speed;
    int location_ID;
    float grand_total;
};

struct purchase_table purchases[SIZE];

struct stack_array{

float cost;
int discount;

};


struct one_day_def{
int dist;
int customer_ID;
};

struct priority_delivery_def{
int dist;
int customer_ID;
};

struct normal_def{
int dist;
int customer_ID;
};


struct seller_queue{
struct one_day_def one_day[SIZE];
struct priority_delivery_def priority_delivery[SIZE];
struct normal_def normal[SIZE];
int one_day_top;
int priority_top;
int normal_top;
};


struct seller_queue seller_q[SIZE];

int top;
struct stack_array cart[SIZE];



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
            fscanf(fp_items,"%d %d %s %f %d",&dummy,&sellers[i].items[j].item_ID,sellers[i].items[j].article_name,&sellers[i].items[j].cost,&sellers[i].items[j].discount);
        i++;
    }
    fclose(fp_seller);
    fclose(fp_items);
}



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

 while(!feof(fp_customer))
    {
        fscanf(fp_customer,"%d %s %s %d",&customers[i].customer_id,customers[i].username,customers[i].password,&customers[i].location_id);
        strcpy(customers[i].location,locations[customers[i].location_id].location_name);
        i++;
    }
    fclose(fp_customer);
}


void floydWarshall(int graph[][V])
{
	int i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];


	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

}


void authentication_load(struct authenticate_info authentications[SIZE])
{
    FILE *fp_customer;
    fp_customer = fopen("customer.txt","r");

    int i = 0,dummy;


 while(!feof(fp_customer))
    {
        fscanf(fp_customer,"%d %s %s %d",&authentications[i].customer_id,authentications[i].username,authentications[i].password,&dummy);
        i++;
    }
    fclose(fp_customer);
}


 void get_shortest_distances()
    {

    int graph[SIZE][V],i=0,j;
    FILE *fp;
    fp = fopen("adjacency_matrix.txt","r");

    while(!feof(fp))
    {
   for(j=0;j<V;j++)
    {
        fscanf(fp,"%d ",&graph[i][j]);
    }
    i++;
    }
    printf("Adjacency Matrix read\n");

    floydWarshall(graph);
	fclose(fp);

    }

int size = 0;


void swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}


void heapify(int array[], int size, int i) {
  if (size == 1)
  {
    printf("Single element in the heap");
  } else
  {

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] > array[largest])
      largest = l;
    if (r < size && array[r] > array[largest])
      largest = r;


    if (largest != i) {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}


void insert(int array[], int newNum) {
  if (size == 0) {
    array[0] = newNum;
    size += 1;
  } else {
    array[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

void push(float cost,int discount)
{
 cart[++top].cost =  cost;
 cart[top].discount = discount;
 printf("\tPUSHED...\n");

}

void pop(float *x,int *y)
{
    *x = cart[top].cost;
    *y = cart[top].discount;
    top--;

}

struct stack_temp_def{
int customer_id;
int dist;
};
struct stack_temp_def stack_temp[SIZE];

int stack_temp_top;



void fill_stack(int seller_id, int customer_id,int delivery)
{
    stack_temp_top = -1;
    int value = dist[seller_id][customer_id];

    if(delivery == 0)
    {
        seller_q[seller_id].normal_top = -1;
        if(value > seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist)
            {

                seller_q[seller_id].normal_top++;
                seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist = value;
                seller_q[seller_id].normal[seller_q[seller_id].normal_top].customer_ID = customer_id;


            }
        else{

            while(value>seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist)
            {
                stack_temp_top++;
                stack_temp[stack_temp_top].dist = seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist;
                stack_temp[stack_temp_top].customer_id = seller_q[seller_id].normal[seller_q[seller_id].normal_top].customer_ID;
                seller_q[seller_id].normal_top--;

            }
                seller_q[seller_id].normal_top++;
                seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist = value;
                seller_q[seller_id].normal[seller_q[seller_id].normal_top].customer_ID = customer_id;

            while(stack_temp_top != -1)
            {
                     seller_q[seller_id].normal_top++;
                     seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist = stack_temp[stack_temp_top].dist;
                     seller_q[seller_id].normal[seller_q[seller_id].normal_top].customer_ID = stack_temp[stack_temp_top].customer_id;
                     stack_temp_top--;
            }
        }

    }
    else if(delivery == 1)
    {
            seller_q[seller_id].priority_top = -1;
        if(value > seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist)
            {

                seller_q[seller_id].priority_top++;
                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist = value;
                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].customer_ID = customer_id;


            }
        else{

            while(value>seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist)
            {
                stack_temp_top++;
                stack_temp[stack_temp_top].dist = seller_q[seller_id].priority_delivery[seller_q[seller_id].normal_top].dist;
                stack_temp[stack_temp_top].customer_id = seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].customer_ID;
                seller_q[seller_id].priority_top--;

            }
                seller_q[seller_id].priority_top++;
                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist = value;
                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].customer_ID = customer_id;

            while(stack_temp_top != -1)
            {
                     seller_q[seller_id].priority_top++;
                     seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist = stack_temp[stack_temp_top].dist;
                     seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].customer_ID = stack_temp[stack_temp_top].customer_id;
                     stack_temp_top--;
            }
        }

    }
    else if(delivery == 2)
    {
        seller_q[seller_id].one_day_top = -1;
        if(value > seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist)
            {

                seller_q[seller_id].one_day_top++;
                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist = value;
                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].customer_ID = customer_id;


            }
        else{

            while(value>seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist)
            {
                stack_temp_top++;
                stack_temp[stack_temp_top].dist = seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist;
                stack_temp[stack_temp_top].customer_id = seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].customer_ID;
                seller_q[seller_id].one_day_top--;

            }
                seller_q[seller_id].one_day_top++;
                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist = value;
                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].customer_ID = customer_id;

            while(stack_temp_top != -1)
            {
                     seller_q[seller_id].one_day_top++;
                     seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist = stack_temp[stack_temp_top].dist;
                     seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].customer_ID = stack_temp[stack_temp_top].customer_id;
                     stack_temp_top--;
            }
        }


    }



}






void purchase(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{
    int i,j;
    float total;
    count++;
    int collect_seller_IDs[SIZE];
    top = -1;


    int z=0, u=0,w;
    int n = (rand() % (5-1+1))+1 ; // Selecting a cohort of sellers
    printf("Selected %d no. of sellers\n",n);
    printf("PURCHASING...\n");
            purchases[count].hash_value = p % SIZE;
            purchases[count].customer_ID = customers[p].customer_id;

    for(i=0;i<n;i++)
    {
        int k = rand() % (5-1+1)+1;  // Randomly selecting a seller_ID
        printf("\t\t%d =>  Seller_ID selected\n",k);


        collect_seller_IDs[u] = k;
        int m = ((p*1000)%5) + i;  // Selecting a cohort of items of seller_ID k
        printf("\t%d no. of items selected for seller_ID %d\n",m,k);
        for(j=0;j<m;j++)
        {
            int q = (p*1000)%(sellers[k].no_of_items+1);  // Select a item_ID q of seller_ID k
            //sellers[k].items[q].popularity++;
            push(sellers[k].items[j].cost,sellers[k].items[j].discount);
            printf("\t\t->->YES\n");
            z++;

        }

        u++;
    }
    total = 0;
    int discount = 0;
    float grand_total;

    float x;
    int y;
    int priority;
    int d;


     while(top != -1)
    {
        printf("Top=>%d\n");
        pop(&x,&y);
        printf("%f,%d\n",x,y);
        total+=x;
        discount+=y;

    }
    printf("\t\t%f=>total\n",total);
    grand_total = total - ((total*discount)/100) + ((total*18/100));
    //Adding taxes of 18 percent on pre -discount total cost;
    purchases[count].grand_total = grand_total;
    printf("Your Grand Total is %.2f\n",grand_total);

    printf("Choose a Delivery Speed\n");
    printf("1\tNormal\n2\tPriority\n3\tOne Day Delivery\n\n");
    int dummy = rand()%3;
    if(dummy == 0)
        printf("Normal Delivery Chosen\n");
    else if(dummy == 1)
        printf("Priority Delivery Chosen\n");
    else if(dummy == 2)
        printf("One Day Delivery Chosen\n");

    printf("\n\t\tYour Product Will Be Delivered Soon\n\n");
    purchases[count].location_ID = customers[p].location_id;
    purchases[count].delivery_speed = dummy;
        for(i=0;i<n;i++)
                {
                    fill_stack(collect_seller_IDs[i],p,dummy);
                    printf("filled stack\n");

                }


}





void login(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{

	printf("\nEnter Your Username\t");
	strcpy(temp_username,authentications[p].username);
	printf("%s\n",temp_username);
	printf("Enter Your Password\t");
	strcpy(temp_password,authentications[p].password);
	printf("%s\n",temp_password);
    int temp = 1;


		if (temp == 1)
        {
            printf("Login Valid!\n");
            purchase(p,sellers,customers,authentications);
        }

		else
            {
			printf("Account doesn't ");
			printf("exist, Please signup!!\n\n");
            }

}

int pick_customer()
{
    return(rand()%500);
}

void forward(struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{

    int i;
    srand((unsigned) time(&t));
    int n = rand()% 10; // We are randomly choosing n no. of customers where  n<10
    printf("Picked %d no. of customers\n",n);
    for(i=0;i<n;i++)
    {
        int p = pick_customer(); //We are picking a random customer_ID p from the range of (0,499), i.e 500  customers
        printf("\tPicked customer_ID => %d\n",p);
        login(p,sellers,customers,authentications);
    }

}



void display(struct seller_info sellers[SIZE],int count)
{
    int i,j;
    printf("SELLER_ID\tNAME\tNo.of Items\tLocation_ID\n");
    for(i = 0; i < count; i++)
    {
       printf("%d\t%s\t%d\t%d\n",sellers[i].seller_id,sellers[i].username,sellers[i].no_of_items,sellers[i].location_id);
       for(j=0;j<sellers[i].no_of_items;j++)
       {
           printf("\t%d\t%s\t%f\t%d\n",sellers[i].items[j].item_ID,sellers[i].items[j].article_name,sellers[i].items[j].cost,sellers[i].items[j].discount);

       }
    }

}


int main()
{

    srand((unsigned) time(&t));

    struct seller_info sellers[SIZE];
        seller_read(sellers);
        printf("Seller Read\n");
        display(sellers,30);

    struct customer_info customers[SIZE];
    struct location_array locations[SIZE];
        populate_location(locations);
        printf("Populated locations\n");



        customer_read(customers, locations);
        printf("Customer Read\n");
            get_shortest_distances();
            printf("Got Shortest Distance\n");
    struct authenticate_info authentications[SIZE];
        authentication_load(authentications);
        printf("Authentication Details Loaded\n");
int choice;
    int b = 1;

    while(b == 1)
   {

    printf("\nEnter\n1\tTo login with already available customers");
    printf("\n2\tTo Exit\n");
    printf("Enter Your Choice : ");


    scanf("%d",&choice);

    switch(choice)
    {

    case 1: forward(sellers,customers,authentications);
            break;
    case 2: b = 0;
            break;
    default: printf("\nPlease Enter the Right Choice!\n");
    }

    }


    return(0);
}
