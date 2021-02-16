#include <stdio.h>
#include <string.h>



struct details {
	char uname[100];
	int age;
	char password[100];
	char email[100];
	char mobile[10];
};




struct details s[100000];


void signup();
void account_check();
int validate();
void login();




int flag = 1, i, j = 0, count = 0, caps = 0;
int small = 0, special = 0, numbers = 0;
int success = 0, x, choice;
char temp_name[100], temp_password1[100];
char temp_password2[100], temp_email[100];
char temp_mobile[100];
int temp_age;

int ch;


int main()
{
	while (1) {

		printf("\n1)SIGNUP\n");
		printf("2)LOGIN\n3)EXIT\n\n");
		printf("Enter your choice\t");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			signup();
			break;
		}
		case 2: {
			login();
			break;
		}
		case 3: {
			// exit(1);
			return 0;
		}
		default: {
			printf("\nPlease Enter the ");
			printf("valid choice\n");
			break;
		}
		}
	}
}


void signup()
{
	printf("Enter Your name\t");
	scanf("%s", temp_name);

	printf("Enter Your Age\t");
	scanf("%d", &temp_age);

	printf("Enter Your Email\t");
	scanf("%s", temp_email);

	printf("Enter Password\t");
	scanf("%s", temp_password1);

	printf("Confirm Password\t");
	scanf("%s", temp_password2);

	printf("Enter Your Mobile Number\t");
	scanf("%s", temp_mobile);


	x = validate();
	if (x == 1)
		account_check();
}


int validate()
{
	// Validate the name
	for (i = 0; temp_name[i] != '\0'; i++) {
		if (!((temp_name[i] >= 'a' && temp_name[i] <= 'z')
			|| (temp_name[i] >= 'A'
				&& temp_name[i] <= 'Z'))) {
			printf("\nPlease Enter the");
			printf("valid Name\n");
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		count = 0;

		// Validate the Email ID
		for (i = 0;
			temp_email[i] != '\0'; i++) {
			if (temp_email[i] == '@'
				|| temp_email[i] == '.')
				count++;
		}
		if (count >= 2
			&& strlen(temp_email) >= 5) {
			// Validating the Password and
			// Check whether it matches
			// with Conform Password
			if (!strcmp(temp_password1,
						temp_password2)) {
				if (strlen(temp_password1) >= 8
					&& strlen(temp_password1) <= 12) {
					caps = 0;
					small = 0;
					numbers = 0;
					special = 0;
					for (i = 0; temp_password1[i] != '\0';
						i++) {
						if (temp_password1[i] >= 'A'
							&& temp_password1[i] <= 'Z')
							caps++;
						else if (temp_password1[i] >= 'a'
								&& temp_password1[i]
										<= 'z')
							small++;
						else if (temp_password1[i] >= '0'
								&& temp_password1[i]
										<= '9')
							numbers++;
						else if (temp_password1[i] == '@'
								|| temp_password1[i] == '&'
								|| temp_password1[i] == '#'
								|| temp_password1[i]
										== '*')
							special++;
					}
					if (caps >= 1 && small >= 1
						&& numbers >= 1 && special >= 1) {
						// Validating the Input age
						if (temp_age != 0 && temp_age > 0) {
							// Validating the Input mobile
							// number
							if (strlen(temp_mobile) == 10) {
								for (i = 0; i < 10; i++) {
									if (temp_mobile[i]
											>= '0'
										&& temp_mobile[i]
											<= '9') {
										success = 1;
									}
									else {
										printf("\n\nPlease");
										printf("Enter Valid ");
										printf("Mobile "
											"Number\n\n");
										return 0;
										break;
									}
								}


								if (success == 1)
									return 1;
							}
							else {
								printf("\n\nPlease Enter the");
								printf("10 digit mobile");
								printf("number\n\n");
								return 0;
							}
						}
						else {
							printf("\n\nPlease Enter ");
							printf("the valid age\n\n");
							return 0;
						}
					}
					else {
						printf("\n\nPlease Enter the");
						printf("strong password, Your ");
						printf("password must contain ");
						printf("atleast one uppercase, ");
						printf("Lowercase, Number and ");
						printf("special character\n\n");
						return 0;
					}
				}
				else {
					printf("\nYour Password is very");
					printf("short\nLength must ");
					printf("between 8 to 12\n\n");
					return 0;
				}
			}
			else {
				printf("\nPassword Mismatch\n\n");
				return 0;
			}
		}
		else {
			printf("\nPlease Enter"
				" Valid E-Mail\n\n");
			return 0;
		}
	}
}

// Function to check if the account
// already exists or not
void account_check()
{
	for (i = 0; i < 100; i++) {
		// Check whether the email
		// and password are already
		// matched with existed account
		if (!(strcmp(temp_email, s[i].email)
			&& strcmp(temp_password1,
						s[i].password))) {
			printf("\n\nAccount Already");
			printf("Existed. Please Login !!\n\n");
			main();
			break;
		}
	}
	// if account does not already
	// existed, it creates a new
	// one with new inputs
	if (i == 100) {
		strcpy(s[j].uname, temp_name);
		s[j].age = temp_age;
		strcpy(s[j].password, temp_password1);
		strcpy(s[j].email, temp_email);
		strcpy(s[j].mobile, temp_mobile);
		j++;
		printf("\n\n\nAccount Successfully");
		printf("Created!!\n\n");
	}
}

// Function to Login the users
void login()
{
	printf("\n\nLOGIN\n\n");
	printf("\nEnter Your Email\t");
	scanf("%s", temp_email);
	printf("Enter Your Password\t");
	scanf("%s", temp_password1);
	for (i = 0; i < 100; i++) {
		// Check whether the input
		// email is already existed or not
		if (!strcmp(s[i].email, temp_email)) {
			// Check whether the password
			// is matched with the email or not
			if (!strcmp(s[i].password, temp_password1)) {
				printf("\n\nWelcome %s, ", s[i].uname);
				printf("Your are successfully logged in\n");

			}
			else {
				printf("\n\nInvalid Password! ");
				printf("Please Enter the ");
				printf("correct password\n\n");
				main();
				break;
			}
		}
		else {
			printf("\n\nAccount doesn't ");
			printf("exist, Please signup!!\n\n");
			main();
			break;
		}
	}
}

