typedef struct{
char username[50];
char password[50];
}users;

int login(char *username, char *password) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;}

    char stored_username[150];
    char stored_password[150];
    int isValid = 0;

    // Read and validate user details

    //fscanf successfully reads and assigns values to both variables, it returns 2,
    //indicating that it matched two items

    while (fscanf(file, "%s %s", stored_username, stored_password) == 2) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            isValid = 1;
            break;}}
    fclose(file);
    return isValid;}

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
