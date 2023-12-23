#include <stdio.h>
#include <string.h>
typedef struct {
    int day;
    int month;
    int year;
}date;
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
void main()
{
    char user[15];
    int pass;
    printf("Username: ");
    scanf("%s",user);
    printf("\nPassword: ");
    scanf("%d",&pass);
}
