#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

typedef enum {owner,manager,employee,admin} Role;

struct userDetail
{
	char uName[20],pass[20],uid[3];
	Role role;
};

struct store 
{
	int quantity;
	char name[30];
	long long int barcodeNum;
	float rate;
};

struct sale
{
	struct store p;
	char date[11];
};

Role login();
void roleFunctions(Role);
void recovery();
void setColor(int);
void owner_Access(Role);
void manager_Access(Role);
void Emp_Access(Role);
void ADMIN();
void addAcc();
void viewAcc();
void modAcc();
void removeAcc();
void list_Product();
void addProduct();
void updateProduct();
void removeProduct();
void sale();
void todaySales();
Role strToRole(char [] );
char* roleToStr(Role);
void get_current_date(char []);	
char* UID_Generator(Role );

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
		fclose(l_fp);
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
			if(flag_2==1)
			{
				setColor(12);
				printf("\nIncorrect Admin password\n");
				setColor(7);
				flag_2++;
				goto l_start;
			}
			setColor(12);
			printf("\nToo many attempts for admin.Forcefully shutting down");
			setColor(7);
			Sleep(2000);
			exit(1);
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
			owner_Access(loggedRole);
			break;
		
		case manager:
			setColor(9);
			manager_Access(loggedRole);
			break;
		
		case employee:
			setColor(9);
			Emp_Access(loggedRole);
			break;
			
		case admin:
			setColor(9);
			ADMIN(admin);
			break;
	}
}

void recovery()
{
	int i=0,j=0,flag=0,size;
	char uName[20],uid[10],ch;
	char pass1[20],pass2[20];
	struct userDetail user;
	FILE *rec_fp;
	rec_fp = fopen("Accounts.dat","rb+");
	size=sizeof(user);
r_start:	
	printf("\nEnter your username: ");
	fflush(stdin);
	gets(uName);
	while(fread(&user,sizeof(user),1,rec_fp))
	{
		if(strcmp(uName,user.uName) == 0)
		{
			goto r_Pass;
		}
	}
	setColor(12);
	printf("\nUser doesn't Exist.Try again.");	
	setColor(9);
	flag++;
	goto r_start;
r_Pass:
	fseek(rec_fp, -size, SEEK_CUR);
	printf("\nEnter your UID: ");
	fflush(stdin);
	gets(uid);
	if(strcmp(uid,user.uid) == 0)
	{
		newPass:
		printf("\nEnter New password: ");
		fflush(stdin);
		i=0;
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
		if(strcmp(pass1,pass2) != 0)
		{
			setColor(12);
			printf("\nPassword doesn't match. Try again.");
			setColor(7);
			goto newPass;
		}
		strcpy(user.pass,pass1);
		fwrite(&user,sizeof(user),1,rec_fp);
		fclose(rec_fp);
		setColor(10);
		printf("\nPassword Successfully Changed.");
		setColor(7);
		printf("\nRedirecting to Login page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		main();
	}
	if(flag>1)
	{
		setColor(12);
		printf("\nInvaild UID.Try Again");
		setColor(9);
		goto r_Pass;	
	}
	setColor(12);
	printf("\nUID couldn't be verified.");
	printf("\nForcefully shutting down.");
	setColor(7);
}

void owner_Access(Role role)
{
	char choice;
o_start:
	system("cls");
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tOwner\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. View Today's Sales.\n");
	printf("\t\t\t\t3. Add Product.\n");
	printf("\t\t\t\t4. Update Product.\n");
	printf("\t\t\t\t5. Remove Product.\n");
	printf("\t\t\t\t6. Sale Product.\n");
	printf("\t\t\t\t7. Manage Accounts.\n");
	printf("\t\t\t\t8. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			list_Product();
			goto o_start;
			break;
		case '2':
			todaySales();
			goto o_start;
			break;
		case '3':
			addProduct();
			goto o_start;
			break;
		case '4':
			updateProduct();
			goto o_start;
			break;
		case '5':
			removeProduct();
			goto o_start;
			break;
		case '6':	
			sale();
			goto o_start;
			break;
		case '7':
			ADMIN(role);
			goto o_start;
			break;
		case '8':
			exit(0);
			break;
		default:
			setColor(12);
			printf("\t\t\t\tPlease Choose a correct option.");
			setColor(7);
			goto o_start;
	}
}

void manager_Access(Role role)
{
	char choice;
m_start:
	system("cls");
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tManager\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. View Today's Sales.\n");
	printf("\t\t\t\t3. Add Product.\n");
	printf("\t\t\t\t4. Update Product.\n");
	printf("\t\t\t\t5. Remove Product.\n");
	printf("\t\t\t\t6. Sale Product.\n");
	printf("\t\t\t\t7. Manage Accounts.\n");
	printf("\t\t\t\t8. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			list_Product();
			goto m_start;
			break;
		case '2':
			todaySales();
			goto m_start;
			break;
		case '3':
			addProduct();
			goto m_start;
			break;
		case '4':
			updateProduct();
			goto m_start;
			break;
		case '5':
			removeProduct();
			goto m_start;
			break;
		case '6':	
			sale();
			goto m_start;
			break;
		case '7':
			ADMIN(role);
			goto m_start;
			break;
		case '8':
			exit(0);
			break;
		default:
			setColor(12);
			printf("\t\t\t\tPlease Choose a correct option.");
			setColor(7);
			goto m_start;
	}
}

void Emp_Access(Role role)
{
	char choice;
emp_start:
	system("cls");
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tEmployee.\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t\t1. View Product.\n");
	printf("\t\t\t\t2. Add Product.\n");
	printf("\t\t\t\t3. Update Product.\n");
	printf("\t\t\t\t4. Remove Product.\n");
	printf("\t\t\t\t5. Sale Product.\n");
	printf("\t\t\t\t6. Exit.\n");
	printf("\t\t\t\tEnter your Choice: ");
	fflush(stdin);
	scanf(" %c",&choice);
	
	switch(choice)
	{
		case '1':
			list_Product();
			goto emp_start;
			break;
		case '2':
			addProduct();
			goto emp_start;
			break;
		case '3':
			updateProduct();
			goto emp_start;
			break;
		case '4':
			removeProduct();
			goto emp_start;
			break;
		case '5':
			sale();
			goto emp_start;
			break;
		case '6':
			exit(0);
			break;
		default:
			setColor(12);
			printf("\t\t\t\tPlease Choose a correct option.");
			setColor(7);
			goto emp_start;
	}
}

void ADMIN(Role role)
{
	char choice;
ADMIN_start:
	system("cls");
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
	fflush(stdin);
	scanf(" %c",&choice);
	switch(choice)
	{
		case '1':
			addAcc();
			goto ADMIN_start;
			break;
		
		case '2':
			viewAcc(role);
			goto ADMIN_start;
			break;
		
		case '3':
			modAcc(role);
			goto ADMIN_start;
			break;
			
		case '4':
			removeAcc(role);
			goto ADMIN_start;
			break;
			
		case '5':
			printf("\n\t\t\t\tThank you for using.");
			return;
			
		default:
			printf("\n\t\t\t\tPlease Choose a correct Option.");
			Sleep(1000);
			goto ADMIN_start;
	}
}

void addAcc()
{
	system("cls");
	int i=0;
	char ch,uName[20],uid[3],role[8],choice;
	struct userDetail user;
	FILE *a_fp;
	a_fp = fopen("Accounts.dat","ab+");
	if(a_fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.\n");
		Sleep(1000);
		setColor(9);
		fclose(a_fp);
		return;
	}
add_start:
	printf("\t\t\t\tEnter Username: ");
	fflush(stdin);
	gets(uName);
	rewind(a_fp);
	while(fread(&user,sizeof(user),1,a_fp))
	{
		if(strcmp(uName,user.uName) == 0)
		{
			setColor(12);
			printf("\n\t\t\t\tUser already exist.Try with a different username.\n");
			setColor(9);
			goto add_start;
		}
	}
	strcpy(user.uName,uName);
	printf("\t\t\t\tEnter Password: ");
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
	printf("\n\t\t\t\tEnter role(Owner,Manager,Employee): ");
	fflush(stdin);
	gets(role);
	user.role = strToRole(role);
	if(user.role == -1)
	{
		setColor(12);
		printf("\n\t\t\t\tInvalid Role.Try Again.\n");
		setColor(9);
		goto add_start;
	}
	strcpy(uid, UID_Generator(user.role));
	if(strcmp(uid,"Invalid") == 0)
	{
		setColor(12);
		printf("\n\t\t\t\tUID generation Error.\n");
		setColor(9);
		goto add_start;
	}
	strcpy(user.uid,uid);
	printf("\n\t\t\t\tYour UID is: %s",uid);
	printf("\n\t\t\t\tMake sure to remember it or note it down.");
	fwrite(&user,sizeof(user),1,a_fp);
	printf("\n\t\t\t\tThe user has been successfully added.");
	printf("\n\t\t\t\tDo you want to add new Account[y/n]: ");
	scanf(" %c",&choice);
	if(choice == 'y')
	{
		goto add_start;
	}
	fclose(a_fp);
	printf("\n\t\t\t\tRedirecting to Admin page");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	return;
}

void viewAcc(Role role)
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
		return;
	}
	printf("\n\t\t\t\t\t\tAccounts");
	printf("\n\t\t\t\t--------------------------------");
	printf("\n\t\t\t\t   Username \t\tPost");
	printf("\n\t\t\t\t--------------------------------");
	i=0;
	rewind(v_fp);
	while(fread(&user,sizeof(user),1,v_fp))
	{
		if( (role == manager && (user.role == manager || user.role == owner)) != 1 )
		{
			if(role != manager)
			{
				rewind(v_fp);
				while(fread(&user,sizeof(user),1,v_fp))
				{	
					if(user.role == owner)
					{
					printf("\n\t\t\t\t%d. %s \t\t%s",i+1,user.uName,roleToStr(user.role));
					i++;
					}
				}
			}
			if(role != manager)
			{
				rewind(v_fp);
				while(fread(&user,sizeof(user),1,v_fp))
				{	
					if(user.role == manager)
					{
					printf("\n\t\t\t\t%d. %s \t\t%s",i+1,user.uName,roleToStr(user.role));
					i++;
					}
				}
			}
			rewind(v_fp);
			while(fread(&user,sizeof(user),1,v_fp))
			{	
				if(user.role == employee)
				{
				printf("\n\t\t\t\t%d. %s \t\t%s",i+1,user.uName,roleToStr(user.role));
				i++;
				}
			}
		}
		continue;
	}
	fclose(v_fp);
	printf("\n\t\t\t\tPress (b) to go back.");
	scanf(" %c",&choice);
	if(choice == 'b')
	{
		return;
	}
	setColor(7);
	printf("\n\t\t\t\tThank you for using.");
	exit(0);
}

void modAcc(Role role)
{
	system("cls");
	int i=0,flag=1,size;
	char ch,choice,uName[20],uRole[8],uid[3];
	struct userDetail user;
	size =sizeof(user);
	FILE *mod_fp;
	mod_fp = fopen("Accounts.dat","rb+");
mod_start:
	if(mod_fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.\n");
		Sleep(2000);
		setColor(9);
		fclose(mod_fp);
		return;
	}
	printf("\n\t\t\t\tEnter Username: ");
	fflush(stdin);
	gets(uName);
	rewind(mod_fp);
	while(fread(&user,sizeof(user),1,mod_fp))
	{
		if(role == manager && user.role == manager)
		{
			continue;
		}
		if(strcmp(uName,user.uName) == 0)
		{
			fseek(mod_fp, -size, SEEK_CUR);
			printf("\t\t\t\tEnter New Username: ");
			fflush(stdin);
			gets(user.uName);
			printf("\t\t\t\tEnter New Password: ");
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
			printf("\n\t\t\t\tEnter New role(Owner,Manager,Employee): ");
			fflush(stdin);
			gets(uRole);
			user.role = strToRole(uRole);
			if(user.role == -1)
			{
				setColor(12);
				printf("\n\t\t\t\tInvalid Role.Try Again.");
				setColor(9);
				fclose(mod_fp);
				goto mod_start;
			}
			strcpy(uid, UID_Generator(user.role));
			if(strcmp(uid,"Invalid") == 0)
			{
				setColor(12);
				printf("\n\t\t\t\tUID generation Error");
				setColor(9);
				fclose(mod_fp);
				goto mod_start;
			}
			strcpy(user.uid,uid);
			printf("\n\t\t\t\tYour UID is: %s",uid);
			printf("\n\t\t\t\tMake sure to remember it or note it down.");
			fwrite(&user,sizeof(user),1,mod_fp);
			setColor(10);
			printf("\n\t\t\t\tThe user has been successfully updated.");
			setColor(9);
			printf("\n\t\t\t\tDo you want to modify another account.[y/n]");
			fflush(stdin);
			scanf(" %c",&choice);
			if(choice == 'y')
			{
				goto mod_start;
			}
			else
			{
				fclose(mod_fp);
				printf("\n\t\t\t\tRedirecting to Admin page");
				for(i=0;i<3;i++)
				{
					printf(".");
					Sleep(500);
				}
				return;
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
		fclose(mod_fp);
		printf("\n\t\t\t\tRedirecting to Admin page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		return;
	}	
}

void removeAcc(Role role)
{
	system("cls");
	int i=0;
	char choice,uName[20];
	struct userDetail user;
	FILE *rmu_fp,*tp_fp;
	rmu_fp = fopen("Accounts.dat","rb+");
	if(rmu_fp == NULL)
	{
		setColor(12);
		printf("Error Accessing the Data.");
		setColor(9);
		return;
	}
rm_user:
	printf("Enter the Account you want to remove: ");
	fflush(stdin);
	gets(uName);
	rewind(rmu_fp);
	while(fread(&user,sizeof(user),1,rmu_fp))
	{	
		if(role == manager)
		{
			continue;
		}
		if(strcmp(uName,user.uName) == 0)
		{
			goto valid_temp;
		}
	}
	printf("\nNo need to remove Account. \nIt was not there from the start.");
	printf("\nRedirecting to main page");
	for(i=0;i<3;i++)
	printf(".");
	Sleep(500);
	fclose(rmu_fp);
	return;	
valid_temp:	
	tp_fp =fopen("tempfile.dat","wb+");
	if(tp_fp == NULL)
	{
		setColor(12);
		printf("Error Creating Temporary File.");
		setColor(9);
		return;
	}
	rewind(rmu_fp);
	while(fread(&user,sizeof(user),1,rmu_fp))
	{	
		if(strcmp(uName,user.uName) != 0)
		{
			fwrite(&user,sizeof(user),1,tp_fp);
		}	
	}
	fclose(rmu_fp);
	fclose(tp_fp);
	if(remove("Accounts.dat") !=0)
	{
		printf("Error");
		printf("\nRedirecting to main page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		return;
	}
	else
	{
		rename("tempfile.dat","Accounts.dat");
	}
	printf("\nAccount has been removed successfully.");
	printf("\nDo you want to remove another Account.");
	printf("\nPress (y/Y) to remove.");
	scanf(" %c",&choice);
	if(choice == 'y' || choice == 'Y')
	{
		goto rm_user;
	}
	printf("\nRedirecting to main page");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	return;
}

void list_Product()
{
	system("cls");
	int i=0;
	char choice;
	struct store product;
	FILE *lp_ptr;
	lp_ptr = fopen("Products.dat","rb");
	if(lp_ptr == NULL)
	{
		setColor(12);
		printf("Error Accessing the data.Try Again.");
		Sleep(1000);
		setColor(9);
		return;
	}
	printf("\n\t\t\tProducts");
	printf("\n------------------------------------------");
	printf("\nS.N  Name\t    Barcode \t Quantity\t Rate");
	while(fread(&product,sizeof(product),1,lp_ptr))
	{
		printf("\n%d.   %s\t %12lld\t   %d\t\t %.2f",i+1,product.name,product.barcodeNum,product.quantity,product.rate);
		i++;
	}
	fclose(lp_ptr);
	printf("\nPress (b) to go back.");
	scanf(" %c",&choice);
	if(choice == 'b')
	{
		printf("\nThank you .");
		return;
	}
	printf("\nThank you for using.");
	exit(0);
}

void addProduct()
{
	system("cls");
	int i=0,size;
	char choice,name[20];
	struct store product;
	FILE *ap_ptr;
	ap_ptr = fopen("Products.dat","ab+");
	if(ap_ptr == NULL)
	{
		setColor(12);
		printf("\nError Accessing the data.Try Again");
		setColor(7);
		fclose(ap_ptr);
		return;
	}
	size = sizeof(product);
	printf("Enter product name: ");
	fflush(stdin);
	gets(name);
	while(fread(&product,sizeof(product),1,ap_ptr))
	{
		if(strcmp(name,product.name) == 0)
		{
			printf("Enter it's quantity: ");
			fflush(stdin);
			scanf(" %d",&product.quantity);
			fseek(ap_ptr, -size, SEEK_CUR);
			fwrite(&product,sizeof(product),1,ap_ptr);
			fclose(ap_ptr);
			printf("\nProduct Added successfully");
			printf("\nDo you want to add another product.");
			printf("\nPress (y/Y) to add.");
			scanf(" %c",&choice);
			if(choice == 'y' || choice == 'Y')
			{
				addProduct();
				return;
			} 
			printf("Redirecting to main page");
			for(i=0;i<3;i++)
			{
				printf(".");
				Sleep(500);
			}
			return;
		}
	}
	fseek(ap_ptr, 0, SEEK_END);
	strcpy(product.name,name);
	printf("Enter it's quantity: ");
	fflush(stdin);
	scanf(" %d",&product.quantity);
	printf("Enter it's Barcode: ");
	fflush(stdin);
	scanf("%lld",&product.barcodeNum);
	printf("Enter it's rate: ");
	fflush(stdin);
	scanf("%f",&product.rate);
	fwrite(&product,sizeof(product),1,ap_ptr);
	fclose(ap_ptr);
	printf("\nProduct Added successfully.");
	printf("\nDo you want to add another product.");
	printf("\nPress (y/Y) to add.");
	scanf(" %c",&choice);
	if(choice == 'y' || choice == 'Y')
	{
		addProduct();
		return;
	} 
	printf("Redirecting to main page");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	return;
}

void updateProduct()
{
	system("cls");
	int i=0,flag=0,size;
	char choice,name[30];
	struct store product;
	size = sizeof(product);
	FILE *up_ptr;
	up_ptr = fopen("Products.dat","rb+");
	if(up_ptr == NULL)
	{
		setColor(12);
		printf("Error Accessing the Data.");
		setColor(9);
		fclose(up_ptr);
		return;
	}
up_start:
	printf("Enter the Product you want to change: ");
	fflush(stdin);
	gets(name);
	rewind(up_ptr);
	while(fread(&product,sizeof(product),1,up_ptr))
	{	
		if(strcmp(name,product.name) == 0)
		{
			fseek(up_ptr, -size, SEEK_CUR);
			printf("Enter New product: ");
			fflush(stdin);
			gets(product.name);
			printf("Enter it's quantity: ");
			fflush(stdin);
			scanf(" %d",&product.quantity);
			printf("Enter it's Barcode: ");
			fflush(stdin);
			scanf("%lld",&product.barcodeNum);
			printf("Enter it's rate: ");
			fflush(stdin);
			scanf("%f",&product.rate);
			fwrite(&product,sizeof(product),1,up_ptr);
			fclose(up_ptr);
			printf("\nProduct has been updated successfully.");
			printf("\nDo you want to update another product.");
			printf("\nPress (y/Y) to update.");
			scanf(" %c",&choice);
			if(choice == 'y' || choice == 'Y')
			{
				goto up_start;
			}
			printf("\nRedirecting to main page");
			for(i=0;i<3;i++)
			{
				printf(".");
				Sleep(500);
			}
			return;
		}	
	}
	if(flag<3)
	{
		setColor(12);
		printf("\nProduct doesn't Exist.Try Again.");
		setColor(9);
		goto up_start;
	}
	else
	{
		setColor(12);
		printf("\nProduct doesn't Exist in the store.");
		setColor(9);
		fclose(up_ptr);
		printf("\nRedirecting to main page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		return;
	}
}

void removeProduct()
{
	system("cls");
	int i=0;
	char choice,name[30];
	struct store product;
	FILE *rm_ptr,*tp_ptr;
	rm_ptr = fopen("Products.dat","rb+");
	if(rm_ptr == NULL)
	{
		setColor(12);
		printf("Error Accessing the Data.");
		setColor(9);
		fclose(rm_ptr);
		return;
	}
rm_start:
	printf("Enter the Product you want to remove: ");
	fflush(stdin);
	gets(name);
	rewind(rm_ptr);
	while(fread(&product,sizeof(product),1,rm_ptr))
	{	
		if(strcmp(name,product.name) == 0)
		{
			goto skip;
		}
	}
	printf("\nNo need to remove product. \nIt was not there from the start.");
	printf("\nRedirecting to main page");
	for(i=0;i<3;i++)
	printf(".");
	Sleep(500);
	return;	
skip:	
	tp_ptr =fopen("temp.dat","wb");
	if(tp_ptr == NULL)
	{
		setColor(12);
		printf("Error Creating Temporary File.");
		setColor(9);
		return;
	}
	rewind(rm_ptr);
	while(fread(&product,sizeof(product),1,rm_ptr))
	{	
		if(strcmp(name,product.name) != 0)
		{
			fwrite(&product,sizeof(product),1,tp_ptr);
		}	
	}
	fclose(tp_ptr);
	fclose(rm_ptr);
	remove("Products.dat");
	rename("temp.dat","Products.dat");
	printf("\nProduct has been removed successfully.");
	printf("\nDo you want to remove another product.");
	printf("\nPress (y/Y) to remove.");
	scanf(" %c",&choice);
	if(choice == 'y' || choice == 'Y')
	{
		goto rm_start;
	}
	printf("\nRedirecting to main page");
	for(i=0;i<3;i++)
	{
		printf(".");
		Sleep(500);
	}
	return;
}

void sale()
{
	system("cls");
	char name[20],choice,date[11];
	long long int barcode;
	int i=0,flag=0,qty,size;
	struct store product;
	struct sale sales;
	FILE *ptr_sale,*ptr_total;
sale_start:
	ptr_sale = fopen("Products.dat","rb+");
	ptr_total = fopen("TotalSales.dat","ab+");
	if(ptr_sale == NULL)
	{
		setColor(12);
		printf("Error Accessing data");
		setColor(9);
		fclose(ptr_sale);
		printf("\nRedirecting to main page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		return;
	}
	size = sizeof(product);
		printf("Enter the Product's name: ");
		fflush(stdin);
		gets(name);
		rewind(ptr_sale);
		while(fread(&product,size,1,ptr_sale))
		{
			if(strcmp(name,product.name) == 0)
			{
				fseek(ptr_sale, -size, SEEK_CUR);
				flag =1;
				break;
			}
		}
		if(flag == 0)
		{
			setColor(12);
			printf("There is no such product in the store.Try Again.\n");
			setColor(9);
			flag--;
			goto sale_start;
		}
		if(flag == -1)
		{
			printf("Try using the product's barcode.\n");
			printf("Enter the Barcode: ");
			fflush(stdin);
			scanf("%lld",&barcode);
			rewind(ptr_sale);
			while(fread(&product,size,1,ptr_sale))
			{
				if(product.barcodeNum == barcode)
				{
					fseek(ptr_sale, -size, SEEK_CUR);
					flag =1;
					goto Q;
				}
			}
			flag = 0;
			setColor(12);
			printf("There is no such product in the store.\n");
			setColor(9);
			goto sale_start;
		}
Q:
		printf("Enter the quantity: ");
		fflush(stdin);	
		scanf(" %d",&qty);
		if( qty > product.quantity)
		{
			setColor(12);
			printf("\nInsufficent Quantity.");
			setColor(9);
			goto sale_start;
		}
		else
		{
		product.quantity -= qty;
		fwrite(&product,size,1,ptr_sale);
		printf("\nYour total cost is %.2f",product.rate*qty);
		get_current_date(date);
		strcpy(sales.p.name,product.name);
		strcpy(sales.date,date);
		sales.p.rate = product.rate;
		sales.p.quantity = qty;
		sales.p.rate *= sales.p.quantity;
		fwrite(&sales,sizeof(sales),1,ptr_total);
		fclose(ptr_sale);
		fclose(ptr_total);
		setColor(10); 
		printf("\nProduct Sale Successfull.");
		setColor(9);
		printf("\nDo you want to sale another product. ");
		printf("\nPress (y/Y) to sale.");
		fflush(stdin);
		scanf(" %c",&choice);
		if(choice == 'y' || choice == 'Y')
		{
			goto sale_start;
		}
		printf("\nRedirecting to main page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		return;
		}
}

void todaySales()
{
	system("cls");
	int i=0,total =0;
	char choice,date[11];
	struct sale sales;
	FILE *pt;
	pt =fopen("TotalSales.dat","rb");
	if(pt == NULL)
	{
		setColor(12);
		printf("Error");
		setColor(9);
		fclose(pt);
		Sleep(1000);
		return;
	}
	i=0;
	printf("\n\t\t\t\t\tToday's Sale");
	printf("\n\t\t\t------------------------------------");
	printf("\nS.N Name\t\t\t Date\t\t\tQuantity\tTotal");
	while(fread(&sales,sizeof(sales),1,pt))
	{
		printf("\n%d.   %s\t\t\t %s\t\t%d\t\t%.2f",i+1,sales.p.name,sales.date,sales.p.quantity,sales.p.rate);
		total += sales.p.rate;
		i++;
	}
	printf("\n---------------------------");
	printf("\nTotal Sales: \t\t\t\t%d",total);
	fclose(pt);
	printf("\nPress (b) to go back.");
	scanf(" %c",&choice);
	if (choice == 'b')
	{
		return;
	}
	printf("Thank you for using.");
	exit(0);
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

char* UID_Generator(Role rol)
{
	int i=1,j=1;
	struct userDetail id;
	char *UID = (char *) malloc(10 * sizeof(char));
	FILE *fp;
	fp = fopen("Accounts.dat","rb");
	if(fp == NULL)
	{
		setColor(12);
		printf("\n\t\t\t\tError Accessing the data.Try Again.");
		Sleep(2000);
		setColor(9);
		fclose(fp);
		return "Invalid";
	}
	while(1)
	{
		if(rol == owner)
		{
			rewind(fp);
			i=1;
			while(fread(&id,sizeof(id),1,fp))
			{
				if(id.role == owner)
				{
					i++;
				}
			}
			sprintf(UID,"00%d",i);
			fclose(fp);
			return UID;
		}
		else if(rol == manager)
		{
			rewind(fp);
			i=1;
			while(fread(&id,sizeof(id),1,fp))
			{
				if(id.role == manager)
				{
					i++;
				}
			}
			sprintf(UID,"0%d0",i);
			fclose(fp);
			return UID;
		}
		else if(rol == employee)
		{			
			rewind(fp);
			i=1;
			while(fread(&id,sizeof(id),1,fp))
			{
				if(id.role == employee)
				{
					i++;
					if(i>9)
					{
						i=1;
						j++;
					}
				}
			}
			sprintf(UID,"%d0%d",j,i);
			fclose(fp);
			return UID;
		}
		else
		{
			sprintf(UID,"Invalid");
			fclose(fp);
			return UID;
		}
	}
	fclose(fp);
	free(UID);
	return "Invalid";
}

void get_current_date(char date[])
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	strftime(date,11,"%Y-%m-%d",tm);
}

void setColor(int textColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor);
}
