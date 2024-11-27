#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "validation.c"
#include "registration.c"
#include "admin.c"
#include "user.c"

#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 100

#define F "user_info.txt"
#define FL "flight.txt"
#define UB "user_bookings.txt"
void usermenu();
void userdetails();
void bookFlight();
void displayAvailableFlights();
void view_user_bookings();
void modifyBookings();
void cancelBooking();
void saveUser_Flights(char *username, char *flightNumber, char *origin, char *destination,
char *travelDate, char *departureTime, char *travelClass,int *ticketCount);
void deleteExpiredFlights();
void deleteExpiredBookings();
int main() {
    char choice;
    loadusers();
    while (1) {
        if (!islogin) {
            printf("\t\t----------------------------WELCOME TO FAST AIRLINE RESERVATION SYSTEM-----------------------------\n");
            printf("\t\t1. REGISTER\n");
            printf("\t\t2. LOGIN AS USER\n");
            printf("\t\t3. LOGIN AS ADMIN\n");
            printf("\t\t4. FORGOT PASSWORD\n");
            printf("\t\t5. EXIT\n");
            printf("\n\t\tENTER YOUR CHOICE(1-5): ");
            scanf(" %c", &choice);
            system("cls");
            switch (choice) {
                case '1':
                    if (count >= MAX_USERS) {
                        printf("\t\tREGISTRATION LIMIT EXCEEDED\n");
                        system("pause");
                        system("cls");
                    } else {
                        register_user();
                    }
                    break;
                case '2': {
                    printf("\t\t-----------LOGIN AS USER-----------\n");
                    char name[MAX_NAME_LEN], password[MAX_PASSWORD_LEN];
                    printf("\t\tENTER USERNAME: ");
                    scanf("%s", name);
                    printf("\t\tENTER YOUR PASSWORD: ");
                    scanf(" %s", password);
                    login_user(name, password);
                    break;
                }
                case '3': {
                    printf("\t\t---------LOGIN AS ADMIN---------\n");
                    char name[MAX_NAME_LEN], password[MAX_PASSWORD_LEN];
                    printf("\t\tENTER USERNAME: ");
                    scanf("%s", name);
                    printf("\t\tENTER YOUR PASSWORD: ");
                    scanf(" %s", password);
                    login_admin(name, password);
                    break;
                }
                case '4':
                	printf("\t\t------------------------FORGOT PASSWORD--------------------------\n");
                    printf("\t\tENTER USERNAME: ");
                    char name[MAX_NAME_LEN];
                    char Email[MAX_EMAIL_LEN];
                    scanf("%s", name);
                    printf("\t\tENTER EMAIL:"),
                    scanf(" %s",Email);
                    forgot_password(name,Email);
                    break;
                case '5':
                    printf("\t---------------------THANK YOU FOR USING FAST AIRLINE-------------------------\n");
                    exit(0);
                default:
                    printf("\t\tINVALID CHOICE. TRY AGAIN\n");
                    system("pause");
                    system("cls");
            }
        } else {
            if (isadmin)
                adminmenu();
            else
                usermenu();
        }
    }
}
void deleteExpiredBookings() {
    int current_day, current_month, current_year, current_hour, current_minute;
    getCurrentDate(&current_day, &current_month, &current_year);
    getCurrentTime(&current_hour, &current_minute);
    FILE *bookingsFile = fopen("user_bookings.txt", "r");
    if (bookingsFile == NULL) {
        printf("Error: Could not open user bookings file for reading.\n");
        return;
    }

    FILE *tempBookingsFile = fopen("temp_user_bookings.txt", "w");
    if (tempBookingsFile == NULL) {
        printf("Error: Could not create temporary bookings file.\n");
        fclose(bookingsFile);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), bookingsFile)) {
        char username[50], flightNumber[20], departureDate[20], departureTime[20];
        int bookingDay, bookingMonth, bookingYear, bookingHour, bookingMinute;
        if (sscanf(line, "%49[^:]: Flight Number: %19[^,], From: %*[^,], To: %*[^,], On: %19[^,], At: %19[^\n]",
                   username, flightNumber, departureDate, departureTime) == 4) {
            sscanf(departureDate, "%d-%d-%d", &bookingDay, &bookingMonth, &bookingYear);
            sscanf(departureTime, "%d:%d", &bookingHour, &bookingMinute);
            if (bookingYear < current_year || 
                (bookingYear == current_year && bookingMonth < current_month) ||
                (bookingYear == current_year && bookingMonth == current_month && bookingDay < current_day) ||
                (bookingYear == current_year && bookingMonth == current_month && bookingDay == current_day && 
                 (bookingHour < current_hour || (bookingHour == current_hour && bookingMinute <= current_minute)))) {
                continue; 
            }
        }
        fputs(line, tempBookingsFile); 
    }

    fclose(bookingsFile);
    fclose(tempBookingsFile);
    remove("user_bookings.txt");
    rename("temp_user_bookings.txt", "user_bookings.txt");
}
void deleteExpiredFlights() {
    int current_day, current_month, current_year, current_hour, current_minute;
    getCurrentDate(&current_day, &current_month, &current_year);
    getCurrentTime(&current_hour, &current_minute);

    FILE *file = fopen(FL, "r");
    if (file == NULL) {
        printf("Error: Could not open flights file for reading.\n");
        return;
    }

    FILE *tempFile = fopen("temp_flights.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file for flights.\n");
        fclose(file);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char flightNumber[20], origin[50], destination[50], travelDate[20], departureTime[20];
        int day, month, year, hour, minute;
        if (sscanf(line, "%*d, %19[^,], %49[^,], %49[^,], %19[^,], %19[^\n]",
                   flightNumber, origin, destination, travelDate, departureTime) == 5) {
            sscanf(travelDate, "%d-%d-%d", &day, &month, &year);
            sscanf(departureTime, "%d:%d", &hour, &minute);
            if (year < current_year || 
                (year == current_year && month < current_month) ||
                (year == current_year && month == current_month && day < current_day) ||
                (year == current_year && month == current_month && day == current_day && 
                 (hour < current_hour || (hour == current_hour && minute <= current_minute)))) {
                continue; 
            }
        }
        fputs(line, tempFile); 
    }

    fclose(file);
    fclose(tempFile);
    remove(FL);
    rename("temp_flights.txt", FL);
    deleteExpiredBookings();
}
