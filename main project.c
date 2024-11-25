#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "validation.c"
#include "registration.c"
#include "admin.c"
//#include  "user.c"

#define MAX_NAME_LEN 20
#define MAX_PASSWORD_LEN 15
#define MAX_USERS 7
#define MAX_DOB_LEN 10
#define MAX_NO_LEN 13
#define MAX_GENDER_LEN 6
#define MAX_EMAIL_LEN 25
#define ADMIN_PASSWORD "1234"
#define ADMIN_NAME "admin"
#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 100

#define F "user_info.txt"
#define FL "flight.txt"
#define UB "user_bookings.txt"

//int islogin = 0, isadmin = 0, count = 0,availableFlightCount = 0;
char usernames[MAX_USERS][MAX_NAME_LEN];
char passwords[MAX_USERS][MAX_PASSWORD_LEN];
char dob[MAX_USERS][MAX_DOB_LEN];
char phone[MAX_USERS][MAX_NO_LEN];
char gender[MAX_USERS][MAX_GENDER_LEN];
char email[MAX_USERS][MAX_EMAIL_LEN];
char user_flights[MAX_USERS][MAX_FLIGHTS];
char currentUser[MAX_NAME_LEN];
int travelFrequency; 
char status[15];  
int birth_day[MAX_USERS];
int birth_month[MAX_USERS];
int birth_year[MAX_USERS];

//typedef struct {
//    char flightNumber[20];
//    char origin[50];
//    char destination[50];
//    char travelDate[20];
//    char departureTime[20];
//    int no;
//} Flight;
//Flight availableFlights[MAX_FLIGHTS];

//functions for login and registration
void loadAvailableFlights();
void register_user();
void login_user(char name[MAX_NAME_LEN], char password[MAX_PASSWORD_LEN]);
void login_admin(char name[MAX_NAME_LEN], char password[MAX_PASSWORD_LEN]);
void forgot_password(char name[MAX_NAME_LEN],char Email[MAX_EMAIL_LEN]);
//void saveusers();
//void loadusers();

//functions for user menu
void usermenu();
void userdetails();
int calculateAge(int birth_day, int birth_month, int birth_year, int current_day, int current_month, int current_year);
void bookFlight();
void displayAvailableFlights();
void view_user_bookings();
void modifyBookings();
void cancelBooking();
void saveUser_Flights(char *username, char *flightNumber, char *origin, char *destination,
char *travelDate, char *departureTime, char *travelClass,int *ticketCount);
void loadUser_Flights(char *username);

//functions for admin menu
void adminmenu();
void addFlight();
void deleteFlight();
void userdetails();
void view_all_bookings();
void searchbookings();
void modify_flights();
void deleteExpiredFlights();
void deleteExpiredBookings();
void update_user_bookings(const char *flightNumber, const char *newDate, const char *newTime);
const char* getUserStatus(int age, int travelFrequency);
const char* getUserPerks(const char* status);
int calculateTravelFrequency(const char* username);
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

void usermenu() {
	 int user_choice;
	 int current_day, current_month, current_year;
    getCurrentDate(&current_day, &current_month, &current_year); 
    printf("\t\t---------------USER MENU------------------\n");
    printf("1. USER DETAILS\n");
	printf("2. VIEW AVAILABLE FLIGHTS\n");
    printf("3. BOOK FLIGHTS\n");
    printf("4. VIEW BOOKINGS\n");
    printf("5. MODIFY BOOKINGS\n");
    printf("6. CANCEL BOOKINGS\n");
    printf("7. LOGOUT\n");
    printf("\n\t\tENTER YOUR CHOICE(1-7): ");
    scanf("%d", &user_choice);
    switch (user_choice) {
    	case 1:
    		system("cls");
    		userdetails();
    		break;
        case 2:
        	system("cls");
            displayAvailableFlights();
            system("pause");
            fflush(stdin);
            system("cls");
        break;
        case 3:{ 
        	system("cls");
            bookFlight();
            system("pause");
            fflush(stdin);
            system("cls");
        break;
        }
        case 4:{
        	system("cls");
        	deleteExpiredFlights();
        	view_user_bookings();
            system("pause");
            fflush(stdin);
            system("cls");
			break;
		}
        case 5: 
            {
            system("cls");
            deleteExpiredFlights();
            modifyBookings();
            system("pause");
            fflush(stdin);
            system("cls");
        break;
        }
        case 6:{
        	system("cls");
        	deleteExpiredFlights();
        	cancelBooking();
        	system("pause");
            fflush(stdin);
            system("cls");
			break;
		}
        case 7:
            islogin = 0;
            system("cls");
            return;
        default:
        	printf("INVALID CHOICE\n");
        	system("pause");
        	system("cls");
            break;
    }
}
void userdetails() {
    int current_day, current_month, current_year;
    getCurrentDate(&current_day, &current_month, &current_year);

    int userIndex = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(usernames[i], currentUser) == 0) {
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) {
        printf("\t\tUser not found.\n");
        return;
    }

    int age = calculateAge(birth_day[userIndex], birth_month[userIndex], birth_year[userIndex], current_day, current_month, current_year);

    int travelFrequency = calculateTravelFrequency(currentUser);
    const char* userStatus = getUserStatus(age, travelFrequency);
    const char* userPerks = getUserPerks(userStatus);

    if (age != -1) {
        printf("\t\t=========== USER DETAILS ===========\n");
        printf("\t\tUSERNAME: %s\n", usernames[userIndex]);
        printf("\t\tDATE OF BIRTH: %02d-%02d-%04d\n", birth_day[userIndex], birth_month[userIndex], birth_year[userIndex]);
        printf("\t\tPHONE NUMBER: %s\n", phone[userIndex]);
        printf("\t\tEMAIL: %s\n", email[userIndex]);
        printf("\t\tGENDER: %s\n", gender[userIndex]);
        printf("\t\tAGE: %d years\n", age);
        printf("\t\tSTATUS: %s\n", userStatus);
        printf("\t\tPERKS: %s\n", userPerks);
    } else {
        printf("\t\tCould not calculate age due to invalid birth date.\n");
    }
    system("pause");
    system("cls");
}
void displayAvailableFlights() {
	deleteExpiredFlights();
    loadAvailableFlights();
    if (availableFlightCount == 0) {
        printf("No flights available.....\n");
        return;
    }
    printf("\n\t\t============ AVAILABLE FLIGHTS ============\n\n");
    for (int i = 0; i < availableFlightCount; i++) {
        printf("%d. Flight Number: %s, From:%s, To:%s, Departure On:%s, At:%s\n", 
               i + 1, availableFlights[i].flightNumber, availableFlights[i].origin, availableFlights[i].destination,
               availableFlights[i].travelDate,availableFlights[i].departureTime);
    }
    printf("\n");
}
void saveUser_Flights(char *username, char *flightNumber, char *origin, char *destination, char *travelDate, char *departureTime, char *travelClass, int *ticketCount) {
    FILE *file = fopen("user_bookings.txt", "a+");
    if (file == NULL) {
        printf("ERROR: Could not open file for writing.\n");
        return;
    }

    // Write the booking details with a single newline at the end
    fprintf(file, "%s: Flight Number: %s, From: %s, To: %s, On: %s, At: %s, Class: %s, No of Tickets: %d\n", 
            username, flightNumber, origin, destination, travelDate, departureTime, travelClass, *ticketCount);

    fclose(file);
}

void bookFlight() {
    deleteExpiredFlights();
    loadAvailableFlights();
    if (availableFlightCount == 0) {
        printf("No available flights to book.\n");
        return;
    }
    displayAvailableFlights();

    int flightChoice;
    printf("\nSelect a flight to book (1-%d): ", availableFlightCount);
    scanf("%d", &flightChoice);

    if (flightChoice < 1 || flightChoice > availableFlightCount) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    // Check if the flight is already booked by the user
    FILE *file = fopen(UB, "r");
    if (file != NULL) {
        char line[256];
        char bookedUser[50], bookedFlight[50];
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%[^:]: Flight Number: %[^,]", bookedUser, bookedFlight) == 2) {
                if (strcmp(currentUser, bookedUser) == 0 &&
                    strcmp(availableFlights[flightChoice - 1].flightNumber, bookedFlight) == 0) {
                    printf("\nYou have already booked this flight.\n");
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    }

    printf("\nSelect the class of travel:\n");
    printf("1. Economy\n");
    printf("2. Economy Plus\n");
    printf("3. Business Class\n");
    printf("4. First Class\n");
    int classChoice;
    printf("Enter your choice (1-4): ");
    scanf("%d", &classChoice);

    char travelClass[20];
    switch (classChoice) {
        case 1:
            strcpy(travelClass, "Economy");
            break;
        case 2:
            strcpy(travelClass, "Economy Plus");
            break;
        case 3:
            strcpy(travelClass, "Business Class");
            break;
        case 4:
            strcpy(travelClass, "First Class");
            break;
        default:
            printf("\n\t\t\tInvalid choice. Booking cancelled.\n");
            return; 
    }

    int ticketCount;
    printf("\nEnter the number of tickets you want to buy: ");
    scanf("%d", &ticketCount);

    if (ticketCount < 1) {
        printf("Invalid number of tickets. Booking cancelled.\n");
        return;
    }

    saveUser_Flights(currentUser, availableFlights[flightChoice - 1].flightNumber, availableFlights[flightChoice - 1].origin, 
                     availableFlights[flightChoice - 1].destination, availableFlights[flightChoice - 1].travelDate,
                     availableFlights[flightChoice - 1].departureTime, travelClass, &ticketCount);
    
    printf("\n\t\t\tFlight booked successfully!\n\n");
}

void loadAvailableFlights() {
    FILE *file = fopen(FL, "r");
    if (file == NULL) {
        return;
    }
    availableFlightCount = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",&availableFlights[availableFlightCount].no, availableFlights[availableFlightCount].flightNumber, 
                  availableFlights[availableFlightCount].origin, availableFlights[availableFlightCount].destination, 
                  availableFlights[availableFlightCount].travelDate,availableFlights[availableFlightCount].departureTime) != EOF) {
        availableFlightCount++;
    }
    fclose(file);
}
void modifyBookings() {
    FILE *file = fopen(UB, "r");
    if (file == NULL) {
        printf("No Flights Available Right Now.\n");
        return;
    }

    char line[256];
    char allBookings[MAX_BOOKINGS][256];
    int bookingCount = 0;

    // Read all bookings from the file
    while (fgets(line, sizeof(line), file)) {
        strcpy(allBookings[bookingCount], line);
        bookingCount++;
    }
    fclose(file);

    // Find current user's bookings
    char userBookings[MAX_BOOKINGS][256];
    int userBookingIndices[MAX_BOOKINGS];
    int userBookingCount = 0;

    for (int i = 0; i < bookingCount; i++) {
        char username[50];
        sscanf(allBookings[i], "%[^:]:", username);
        if (strcmp(username, currentUser) == 0) {
            strcpy(userBookings[userBookingCount], allBookings[i]);
            userBookingIndices[userBookingCount] = i; // Save the index in the main array
            userBookingCount++;
        }
    }

    if (userBookingCount == 0) {
        printf("You have no bookings to modify.\n");
        return;
    }

    // Display current user's bookings
    printf("\n\t\t============ FLIGHT BOOKING MODIFICATION ============\n");
    printf("\n\t\t\t========= YOUR CURRENT BOOKINGS =========\n\n");
    for (int i = 0; i < userBookingCount; i++) {
        printf("%d.%s", i + 1, userBookings[i]);
    }

    int bookingChoice;
    printf("\nSelect a booking to modify (1-%d): ", userBookingCount);
    scanf("%d", &bookingChoice);

    if (bookingChoice < 1 || bookingChoice > userBookingCount) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    // Ask for modification details
    int modifyChoice;
    printf("\nWhat would you like to modify?\n");
    printf("1. Class of travel\n");
    printf("2. Number of tickets\n");
    printf("3. Both\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &modifyChoice);

    char newTravelClass[20] = "";
    int newTicketCount = 0;
    if (modifyChoice == 1 || modifyChoice == 3) {
        printf("\nSelect the new class of travel:\n");
        printf("1. Economy\n");
        printf("2. Economy Plus\n");
        printf("3. Business Class\n");
        printf("4. First Class\n");
        int newClassChoice;
        printf("Enter your choice (1-4): ");
        scanf("%d", &newClassChoice);

        switch (newClassChoice) {
            case 1: strcpy(newTravelClass, "Economy"); break;
            case 2: strcpy(newTravelClass, "Economy Plus"); break;
            case 3: strcpy(newTravelClass, "Business Class"); break;
            case 4: strcpy(newTravelClass, "First Class"); break;
            default: printf("\nInvalid choice. Modification cancelled.\n"); return;
        }
    }

    if (modifyChoice == 2 || modifyChoice == 3) {
        printf("Enter the new number of tickets: ");
        scanf("%d", &newTicketCount);
    }

    // Modify the selected booking
    char updatedBooking[256];
    char *classStart = strstr(userBookings[bookingChoice - 1], "Class:");
    char *ticketsStart = strstr(userBookings[bookingChoice - 1], "No of Tickets:");

    if (classStart != NULL && ticketsStart != NULL) {
        strncpy(updatedBooking, userBookings[bookingChoice - 1], classStart - userBookings[bookingChoice - 1] + strlen("Class: "));
        updatedBooking[classStart - userBookings[bookingChoice - 1] + strlen("Class: ")] = '\0';

        if (modifyChoice == 1 || modifyChoice == 3) {
            strcat(updatedBooking, newTravelClass);
            strcat(updatedBooking, ", ");
        } else {
            strncat(updatedBooking, classStart + strlen("Class: "), ticketsStart - classStart - strlen("Class: "));
        }

        if (modifyChoice == 2 || modifyChoice == 3) {
            strcat(updatedBooking, "No of Tickets: ");
            char ticketStr[10];
            sprintf(ticketStr, "%d", newTicketCount);
            strcat(updatedBooking, ticketStr);
        } else {
            strcat(updatedBooking, ticketsStart);
        }
        strcat(updatedBooking, "\n");

        // Update the booking in the main array
        strcpy(allBookings[userBookingIndices[bookingChoice - 1]], updatedBooking);
    } else {
        printf("\nError: Could not find class or ticket information in the booking.\n");
        return;
    }

    // Write all bookings back to the file
    file = fopen(UB, "w");
    for (int i = 0; i < bookingCount; i++) {
        fputs(allBookings[i], file);
    }
    fclose(file);

    printf("\n\t\t\tBooking modified successfully!\n\n");
}

void cancelBooking() {
    FILE *file = fopen(UB, "r");
    if (file == NULL) {
        printf("No Flights Available Right Now.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to create a temporary file.\n");
        fclose(file);
        return;
    }
    char line[256];
    char userBookings[MAX_BOOKINGS][256];
    int userBookingCount = 0;
    while (fgets(line, sizeof(line), file)) {
        char username[50];
        char bookingDetails[200];
        sscanf(line, "%[^:]: %[^\n]", username, bookingDetails);

        if (strcmp(username, currentUser) == 0) {
            strcpy(userBookings[userBookingCount], line);
            userBookingCount++;
        } else {
            fputs(line, tempFile); 
        }
    }
    fclose(file);
    if (userBookingCount == 0) {
        printf("You have no bookings to cancel.\n");
        fclose(tempFile);
        remove("temp.txt");
        return;
    }
    printf("\n\t\t============ FLIGHT BOOKING CANCELATION ============\n");
    printf("\n\t\t\t========= YOUR CURRENT BOOKINGS =========\n\n");
    for (int i = 0; i < userBookingCount; i++) {
        printf("%d. %s", i + 1, userBookings[i]); 
    }

    int bookingChoice;
    printf("\nSelect a booking to cancel (1-%d): ", userBookingCount);
    scanf("%d", &bookingChoice);

    if (bookingChoice < 1 || bookingChoice > userBookingCount) {
        printf("Invalid choice. Please try again.\n");
        fclose(tempFile);
        remove("temp.txt");
        return;
    }
    for (int i = 0; i < userBookingCount; i++) {
        if (i != bookingChoice - 1) {
            fputs(userBookings[i], tempFile);
        }
    }
    fclose(tempFile);
    remove(UB);
    rename("temp.txt", UB);

    printf("\n\t\t\tBooking cancelled successfully!\n\n");
}
void view_user_bookings() {
    FILE *file = fopen(UB, "r");
    if (file == NULL) {
        printf("No bookings currently.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    printf("\n\t\t============ YOUR BOOKINGS ============\n\n");
    int foundBookings = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char username[50];
        sscanf(line, "%[^:]:", username);

        if (strcmp(username, currentUser) == 0) {
            foundBookings = 1;
            char *bookingDetails = strchr(line, ':') + 1;
            char flightNumber[50];
            sscanf(bookingDetails, " Flight Number: %[^,]", flightNumber);

            if (strstr(line, "(CANCELED)")) {
                printf("%s\n", bookingDetails);
                printf("Note: The flight (%s) has been canceled.\n", flightNumber);
                continue; 
            } 
            else if (strstr(line, "[Modified: Departure Date Changed]")) {
                printf("%s\n", bookingDetails);
                printf("Note: The departure date for flight (%s) has been modified.\n", flightNumber);
                char *modifiedPos = strstr(line, "[Modified: Departure Date Changed]");
                if (modifiedPos) {
                    *modifiedPos = '\0'; 
                }
            } else if (strstr(line, "[Modified: Departure Time Changed]")) {
                printf("%s\n", bookingDetails);
                printf("Note: The departure time for flight (%s) has been modified.\n", flightNumber);
                char *modifiedPos = strstr(line, "[Modified: Departure Time Changed]");
                if (modifiedPos) {
                    *modifiedPos = '\0'; 
                }
            } else {
                printf("%s\n", bookingDetails);
            }

            fprintf(tempFile, "%s\n", line);
        } else {
            fputs(line, tempFile); 
        }
    }

    if (!foundBookings) {
        printf("\tYou have no bookings.\n\n");
    }

    fclose(file);
    fclose(tempFile);
    remove(UB);
    rename("temp.txt", UB);
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