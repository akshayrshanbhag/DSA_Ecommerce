#include <stdio.h>
#include <string.h>


void purchase(int );

char temp_username[100], temp_password[100];
int ch;

int account_check()
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


void login(int p)
{

	printf("\nEnter Your Username\t");
	temp_username = authentications[p].username;
	printf("%s",temp_username);
	printf("Enter Your Password\t");
	temp_password = authentications[p].password;
	printf("%s",temp_password);


		int temp = account_check();
		if (temp == 1)
            purchase(p);
		else
            {
			printf("Account doesn't ");
			printf("exist, Please signup!!\n\n");
            }

}


int main()
{
    int p; //customer_ID
	login(p);
	return(0);
}






