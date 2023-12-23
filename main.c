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
int checkLogin(char *username, char *password) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;}

    users stored;
    int isValid = 0;

    // Read and validate user details
    //fscanf successfully reads and assigns values to both variables, it returns 2,
    //indicating that it matched two items

      while (fscanf(file, "%s %s", stored.username, stored.password) == 2) {
        if (strcmp(username, stored.username) == 0 && strcmp(password, stored.password) == 0) {
            isValid = 1;
            break;}}
    fclose(file);
    return isValid;}
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
            load();
            break;}
             else {
            printf("Wrong, try again\n");}}
             while (1); // Loop until valid login

    return 0;
}
