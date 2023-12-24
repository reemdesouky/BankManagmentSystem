#include <stdio.h>
#include <string.h>

#define maxrow 500
#define maxcol 500

typedef struct {
    char day[3];
    char month[3];
    char year[5];
} date;

typedef struct {
    char accountnum[11];
    char name[100];
    char mail[50];
    char mobilenum[12];
    double balance;
    date dateOpened;
} Accounts;

void print_accounts(Accounts acc) {
    printf("Account Number=%s\nName=%s\nEmail=%s\nBalance=%.2f\nMobile Number=%s\nDate Opened=%s/%s/%s\n",
           acc.mobilenum, acc.name, acc.mail, acc.balance, acc.mobilenum, acc.dateOpened.day,
           acc.dateOpened.month, acc.dateOpened.year);
}

void assign(char temp[], Accounts *acc) {
    char *token = strtok(temp, ",");
    strcpy(acc->accountnum, token);
    token = strtok(NULL, ",");
    strcpy(acc->name, token);
    token = strtok(NULL, ",");
    strcpy(acc->mail, token);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &acc->balance);
    token = strtok(NULL, ",");
    strcpy(acc->mobilenum, token);
    token = strtok(NULL, "/");
    strcpy(acc->dateOpened.day, token);
    token = strtok(NULL, "/");
    strcpy(acc->dateOpened.month, token);
    token = strtok(NULL, "/");
    strcpy(acc->dateOpened.year, token);
}

int main() {
    char temp[maxrow][maxcol];
    int i = 0;
    Accounts acc[maxrow];
    FILE *ptr = fopen("accounts.txt", "r");

    if (!ptr) {
        printf("File can't be reached!");
        return 1;
    } else {
        while (fgets(temp[i], maxcol, ptr)) {
            assign(temp[i], &acc[i]);
            i++;
        }
        printf("Data has been successfully uploaded to the system.");
    }

    fclose(ptr);
    return 0;
}
