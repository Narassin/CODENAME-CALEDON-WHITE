#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include <stdlib.h>

//function prototype
void intro(void);
void drgmanager(void);
void drgbudget(void);
void drglist(void);
void drgcheckoff(void);
int printlist(void);
void rcal(void);
void help(void);
void credit(void);
//Variables(global parameter + arrays)
char username[30];
int cal[] = 	{100,100,130,10,130,260,130,140,150,150,260,120,180,120,330,320,240,320,440,300,100,260,530,420,290,510,310,420,150,70,80,65,40,40,38,80,520,200,130,
				50,120,70,40,20,20,60,50,50,50,80,60,40,80,50,40,240,130,150,160,160,40,50,40,50,40,50,30,30,50,70,70,60,70,130,40,60,20,140};
//structure declaration
struct children
{
	int rollNo;
	char Name[30];
	float amount;
	int status;
};


//main function
int main()
{
	//local var
	FILE *logger;
	int i=0;
	char opt;
	system("title ProRaya");
	time_t current_time;
    char* c_time_string;

	
	logger = fopen("Database\\LOG.txt","a+");
	//Begginning Mesage + Name Input
	printf("It is recomended to have the program maximize to fullscreen for optimum experience\nThank you for using the ProRaya v2.5\nEnter your name: ");
	scanf("%s",username);
	fflush(stdin);
    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);
	fprintf(logger,"%s%s\n",c_time_string,username);
	fclose(logger);
	system("cls");
	intro();
	system("pause");
	system("cls");
	//Main Menu Loop
	while(i==0)
	{
		printf("\tPRORAYA\n**************************\nHAPPY EIDUL FITRI MUBARAK,%s\n==============\nMAIN MENU\n==============\n",strupr(username));
		printf("1.Money Giving Manager\n2.Calories Calculator\n3.Credit\n4.Exit\nChoose an option: ");
		scanf("%c",&opt);
		fflush(stdin);
		switch(opt)
		{
			case '1':drgmanager();break;
			case '2':rcal();break;
			case '3':credit();break;
			case '4':i=1;break;
			default:printf("Incorrect input\n");
		}
		system("cls");
	}
	system("pause");
	return 0;
}

//intro
void intro(void)
{
	char dataToBeRead[600];
	printf("Welcome %s,\n",username);
	FILE *fint;
	fint = fopen("Database\\Intro.txt","r");
	
	 while( fgets ( dataToBeRead, 50, fint) != NULL ) 
    {      
    	// Print the dataToBeRead  
    	printf( "%s" , dataToBeRead ) ; 
	}
	fclose(fint) ;
	printf("\n"); 
}

//DR Giver Manager(budget manager)
void drgmanager(void)
{
	//Local Var
	int i=0;
	char opt;
	system("cls");
	
	//Sub Menu
	while(i==0)
	{
		printf("Duit Raya Giver Manager\n");
		printf("1.Manage Budget\n2.Add Receiver\n3.Check off List\n4.Return to Main Menu\nOption: ");
		scanf("%c",&opt);
		fflush(stdin);
		switch(opt)
		{
			case '1':drgbudget();break;
			case '2':drglist();break;
			case '3':drgcheckoff();break;
			case '4':printf("Returning to main menu");i=1;break;
			default:printf("Invalid option");
		}
		system("cls");
	}
}

//Budget Advisor v2.0
void drgbudget(void)
{
	//local var
	float drg_budget,budget_avg;
	int kids;
	printf("*************************************\n");
	printf("BUDGET ADVISOR\n");
	//prompt budget
	printf("\nAlright %s,\nEnter your Budget: ",username);
	scanf("%f",&drg_budget);
	fflush(stdin);
	//prompt number of attendee
	printf("Enter estimate duit raya receiver(Most likely your relative): ");
	scanf("%d",&kids);
	fflush(stdin);
	//calculate average(max average) of duit raya
	budget_avg =(float) drg_budget / kids;
	//display result and give a little advise
	printf("The most you can give per duit raya receiver is  RM%.2f. If given equally...\"IF\"\n",budget_avg);
	if(budget_avg>11)
		printf("If you give RM 5 or RM 10, you'll still have plenty for the neighbor's kid that randomly come to your house.\n");
	else
		printf("If you give RM 2 - RM 5, you'll still have plenty for the neighbor's kid that randomly come to your house.\n");
	system("pause");
}

//Duit Raya Checklist
void drglist(void)
{
	//variable
	int i = 0;
	struct children s1,s2;
	char boolean;
	
	printf("*************************************\n");
	//print current list
	i = printlist();
	
	//opening the database.txt file for adding new entries
	FILE *database = fopen("Database\\Data01.txt","a+");
	if(database == 0)
	{
		printf("File does not exist @ not found");

	}
	
	//loop for continuous entry prompting
	do
	{
		s1.rollNo = ++i;
		printf("Enter Name: ");
		scanf("%s",s1.Name);
		fflush(stdin);
		printf("Enter Amount(RM): ");
		scanf("%f",&s1.amount);
		fflush(stdin);
		printf("Status?(0-Given/1-Not Given Yet)");
		do
		{
			scanf("%d",&s1.status);
			switch(s1.status)
			{
				case 0:break;
				case 1:break;
				default:printf("Incorrect input!! Please RE-ENTER:");
			}
		}while(!(s1.status==1||s1.status==0));
		fflush(stdin);
		//printing into the files
		fprintf(database,"%d\t%s\t%.2f\t%d\n",s1.rollNo,s1.Name,s1.amount,s1.status);
		
		printf("Continue?(Y=Yes/N=No) ");
		boolean = getch();
		printf("\n");
	}while(!(boolean == 'N'||boolean == 'n'));
	fclose(database);
	//reprint new list
	i = printlist();
	printf("\n*************************************\n");
	
	system("pause");
}

//duit raya list checkist
void drgcheckoff(void)
{
	//variable
	struct children s1,s2;
	FILE *fp1, *fp2;
	char c;
	int del_line, temp = 1, i;
	printf("*************************************\n");	
	//print current list
	i = printlist();
	//open filename
	fp1 = fopen("Database\\Data01.txt","r");
	//ask user for line to edit
	printf("Enter number to update status: ");
	scanf("%d",&del_line);
	//open copy.txt
	fp2 = fopen("Database\\Copy.txt","w");
	c = getc(fp1);
	while(c != EOF) 
	{
		if(c == '\n')
		{
			temp++;
		}
		//till the destined updated code
		if(temp != del_line)
		{
			putc(c,fp2);
		}
		else
		{
			//print the line and change the status value
			fscanf(fp1,"%d\t%s\t%f\t%d\n",&s1.rollNo,&s1.Name,&s1.amount,&s1.status);
			printf("Status owner: %s\n",s1.Name);
			if(s1.status == 1)
				s1.status = 0;
			else
				s1.status = 1;
			fprintf(fp2,"\n%d\t%s\t%.2f\t%d\n",s1.rollNo,s1.Name,s1.amount,s1.status);
			temp++;
		}
		c = getc(fp1);
	}
	//close the file
	fclose(fp1);
	fclose(fp2);
	//replacing the Data01
	remove("Database\\Data01.txt");
	rename("Database\\copy.txt","Database\\Data01.txt");
	printf("\nNew list:\n");
	i = printlist();
	printf("\n*************************************\n");
	system("pause");
}

int printlist(void)
{
	///variable
	int cev=0,x = 0;
	struct children s1,s2;
	//opening file
	FILE *database = fopen("Database\\Data01.txt","r");
	if(database == 0)
	{
		printf("File does not exist, creating new file\n");
		return 0;
	}
	else
		printf("NO\tNAME\t\t\tAMOUNT(RM)\tSTATUS\n--\t----\t\t\t----------\t------\n");
	
	while(cev != -1)
	{
	cev = fscanf(database,"%d\t%s\t%f\t%d\n",&s1.rollNo,&s1.Name,&s1.amount,&s1.status);
	if(cev==-1)
		break;
	printf("%d\t%-20s\t%.2f\t\t",s1.rollNo,s1.Name,s1.amount);
	if(s1.status==0)
		printf("Given\n");
	else
		printf("Not Given Yet\n");
	}
	x = s1.rollNo;
	fclose(database);
	return x;
}

//Raya Calories calculator
void rcal(void)
{
	//variable
	int n,calo;
	float quant, ttl_cal=0;
	char verify;
	//call txt file to display the calory catalog
	char dataToBeRead[400];
	system("cls");
    //prommpt for use to enter food code
    do
    {
		do
		{
			printf("RAYA CALORIES CALCULATOR\n");
			FILE *fint;
			fint = fopen("Database\\RayCal.txt","r");
			
			while( fgets ( dataToBeRead, 400, fint) != NULL ) 
		    { 
		      
		        // Print the dataToBeRead  
		        printf( "%s" , dataToBeRead ) ; 
		    } 
		          
		        // Closing the file using fclose() 
		    fclose(fint) ;
		    printf("\n");
			printf("\n*************************************\n");
			printf("Enter Item No.(1-77): ");
			scanf("%d",&n);
			if(!(n>0&&n<77))
				printf("Invalid Item No.!! Re-enter: ");
		}while(!(n>0&&n<77));
		if(n==76)
		{
			printf("How much calories does it contain(cal)? ");
			scanf("%d",&calo);
		}
		else
			calo = cal[n-1]; 
		printf("Enter serving size multiplier: ");
		scanf("%f",&quant);
		
		ttl_cal += quant * calo;
		printf("Current cal tally %.1f cal\n",ttl_cal);
		printf("Did you eat anything else?(Y-Yes/N-No): ");
		do
		{
			verify = toupper(getch());
			fflush(stdin);
			printf("\n*************************************\n");
			if(!(verify=='Y'||verify=='N'))
				printf("Invalid option!!Re-enter: ");
		}while(!(verify=='Y'||verify=='N'));
		if(verify=='N')
		{
			if(ttl_cal>=1000.00)
			{
				ttl_cal /= 1000;
				printf("Your total calory intake of the day is %.2f kcal",ttl_cal);
			}
			else
				printf("Your total calory intake of the day is %.2f cal",ttl_cal);
			printf("\n");
		}
		else
		system("cls");
	}while(verify=='Y');
	 
	system("pause");
}

//credit function
void credit(void)
{
	system("cls");
	printf("CREDIT\n*******\n");
	printf("Project Codename: CELADON WHITE\nSoftware name: ProRaya\nVersion: 1.0\nDeveloper: Ahmad Nuruddin Bin Muksalmina\nProject Start Date: 10/6/2019\nProject Final Edit Date: 1/7/2019");
	printf("\n\n*************************************************\n");
	system("pause");
}

