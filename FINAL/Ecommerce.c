#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>
#include <time.h>

//PRE PROCESSING INCLUSIONS

#define SIZE 100

// A SIZE is defined as 100

#define V 50

//V IS NO. OF VERTICES OF GRAPH

// WHICH IS USED IN FLOYED WARSHALL ALGORITHM

#define INF 99999

//IF A NODE IS NOT REACHABLE IT IS ASSIGNED AS INFINITY i.e INF

//GLOBAL DECLARATIONS

char temp_username[100];

char temp_password[100];

// FOR USE IN AUTHENTICATION

int ch;

time_t t;

//system time variable for use in rand() function

int one_day_count = -1;

int priority_count = -1;

int normal_count = -1;


int count = -1;


// VARIOUS OTHER DECLARATIONS WHICH HAD TO BE DECLARED GLOBALLY

int dist[V][V];

// SHORTEST DISTANCE MATRIX GOT FROM FLOYD WARSHALL ALGORITHM



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

struct articles items[20];

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

    float cost;

    int discount;
};




struct purchase_table
{
    int hash_value;

    int customer_ID;

    struct purchase_items items_purchase[SIZE];

    int delivery_speed;

    int location_ID;

    float grand_total;

    int n;
};



struct purchase_table purchases[SIZE];


struct stack_array
{

float cost;

int discount;

};



struct one_day_def
{

int dist;

int customer_ID;

};




struct priority_delivery_def
{
int dist;
int customer_ID;
};




struct normal_def
{
int dist;
int customer_ID;
};




struct queue
{
int priority;

int customer_ID;
};


struct seller_queue
{
struct one_day_def one_day[SIZE*5];

struct priority_delivery_def priority_delivery[SIZE*5];

struct normal_def normal[SIZE];

struct queue queues[SIZE*5];

int one_day_top;

int priority_top;

int normal_top;

int size;
};



struct seller_queue seller_q[SIZE];


int top;


struct stack_array cart[SIZE*5];




struct stack_temp_def
{
int customer_id;

int dist;

};
struct stack_temp_def stack_temp[SIZE];

int stack_temp_top;




void seller_read(struct seller_info sellers[SIZE]);


void populate_location(struct location_array locations[SIZE*5]);


void customer_read(struct customer_info customers[SIZE], struct location_array locations[SIZE]);


void floydWarshall(int graph[][V]);


void authentication_load(struct authenticate_info authentications[SIZE]);


void get_shortest_distances();


void swap(int *a, int *b);


void heapify(struct seller_queue array[SIZE*5], int size, int i,int j);


void deleteRoot(struct seller_queue array[SIZE*5],int num, int k);


void print_Array(struct seller_queue array[SIZE*5],int size,int k);


void fill();


void insert(struct seller_queue array[SIZE*5],int i,int priority,int customer_ID);


void push(float cost,int discount);


void pop(float *x,int *y);


void fill_stack(int seller_id, int customer_id,int delivery);


void purchase(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE]);


void login(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE]);


int pick_customer();


void forward(struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE]);


void printSolution();



// MAIN FUNCTION=>



int main()
{
    printf("\t\tE_COMMERCE PURCHASE AND MANAGEMENT SYSTEM\n");
    printf("\t\t\tFOR INDIAN ARTISANS\n");

    srand((unsigned) time(&t));

    struct seller_info sellers[SIZE];

        seller_read(sellers);

        printf("Seller Information Loaded\n");

        //display(sellers,30);

    struct customer_info customers[SIZE*5];

    struct location_array locations[SIZE*5];

        populate_location(locations);

        printf("Populated locations\n");


        customer_read(customers, locations);

        printf("Customer Information Loaded\n");

            get_shortest_distances();

            printf("Got Shortest Distance\n");

            printSolution();

    struct authenticate_info authentications[SIZE];

        authentication_load(authentications);

        printf("Authentication Details Loaded\n");


    int choice;

    int b = 1;

    int w;


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

    FILE *fp;

    fp = fopen("history.txt","a");

    //fprintf(fp,"HASH_VALUE\tCUSTOMER_ID\tDEL_SPEED\tLOC\t\tGRAND_TOTAL\n");

    int f;

    printf("WRITING TO HISTORY FILE....\n");



    for(w=0;w<count;w++)
    {
        fprintf(fp,"HASH_VALUE\tCUSTOMER_ID\tDEL_SPEED\tLOC\t\tGRAND_TOTAL\n");

        fprintf(fp,"%d\t\t%d\t\t%d\t\t%s\t\t%.2f\n",purchases[w].hash_value,purchases[w].customer_ID,purchases[w].delivery_speed,customers[purchases[w].hash_value,purchases[w].customer_ID].location,purchases[w].grand_total);

        fprintf(fp,"\tSELLER_ID\tITEM_ID\tCOST\tDiscount\n");

        for(f=0;f<purchases[w].n;f++)
            fprintf(fp,"\t%d\t\t%d\t\t%.2f\t\t%d\n",purchases[w].items_purchase[f].seller_ID,purchases[w].items_purchase[f].item_ID,purchases[w].items_purchase[f].cost,purchases[w].items_purchase[f].discount);

        fprintf(fp,"\n");


        fprintf(fp,"------------------------------------------------------------------\n");
    }

    printf("HISTORY FILE WRITTEN...\n");


    fclose(fp);


    return(0);
}



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
        fscanf(fp_seller,"%d %d %d %s",&sellers[i].seller_id,&sellers[i].no_of_items,&sellers[i].location_id,sellers[i].username);

        int j;
        //printf("\t\t%d=>\n",sellers[i].no_of_items);
        for(j=0;j<sellers[i].no_of_items;j++)
           {
               fscanf(fp_items,"%d %d %f %d %s",&dummy,&sellers[i].items[j].item_ID,&sellers[i].items[j].cost,&sellers[i].items[j].discount,sellers[i].items[j].article_name);
            //printf("\n%d\t%d\t%s\t%f\t%d\n",dummy,sellers[i].items[j].item_ID,sellers[i].items[j].article_name,sellers[i].items[j].cost,sellers[i].items[j].discount);

           }

        i++;
    }

    fclose(fp_seller);

    fclose(fp_items);

}



void populate_location(struct location_array locations[SIZE*5])
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
	int i;
	int j;
	int k;


	printf("\t\tRUNNING FLOYD WARSHALL ALGORITHM!\n");

	for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {

            dist[i][j] = graph[i][j];
        }

    }




	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					{
					    dist[i][j] = dist[i][k] + dist[k][j];
					}
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

    int graph[SIZE][V];

    int i=0;

    int j;


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




void swap(int *a, int *b)
{
  int temp = *b;

  *b = *a;

  *a = temp;

}



void heapify(struct seller_queue array[SIZE*5], int size, int i,int j)
{
  if (size == 1)
  {

    printf("Single element in the heap");
  }
  else
  {

    int largest = j;

    int l = 2 * j + 1;

    int r = 2 * j + 2;

    if (l < size && array[i].queues[l].priority > array[i].queues[largest].priority)
      {
          largest = l;
      }
    if (r < size && array[i].queues[l].priority > array[i].queues[largest].priority)
      {
          largest = r;
      }


int temp1;

int temp2;


    if (largest != j)
    {
        temp1=array[i].queues[j].priority;

        temp2=array[i].queues[j].customer_ID;

        array[i].queues[largest].priority = array[i].queues[j].priority;

        array[i].queues[largest].customer_ID = array[i].queues[j].customer_ID;

        array[i].queues[j].priority=temp1;

        array[i].queues[j].customer_ID=temp2;

      //swap(array[i],array[largest]);

      heapify(array, size, i, largest);
    }

  }

}



void deleteRoot(struct seller_queue array[SIZE*5],int num, int k)
{
  int i;

  int temp1;

  int temp2;


  for (i = 0; i < array[k].size; i++)
  {

    if (num == array[k].queues[i].priority)
    {
       break;
    }

  }

        temp1 = array[k].queues[i].priority;

        temp2=array[k].queues[i].customer_ID;


        array[k].queues[i].priority = array[k].queues[(array[k].size)-1].priority;

       array[k].queues[i].customer_ID =  array[k].queues[(array[k].size)-1].customer_ID;

        array[k].queues[(array[k].size)-1].priority =temp1;

        array[k].queues[(array[k].size)-1].customer_ID = temp2;


  array[k].size -= 1;


  for (int i = array[k].size / 2 - 1; i >= 0; i--)
  {
    heapify(array, array[k].size, k, i);
  }


}


void print_Array(struct seller_queue array[SIZE*5],int size,int k)
{

  for (int i = 0; i < size; ++i)
  {
      if( array[k].queues[i].priority!=0 && array[k].queues[i].customer_ID != -1)
      {

            printf("%d\t\t%d\t\t%d\n",k, array[k].queues[i].priority, array[k].queues[i].customer_ID);

            deleteRoot(array,array[k].queues[i].priority,k);
      }
  }


}



int o;


void fill()
{
int o=0;

while(o<30)
{
seller_q[o].normal_top = -1;

seller_q[o].priority_top = -1;

seller_q[o].one_day_top = -1;

o++;

}

}




void insert(struct seller_queue array[SIZE*5],int i,int priority,int customer_ID)
{


 if (array[i].size == 0)
    {
    array[i].queues[0].priority = priority;

    array[i].queues[0].customer_ID = customer_ID;

    array[i].size += 1;
  }

  else
    {
    array[i].queues[array[i].size].priority = priority;

    array[i].queues[array[i].size].customer_ID = customer_ID;

    array[i].size += 1;


    for (int j = array[i].size / 2 - 1; j >= 0; j--)
    {
      heapify(array, array[i].size, i, j);

    }

    }

}



void push(float cost,int discount)
{
 top++;

 cart[top].cost = cost;

 cart[top].discount = discount;

 //printf("\tPUSHED...\n");

}



void pop(float *x,int *y)
{
    *x = cart[top].cost;

    *y = cart[top].discount;

    top--;


    //Dcreament the global top(it is declared globallu)
}




void fill_stack(int seller_id, int customer_id,int delivery)
{
    stack_temp_top = -1;


    int value = dist[seller_id][customer_id];

    if(delivery == 0)
    {

        if(value > seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist)
            {

                seller_q[seller_id].normal_top++;

                seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist = value;

                seller_q[seller_id].normal[seller_q[seller_id].normal_top].customer_ID = customer_id;


            }
        else{

            while(value < seller_q[seller_id].normal[seller_q[seller_id].normal_top].dist)
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

        int m=0;

        //printf("Normal_top=>%d \n",seller_q[seller_id].normal_top);


    }
    else if(delivery == 1)
    {

        if(value > seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist)
            {

                seller_q[seller_id].priority_top++;

                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist = value;

                seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].customer_ID = customer_id;


            }
        else{

            while(value<seller_q[seller_id].priority_delivery[seller_q[seller_id].priority_top].dist)
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

        //printf("Priority_top=>%d \n",seller_q[seller_id].priority_top);

    }
    else if(delivery == 2)
    {

        if(value > seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist)
            {

                seller_q[seller_id].one_day_top++;

                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist = value;

                seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].customer_ID = customer_id;


            }
        else{

            while(value<seller_q[seller_id].one_day[seller_q[seller_id].one_day_top].dist)
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

        //printf("One_Day_TOp=>%d \n",seller_q[seller_id].one_day_top);
    }



}



void purchase(int p,struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{
    int i;

    int j;

    float total;

    count++;

    //printf("CAME!\n");

    int discount;

    int collect_seller_IDs[SIZE];

    top = -1;

    int u=0;

    int k;

    int m;

    int q;

    int n;

    purchases[count].customer_ID = p;

    purchases[count].hash_value = (p*1567)%SIZE;

    purchases[count].location_ID = customers[p].location_id;

    purchases[count].n = 0;


    n = rand() % 10 ; // Selecting a cohort of sellers

    printf("Selected %d no. of sellers\n",n);


    printf("\t\tPRESS ANY KEY TO CONTINUE..\n");
    getch();

    printf("PURCHASING...\n");

           // purchases[count].hash_value = p % SIZE;

            //purchases[count].customer_ID = customers[p].customer_id;

    for(i=0;i<n;i++)
    {
        k = rand()%30;

        // Randomly selecting a seller_ID

        printf("\t%d =>  Seller_ID selected\n",k);



        collect_seller_IDs[i] = k;

        int temp = sellers[k].no_of_items;


       // printf("%d=>temp\n",temp);
        m = rand()%temp ;  // Selecting a cohort of items of seller_ID k



        printf("\t%d no. of items selected for seller_ID %d\n",m,k);


        for(j=0;j<m;j++)
        {
            q = rand()% temp;

            // Select a item_ID q of seller_ID k

            sellers[k].items[q].popularity++;

            //printf("Cost =>%.2f\n",sellers[k].items[q].cost);

            //printf("Discount=> %d\n",sellers[k].items[q].discount);

              purchases[count].items_purchase[u].item_ID = q;

              purchases[count].items_purchase[u].seller_ID = k;

              purchases[count].items_purchase[u].cost = sellers[k].items[q].cost;

              purchases[count].items_purchase[u].discount = sellers[k].items[q].discount;

              u++;

              purchases[count].n++;

            //total += sellers[k].items[q].cost;

            //discount += sellers[k].items[q].discount;

            push(sellers[k].items[q].cost,sellers[k].items[q].discount);


            //printf("\t\t->->YES\n");

        }


    }


    total =0;

    discount = 0;

    float grand_total;

    float x;

    int y;

    int priority;

    int d;


     while(top != -1)
    {
        //printf("Top=>%d\n",top);

        pop(&x,&y);

        //printf("\t\t\t%f,%d\n",x,y);

        total+=x;

        discount+=y;


    }

    //printf("\t\t%f=>total\n",total);

    grand_total = total + ((total*18/100)) - ((total*discount)/100);

    //Adding taxes of 18 percent on pre -discount total cost;


    purchases[count].grand_total = grand_total;

    printf("\t\tYour Grand Total is %.2f\n\n",grand_total);

    printf("....FILLING THE PURCHASE TABLE....\n");

    printf("....PURCHASE TABLE FILLED.....\n");



    printf("\t\tPRESS ANY KEY TO CONTINUE..\n");
     purchases[count].grand_total = grand_total;
     getch();



    printf("Choose a Delivery Speed\n");
    printf("1\tNormal\n2\tPriority\n3\tOne Day Delivery\n\n");


    int dummy = rand()%3;


    purchases[count].delivery_speed = dummy;


    if(dummy == 0)
    {
        printf("Normal Delivery Chosen\n");

    }
    else if(dummy == 1)
       {
           printf("Priority Delivery Chosen\n");

       }
    else if(dummy == 2)
        {

            printf("One Day Delivery Chosen\n");
        }


    printf("\n\t\tYour Product Will Be Delivered Soon\n\n");

    printf("==================================================\n");


    printf("\t\tPress Any Key to Continue..\n");

    getch();

        for(i=0;i<n;i++)
                {
                    if(total==0)
                    {
                        dummy=10;

                    }

                    fill_stack(collect_seller_IDs[i],p,dummy);

                    //printf("filled stack\n");

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

/*
void init_array()
{
    int i;
    int max = 9999;
    int array[max];
    for (i = 0; i < max; i++)
    {
	array[i] = 0;
    }
}
*/

int pick_customer()
{
    int x;

    x = rand()%500;

    return(x);
}

void forward(struct seller_info sellers[SIZE], struct customer_info customers[SIZE],struct authenticate_info authentications[SIZE])
{

    int i;

    srand((unsigned) time(&t));


    int n = rand()% 10;

    // We are randomly choosing n no. of customers where  n<10

    printf("Picked %d no. of customers\n",n);


    printf("\t\tPRESS ANY KEY TO CONTINUE..\n");

    getch();

    fill();

    int z;

    int y;

    for(z=0;z<30;z++)
    {
        for(y=0;y<SIZE*5;y++)
        {
            seller_q[z].queues[y].priority = 0;

            seller_q[z].queues[y].customer_ID = -1;
        }
    }




    for(i=0;i<n;i++)
    {
        int p = pick_customer();

        //We are picking a random customer_ID p from the range of (0,499), i.e 500  customers

        printf("\tPicked customer_ID => %d\n",p);

        login(p,sellers,customers,authentications);

    }

    int f;

    int m;

    int w;



    printf("\n\nASSIGNING PRIORITIES....:\n");

    for(m=0;m<30;m++)
    {

        //insert(sellers_q,m,,)

    if(seller_q[m].priority_top!=-1)
     {
        for(w=0;w<=seller_q[m].priority_top;w++)
        {
            //printf("1=>%d %d %d\n",m,seller_q[m].priority_delivery[w].dist,seller_q[m].priority_delivery[w].customer_ID);

            insert(seller_q,m,w+2000,seller_q[m].priority_delivery[w].customer_ID);
        }

     }
       // printf("\n");


    if(seller_q[m].one_day_top!=-1)
     {

         for(w=0;w<=seller_q[m].one_day_top;w++)
        {
            //printf("2=>%d %d %d\n",m,seller_q[m].one_day[w].dist,seller_q[m].one_day[w].customer_ID);

            insert(seller_q,m,w+3000,seller_q[m].one_day[w].customer_ID);
        }

     }


        //printf("\n");


        //printf("\n");


     if(seller_q[m].normal_top!=-1)
     {
       for(w=0;w<=seller_q[m].normal_top;w++)
        {
            //printf("0=>%d %d %d\n",m,seller_q[m].normal[w].dist,seller_q[m].normal[w].customer_ID);

            insert(seller_q,m,w+1000,seller_q[m].normal[w].customer_ID);

        }


     }


    }
    int k;

    printf("PRIORITIES ASSIGNED!\n\n");

     printf("ENQUEUING INTO PRIORITY QUEUE OF EACH SELLER...IN PROGRESS.=>\n");

     printf("NOW SELLERS HAVE RECEIVED ORDERS!\n");
     printf("\n\t\tPRESS ANY KEY TO START DELIVERY..\n");
     getch();

    printf("SELLERS ARE DELIVERING i.e => DEQUEUEING...\n\n");
    printf("SELLER ID\tPRIORITY\tCUSTOMER ID\n");

    for(k=0;k<30;k++)
        {
            print_Array(seller_q,(sizeof(seller_q[k].queues)/sizeof(seller_q[k].queues[0])),k);
  //  printf("%d\n",f);

        }


}


void printSolution()
{
    FILE *fp;

    fp=fopen("shortest_distance.txt","w");

	fprintf (fp,"The following matrix shows the shortest distances"
			" between every pair of locations \n");


	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (dist[i][j] == INF)
            {

                fprintf(fp,"%7s","INF");
            }

			else
				fprintf (fp,"%7d", dist[i][j]);
		}


		fprintf(fp,"\n");
	}

	printf("=>Shortest Distance file created...\n");


	fclose(fp);
}





void display(struct seller_info sellers[SIZE],int count)
{
    int i;

    int j;

    printf("SELLER_ID\tNAME\tNo.of Items\tLocation_ID\n");

    for(i = 0; i < count; i++)
    {
       printf("%d\t%s\t%d\t%d\n",sellers[i].seller_id,sellers[i].username,sellers[i].no_of_items,sellers[i].location_id);


       for(j=0;j<sellers[i].no_of_items;j++)
       {

           printf("\t%d\t%s\t%.2f\t%d\n",sellers[i].items[j].item_ID,sellers[i].items[j].article_name,sellers[i].items[j].cost,sellers[i].items[j].discount);

       }
    }


}



