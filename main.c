#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define maxrow 500
#define maxcol 500
#define MAX_TRANSACTIONS 5
#define MAX_TRANSACTION_LINE_LENGTH 100
typedef struct
{
    char transactionDetails[MAX_TRANSACTION_LINE_LENGTH];
} Transaction;

typedef struct
{
    char username[50];
    char password[50];
} users;

typedef struct
{
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
Accounts acc[200]; // to store accounts // size are extendable
int NumberOfAccounts = 0;
Transaction transactions[MAX_TRANSACTIONS]; // to load existing transactions into an array
int login(char *username, char *password)   // A function to check whether the user is correct or not
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) // handling if the file is not found
    {
        printf("Error opening file.\n");
        return 0;
    }

    users stored;
    int isValid = 0;

    // Read and validate user details
    // fscanf successfully reads and assigns values to both variables, it returns 2,
    // indicating that it matched two items

    while (fscanf(file, "%s %s", stored.username, stored.password) == 2)
    {
        if (strcmp(username, stored.username) == 0 && strcmp(password, stored.password) == 0)
        {
            isValid = 1; // means it is correct user
            break;
        }
    }
    fclose(file);
    return isValid;
}

void print_accounts(Accounts acc) // A function to print one account details
{
    if (acc.name == NULL)
    {
        printf("Account doesn't exist!");
    }
    else
    {
        printf("Account Number:%s\nName:%s\nEmail:%s\nBalance:%.2f\nMobile Number:%s\nDate Opened:%s-%s\n",
               acc.accountnum, acc.name, acc.mail, acc.balance, acc.mobilenum,
               acc.dateOpened.month, acc.dateOpened.year);
    }
}

void load(char temp[][maxcol], Accounts *account) // loading data and store it in the array structure acc
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
    token = strtok(NULL, "-");
    strcpy(account->dateOpened.month, token);
    token = strtok(NULL, "\n");
    strcpy(account->dateOpened.year, token);
}
void todayDate(date *daydate) // function to get date of the day from the machine
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    // sprintf converts int to char value in a struct
    sprintf(daydate->month, "%0.2d", tm->tm_mon + 1);
    sprintf(daydate->year, "%0.4d", tm->tm_year + 1900);
    // values 1&1900 are added by nature in the function
}
int check_chars(char name[], int j) // to check the whether the entered names are correct or not
{
    int flag = 1;
    for (int i = 0; i < j; i++)
    {
        if (!((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || name[i] == 32))
            flag = 0;
    }
    if (!flag)
        printf("Please enter valid name.");
    return flag;
}
int check_numbers(char number[], int j) // to check the whether the entered account\mobile numbers are correct or not
{
    int flag = 1;
    for (int i = 0; i < j; i++)
    {
        if (!(number[i] >= 48 && number[i] <= 57))
            flag = 0;
    }
    if (number[j] != '\0')
        flag = 0;
    if (!flag)
        printf("Please enter %d digits number.", j);
    return flag;
}
int check_mail(char mail[]) // to check whether the entered email is correct or not
{
    int flag = 1;
    int k = 0, i = 0;
    char temp1[10] = "@gmail.com";
    char temp2[13] = "@outlook.com";
    char temp3[10] = "@yahoo.com";
    char temp4[12] = "@hotmail.com";

    for (i = 0; mail[i] != '@'; i++) // stops before @
    {
        if (!((mail[i] >= 97 && mail[i] <= 122) || mail[i] == '.' || mail[i] == '_' || (mail[i] >= 48 && mail[i] <= 57)))
        {
            flag = 0;
        }
    }

    if (mail[i] == '\0') // Check if '@' is not found or email is too long or too short
    {
        flag = 0;
    }

    // checks for fixed format (only check the domain part)
    char *domain = mail + i; // points to the domain part of the email

    while (k < 13 && domain[k] != '\0')
    {
        if (domain[k] != temp1[k] && domain[k] != temp2[k] && domain[k] != temp3[k] && domain[k] != temp4[k])
        {
            flag = 0;
            break;
        }
        k++;
    }

    if (!flag)
    {
        printf("Please enter email in the format of \"small alphabetic letters@domain.com\"\n");
    }

    return flag;
}

// Function to search for an account
int querysearch(char *accountNumber, Accounts *found)
{
    // Find the account with the given account number
    for (int i = 0; i < NumberOfAccounts; i++)
    {
        if (strcmp(acc[i].accountnum, accountNumber) == 0)
        {
            // Copy the found account details
            *found = acc[i];
            return 1; // Account found
        }
    }
    return 0; // Account not found
}
void advancedSearch(char *keyword)
{
    printf("\n");
    printf("Search results:\n");
    int k;
    char lowercasekey[50];
    for (k = 0; keyword[k] != '\0'; ++k)
    {
        lowercasekey[k] = tolower(keyword[k]);
    }
    lowercasekey[k] = '\0'; // add null at the end

    int i = 0;
    int count = 0;
    while (i < NumberOfAccounts)
    {
        char lowercaseName[50];
        int j = 0;
        while (acc[i].name[j] != '\0')
        {
            lowercaseName[j] = tolower(acc[i].name[j]); // devide the name into letters //array of chars
            j++;
        }
        lowercaseName[j] = '\0'; // add null at the end

        if (strstr(lowercaseName, lowercasekey) != NULL)
        {
            print_accounts(acc[i]); // strstr finds the first occurrence of a string within another string
            count++;
        }
        i++;
    }
    if (!count)
        printf("No search results.\n");
    exit_program();
}

int accountsearch(char *accountNumber, int *found)
{
    // Find the account with the given account number
    // different from querysearch that this function stores the index in order to modify the balance
    for (int i = 0; i < NumberOfAccounts; i++)
    {
        if (strcmp(acc[i].accountnum, accountNumber) == 0)
        {
            *found = i; // saving the index
            return 1;   // Account found
        }
    }
    return 0; // Account not found
}

void deposit(char accountNumber[], char amount[])
{
    int stored;
    double depositamount;

    if (accountsearch(accountNumber, &stored) == 1)
    {
        sscanf(amount, "%lf", &depositamount);
        // to transform string into double
        if (depositamount >= 0 && depositamount <= 10000)
        {
            acc[stored].balance += depositamount;
            if (saveTransactions())
            {
                printf("Deposite is successful\n");
                Transaction newtrans[MAX_TRANSACTION_LINE_LENGTH];
                sprintf(newtrans, "Deposit + %.2lf\n", depositamount); // to convert double into string
                addTransaction(newtrans, &acc[stored].accountnum);     // to add transaction to file
            }
        }
        else
        {
            printf("The amount you entered can't be deposited !\nNotice that the maximum amount is 10000.\n");
            menu();
        }
    }
    else
    {
        printf("Account not found.\n");
    }
}

void withdraw(char accountNumber[], char amount[])
{
    int stored;
    double withdrawamount;

    if (accountsearch(accountNumber, &stored) == 1)
    {
        sscanf(amount, "%lf", &withdrawamount); // to transform string into double
        if (withdrawamount >= 0 && withdrawamount <= 10000)
        {
            if (acc[stored].balance >= withdrawamount)
            {
                acc[stored].balance -= withdrawamount;

                if (saveTransactions())
                {
                    printf("Withdraw is successful!");
                    Transaction newtrans[MAX_TRANSACTION_LINE_LENGTH];
                    sprintf(newtrans, "Withdraw - %.2lf\n", withdrawamount); // to convert double into string
                    addTransaction(newtrans, &acc[stored].accountnum);       // to add transaction to file
                }
            }
            else
            {
                printf("Insufficient balance for withdrawal.\n");
            }
        }
        else
        {
            printf("The amount you entered can't be withdraw!\nNotice that the maximum amount is 10000.\n");
            menu();
        }
    }
    else
    {
        printf("Account not found.\n");
    }
}

void transfer(char *fromAccountNumber, char *toAccountNumber, char amount[])
{
    int fromAccount, toAccount;
    double transferamount;

    // searches for the accounts entered by the user and stores its information in fromAccount
    if (accountsearch(fromAccountNumber, &fromAccount) == 1 &&
        accountsearch(toAccountNumber, &toAccount) == 1 && strcmp(fromAccountNumber, toAccountNumber) != 0)
    {
        sscanf(amount, "%lf", &transferamount); // to transform string into double

        if (acc[fromAccount].balance >= transferamount)
        {
            acc[fromAccount].balance -= transferamount;
            acc[toAccount].balance += transferamount;

            if (saveTransactions())
            {
                printf("Transfer completed successfully\n");
                printf("From Account: %s\n", acc[fromAccount].accountnum);
                printf("To Account: %s\n", acc[toAccount].accountnum);
                Transaction newtrans1[MAX_TRANSACTION_LINE_LENGTH];
                sprintf(newtrans1, "transfer - %.2lf\n", transferamount); // to convert double into string
                addTransaction(newtrans1, &acc[fromAccount].accountnum);  // to add transaction to file to the account transfered from
                Transaction newtrans2[MAX_TRANSACTION_LINE_LENGTH];
                sprintf(newtrans2, "transfer + %.2lf\n", transferamount); // to convert double into string
                addTransaction(newtrans2, &acc[toAccount].accountnum);    // to add transaction to file to the account transfered to
            }
        }
        else
        {
            printf("Insufficient balance for transfer.\n");
        }
    }
    else
    {
        printf("One or both accounts not found.\n");
    }
}
void modifyAccount(Accounts arraccounts[], int numofaccounts)
{
    char numaccountmod[11];
    int found = 0, i;

    do
    {
        printf("Enter account number to modify:");
        gets(numaccountmod);

        for (i = 0; i < numofaccounts; ++i)
        {
            if (strcmp(arraccounts[i].accountnum, numaccountmod) == 0)
            {
                found = 1;
                break;
            }
        }
    } while (!check_numbers(numaccountmod, 10));
    if (found)
    {
        char field[5];
        do
        {
            printf("1-Name.\n");
            printf("2-Email address.\n");
            printf("3-Mobile Number.\n");
            printf("4-Nothing.\n");
            printf("Please Enter the number of the field you want to modify:");
            gets(field);
            if (strcmp(field, "1") == 0)
            {
                do
                {
                    printf("Enter your new name:");
                    gets(arraccounts[i].name); // read until new line
                } while (!check_chars(arraccounts[i].name, strlen(arraccounts[i].name)));
            }
            else if (strcmp(field, "2") == 0)
            {
                do
                {
                    printf("Enter your new email:");
                    gets(arraccounts[i].mail);
                } while (!check_mail(arraccounts[i].mail));
            }
            else if (strcmp(field, "3") == 0)
            {
                do
                {
                    printf("Enter mobile number:");
                    gets(arraccounts[i].mobilenum);

                } while (!check_numbers(arraccounts[i].mobilenum, 11));
            }
            else if (strcmp(field, "4") == 0)
            {
                printf("Nothing modified.\n");
            }
            else
            {
                printf("Invalid choice , Please try again.\n");
            }
        } while (strcmp(field, "4") != 0);
        printf("Account modified successfully.\n");
        save();
    }
    else
        printf("Account does not exist.");
}
void deleteAccount(Accounts arraccounts[], int *numofaccounts)
{
    char numaccountdel[20];
    int found = 0, i, j;

    do
    {
        printf("Enter account number to delete: ");
        gets(numaccountdel);

        for (i = 0; i < *numofaccounts; i++)
        {
            if (strcmp(arraccounts[i].accountnum, numaccountdel) == 0)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            if (arraccounts[i].balance == 0.0)
            {
                for (j = i; j < *numofaccounts - 1; j++)
                {
                    arraccounts[j] = arraccounts[j + 1];
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
            deleteAccount(acc, &NumberOfAccounts);
        }
    } while (!check_numbers(numaccountdel, 10));

    save();
}
void add() // A function to add new acount
{
    Accounts found;

    Accounts newaccount; // struct for the new account
    // do while method to get all members of struct while checking using above functions
    do
    {
        printf("Enter account number:");
        gets(newaccount.accountnum);
        if (querysearch(newaccount.accountnum, &found))
            printf("Repeated account number , Please try again.\n");
    } while (querysearch(newaccount.accountnum, &found) || !check_numbers(newaccount.accountnum, 10));

    do
    {
        printf("Enter name:");
        gets(newaccount.name);
    } while (!check_chars(newaccount.name, strcspn(newaccount.name, "\n")));

    do
    {
        printf("Enter mobile number:");
        gets(newaccount.mobilenum);
    } while (!check_numbers(newaccount.mobilenum, 11) ||
             (newaccount.mobilenum[0] != '0' ||
              newaccount.mobilenum[1] != '1' ||
              (newaccount.mobilenum[2] != '1' && newaccount.mobilenum[2] != '2' && newaccount.mobilenum[2] != '0')));

    do
    {
        printf("Enter email:");
        gets(newaccount.mail); // Limit the length to MAX_EMAIL_LENGTH - 1
    } while (!check_mail(newaccount.mail));

    todayDate(&newaccount.dateOpened); // to assign the day
    newaccount.balance = 0;            // account starts by 0.0 balance
    NumberOfAccounts++;

    acc[NumberOfAccounts - 1] = newaccount;
    // prints the new account in the array
    printf("Account added successfully.\n"); // confirmation of the process success
    save();                                  // to check for saving
}
void name_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i < NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts - i - 1; j++)
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
        print_accounts(acc[i]);
        printf("\n\n");
    }
}
void date_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i < NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts - i - 1; j++)
        {
            if (strcmp(acc[j].dateOpened.year, acc[j + 1].dateOpened.year) == 1)
            {
                // Swap accounts
                temp = acc[j];
                acc[j] = acc[j + 1];
                acc[j + 1] = temp;
            }
            else if (strcmp(acc[j].dateOpened.year, acc[j + 1].dateOpened.year) == 0)
            {
                if (strcmp(acc[j].dateOpened.month, acc[j + 1].dateOpened.month) == 1)
                {
                    temp = acc[j];
                    acc[j] = acc[j + 1];
                    acc[j + 1] = temp;
                }
            }
        }
    }
    for (int k = 0; k < NumberOfAccounts; k++)
    {
        print_accounts(acc[k]);
        printf("\n\n");
    }
}

void balance_bubbleSort()
{
    int i, j;
    Accounts temp;

    for (i = 0; i < NumberOfAccounts; i++)
    {
        for (j = 0; j < NumberOfAccounts - i - 1; j++)
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
        print_accounts(acc[i]);
        printf("\n\n");
    }
}
void addTransaction(Transaction newTransaction, char accountnum[])
{
    char filename[15]; // 10 for the acc num +4 for .txt +1 for null char
    sprintf(filename, "%s.txt", accountnum);
    FILE *file = fopen(filename, "a+");

    int transactionCount = 0;

    while (fgets(transactions[transactionCount].transactionDetails, sizeof(transactions[transactionCount].transactionDetails), file) != NULL)
    // count the number of transactions in the file by counting the lines
    {
        transactionCount++;
    }

    // Append the new transaction to the file
    fprintf(file, "%s", newTransaction);

    fclose(file);
    if (transactionCount < MAX_TRANSACTIONS) // update the array of transactions, keeping only the last 5
    {
        strcpy(transactions[transactionCount].transactionDetails, newTransaction.transactionDetails);
    }
    else
    {
        FILE *file = fopen(filename, "w");

        for (int j = 0; j < MAX_TRANSACTIONS - 1; j++)
        {
            strcpy(transactions[j].transactionDetails, transactions[j + 1].transactionDetails); // Shift existing transactions to keep last 5 only
            fprintf(file, "%s", transactions[j].transactionDetails);                            // over write the file to keep only the last 5
        }

        strcpy(transactions[MAX_TRANSACTIONS - 1].transactionDetails, newTransaction.transactionDetails); // add the new transaction to the last position
        fprintf(file, "%s", transactions[MAX_TRANSACTIONS - 1].transactionDetails);
        fclose(file);
    }
}
void report()
{
    char accountnum[11];
    printf("Enter account number to print transaction of: \n");
    gets(accountnum);
    char filename[15]; // 10 for the acc num +4 for .txt +1 for null char
    sprintf(filename, "%s.txt", accountnum);
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("Error opening transactions file or no transaction found.\n");
        return;
    }

    int i = 0;

    while (fgets(transactions[i].transactionDetails, sizeof(transactions[i].transactionDetails), file) != NULL)
    {
        i++; // counting lines //lines represent number of transactions
    }

    printf("\nLast %d transactions:\n", i); // print last transactions
    for (int j = 0; j < i; j++)
    {
        printf("%s", transactions[i - j - 1].transactionDetails);
    }

    fclose(file);
}
int saveTransactions() // to save without exit in order to execute addTransation function
{
    printf("Do you want to save ? Enter the number of your choice\n1- YES\n2- NO\n");
    char choice[5];
    do
    {
        scanf("%s", choice);
        if (strcmp(choice, "1") == 0)
        {
            FILE *ptr = fopen("accounts.txt", "w");
            for (int i = 0; i < NumberOfAccounts; i++)
            {
                fprintf(ptr, "%s,", acc[i].accountnum);
                fprintf(ptr, "%s,", acc[i].name);
                fprintf(ptr, "%s,", acc[i].mail);
                fprintf(ptr, "%.2lf,", acc[i].balance);
                fprintf(ptr, "%s,", acc[i].mobilenum);
                fprintf(ptr, "%s-", acc[i].dateOpened.month);
                fprintf(ptr, "%s\n", acc[i].dateOpened.year);
            }
            printf("Changes have been successfully saved.\n");
            fclose(ptr);
            return 1;
        }
        else if (strcmp(choice, "2") == 0)
        {
            return 0;
        }

        else
        {
            printf("Sorry I don't understand your choice please enter a valid choice: \n");
        }
    } while ((strcmp(choice, "1") != 0) || (strcmp(choice, "2") != 0));
}
void save()
{
    char choice[5];
    do
    {
        printf("Do you want to save ? Enter the number of your choice\n1- YES\n2- NO\n");
        gets(choice);
        if (strcmp(choice, "1") == 0)
        {
            FILE *ptr = fopen("accounts.txt", "w");
            for (int i = 0; i < NumberOfAccounts; i++)
            {
                fprintf(ptr, "%s,", acc[i].accountnum);
                fprintf(ptr, "%s,", acc[i].name);
                fprintf(ptr, "%s,", acc[i].mail);
                fprintf(ptr, "%.2lf,", acc[i].balance);
                fprintf(ptr, "%s,", acc[i].mobilenum);
                fprintf(ptr, "%s-", acc[i].dateOpened.month);
                fprintf(ptr, "%s\n", acc[i].dateOpened.year);
            }
            printf("Changes has been successfully saved.\n");
            fclose(ptr);
            exit_program();
        }
        else if (strcmp(choice, "2") == 0)
        {
            NumberOfAccounts--;
            exit_program();
        }

        else
        {
            printf("Please enter a valid choice: \n");
        }
    } while ((strcmp(choice, "1") != 0) && (strcmp(choice, "2") != 0) && !check_numbers(choice, "1"));
}
// A function to be called in other functions to exit program
void exit_program()
{
    char choice[5];
    do
    {
        printf("Do you want to exit? Enter the number of your choice.\n1-YES\n2-NO\n");
        scanf("%s", choice);
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
        else
            ("Sorry I don't understand your choice please enter a valid choice: \n");
    } while ((strcmp(choice, "1") != 0) || (strcmp(choice, "2") != 0));
}
void exit_before_login()
{
    char choice[5];
    do
    {
        printf("Do you want to exit? Enter the number of your choice.\n1-YES\n2-NO\n");
        scanf("%s", choice);
        getchar();
        if (strcmp(choice, "1") == 0)
        {
            printf("Exiting program.\n");
            exit(0);
        }
        else if (strcmp(choice, "2") == 0)
        {
            main();
            break;
        }
        else
            ("Sorry I don't understand your choice please enter a valid choice: \n");
    } while ((strcmp(choice, "1") != 0) || (strcmp(choice, "2") != 0));
}
int checkbalance(char amount[])
{
    int flag = 1;
    int pointCount = 0;
    for (int i = 0; amount[i] != '\0'; i++)
    {
        if (!(amount[i] >= 48 && amount[i] <= 57) && amount[i] != 46) // the point for the double amount
        {
            flag = 0;
        }
        if (amount[i] == '.')
        {
            pointCount++;
        }
    }

    if (pointCount > 1)
    {
        flag = 0;
    }
    if (!flag)
        printf("Enter valid amount.\n");
    return flag;
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
        if (strcmp(choice, "1") == 0)
        {
            add();
        }
        else if (strcmp(choice, "2") == 0)
        {
            deleteAccount(acc, &NumberOfAccounts);
        }
        else if (strcmp(choice, "3") == 0)
        {
            modifyAccount(acc, NumberOfAccounts);
        }
        else if (strcmp(choice, "4") == 0)

        {
            char numsearch[11]; // a string just to scan account number
            do
            {
                printf("Enter account number :\n");
                gets(numsearch);
            } while (check_numbers(numsearch, 10) == 0);
            Accounts store;
            if (querysearch(numsearch, &store))
            {

                do
                {
                    printf("Account found  ! Do you want to print account datails ?\n1- YES \n2- NO\n");
                    char yesOrNo[5]; // variable to help to choose
                    gets(yesOrNo);
                    if (strcmp(yesOrNo, "1") == 0)
                    {
                        print_accounts(store);
                        exit_program();
                        break;
                    }
                    else if (strcmp(yesOrNo, "2") == 0)
                        exit_program();
                    else
                        printf("Your entry is not valid!\n");
                } while (1);
            }
            else
            {
                printf("Account is not found !\n");
                exit_program();
            }
        }
        else if (strcmp(choice, "5") == 0)
        {
            char keyword[50];
            printf("Enter search keyword :\n");
            scanf("%s", keyword);
            getchar();
            advancedSearch(&keyword);
            exit_program();
        }
        else if (strcmp(choice, "6") == 0)
        {
            char accountnumber[11];
            char amount[10];
            do
            {
                printf("Enter account number: \n");
                gets(accountnumber);
            } while (!check_numbers(accountnumber, 10));
            do
            {
                printf("Enter withdraw amount: \n");
                gets(amount);
            } while (!checkbalance(amount));
            withdraw(accountnumber, amount); // pass accountnumber as a pointer to allow access all the data in that accountnumber
        }
        else if (strcmp(choice, "7") == 0)
        {
            char accountnumber[11];
            char amount[10];
            do
            {
                printf("Enter account number: ");
                gets(accountnumber);
            } while (!check_numbers(accountnumber, 10));
            do
            {
                printf("Enter deposit amount: ");
                gets(amount);
            } while (!checkbalance(amount));
            deposit(accountnumber, amount); // pass accountnumber as a pointer to allow access all the data in that accountnumber
        }
        else if (strcmp(choice, "8") == 0)
        {
            char fromAccount[11];
            char toAccount[11];
            char amount[10];
            do
            {
                printf("Enter the account number to transfer from: ");
                gets(fromAccount);
            } while (!check_numbers(fromAccount, 10));
            do
            {
                printf("Enter the account number to transfer to: ");
                gets(toAccount);
            } while (!check_numbers(toAccount, 10));
            do
            {
                printf("Enter the amount to transfer: ");
                gets(amount);
            } while (!checkbalance(amount));

            transfer(&fromAccount, &toAccount, amount); // pass accountnumber as a pointer to allow access all the data in that accountnumber
        }
        else if (strcmp(choice, "9") == 0)
        {
            report();
        }
        else if (strcmp(choice, "10") == 0)
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
                if (strcmp(n, "1") == 0)
                {
                    name_bubbleSort();
                }
                else if (strcmp(n, "2") == 0)
                {
                    date_bubbleSort();
                }
                else if (strcmp(n, "3") == 0)
                {
                    balance_bubbleSort();
                }
                else if (strcmp(n, "4") == 0)
                {
                    for (int i = 0; i < NumberOfAccounts; i++)
                    {
                        print_accounts(acc[i]);
                    }
                }

                else
                {
                    printf("Invalid choice! Please try again.\n");
                }
            } while (!(strcmp(n, "1") == 0 || strcmp(n, "2") == 0 || strcmp(n, "3") == 0 || strcmp(n, "4") == 0));
        }
        else if (strcmp(choice, "11") == 0)
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
    char choice[5];
    do
    {
        printf("Bank Management System\n1- LOGIN \n2- QUIT\nPlease enter the number of your choice.\n");
        gets(choice);
        if (strcmp(choice, "1") == 0)
        {
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
            } while (1); // Loop until valid login
            char temp[maxrow][maxcol]; // temporary array to avoid editing in the file and\or the acc array
            int i = 0;
            FILE *ptr = fopen("accounts.txt", "r");

            if (!ptr) // handling if the file is not found
            {
                printf("File can't be reached!");
                return 1;
            }
            else
            {
                while (fgets(temp[i], maxcol, ptr)) // reads each line and load it separately
                {
                    load(temp[i], &acc[i]);
                    NumberOfAccounts++;
                    i++;
                }
                printf("Data has been successfully uploaded to the system.\nNumber of accounts =%d\n", i + 1);
                // indicating to success and shows the user number of accounts
            }

            fclose(ptr);
            menu();
        }
        else if (strcmp(choice, "2") == 0)
            exit_before_login();
        else
            printf("Sorry Your choice is invalid!");
    } while (strcmp(choice, "2") != 0 || strcmp(choice, "1") != 0);
    return 0;
}
