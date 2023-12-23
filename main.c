#include <stdio.h>
#include <string.h>
//users
typedef struct{
char username[50];
char password[50];
}users;
//date opened
typedef struct {
    int day;
    int month;
    int year;
}date;
//accounts
typedef struct{
    char accountnum[10];
    char name[100];
    chat mobilenum[11];
    char mail[50];
    char balance[20]; 
    date dateOpened;
}Accounts;
void checkLogin (char user[],int pass)
{
    
}
void load ()
{
    char info [200][200]
    FILE *p=fopen("users.txt"."r");
    fcolse(p);
}
void menu ()
{
    
}
void add()
{
    
}
void accountDelete()
{
    
}
void accountModify()
{
    
}
void accountSearch()
{
    
}
void withdraw()
{
    
}
void deposite()
{
    
}
void transfer()
{
    
}
void report()
{
    
}
void print()
{
    
}
void sortByName()
{
    
}
void sortByDate()
{
    
}
void sortByBalance()
{
    
}
void save()
{
    
}
void exit()
{
    
}
int main(){
    char entered_username[50];
    char entered_password[50];
     do {
    printf("HELLO\n");
    printf("Enter username:");
    scanf("%s", entered_username);
    printf("Enter password:");
    scanf("%s", entered_password);
     if (login(entered_username, entered_password)) {
            printf(".........LOADING.........\n");
            break;}
             else {
            printf("Wrong, try again\n");}}
             while (1); // Loop until valid login

    return 0;
}
