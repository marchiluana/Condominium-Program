#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct person
{
	char code[128];
	char id[128];
	char name[128];
	char apartment[128];
	char debit [128];

} Person;

typedef struct remove
{
	char code[128];
	char id[128];
	char name[128];
	char apartment[128];
	char debit [128];
} Remove;


typedef struct condominium
{
	Person person[100];
	Remove remove[100];
	int numRegis;

} Condominium;

FILE* file;
FILE* number;

void dumpToConsole(Condominium * p, int numPerson);
void extractString(char line[], char extractedString[]);
void updateFile(Condominium * p);
void pullFile(Condominium * p);
void newRes (Condominium * p);
void show (Condominium * p);
void update (Condominium * p);
void displayDeb(Condominium * p);
void displayEven (Condominium * p);
void removeRes (Condominium * p);

int main ()
{
	setlocale(LC_ALL, "Portuguese");
	int menu;
	Condominium c;
	Remove r;
	char buffer[128];
	
	do
	{
		printf("--------------------- MENU ----------------------\n\n\n");
		printf("\t1-Insert a new resident.\n\n");
		printf("\t2-View resident data. \n\n");
		printf("\t3-Update rent owing. \n\n");
		printf("\t4-Display residents who owe rent.\n\n");
		printf("\t5-Display residents whose rent is paid. \n\n");
		printf("\t6-Remove resident.\n\n");
		printf("\t0-Exit\n\n\n-------------------------------------------------\n");
		
		printf("\nChoose an option: ");
		fflush(stdin);
		fgets(buffer, 127, stdin);
		sscanf(buffer, "%d", &menu);
	
		if((menu > 0) && (menu <= 6))
			{
				switch(menu)
				{
			
					case 0:
						break;
						
					case 1:
						printf("\nInsert new resident option selected.\n\n");
						newRes(&c);
						break;
						
						
					case 2:
						printf("\nView resident data option selected.\n\n");
						show(&c);		
						break;
							
					case 3:
						printf("\nUpdate rent owing option selected.\n\n");
						update(&c);
						
						break;
						
					case 4:
						printf("\nDisplay residents who owe rent option selected.\n\n");
						displayDeb(&c);
						
						break;
						
					case 5:
						printf("\nDisplay residents whose rent is paid option selected.\n\n");
						displayEven(&c);
						
						break;
						
					case 6:
						printf("Remove resident option selected.\n\n");
						removeRes(&c);
				
					default:
						("Value invalid! Only 1-6 numbers valid!");
					}
			}
			
			else if(menu == 0)
			{
				printf("!Program closed!");
				break;
			}
			
			else 
			{
				printf("\n!!! Type a number between 1 - 6 !!!");
				
				continue;
			}
		
	}while(menu!=0);
	
	return 0;
		
}

void pullFile(Condominium * p)
{
	char buffer [1024];
	int i, j;
	int num;
	
	file = fopen("documento.txt", "r");
	number = fopen("qnt.txt", "r");
	
	fgets(buffer, 127, number);
	sscanf(buffer, "%d", &p->numRegis);
	
	fclose(number);
	
	for (i = 0; i < p->numRegis - 1; i++) // Loop through all the lines of data.
	{
		
		// Get the CODE from the file and store it in the struct.
		fgets(buffer, 127, file);
		extractString(buffer, p->person[i].code);
		
		// Get the ID from the file and store it in the struct.
		fgets(buffer, 127, file);
		extractString(buffer, p->person[i].id);
		
		// Get the NAME from the file and store in the struct.
		fgets(buffer, 127, file);
		extractString(buffer, p->person[i].name);
		
		// Get the APARTMENT NUMBER from the file and store it in the struct.
		fgets(buffer, 127, file);
		extractString(buffer, p->person[i].apartment);
		
		// Get the DEBIT from the file and store in the struct.
		char debBuffer[32];
		fgets(buffer, 127, file);
		extractString(buffer, debBuffer);
		sscanf(debBuffer, "%[^\n]s", &p->person[i].debit);
	  
	}
	
	fclose (file);
	
//	dumpToConsole(p, p->numRegis);
    
}

void newRes (Condominium * p)
{		

	char buffer[128];
	char bufferNum[128];
	char id[128];
	char name[128];
	char apartment[128];
	char debit[128];
	int num = 0;
	char f[256];
	int i;
	
	file = fopen("documento.txt", "a");
	
	number = fopen("qnt.txt", "r");
	
	printf("How many people do you want to insert: ");
	fgets(bufferNum, 127, stdin);
	sscanf(bufferNum, "%d", &num);
	
	
	fgets(buffer, 127, number);
	sscanf(buffer, "%d", &p->numRegis);

	fclose(number);
	
	for(i = 1; i <= num; i++)
	{
		printf("\nResident #%d!\n\n", i);
		
		printf("Enter new condominium ID:\n");
		fgets(id, 127, stdin);
	
		printf("\nEnter new condominium name:\n");
		fgets(name, 127, stdin);		

		printf("\nEnter new condominium apartment number:\n");
		fgets(apartment, 127, stdin);
		
		printf("\nEnter the rent owing:\nR$");
		fgets(debit, 127, stdin);

		printf("\nResident registered sucessfully!\nYour code is 00%d!\n", p->numRegis);
		printf("\n\n-------------------------------------------------\n\n");
			
		fprintf(file, "Code:00%d\nID:%sName:%sAp.:%sRent owing:%s", p->numRegis, id, name, apartment, debit);
		p->numRegis++;
		
	}
			
	number = fopen("qnt.txt", "w");
				
	fseek(number, 0, SEEK_SET);
	fprintf(number,"%d", p->numRegis);	
	
	fclose(file);
	fclose(number);	
	
}

void show (Condominium * p)
{		
	char code[10];
	char buffer[10];
	int i;
	int x = 0;
	char c;
	BOOL isContinuing = TRUE;
	
	while(isContinuing)
	{	
	
		printf("Enter code to view resident:\n");
		fflush(stdin);
		fgets(buffer, 9, stdin);
		sscanf(buffer, "%[^\n]s", &code);
		
		pullFile(p);
	
		for (i = 0; i < p->numRegis - 1; i++)
		{
			if (strcmp(code, p->person[i].code) == 0)
			{
				x++;
				
				printf("------------------------------\n\n");
				printf("Code: %s\n", p->person[i].code);
				printf("ID: %s\n", p->person[i].id);
				printf("Name: %s\n", p->person[i].name);
				printf("Apartment: %s\n", p->person[i].apartment);
				printf("Rent owing: R$%s\n", p->person[i].debit);
				printf("\n------------------------------\n\n");
				
				printf("Do you want to view another resident?\n(Y/N): ");
				c = getchar();
				
				if(c == 'N' || c == 'n' )
				{
					printf("\n");
					isContinuing = FALSE;
					break;
				}
				
				else if (c == 'Y' || c == 'y')
				{
					printf("\n");
					continue;
				}
				
				else
				{
					printf("!!!Invalid input!!!");
					getchar();
					break;
				}
				
			}
		}
		
		if(x = 0)
		{
			printf("\n!!!This code doens't exist!!!\n");
			printf("Try again!\n\n");
		}	
	}
}

void update (Condominium * p)
{
	char code[10];
	char buffer[128];
	char debit[128];
	int i;
	int x = 0;
	char c;
	BOOL isContinuing = TRUE;

	while(isContinuing)
	{	
	
		printf("Enter code to change rent owing:\n");
		fflush(stdin);
		fgets(buffer, 127, stdin);
		sscanf(buffer, "%[^\n]s", &code);
		
		pullFile(p);
	
		for (i = 0; i < p->numRegis - 1; i++)
		{
			if (strcmp(code, p->person[i].code) == 0)
			{
				x++;
				
				printf("------------------------------\n\n");
				printf("Code: %s\n", p->person[i].code);
				printf("ID: %s\n", p->person[i].id);
				printf("Name: %s\n", p->person[i].name);
				printf("Apartment: %s\n", p->person[i].apartment);
				printf("Rent owing: R$%s\n", p->person[i].debit);
				printf("\n------------------------------\n\n");
				
				printf("Enter new rent owing:\nR$");
				fgets(buffer, 127, stdin);
				sscanf(buffer, "%[^\n]s", &debit);
								
				strcpy(p->person[i].debit, debit);
				
				updateFile(p);
			    
			    printf("\nRent owing updated!\n");
			    
			    printf("\n\n------------------------------\n\n");
				printf("Code: %s\n", p->person[i].code);
				printf("ID: %s\n", p->person[i].id);
				printf("Name: %s\n", p->person[i].name);
				printf("Apartment: %s\n", p->person[i].apartment);
				printf("Rent owing:R$%s\n", p->person[i].debit);
				printf("\n------------------------------\n\n");
				
				printf("Do you want to change another rent owing?\n(Y/N): ");
				c = getchar();
				fflush(stdin);
				printf("\n");
			    
			    if(c == 'N' || c == 'n' )
				{
					isContinuing = FALSE;
				}
				
				else if (c == 'Y' || c == 'y')
				{
					continue;
				}
				
				else
				{
					printf("!!!Invalid input!!!");
					getchar();
				}	
			}
		}	
		
		if(x = 0)
		{
			printf("\n!!!This code doens't exist!!!\n");
			printf("Try again!\n\n");
		}
	}
}

void displayDeb (Condominium * p)
{
	int i;
	int x = 0;
	int result;
	
	printf("-------------- RESIDENTS OWING RENT --------------\n\n");
	
	pullFile(p);
	
	for (i = 0; i < p->numRegis - 1; i++)
	{
		result = strcmp(p->person[i].debit, "0");
		x++;
		
		if (result != 0)
		{	
		
			printf("%d- %s (R$%s).\n", x, p->person[i].name, p->person[i].debit);
			printf("\n");
			
		}
	}
	
	if (x == 0)
	{
		printf("!!!That renter is not in the database!!!");
	}
}

void displayEven (Condominium * p)
{
	int i;
	int x = 0;
	int y = 0;
	int result;
	
	printf("---------------- RENTERS PAID IN FULL ----------------\n\n");
	
	pullFile(p);
	
	for (i = 0; i < p->numRegis - 1; i++)
	{
		result = strcmp(p->person[i].debit, "0");
		
		x++;
		
		if (result == 0)
		{	
		
			printf("%d- %s.\n", x, p->person[i].name);
			printf("\n");
			
		}
	}
	
	if (x == 0)
	{
		printf("!!!That renter is not in the database.!!!");
	}
	
}

void removeRes(Condominium * p)
{
	
	char code[10];
	char buffer[10];
	int i, j;
	int x = 0;
	char c;
	BOOL isContinuing = TRUE;
	
	while(isContinuing)
	{	
		printf("Enter code to remove resident:\n");
		fflush(stdin);
		fgets(buffer, 9, stdin);
		sscanf(buffer, "%[^\n]s", &code);
		
		pullFile(p);
	
		for (i = 0; i < p->numRegis - 1; i++)
		{
			if (strcmp(code, p->person[i].code) == 0)
			{
				x++;
				
				strcpy(p->person[i].code, p->remove[i].code);
				strcpy(p->person[i].id, p->remove[i].id);
				strcpy(p->person[i].name, p->remove[i].name);
				strcpy(p->person[i].apartment, p->remove[i].apartment);
				strcpy(p->person[i].debit, p->remove[i].debit);
				
				updateFile(p);
				
				printf("!!!Resident sucessfully removed!!!\n\n");
				
				printf("Do you want to remove another resident?\n(Y/N): ");
				c = getchar();
				
				if(c == 'N' || c == 'n' )
				{
					isContinuing = FALSE;
				}
				
				else if (c == 'Y' || c == 'y')
				{
					continue;
				}
				
				else
				{
					printf("!!!Invalid input!!!");
					getchar();
				}
				
			}
		}	
		
		if(x = 0)
		{
			printf("\n!!!This code doens't exist!!!\n");
			printf("Try again!\n\n");
		}	
	}
}

void updateFile(Condominium * p)
{
	int i;
	
	file = fopen("documento.txt", "w");
	
	for(i = 0; i < p->numRegis - 1; i++)
	{
		if(p->person[i].code)
		{
			fprintf(file, "Code:%s\n", p->person[i].code);
			fprintf(file, "ID:%s\n", p->person[i].id);
			fprintf(file, "Name:%s\n", p->person[i].name);
			fprintf(file, "Ap.:%s\n", p->person[i].apartment);
			fprintf(file, "Debit:%s\n", p->person[i].debit);

			number = fopen("qnt.txt", "w");
				
			fseek(number, 0, SEEK_SET);
			fprintf(number,"%d", p->numRegis - 1);	

			fclose(number);					
		}
	}

	pullFile(p);
		
	fclose(file);
	
}

void extractString(char line[], char extractedString[])
{
    int i = 0;
    int j = 0;
    char c;
    int state = 0;
    BOOL isProcessing = TRUE;
    while (isProcessing)
    {
        switch (state)
        {
            // In this state we are reading the line until we get to the colon.  When we get to the colon
            // we change to state 1.
            case 0: 
                if (line[i] == ':')
                {
                    state = 1;
                }
                break;
            // In this state we are reading each character and putting it into the extractedString array.
            // When we get to the newline character, we will change to state 2.
            case 1:
                if (line[i] != '\n')
                {
                    extractedString[j] = line[i];
                    j++;
                }
                else
                {
                    state = 2;
                }
                break;
            // In this state we are appending the null character to cap off the string and then setting
            // the bool to exit the isProcessing loop.
            case 2:
                extractedString[j] = '\0';
                isProcessing = FALSE;
                break;
        }
        i++;
    }
}

void dumpToConsole(Condominium * p, int numPerson)
{
	int i;
	
    for (i = 0; i < numPerson - 1; i++)
    {
		printf("------------------------------");
    	printf("Code: %s\n", p->person[i].code);
        printf("ID: %s\n", p->person[i].id);
        printf("Name: %s\n", p->person[i].name);
        printf("Apartment: %s\n", p->person[i].apartment);
        printf("Debit: %s\n\n", p ->person[i].debit);
		printf("------------------------------");
    }
}
