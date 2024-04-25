This is a complete Bank Managment System project with all the needed features. there are a main function, a separated functions ,but they are also contained in the main, and the test files which are 'accounts.txt' and 'users.txt'. all you need to look at is 'main.c', the test files, and 'README.md' of course. More details about features, algorithms used, and a user manual are attached below:
1. Structures: 
Transaction Structure (Transaction): This structure is used to store transaction 
details. 
User Structure (users): It is used to store usernames and passwords. 
Date Structure (date): Represents the date with month and year. Accounts 
Structure (Accounts): Contains information about each bank account, including 
account number, name, e-mail, mobile number, balance, and date opened. 
2. Global Variables: 
acc[200]: An array of Accounts structures to store account information. The size 
is set to 200, indicating it can store information for up to 200 accounts and it’s 
extendable. 
NumberOfAccounts: An integer to identify the number of accounts. 
transactions[MAX_TRANSACTIONS]: An array of Transaction structures to store 
transaction details. 
3. Functions: 
login: Validates the user by checking the entered username and password with 
the stored values in the file "users.txt."  print_accounts: Prints details of a given 
account. 
load: Loads data from a temporary array into the Accounts structure.  
todayDate: Retrieves the current date and stores it in a date structure. 
check_chars, check_numbers, check_mail: Functions to check if characters, 
numbers, and email addresses are valid.  querysearch: Searches for an account 
using the account number.  advancedSearch: Searches for accounts based on a 
keyword in the name. 
accountsearch: Searches for an account and stores the index for modifications. 
deposit, withdraw, transfer: Functions to perform deposit, withdrawal, and 
transfer operations. 
modifyAccount, deleteAccount: Functions to modify and delete an account, 
respectively. 
add: Adds a new account. 
name_bubbleSort, date_bubbleSort, balance_bubbleSort: Sorting functions to 
sort accounts by name, date, and balance, respectively. 
addTransaction: Adds a new transaction to the file associated with an 
account.  report: Prints the last transactions for a given account.  
saveTransactions: Saves changes made in transactions to the file.  save: 
Saves account information to the file. 
exit_program: Asks the user if they want to exit and terminates the program if 
chosen. 
checkbalance: Checks if the entered amount of balance is valid.  menu: 
Displays the main menu . 
main: The main function that initiates the login process and calls the menu 
function. 
#include <stdio.h>: This line includes the standard input/output library in C, which 
is necessary for functions like printf and scanf. 
#include <string.h>: This line includes the string manipulation library, which 
provides functions for working with strings, such as strlen and strcpy. 
#include <time.h>: This line includes the time library, which is used for working 
with date and time-related functions, like time and ctime. 
#include <ctype.h>: This line includes the character handling library, providing 
functions for character-based operations, such as isalpha and toupper. 
#define maxrow 500: This line defines a constant named maxrow with a value of 
500. Constants defined using #define are replaced by the preprocessor before 
compilation. 
#define maxcol 500: This defines a constant named maxcol with a value of 500. 
#define MAX_TRANSACTIONS 5: Defines a constant named 
MAX_TRANSACTIONS with a value of 5. This likely indicates the maximum number 
of transactions that can be stored. 
#define MAX_TRANSACTION_LINE_LENGTH 100: Defines a constant named 
MAX_TRANSACTION_LINE_LENGTH with a value of 100. This likely represents the 
maximum length of a transaction line. 
Why did we use define? 
1.Readability: provides meaningful names to constants, improving code 
readability. 
2.Maintainability: Easy to update constant values. 
3.Consistency and Flexibility: Avoiding magic numbers improves code 
consistency, while easy modification of constants offers flexibility and 
portability. 
USER MANUAL FOR THE BANK MANAGEMENT SYSTEM 
USER MANUAL. 
1. Introduction  
2. Getting Started  
2. 1.Login  
3. Main Menu  
3.1. Add Account.  
3.2. Delete account. 3.3. Modify Account.  
3.4. Search.                                   
3.5. Advanced Search.  
3.6. Withdraw.  
3.7. Deposit.  
3.8. Transfer.  
3.9. Report.  
3.10. Print.  
3.11. QUIT.  
Here's a brief of what each function does: 
1. Introduction.  
This system allows bank employees to manage accounts efficiently. It includes 
programs such as adding accounts, searching for accounts, modifying data, etc… 2. 
Getting started.  
2. 1.login.  
To access the system, you need to log in with your username and password.  
Your username and password are validated against the information stored in 
"users.txt".  
3. Menu.  
Choose the number corresponding to your choice. Write a number, 
not a letter or a word.  
3.1. add account.  
Add your account data such as your name, E-mail, and mobile number. and the 
system will update "accounts.txt".  
Choose number 1 from the menu to add an account. Example:  
3.2. delete account.  
Enter your account number and it will be deleted by the system if the balance 
equals zero.  
Choose number 2 from the menu to delete the account.  
3.3. modify account  
Enter your account number and the system will change one or more fields (name, mobile 
number, E-mail).  
Choose number 3 from the menu to modify the account.  
You can modify three fields, two fields, or one only.  
3.4. Search.  
Enter your account number and the system will display your account data if found.  
Choose number 4 from the system.  
3.5. advanced search.  
Find your account using a specific keyword.  
Choose number 5 from the menu.  
3.6. withdraw.  
Enter the account number and the withdrawal amount (up to $10,000). Choose number 6 from 
the menu to withdraw money.  
3.7. deposit.  
Enter the account number and the deposit amount (up to $10,000). Choose number 7 from 
the menu to deposit money.  
3.8. Transfer.  
Enter the account numbers of the sender and receiver, along with the transfer amount.  
Choose number 8 from the menu to transfer money 
3.9. Report.  
Enter the account number, and the system will display the transaction history.  
You can only know the last 5 transactions.  
Choose number 9 from the menu to view the history of your account.  
3.10. Print.  
Printing all accounts in sorted order.  
You can sort by name, balance, or data Opened.  
Choose number 10 from the menu to view sorted accounts.  
3.11. Quit.  
To exit the program, choose number 11. 
NOTES 
Data Saving: 
The system prompts you to save changes before exiting. Choose '1' to save 
changes or '2' to exit without saving. 
Balance Limits: 
During transactions, please make sure the amount is valid. The maximum 
deposit/withdrawal amount is $10,000. 
Transaction History: 
The system keeps track of the last five transactions for each account. 
Exiting the Program: 
To exit the program, choose '11' from the main menu. 
The system will prompt you to confirm the exit.
