#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

typedef enum {owner,manager,employee,admin} Role;

struct userDetail
{
	char uName[20],pass[20],uid[10];
	Role role;
};

Role login();
void roleFunctions(Role role);
void recovery();
void setColor(int);
void owner_Access();
void manager_Access();
void Emp_Access();
void ADMIN();
void addAcc();
void viewAcc();
void modAcc();
void removeAcc();
Role strToRole(char [] );
char* roleToStr(Role);
int main()
{
	char choice;
	Role loggedRole = login();
	if(loggedRole != -1)
	{
		roleFunctions(loggedRole);
	}
	else
	{
		setColor(7);
		printf("\nDid you for forget your password.");
		printf("\nDo you want to recover the account.[y/n]");
		fflush(stdin);
		scanf(" %c",&choice);
		
		if(choice == 'y' || choice == 'Y')
		{
			recovery();
		}
	}
	return 0;
}

Role login()
{
	system("cls");
	int i=0,j=0,flag_1=1,flag_2=1;
	char ch;
	char uName[20],pass[20];
	struct userDetail user;
	FILE *l_fp;
	l_fp = fopen("Accounts.dat","rb");
l_start:	
	printf("Enter Username: ");
	fflush(stdin);
	gets(uName);
	if(strcmp(uName,"Admin") == 0)
	{
		printf("Enter Password: ");
		fflush(stdin);
		flag_1=0;
		i=0;
		while(1)
		{
			if(_kbhit())
			{
				ch = _getch();
				if(ch == '\r')
				{
					pass[i] = '\0';
					break;
				}
				else if(ch == '\b' && i> 0)
				{
					printf("\b \b");
					i--;
				}
				else if(i<100)
				{
					pass[i] = ch;
					printf("*");
					i++;
				}
			}
		}	
		if(strcmp(pass,"Admin") == 0)
		{
			return admin;
		}
		else
		{
			setColor(12);
			printf("\nIncorrect Admin password\n");
			setColor(7);
			goto l_start;
		}
	}
	rewind(l_fp);
	while(fread(&user,sizeof(user),1,l_fp))
	{
		if(strcmp(uName,user.uName) == 0)
		{
			goto l_Pass;
		}
	}
	if(flag_1<3)
	{
	setColor(12);
	printf("User doesn't Exist.Try again.\n\n");
	setColor(7);
	flag_1++;
	goto l_start;
	}
	else
	{
		setColor(12);
		printf("\nUsername couldn't be verified.Please contact the manager.");
		setColor(7);
		fclose(l_fp);
		exit(0);
	}
l_Pass:
	printf("Enter Password: ");
	fflush(stdin);
	i=0;
	while(1)
	{
		if(_kbhit())
		{
			ch = _getch();
			if(ch == '\r')
			{
				pass[i] = '\0';
				break;
			}
			else if(ch == '\b' && i> 0)
			{
				printf("\b \b");
				i--;
			}
			else if(i<100)
			{
				pass[i] = ch;
				printf("*");
				i++;
			}
		}
	}	
	rewind(l_fp);
	while(fread(&user,sizeof(user),1,l_fp))
	{
		if(strcmp(user.uName,uName) == 0 && strcmp(user.pass,pass) == 0)
		{
			setColor(10);
			printf("\nLogin successful. Welcome %s.",uName);
			setColor(7);
			return user.role;
		}
	}
	if(flag_2==1)
	{
	setColor(12);
	printf("\nLogin Error.Try again.\n\n");
	setColor(7);
	flag_2++;
	goto l_start;
	}
	return -1;
}

void roleFunctions(Role loggedRole)
{
	int i;
	printf("\nLoading");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	switch(loggedRole)
	{
		case owner:
			setColor(9);
			printf("\nOwner");
			owner_Access();
			break;
		
		case manager:
			setColor(9);
			printf("\nManager");
			manager_Access();
			break;
		
		case employee:
			setColor(9);
			printf("\nEmp");
			Emp_Access();
			break;
			
		case admin:
			setColor(9);
			printf("\nEmp");
			ADMIN();
			break;
			
		default:
			setColor(12);
			printf("Error");
	}
	setColor(7);
}

void recovery()
{
	int i=0,j=0,flag=1;
	char uName[20],uid[10],ch;
	char pass1[20],pass2[20];
	struct userDetail user;
r_start:	
	printf("\nEnter your username: ");
	fflush(stdin);
	scanf("%19s",uName);
	for(j=0;j<5;j++)
	{
		if(strcmp(uName,user.uName) == 0)
		{
			goto r_Pass;
		}
	}
r_Pass:
	for(j=0;j<5;j++)
	{
		if(strcmp(uName,user.uName) == 0)
		{
			printf("\nEnter your UID: ");
			fflush(stdin);
			scanf("%s",uid);
			if(strcmp(uid,user.uid) == 0)
			{
				newPass:
				printf("\nEnter New password: ");
				fflush(stdin);
				while(1)
				{
					if(_kbhit())
					{
						ch = _getch();
						if(ch == '\r')
						{
							pass1[i] = '\0';
							break;
						}
						else if(ch == '\b' && i> 0)
						{
							printf("\b \b");
							i--;
						}
						else if(i<100)
						{
							pass1[i] = ch;
							printf("*");
							i++;
						}
					}
				}
				i=0;
				printf("\nConfirm password: ");
				fflush(stdin);
				while(1)
				{
					if(_kbhit())
					{
						ch = _getch();
						if(ch == '\r')
						{
							pass2[i] = '\0';
							break;
						}
						else if(ch == '\b' && i> 0)
						{
						printf("\b \b");
							i--;
						}
						else if(i<100)
						{
							pass2[i] = ch;
							printf("*");
							i++;
						}
					}
				}
				i=0;
				if(strcmp(pass1,pass2) != 0)
				{
					printf("\nPassword doesn't match. Try again.");
					goto newPass;
				}
				strcpy(user.pass,pass1);
				printf("\nPassword Successfully Changed.");
				printf("\nRedirecting to Login page");
				for(i=0;i<3;i++)
				{
					printf(".");
					Sleep(500);
				}
				main();
			}
		setColor(12);
		printf("\nInvaild UID.");
		setColor(7);
		return;
	
		}
	}
	setColor(12);
	printf("\nUser doesn't Exist.Try again.");	
	setColor(7);
	flag++;
	goto r_start;
}

void owner_Access()
{
	system("cls");
	char choice;
o_start:
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tAdmin\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. View Today's Sales.\n");
	printf("\t\t\t\t3. View Remaining Stock.\n");
	printf("\t\t\t\t4. Add Product.\n");
	printf("\t\t\t\t5. Update Product.\n");
	printf("\t\t\t\t6. Remove Product.\n");
	printf("\t\t\t\t7. Manage Accounts.\n");
	printf("\t\t\t\t8. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			printf("In Progress.");
			break;
		case '2':
			printf("In Progress.");
			break;
		case '3':
			printf("In Progress.");
			break;
		case '4':
			printf("In Progress.");
			break;
		case '5':
			printf("In Progress.");
			break;
		case '6':
			printf("In Progress.");
			break;
		case '7':
			printf("In Progress.");
			break;
		case'8':
			exit(0);
			break;
		default:
			printf("\t\t\t\tPlease Choose a correct option.");
			goto o_start;
	}
}

void manager_Access()
{
	system("cls");
	char choice;
m_start:
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tAdmin\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. View Today's Sales.\n");
	printf("\t\t\t\t3. View Remaining Stock.\n");
	printf("\t\t\t\t4. Add Product.\n");
	printf("\t\t\t\t5. Update Product.\n");
	printf("\t\t\t\t6. Remove Product.\n");
	printf("\t\t\t\t7. Manage Accounts.\n");
	printf("\t\t\t\t8. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			printf("H");
			break;
		case '2':
			printf("E");
			break;
		case '3':
			printf("L");
			break;
		case '4':
			printf("O");
			break;
		case '5':
			printf("A");
			break;
		case '6':
			printf("B");
			break;
		case '7':
			printf("C");
			break;
		case'8':
			exit(0);
			break;
		default:
			printf("\t\t\t\tPlease Choose a correct option.");
			goto m_start;
	}
}

void Emp_Access()
{
	system("cls");
	char choice;
emp_start:
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tEmployee.\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. View Remaining Stock.\n");
	printf("\t\t\t\t3. Add Product.\n");
	printf("\t\t\t\t4. Update Product.\n");
	printf("\t\t\t\t5. Remove Product.\n");
	printf("\t\t\t\t6. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			printf("H");
			break;
		case '2':
			printf("E");
			break;
		case '3':
			printf("L");
			break;
		case '4':
			printf("O");
			break;
		case '5':
			printf("A");
			break;
		case'6':
			exit(0);
			break;
		default:
			printf("\t\t\t\tPlease Choose a correct option.");
			goto emp_start;
	}
}

void ADMIN()
{
	system("cls");
	char choice;
ADMIN_start:
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tAdmin\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1.Add Account.\n");
	printf("\t\t\t\t2.View Account.\n");
	printf("\t\t\t\t3.Modify Account.\n");
	printf("\t\t\t\t4.Remove Account.\n");
	printf("\t\t\t\t5.Exit.\n");
	printf("\t\t\t\tEnter your option: ");
	scanf(" %c",&choice);
	switch(choice)
	{
		case '1':
			addAcc();
			break;
		
		case '2':
			viewAcc();
			break;
		
		case '3':
			modAcc();
			break;
			
		case '4':
			removeAcc();
			break;
			
		case '5':
			exit(0);
			
		default:
			printf("\t\t\t\tPlease Choose a correct Option.");
			goto ADMIN_start;
	}
}

void addAcc()
{
	system("cls");
	int i=0;
	char ch,uName[20],pass[20],uid[10],role[10];
	struct userDetail user;
	FILE *a_fp;
	a_fp = fopen("Accounts.dat","ab");
	if(a_fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.");
		Sleep(2000);
		setColor(9);
		fclose(a_fp);
		ADMIN();
	}
add_start:
	printf("Enter Username: ");
	fflush(stdin);
	gets(user.uName);
	printf("Enter Password: ");
	fflush(stdin);
	i=0;
	while(1)
	{
		if(_kbhit())
		{
			ch = _getch();
			if(ch == '\r')
			{
				user.pass[i] = '\0';
				break;
			}
			else if(ch == '\b' && i> 0)
			{
				printf("\b \b");
				i--;
			}
			else if(i<100)
			{
				user.pass[i] = ch;
				printf("*");
				i++;
			}
		}
	}
	printf("Enter UID: ");
	fflush(stdin);
	gets(user.uid);
	printf("Enter role: ");
	fflush(stdin);
	gets(role);
	user.role = strToRole(role);
	if(user.role == -1)
	{
		setColor(12);
		printf("\n\t\t\t\tInvalid Role.Try Again.");
		setColor(7);
		goto add_start;
	}
	fwrite(&user,sizeof(user),1,a_fp);
	fclose(a_fp);
	system("cls");
	printf("\n\t\t\t\tThe user has been successfully added.");
	printf("\n\t\t\t\tRedirecting to Admin page");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	ADMIN();
}

void viewAcc()
{
	system("cls");
	int i=0;
	char choice;
	struct userDetail user;
	FILE *v_fp;
	v_fp = fopen("Accounts.dat","rb");
	if(v_fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.");
		Sleep(2000);
		setColor(9);
		fclose(v_fp);
		ADMIN();
	}
	printf("\n\t\t\t\t\t\tAccounts");
	printf("\n\t\t\t\t--------------------------------");
	printf("\n\t\t\t\t   Username \t\tPost");
	printf("\n\t\t\t\t--------------------------------");
	i=0;
	rewind(v_fp);
	while(fread(&user,sizeof(user),1,v_fp))
	{
		printf("\n\t\t\t\t%d. %s \t\t\t%s",i+1,user.uName,roleToStr(user.role));
		i++;
	}
	printf("\n\t\t\t\tPress (b) to go back.");
	scanf(" %c",&choice);
	if(choice == 'b')
	{
		ADMIN();
	}
	setColor(7);
	printf("\n\t\t\t\tThank you fo using.");
	exit(0);
}

void modAcc()
{
	system("cls");
	int i=0,flag=1,size;
	char ch,choice,uName[20],role[10];
	struct userDetail user;
	size =sizeof(user);
	FILE *mod_fp;
	mod_fp = fopen("Accounts.dat","rb+");
	if(mod_fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.");
		Sleep(2000);
		setColor(9);
		fclose(mod_fp);
		ADMIN();
	}
mod_start:
	printf("Enter Username: ");
	fflush(stdin);
	gets(uName);
	rewind(mod_fp);
	while(fread(&user,sizeof(user),1,mod_fp))
	{
		if(strcmp(uName,user.uName) == 0)
		{
			fseek(mod_fp, -size, SEEK_CUR);
			printf("Enter New Username: ");
			fflush(stdin);
			gets(user.uName);
			printf("Enter New Password: ");
			fflush(stdin);
			i=0;
			while(1)
			{
				if(_kbhit())
				{
					ch = _getch();
					if(ch == '\r')
					{
						user.pass[i] = '\0';
						break;
					}
					else if(ch == '\b' && i> 0)
					{
						printf("\b \b");
						i--;
					}
					else if(i<100)
					{
						user.pass[i] = ch;
						printf("*");
						i++;
					}
				}
			}
			printf("\nEnter New UID: ");
			fflush(stdin);
			gets(user.uid);
			printf("Enter New role: ");
			fflush(stdin);
			gets(role);
			user.role = strToRole(role);
			fwrite(&user,sizeof(user),1,mod_fp);
			fclose(mod_fp);
			system("cls");
			setColor(13);
			printf("\n\t\t\t\tThe user has been successfully updated.");
			setColor(9);
			printf("\nDo you want to modify another account.[y/n]");
			fflush(stdin);
			scanf(" %c",&choice);
			if(choice == 'y')
			{
				continue;
			}
			else
			{
				printf("\n\t\t\t\tRedirecting to Admin page");
				for(i=0;i<3;i++)
				{
					printf(".");
					Sleep(500);
				}
				fclose(mod_fp);
				ADMIN();
			}
		}
	}
	if(flag<3)
	{
		setColor(12);
		printf("User doesn't Exist.Try again.\n\n");
		setColor(9);
		flag++;
		goto mod_start;
	}
	else
	{
		setColor(12);
		printf("Too many attempts.Try again.");
		setColor(9);
		printf("\n\t\t\t\tRedirecting to Admin page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		fclose(mod_fp);
		ADMIN();
	}	
}

void removeAcc()
{
	printf("IN Progress.");
}

Role strToRole(char role[])
{
	if(strcmp(role,"Owner") == 0)
	{
		return owner;
	}
	else if(strcmp(role, "Manager") == 0)
	{
		return manager;
	}
	else if(strcmp(role,"Employee") == 0)
	{
		return employee;
	}
	else if(strcmp(role, "Admin") == 0)
	{
		return admin;
	}
	else
	{
		return -1;
	}
}
char* roleToStr(Role role)
{
	if(role == owner)
	{
		return "Owner";
	}
	else if(role == manager)
	{
		return "Manager";
	}
	else if(role == employee)
	{
		return "Employee";
	}
	else if(role == admin)
	{
		return "Admin";
	}
}
void setColor(int textColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor);
}
