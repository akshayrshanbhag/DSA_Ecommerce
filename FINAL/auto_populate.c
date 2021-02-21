#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 8

char temp1[SIZE+1];
char temp2[SIZE+1];

char alphabet[52];
char number[10];
char special_char[2];

time_t t;


void generate_username()
{int x, k;

for(k=0;k<8;k++)
{
    x = rand()% 52;
    temp1[k] = alphabet[x];
}
temp1[k+1]='/0';

}


void generate_password()
{
int m;
int j;
for(m=0;m<SIZE;m++)
{
    j = rand() % 3;
    if(j==0)
        temp2[m] = alphabet[rand()%52];
    else if(j==1)
        temp2[m] = number[rand()%10];

    else if(j==2)
        temp2[m] = special_char[rand()%2];

}
temp1[m+1]='/0';
}

int main()
{

FILE *fp;

fp = fopen("customer.txt","w");

int i,j;

char k;

char c;
    for (c = 'A'; c <= 'Z'; ++c)
    {
        alphabet[k] = c;
        k++;
    }

    for (c = 'a'; c <= 'z'; ++c)
    {
        alphabet[k] = c;
        k++;
    }

    int n;

    number[0] ='0';
    number[1] ='1';
    number[2] ='2';
    number[3] ='3';
    number[4] ='4';
    number[5] ='5';
    number[6] ='6';
    number[7] ='7';
    number[8] ='8';
    number[9] ='9';





special_char[0] = '@';
special_char[1] = '#';



srand((unsigned) time(&t));
for(i=0;i<500;i++)
{


    generate_username();
    generate_password();



    fprintf(fp,"%d\t%s\t%s\t%d\n",i,temp1,temp2,rand()%50);

}
fclose(fp);

return 0;
}
