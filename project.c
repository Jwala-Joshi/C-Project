#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

typedef enum {owner,manager,employee,admin} Role;

struct userDetail
{
	char uName[20],pass[20],uid[10];
	Role role;
};

struct store 
{
	int quantity;
	char name[30];
	long long int barcodeNum[13];
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
Role strToRole(char [] );
char* roleToStr(Role);
void get_cuurent_date(char []);	
void todaySales()
{
	system("cls");
	int i;
	char choice;
	struct sale sales;
	FILE *pt;
	pt =fopen("Total Sales.dat","rb");
	if(pt == NULL)
	{
		printf("Error");
		return;
	}
	i=0;
	while(fread(&sales,sizeof(sales),1,pt))
	{
		printf("\n%d %s %d",i+1,sales.p.name,sales.p.quantity);
		i++;
	}
	printf("press (e) to view total sales or (b) to go back. ");
	scanf("&c",choice);
	if(choice =='e')
	{
		
	}
	else if (choice == 'b')
	{
		return;
	}
}

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
			owner_Access(loggedRole);
			break;
		
		case manager:
			setColor(9);
			printf("\nManager");
			manager_Access(loggedRole);
			break;
		
		case employee:
			setColor(9);
			printf("\nEmp");
			Emp_Access(loggedRole);
			break;
			
		case admin:
			setColor(9);
			printf("\nEmp");
			ADMIN(admin);
			break;
			
		default:
			setColor(12);
			printf("Error");
	}
	setColor(7);
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
	setColor(7);
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
			printf("\nPassword doesn't match. Try again.");
			goto newPass;
		}
		strcpy(user.pass,pass1);
		fwrite(&user,sizeof(user),1,rec_fp);
		fclose(rec_fp);
		printf("\nPassword Successfully Changed.");
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
		printf("\nUID couldn't be verified.Try Again.");
		setColor(7);
			
	}
	setColor(12);
	printf("\nInvaild UID.Try Again");
	setColor(7);
	goto r_Pass;
}

void owner_Access(Role role)
{
	char choice;
o_start:
	system("cls");
	printf("\n\n\n\t\t\t\t\tSmall Mart\n\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\t\t\t---------------------------------------\n");
	printf("\n\n\t\t\t\t\tAdmin\n\n");
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
			printf("In Progress.");
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
	printf("\n\n\t\t\t\t\tAdmin\n\n");
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
			printf("E");
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
			exit(0);
			
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
		return;
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
		if(role == manager && user.role == manager)
		{
			continue;
		}
		printf("\n\t\t\t\t%d. %s \t\t\t%s",i+1,user.uName,roleToStr(user.role));
		i++;
	}
	printf("\n\t\t\t\tPress (b) to go back.");
	scanf(" %c",&choice);
	if(choice == 'b')
	{
		return;
	}
	setColor(7);
	printf("\n\t\t\t\tThank you fo using.");
	exit(0);
}

void modAcc(Role role)
{
	system("cls");
	int i=0,flag=1,size;
	char ch,choice,uName[20],uRole[10];
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
		return;
	}
mod_start:
	printf("Enter Username: ");
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
			gets(uRole);
			user.role = strToRole(uRole);
			fwrite(&user,sizeof(user),1,mod_fp);
			fclose(mod_fp);
			system("cls");
			setColor(10);
			printf("\n\t\t\t\tThe user has been successfully updated.");
			setColor(9);
			printf("\n\t\t\t\tDo you want to modify another account.[y/n]");
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
		printf("\n\t\t\t\tRedirecting to Admin page");
		for(i=0;i<3;i++)
		{
			printf(".");
			Sleep(500);
		}
		fclose(mod_fp);
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
		if( user.role == manager)
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
	remove("Accounts.dat");
	rename("tempfile.dat","Accounts.dat");
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
	printf("\nS.N  Name\t Barcode \tQuantity\t rate");
	while(fread(&product,sizeof(product),1,lp_ptr))
	{
		printf("\n%d.   %s\t %lld\t   %d\t\t %.2f",i+1,product.name,product.barcodeNum,product.quantity,product.rate);
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
	int i=0;
	char choice;
	struct store product;
	FILE *ap_ptr;
	ap_ptr = fopen("Products.dat","ab");
	if(ap_ptr == NULL)
	{
		setColor(12);
		printf("\nError Accessing the data.Try Again");
		setColor(7);
		fclose(ap_ptr);
		return;
	}
	choice = 'y';
	while(choice == 'y' || choice == 'Y')
	{
		printf("Enter product name:");
		fflush(stdin);
		gets(product.name);
		printf("Enter it's quantity");
		fflush(stdin);
		scanf(" %d",&product.quantity);
		printf("Enter it's Barcode");
		fflush(stdin);
		scanf("%lld",&product.barcodeNum);
		printf("Enter it's rate");
		fflush(stdin);
		scanf("%f",&product.rate);
		fwrite(&product,sizeof(product),1,ap_ptr);
		printf("\nProduct Added successfully");
		printf("\nDo you want to add another product.");
		printf("\nPress (y/Y) to add.");
		scanf(" %c",&choice);
	}
	fclose(ap_ptr);
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
			printf("Enter New product");
			fflush(stdin);
			gets(product.name);
			printf("Enter it's quantity");
			fflush(stdin);
			scanf(" %d",&product.quantity);
			printf("Enter it's Barcode");
			fflush(stdin);
			scanf("%lld",&product.barcodeNum);
			printf("Enter it's rate");
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
	long int barcode;
	int quanti,size;
	struct store product;
	struct sale sales;
	time_t t = time(NULL);
	FILE *ptr_sale,*ptr_total;
	ptr_sale = fopen("Products.dat","r+");
	if(ptr_sale == NULL)
	{
		setColor(12);
		printf("Error Accessing data");
		setColor(9);
		return;
	}
	size = sizeof(product);
	choice ='y';
	while(choice == 'y')
	{
		printf("\nEnter the Product's name: ");
		fflush(stdin);
		gets(name);
		while(fread(&product,sizeof(product),1,ptr_sale))
		{
			if(strcmp(name,product.name) == 0)
			{
				goto okay;
			}
		}
		printf("\nThere is no such product in the store.Try Again.");
		continue;
	okay:
		printf("\nEnter the quantity: ");
		fflush(stdin);	
		scanf(" %d",&quanti);
		printf("\nYour total cost is %.2f",product.rate*quanti);
		fseek(ptr_sale, -size,SEEK_CUR);
		product.quantity -=quanti;
		rewind(ptr_sale);
		fwrite(&product,size,1,ptr_sale);
		ptr_total = fopen("Total Sales.dat","ab+");
		sales.p.quantity = quanti;
		sales.date = get_current_date(date);
		fwrite(&sale,sizeof(sale),1,ptr_total);
		fclose(ptr_total); 
		printf("\nDo you want to exit[y/n]: ");
		fflush(stdin);
		scanf(" %c",&choice);
	}
	printf("\nThank you for using");
	return;
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

void get_cuurent_date(char date)
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
