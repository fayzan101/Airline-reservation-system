#include<stdio.h>
#include <time.h>
#include<string.h>
#include<stdlib.h>
#define MAX_NAME_LEN 20
#define MAX_PASSWORD_LEN 15
#define MAX_USERS 20
#define MAX_NO_LEN 13
#define MAX_GENDER_LEN 7
#define MAX_EMAIL_LEN 25
#define ADMIN_PASSWORD "1234"
#define ADMIN_NAME "admin"
#define F "user_info.txt"
#define FL "flight.txt"
#define UB "user_bookings.txt"

void saveusers();
void adminmenu();
void addFlight();
void  deleteFlight();
void view_all_bookings();
void searchbookings();
void modify_flights();
void displayAvailableFlights();
void deleteExpiredFlights(); 
void loadAvailableFlights();
void update_user_bookings(const char *flightNumber, const char *newDate, const char *newTime);

int islogin = 0, isadmin = 0, count = 0,availableFlightCount = 0;
char usernames[MAX_USERS][MAX_NAME_LEN];
char passwords[MAX_USERS][MAX_PASSWORD_LEN];
char phone[MAX_USERS][MAX_NO_LEN];
char gender[MAX_USERS][MAX_GENDER_LEN];
char email[MAX_USERS][MAX_EMAIL_LEN];
char currentUser[MAX_NAME_LEN];
int travelFrequency; 
char status[15];  
int birth_day[MAX_USERS];
int birth_month[MAX_USERS];
int birth_year[MAX_USERS];
void register_user() {
    printf("\t\t----------------USER REGISTRATION--------------\n");
    int isregister = 0, i;
    char name[MAX_NAME_LEN];
     do {
        printf("\t\tENTER USERNAME: ");
        scanf(" %[^\n]", name); 
        int has_space = 0;
        for (i = 0; name[i] != '\0'; i++) {
            if (name[i] == ' ') {
                has_space = 1;
                break;
            }
        }
        if (has_space) {
            printf("\t\tUSERNAME CANNOT HAVE SPACES. PLEASE TRY AGAIN.\n");
        } else {
            break;
        }
    } while (1);
    
    for (i = 0; i < count; i++) {
        if (strcmp(usernames[i], name) == 0) {
            printf("\t\tACCOUNT ALREADY REGISTERED WITH THIS NAME\n");
            isregister = 1;
            system("pause");
            system("cls");
            break;
        }
    }
    if (!isregister) {
        strcpy(usernames[count], name);
        do {
            printf("\t\tENTER PASSWORD: ");
            scanf(" %s", passwords[count]);
            if (strlen(passwords[count]) < 8) {
                printf("\t\tPASSWORD SHOULD BE AT LEAST 8 CHARACTERS LONG.\n");
            }
        } while (strlen(passwords[count]) < 8);

        int valid_dob = 0;
        do {
            printf("\t\tDATE OF BIRTH (DD-MM-YYYY): ");
            scanf("%d-%d-%d", &birth_day[count], &birth_month[count], &birth_year[count]);
            
            valid_dob = validateBirthDate(birth_day[count], birth_month[count], birth_year[count]);

            if (!valid_dob) {
                printf("\t\tINVALID DATE OF BIRTH. PLEASE ENTER A VALID DATE (DD-MM-YYYY).\n");
            }
        } while (!valid_dob);
          int valid_phone = 0;
        do {
            printf("\t\tPHONE NO: ");
            scanf(" %s", phone[count]);

            valid_phone = 1;
            for (i = 0; phone[count][i] != '\0'; i++) {
                if (!isdigit(phone[count][i])) { 
                    valid_phone = 0;
                    break;
                }
            }
            if (valid_phone && (i < 10 || i > 15)) { 
                valid_phone = 0;
            }
            if (!valid_phone) {
                printf("\t\tINVALID PHONE NUMBER. PLEASE ENTER A VALID PHONE NUMBER (10-15 DIGITS).\n");
            }
        } while (!valid_phone);

        printf("\t\tGENDER: ");
        scanf(" %s", gender[count]);
         int valid_email = 0;
        do {
            printf("\t\tEMAIL: ");
            scanf(" %s", email[count]);
            char *at = strchr(email[count], '@');
            char *dot = strchr(email[count], '.');
            if (at && dot && at < dot) {
                valid_email = 1;
            } else {
                printf("\t\tINVALID EMAIL. PLEASE ENTER A VALID EMAIL (e.g., user@example.com).\n");
            }
        } while (!valid_email);
        count++;
        printf("\t\tSUCCESSFULLY REGISTERED...\n");
        saveusers();
        system("pause");
        system("cls");
    }
}
void saveusers() {
    FILE *file = fopen(F, "w");
    if (file == NULL) {
        printf("ERROR FILE NOT FOUND\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%02d-%02d-%04d,%s,%s,%s\n", 
                usernames[i], 
                passwords[i], 
                birth_day[i], birth_month[i], birth_year[i], 
                phone[i], 
                gender[i], 
                email[i]);
    }
    fclose(file);
}
void login_user(char name[MAX_NAME_LEN], char password[MAX_PASSWORD_LEN]) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(usernames[i], name) == 0 && strcmp(passwords[i], password) == 0) {
            printf("\t\tLOGIN SUCCESSFULLY..\n");
            islogin = 1;
            isadmin = 0;
            strcpy(currentUser, name);
            system("pause");
            fflush(stdin);
            system("cls");
            return;
        }
    }
    printf("\t\tINCORRECT USERNAME OR PASSWORD...\n");
    system("pause");
    fflush(stdin);
    system("cls");
}
void login_admin(char name[MAX_NAME_LEN], char password[MAX_PASSWORD_LEN]) {
    if (strcmp(ADMIN_NAME, name) == 0 && strcmp(ADMIN_PASSWORD, password) == 0) {
        printf("\t\tLOGIN SUCCESSFULLY..\n");
        islogin = 1;
        isadmin = 1;
        strcpy(currentUser, name);
        system("pause");
        fflush(stdin);
        system("cls");
        adminmenu();
        return;
    }
    printf("\t\tINCORRECT USERNAME OR PASSWORD...\n");
    system("pause");
    fflush(stdin);
    system("cls");
}
void forgot_password(char name[MAX_NAME_LEN],char Email[MAX_EMAIL_LEN]) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(name, usernames[i]) == 0 && strcmp(Email,email[i])==0) {
            printf("\t\tYOUR PASSWORD IS %s\n", passwords[i]);
            system("pause");
            fflush(stdin);
            system("cls");
            return;
        }
    }
    printf("\t\tUSER NOT FOUND\n");
    system("pause");
    fflush(stdin);
    system("cls");
}

void loadusers() {
    FILE *file = fopen(F, "r");
    if (file == NULL) {
        return;
    }
    count = 0;
    while (fscanf(file, "%[^,],%[^,],%d-%d-%d,%[^,],%[^,],%[^\n]\n", 
                  usernames[count], 
                  passwords[count], 
                  &birth_day[count], 
                  &birth_month[count], 
                  &birth_year[count], 
                  phone[count], 
                  gender[count], 
                  email[count]) != EOF) {
        count++;
    }
    fclose(file);
}