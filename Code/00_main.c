#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10000
#define V 50
#define INF 99999


char temp_username[100], temp_password[100];
int ch;

time_t t;



int count = 0;


int dist[V][V];

struct articles
{
char article_name[100];
float cost;
float discount;
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

int top = -1;
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
            fscanf(fp_items,"%d %s %d %f %f",&dummy,sellers[i].items[j].article_name,&sellers[i].items[j].cost,&sellers[i].items[j].discount);
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

    int i = 0;


 while(!feof(fp_customer))
    {
        fscanf(fp_customer,"%d %s %s",&authentications[i].customer_id,authentications[i].username,authentications[i].password);
        i++;
    }
    fclose(fp_customer);
}


 void get_shortest_distances()
    {

    int graph[V][V],i,j;
    FILE *fp;
    fp = fopen("adjacency_matrix.txt","r");
    while(!feof(fp))
    {
   for(j=0;j<V;j++)
    {
        fscanf(fp,"%d",&graph[i][j]);
    }
    i++;
    }

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


 void enqueue(int seller_ID,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
 {








 }




void push(float cost,int discount)
{
 cart[++top].cost =  cost;
 cart[top].discount = discount;

}

void pop(float *x,int *y)
{
    *x = cart[top].cost;
    *y = cart[top--].discount;

}



void purchase(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{
    int i,j;
    float total;
    count++;
    int collect_seller_IDs[SIZE];

    int z=0, u=0;
    int n = rand() % 30; // Selecting a cohort of sellers

    for(i=0;i<n;i++)
    {
        int k = rand() % 30;  // Randomly selecting a seller_ID
        collect_seller_IDs[u] = k;
        int m = rand() % sellers[k].no_of_items;  // Selecting a cohort of items of seller_ID k
        for(j=0;j<m;j++)
        {
            int q = rand() % sellers[k].no_of_items;  // Select a item_ID q of seller_ID k
            purchases[count].hash_value == p % SIZE;
            purchases[count].customer_ID == customers[p].customer_id;
            purchases[count].items_purchase[z].seller_ID = k;
            purchases[count].items_purchase[z].item_ID = q;
            push(sellers[k].items[q].cost,sellers[k].items[q].discount);
            sellers[k].items[q].popularity++;
            z++;
        }
        u++;
    }

    total = 0;
    int discount = 0;
    float grand_total;
    int temp = top;
    float x;
    int y;

     while(top!= -1)
    {

        pop(&x,&y);
        total+=x;
        discount+=y;
    }
    grand_total = (float)total - ((total*discount)/100) + ((total*18/100));
    //Adding taxes of 18 percent on pre -discount total cost;
    purchases[count].grand_total = grand_total;
    printf("Your Grand Total is %f\n",grand_total);

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
       enqueue(collect_seller_IDs[i],sellers,customers);

}


int account_check(struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{
    int flag = 0, i;
	for (i = 0; i < 100; i++)
    {
		if (!(strcmp(temp_username, authentications[i].username)&& strcmp(temp_password,authentications[i].password)))
        {
			printf("\n\nAccount Exists");
			flag = 1;
		}
    }
return flag;
}


void login(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{

	printf("\nEnter Your Username\t");
	strcpy(temp_username,authentications[p].username);
	printf("%s\n",temp_username);
	printf("Enter Your Password\t");
	strcpy(temp_password,authentications[p].password);
	printf("%s\n",temp_password);


		int temp = account_check(sellers,customers,authentications);
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
    int n = rand()% 100; // We are randomly choosing n no. of customers where  n<100
    for(i=0;i<n;i++)
    {
        int p = pick_customer(); //We are picking a random customer_ID p from the range of (0,499), i.e 500  customers
        login(p,sellers,customers,authentications);
    }

}


int main()
{

    struct seller_info sellers[SIZE];
        seller_read(sellers);
    struct customer_info customers[SIZE];
    struct location_array locations[SIZE];
        populate_location(locations);
        customer_read(customers, locations);
            get_shortest_distances();
    struct authenticate_info authentications[SIZE];
        authentication_load(authentications);
int choice;
    int b = 1;

    while(b = 1)
   {
    printf("\nEnter\n1\tTo Register a new customer");
    printf("\n2\tTo login with already available customers");
    printf("\n3\tTo Exit");


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
