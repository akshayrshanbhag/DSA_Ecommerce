#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE 8

char temp1[SIZE+1];


char alphabet[52];


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


int main()
{

FILE *fp;

fp = fopen("seller.txt","w");

int i;

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

srand((unsigned) time(&t));
for(i=0;i<30;i++)
{
    generate_username();
    fprintf(fp,"%d\t%s\t%d\t%d\n",i,temp1,rand()%11,rand()%50);

}
fclose(fp);

return 0;
}

