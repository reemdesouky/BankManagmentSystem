#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include<time.h>
#define maxrow 500
#define maxcol 500
typedef struct
{
    char username[50];
    char password[50];
} users;

typedef struct
{
    char day[3];
    char month[3];
    char year[6];
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
Accounts acc[200];
int NumberOfAccounts =0;
int login(char *username, char *password) // A function to check whether the user is correct or not
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) //handling if the file is not found
    {
        printf("Error opening file.\n");
        return 0;
    }

    users stored;
    int isValid = 0;

    // Read and validate user details
    //fscanf successfully reads and assigns values to both variables, it returns 2,
    //indicating that it matched two items

    while (fscanf(file, "%s %s", stored.username, stored.password) == 2)
    {
        if (strcmp(username, stored.username) == 0 && strcmp(password, stored.password) == 0)
        {
            isValid = 1;  //means it is correct user
            break;
        }
    }
    fclose(file);
    return isValid;
}


void print_accounts(Accounts acc) //A function to print one account details
{
    if (acc.name==NULL)
    {
        printf("Account doesn't exist!");
    }
    else
    {
        printf("Account Number=%s\nName=%s\nEmail=%s\nBalance=%.2f\nMobile Number=%s\nDate Opened=%s/%s/%s\n",
               acc.accountnum, acc.name, acc.mail, acc.balance, acc.mobilenum, acc.dateOpened.day,
               acc.dateOpened.month, acc.dateOpened.year);
    }
}

void load(char temp[][maxcol], Accounts *account) //loading data and store it in the array structure acc
{
    char *token = strtok(temp, ",");
    strcpy(account->accountnum, token);
    token = strtok(NULL, ",");
    strcpy(account->name, token);
    token = strtok(NULL, ",");
    strcpy(account->mail, token);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &account->balance);
    token = strtok(NULL, ",");
    strcpy(account->mobilenum, token);
    token = strtok(NULL, "/");
    strcpy(account->dateOpened.day, token);
    token = strtok(NULL, "/");
    strcpy(account->dateOpened.month, token);
    token = strtok(NULL, "/");
    strcpy(account->dateOpened.year, token);
}
void todayDate(date *daydate) //function to get date of the day from the machine
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(daydate->day, "%0.2d", tm->tm_mday); //sprintf converts int to char value in a struct
    sprintf(daydate->month, "%0.2d", tm->tm_mon + 1);
    sprintf(daydate->year, "%0.4d", tm->tm_year + 1900);
    //values 1&1900 are added by nature in the function
}
int check_chars(char name[],int j) // to check the whether the entered names are correct or not
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
int check_numbers(char number[],int j) // to check the whether the entered account\mobile numbers are correct or not
{
    int flag=1;
    for (int i=0; i<j; i++)
    {
        if(!(number[i]>=48&&number[i]<=57))
            flag=0;
    }
    if (number[j]!='\0')
        flag=0;
    if (!flag) printf("Please enter %d digits number.",j);
    return flag;
}
int check_mail(char mail[]) // to check the whether the entered email are correct or not
{
    int flag=1;
    int k=0,i=0;
    char temp[10]="@gmail.com";

    for (i; mail[i]!='@'; i++) //stops before @
    {
        if (!((mail[i]>=97&&mail[i]<=122)||mail[i]=='.'||mail[i]=='_'||(mail[i]>=48&&mail[i]<=57)))
        {
            flag=0;
        }
    }

    if (mail[i]=='\0'||k==10)
    {
        flag=0; // Handle the case when '@' is not found or email is too long
    }

    for (; k<10&&mail[i]!='\0'; i++,k++) //checks for fixed format
    {
        if (mail[i]!=temp[k])
        {
            flag=0;
        }
    }

    if (!flag)
    {
        printf("Please enter email in the format of \"small alphabetic letters@gmail.com\"\n");
    }

    return flag;
}

// Function to search for an account
int querysearch(char *accountNumber, Accounts *found)
{
    // Find the account with the given account number
    for(int i=0; i<NumberOfAccounts; i++)
    {
        if (strcmp(acc[i].accountnum, accountNumber) == 0)
        {
            // Copy the found account details
            *found = acc[i];
            return 1;  // Account found
        }
    }
    return 0;  // Account not found
}
/*void advancedSearch(char *keyword) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("ERROR.\n");
        return;
    }

    Accounts stored;

    printf("\n");
    printf("Search results:\n");

    while (fscanf(file, " %19[^,], %49[^,], %49[^,], %f, %14[^,], %19[^\n]",
                  stored.accountnum, stored.name, stored.mail,
                  &stored.balance, stored.mobilenum, stored.dateOpened) == 6) {

        if (strstr(stored.name, keyword) != NULL) {
            print_accounts(stored);  //question of how mechanism
        }
    }

    fclose(file);
    exit_program();
}
*/
void modifyAccount(Accounts arraccounts[], int numofaccounts)
{
    char numaccountmod[11];
    int found=0,i;

    do
    {
        printf("Enter account number to modify:");
        scanf("%s",numaccountmod);

        for (i=0; i<numofaccounts; ++i)
        {
            if (strcmp(arraccounts[i].accountnum,numaccountmod)==0)
            {
                found=1;
                break;
            }
        }
    }
    while (!check_numbers(numaccountmod,10));
    if(found)
    {
        char field[5];
        do
        {
            printf("1-Name.\n");
            printf("2-Email address.\n");
            printf("3-Mobile Number.\n");
            printf("4-Nothing.\n");
            printf("Please Enter the number of the field you want to modify:");
            getchar();
            scanf("%s",field);
            if (strcmp(field,"1")==0)
            {
                do
                {
                    printf("Enter your new name:");
                    getchar();
                    scanf("%[^\n]", arraccounts[i].name); //read until new line
                }
                while(!check_chars(arraccounts[i].name,strlen(arraccounts[i].name)));

            }
            else if (strcmp(field,"2")==0)
            {
                do
                {
                    printf("Enter your new email:");
                    getchar();
                    scanf("%[^\n]", arraccounts[i].mail);
                }
                while (!check_mail(arraccounts[i].mail));

            }
            else if (strcmp(field,"3")==0)
            {
                do
                {
                    printf("Enter mobile number:");
                    getchar();
                    scanf("%12s",arraccounts[i].mobilenum);
                }
                while (!check_numbers(arraccounts[i].mobilenum, 11));

            }
            else if (strcmp(field,"4")==0)
            {
                printf("Nothing modified.\n");

            }
            else
            {
                printf("Invalid choice , Please try again.\n");

            }
        }
        while(strcmp(field,"4")!=0);
        printf("Account modified successfully.\n");
        save();
    }
    else
        printf("Account does not exist.");

}
void deleteAccount(Accounts arraccounts[], int* numofaccounts)
{
    char numaccountdel[20];
    int found = 0, i, j;

    do
    {
        printf("Enter account number to delete: ");
        scanf("%s", numaccountdel);

        for (i = 0; i < *numofaccounts; i++)
        {
            if (strcmp(arraccounts[i].accountnum, numaccountdel)==0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            if (arraccounts[i].balance==0.0)
            {
                for (j=i; j <*numofaccounts-1; j++)
                {
                    arraccounts[j]=arraccounts[j + 1];
                }
                (*numofaccounts)--;
                printf("Account deleted successfully.\n");
            }
            else
            {
                printf("Cannot delete accounts with non-zero balance.\n");
            }
        }
        else
        {
            printf("Account does not exist or written wrong please try again.\n");
        }
    }
    while (!check_numbers(numaccountdel,10));

    save();
}
void add() //A function to add new acount
{
    Accounts found;

    Accounts newaccount; //struct for the new account
    // do while method to get all members of struct while checking using above functions
    do
    {
        printf("Enter account number:");
        gets(newaccount.accountnum);
        if (querysearch(newaccount.accountnum, &found))
            printf("Repeated account number , Please try again.\n");
    }
    while (querysearch(newaccount.accountnum,&found)||!check_numbers(newaccount.accountnum,10));

    do
    {
        printf("Enter name:");
        gets(newaccount.name);
    }
    while (!check_chars(newaccount.name,strcspn(newaccount.name, "\n")));

    do
    {
        printf("Enter mobile number:");
        gets(newaccount.mobilenum);
    }
    while (!check_numbers(newaccount.mobilenum, 11) ||
            (newaccount.mobilenum[0]!='0'||
             newaccount.mobilenum[1]!='1'||
             (newaccount.mobilenum[2]!='1'&&newaccount.mobilenum[2]!='2'&&newaccount.mobilenum[2]!='0')));

    do
    {
        printf("Enter email:");
        gets(newaccount.mail);  // Limit the length to MAX_EMAIL_LENGTH - 1
    }
    while (!check_mail(newaccount.mail));


    todayDate(&newaccount.dateOpened); //to assign the day
    newaccount.balance=0; //account starts by 0.0 balance
    NumberOfAccounts++;
    newaccount.dateOpened.year[strlen(newaccount.dateOpened.year)] = '\n';

    acc[NumberOfAccounts-1]=newaccount;
    //prints the new account in the array
    printf("Account added successfully.\n"); //confirmation of the process success
    save(); //to check for saving
}
void name_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i < NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts-i-1; j++)
        {
            if (strcmp(acc[j].name, acc[j + 1].name) > 0)
            {
                // Swap accounts
                temp = acc[j];
                acc[j] = acc[j + 1];
                acc[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < NumberOfAccounts; i++)
    {
        print_accounts( acc[i]);
    }

}
void date_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i < NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts-i-1; j++)
        {
            if (strcmp(acc[j].dateOpened.year,acc[j + 1].dateOpened.year)==1)
            {
                // Swap accounts
                temp = acc[j];
                acc[j] = acc[j + 1];
                acc[j + 1] = temp;
            }
            else if(strcmp(acc[j].dateOpened.year,acc[j + 1].dateOpened.year)==0)
            {
                if(strcmp(acc[j].dateOpened.month,acc[j + 1].dateOpened.month)==1)
                {
                    temp = acc[j];
                    acc[j] = acc[j + 1];
                    acc[j + 1] = temp;
                }
                else if(strcmp(acc[j].dateOpened.month,acc[j + 1].dateOpened.month)==0)
                {
                    if(strcmp(acc[j].dateOpened.day,acc[j + 1].dateOpened.day)==1)
                    {
                        temp = acc[j];
                        acc[j] = acc[j + 1];
                        acc[j + 1] = temp;
                    }
                }
            }
        }
    }
    for (int k = 0; k < NumberOfAccounts; k++)
    {
        print_accounts( acc[k]);
    }
}
void balance_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i <NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts-i-1; j++)
        {
            if (acc[j].balance > acc[j + 1].balance)
            {
                // Swap accounts
                temp = acc[j];
                acc[j] = acc[j + 1];
                acc[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < NumberOfAccounts; i++)
    {
        print_accounts( acc[i]);
    }
}
void save()
{
    printf("Do you want to save ? Enter the number of your choice\n1- YES\n2- NO\n");
    char choice[5];
    do
    {
        scanf("%s",choice);
        if (strcmp(choice, "1") == 0)
        {
            FILE *ptr=fopen("accounts.txt","w");
            for (int i=0 ; i<NumberOfAccounts; i++)
            {
                fprintf(ptr,"%s,",acc[i].accountnum);
                fprintf(ptr,"%s,",acc[i].name);
                fprintf(ptr,"%s,",acc[i].mail);
                fprintf(ptr,"%.2lf,",acc[i].balance);
                fprintf(ptr,"%s,",acc[i].mobilenum);
                fprintf(ptr,"%s/",acc[i].dateOpened.day);
                fprintf(ptr,"%s/",acc[i].dateOpened.month);
                fprintf(ptr,"%s",acc[i].dateOpened.year);

            }
            printf("Changes has been successfully saved.\n");
            do
            {
                exit_program();
            }
            while((strcmp(choice, "1") != 0)||(strcmp(choice, "2") != 0));
            fclose(ptr);

        }
        else if (strcmp(choice, "2") == 0)
        {
            exit_program();

        }

        else
        {
            ("Sorry I don't understand your choice please enter a valid choice: \n");
        }
    }
    while((strcmp(choice, "1") != 0)||(strcmp(choice, "2") != 0));
}
// A function to be called in other functions to exit program
void exit_program ()
{
    char choice[5];
    do
    {
        printf("Do you want to exit? Enter the number of your choice.\n1-YES\n2-NO\n");
        scanf("%s",choice);
        getchar();
        if (strcmp(choice, "1") == 0)
        {
            printf("Exiting program.\n");
            exit(0);
        }
        else if (strcmp(choice, "2") == 0)
        {
            menu();
            break;
        }
        else ("Sorry I don't understand your choice please enter a valid choice: \n");
    }
    while((strcmp(choice, "1") != 0)||(strcmp(choice, "2") != 0));

}

void menu()
{
    char choice[5];
    printf("\nWelcome! Please choose what you want to do\n");
    printf("1- ADD\n");
    printf("2- DELETE\n");
    printf("3- MODIFY\n");
    printf("4- SEARCH\n");
    printf("5- ADVANCED SEARCH\n");
    printf("6- WITHDRAW\n");
    printf("7- DEPOSIT\n");
    printf("8- TRANSFER\n");
    printf("9- REPORT\n");
    printf("10- PRINT\n");
    printf("11- QUIT\n");
    printf("Enter the number of your choice: ");
    scanf("%s", &choice);
    getchar();
    // Perform the selected action
    while (1)
    {
        if(strcmp(choice,"1")==0)
        {
            add();
        }
        else if(strcmp(choice,"2")==0)
        {
            deleteAccount(acc, &NumberOfAccounts);
        }
        else if(strcmp(choice,"3")==0)
        {
            modifyAccount(acc, NumberOfAccounts);
        }
        else if(strcmp(choice,"4")==0)

        {
            char numsearch[11]; //a string just to scan account number
            do
            {
                printf("Enter account number :\n");
                scanf("%s",numsearch);
                Accounts store;
                if (querysearch(numsearch,&store))
                {

                    do
                    {
                        printf("Account found  ! Do you want to print account datails ?\n1- YES \n2- NO\n");
                        char yesOrNo[5]; //variable to help to choose
                        scanf("%s",yesOrNo);
                        if(strcmp(yesOrNo,"1")==0)
                        {
                            print_accounts(store);
                            exit_program();
                            break;
                        }
                        else if(strcmp(yesOrNo,"2")==0) exit_program();
                        else printf("Your entry is not valid!\n");
                    }
                    while(1);
                }
                else
                {
                    printf("Account is not found!\n");
                    exit_program();
                    break;
                }
            }
            while(check_numbers(numsearch,10)==0);
        }
        else if(strcmp(choice,"5")==0)
        {
            /*char keyword[50];
            printf("Enter search keyword :\n");
            scanf("%s",keyword);
            getchar();
            advancedSearch(&keyword);
            exit_program();*/
        }
        else if(strcmp(choice,"10")==0)
        {
            char n[5];
            do
            {
                printf("Do you want to print all data sorted by name or balance or date ? ");
                printf("Enter number of sorting option: \n");
                printf("1- for sorting by name\n");
                printf("2- for sorting by date\n");
                printf("3- for sorting by balance\n");
                printf("4- not sorted\n");
                gets(n);
                if(strcmp(n,"1")==0)
                {
                    name_bubbleSort();
                }
                else if(strcmp(n,"2")==0)
                {
                    date_bubbleSort();
                }
                else if(strcmp(n,"3")==0)
                {
                    balance_bubbleSort();
                }
                else if(strcmp(n,"4")==0)
                {
                    for (int l=0 ; l<NumberOfAccounts ; l++)
                    {
                        print_accounts(acc[l]);
                    }
                }

                else
                {
                    printf("Invalid choice! Please try again.\n");
                }
            }
            while(!(strcmp(n,"1")==0||strcmp(n,"2")==0||strcmp(n,"3")==0||strcmp(n,"4")==0));
        }
        else if(strcmp(choice,"11")==0)
        {
            printf("Exiting program.");
            exit(0);
        }
        else
            printf("Invalid choice. Please enter a valid choice.\n");
        menu();
    }

}

int main()
{
    char entered_username[50];
    char entered_password[50];
    printf("Bank Management System\n");
    do
    {
        printf("Enter username:");
        scanf("%s", entered_username);
        printf("Enter password:");
        scanf("%s", entered_password);
        if (login(entered_username, entered_password))
        {
            printf("Data is uploading\n");
            break;
        }
        else
        {
            printf("Wrong, try again\n");
        }
    }
    while (1); // Loop until valid login
    char temp[maxrow][maxcol];  //temporary array to avoid editing in the file and\or the acc array
    int i=0;
    FILE *ptr = fopen("accounts.txt", "r");

    if (!ptr) //handling if the file is not found
    {
        printf("File can't be reached!");
        return 1;
    }
    else
    {
        while (fgets(temp[i], maxcol, ptr)) //reads each line and load it separately
        {
            load(temp[i], &acc[i]);
            NumberOfAccounts++;
            i++;
        }
        printf("Data has been successfully uploaded to the system.\nNumber of accounts =%d\n",i+1);
        //indicating to success and shows the user number of accounts
    }

    fclose(ptr);
    menu();
    return 0;
}
