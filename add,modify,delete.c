#include <stdio.h>
#include <string.h>
#include <time.h>
#define maxrow 500
#define maxcol 500

typedef struct
{
    char day[3];
    char month[3];
    char year[5];
} date;

typedef struct
{
    char accountnum[11];
    char name[100];
    char mail[50];
    char mobilenum[12];
    double balance;
    date dateOpened;
} Accounts;
void todayDate(date *daydate)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(daydate->day, "%02d", tm->tm_mday); //sprintf converts int to char value in a struct
    sprintf(daydate->month, "%02d", tm->tm_mon + 1);
    sprintf(daydate->year, "%04d", tm->tm_year + 1900);
}
int check_chars(char name[],int j)
{
    int flag=1;
    for (int i=0; i<j; i++)
    {
        if(!((name[i]>=65&&name[i]<=90)||(name[i]>=97 && name[i]<=122)||name[i]==32))
            flag=0;
    }
    if (!flag) printf("Please enter valid name.");
    return flag;
}
int check_numbers(char number[],int j)
{
    int flag=1;
    for (int i=0; i<j; i++)
    {
        if(!(number[i]>=48&&number[i]<=57))
            flag=0;
    }
    if (!flag) printf("Please enter %d digits number.",j);
    return flag;
}
int check_mail(char mail[])
{
    int flag=1;
    int k=0,i=0;
    char temp[10]="@gmail.com";

    for (i;mail[i]!='@';i++)
    {
        if (!((mail[i]>=65&&mail[i]<=90)||(mail[i]>=97&&mail[i]<=122)||mail[i]=='.'||mail[i]=='_'))
        {
            flag=0;
        }
    }

    if (mail[i]=='\0'||k==10)
    {
        flag=0; // Handle the case when '@' is not found or email is too long
    }

    for (;k<10&&mail[i]!='\0';i++,k++)
    {
        if (mail[i]!=temp[k])
        {
            flag=0;
        }
    }

    if (!flag)
    {
        printf("Please enter email in the format of \"alphabetic letters@gmail.com\"\n");
    }

    return flag;
}
// Function to search for an account
int querysearch(char *accountNumber, Accounts *found)
{
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    Accounts stored;

    // Find the account with the given account number
    while (fscanf(file, " %19[^,], %49[^,], %49[^,], %f, %14[^,], %19[^\n]",
                  stored.accountnum, stored.name, stored.mail,
                  &stored.balance, stored.mobilenum, stored.dateOpened) == 6)
    {

        if (strcmp(stored.accountnum, accountNumber) == 0)
        {
            // Copy the found account details
            *found = stored;
            fclose(file);
            return 1;  // Account found
        }
    }

    fclose(file);
    return 0;  // Account not found
}
void add(Accounts accounts[], int *numAccounts)
{
    FILE *f = fopen("accounts.txt", "a");
    Accounts found;

    if (f!=NULL)
    {
        Accounts newaccount;
        do
        {
            printf("Enter account number:");
            scanf("%s",newaccount.accountnum);

            if (querysearch(newaccount.accountnum, &found))
                printf("Repeated account number , Please try again.\n");
        }
        while (querysearch(newaccount.accountnum,&found)||!check_numbers(newaccount.accountnum,10));

        getchar(); // to handle newline left by scanf
        do
        {
            printf("Enter name:");
            fgets(newaccount.name, sizeof(newaccount.name), stdin);
            newaccount.name[strcspn(newaccount.name, "\n")] = '\0';
        }
        while (!check_chars(newaccount.name,strcspn(newaccount.name, "\n")));

        do
        {
            printf("Enter mobile number:");
            scanf("%12s", newaccount.mobilenum);
        }
        while (!check_numbers(newaccount.mobilenum,11));
        getchar();

        do
        {
            printf("Enter email:");
            scanf("%49s", newaccount.mail);  // Limit the length to MAX_EMAIL_LENGTH - 1
            while (getchar() != '\n');  // Consume any extra characters, including newline
        }
        while (!check_mail(newaccount.mail));


        todayDate(&newaccount.dateOpened);
        newaccount.balance=0;
        (*numAccounts)++;

        fprintf(f, "%s,%s,%s,%.2lf,%s,%s/%s/%s\n", newaccount.accountnum, newaccount.name, newaccount.mail,newaccount.balance,
                newaccount.mobilenum,newaccount.dateOpened.day,newaccount.dateOpened.month,newaccount.dateOpened.year);
        printf("Account added successfully.\n");
        fclose(f);
    }
    else
    {
        printf("File does not exist.\n");
    }
}
void deleteAccount(Accounts arraccounts[], int *numofaccounts)
{
    int targetaccount, found = 0, i;
    FILE *f = fopen("accounts.txt", "a");
    FILE *temp = fopen("temp.txt", "w");
    if (f==NULL || temp==NULL)
        printf("File does not exist.\n");
    else
    {
        printf("Enter the number of the account you want to delete: ");
        scanf("%d", &targetaccount);
        if (querysearch(&arraccounts->accountnum,&found))
        {
            found = 1;
            printf("Account found and deleted.\n");
        }
        else
        {
            printf("Account does not exist.\n");
        }

        for (i = 0; i < *numofaccounts; i++)
        {
            if (arraccounts[i].accountnum != targetaccount)
            {
                fprintf(temp, "%d %s %s %s %.2f\n", arraccounts[i].accountnum, arraccounts[i].name,
                        arraccounts[i].mobilenum, arraccounts[i].mail, arraccounts[i].balance);
            }
        }
    }
    fclose(f);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}
void modifyAccount(Accounts arraccounts[], int *numofaccounts)
{
    int targetaccount,found=0,i;
    FILE*f=fopen("accounts.txt","a");
    FILE *temp = fopen("temp.txt", "w");
    if(f==NULL || temp==NULL)
        printf("File does not exist.");

    printf("Enter number of the account you want to modify:");
    scanf("%s",targetaccount);
    for(i=0; i<*numofaccounts; i++)
    {
        if(arraccounts[i].accountnum==targetaccount)
        {
            found=1;
            break;
        }
        if(found)
        {
            int field;
            printf("Please choose the field you want to modify:\n");
            printf("1-Name.\n");
            printf("2-Mobile number.\n");
            printf("3-Email address.\n");
            scanf("%d",&field);

            switch(field)
            {
            case 1:
                printf("enter your new name:\n");
                scanf("%s",arraccounts[i].name);
                break;
            case 2:
                printf("enter your new email address:\n");
                scanf("%s",&arraccounts[i].mail);
                break;
            case 3:
                printf("enter your new mobile number:\n");
                scanf("%d",&arraccounts[i].mobilenum);
                break;
            default :
                printf("Invalid choice , Please try again.\n");
                break;
            }
            printf("Your account modified successfully.");

        }
        else
        {

            fprintf(temp,"%d %s %s %s %f\n",arraccounts[i].accountnum, arraccounts[i].name,
                    arraccounts[i].mobilenum, arraccounts[i].mail, arraccounts[i].balance);
        }
    }
    fclose(f);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}
int main()
{
    Accounts accounts[100];
    int numAccounts = 0;
    int choice;
    do
    {
        printf("\nBank Management System\n");
        printf("1- ADD\n");
        printf("2- DELETE\n");
        printf("3- MODIFY\n");
        printf("4- EXIT\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        // Perform the selected action
        switch (choice)
        {
        case 1:
            add(accounts, &numAccounts);
            break;
        case 2:
            deleteAccount(accounts, &numAccounts);
            break;
        case 3:
            modifyAccount(accounts, numAccounts);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid choice.\n");
        }

    }
    while (choice!= 4);
    return 0;
}
