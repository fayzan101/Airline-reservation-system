#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void usermenu() {
	 int user_choice;
	 int current_day, current_month, current_year;
    getCurrentDate(&current_day, &current_month, &current_year); 
    while(1)
    {
    printf("\n\t\t============ USER MENU ============\n");
    printf("1. USER DETAILS\n");
	printf("2. VIEW AVAILABLE FLIGHTS\n");
    printf("3. BOOK FLIGHTS\n");
    printf("4. VIEW BOOKINGS\n");
    printf("5. MODIFY BOOKINGS\n");
    printf("6. CANCEL BOOKINGS\n");
    printf("7. LOGOUT\n");
    printf("\n\t\tENTER YOUR CHOICE(1-7): ");
     if (scanf("%d", &user_choice) != 1) { 
            printf("\n\t\tINVALID INPUT! PLEASE ENTER A NUMBER BETWEEN 1 AND 7.\n");
            while (getchar() != '\n'); 
            system("pause");
            system("cls");
            continue; 
        }

        if (user_choice < 1 || user_choice > 7) { 
            printf("\n\t\tINVALID CHOICE! PLEASE ENTER A NUMBER BETWEEN 1 AND 7.\n");
            system("pause");
            system("cls");
            continue;
        }
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

        printf("\t\t=========== USER DETAILS ===========\n");
        printf("\t\tUSERNAME: %s\n", usernames[userIndex]);
        printf("\t\tDATE OF BIRTH: %02d-%02d-%04d\n", birth_day[userIndex], birth_month[userIndex], birth_year[userIndex]);
        printf("\t\tPHONE NUMBER: %s\n", phone[userIndex]);
        printf("\t\tEMAIL: %s\n", email[userIndex]);
        printf("\t\tGENDER: %s\n", gender[userIndex]);
        printf("\t\tAGE: %d years\n", age);
        printf("\t\tSTATUS: %s\n", userStatus);
        printf("\t\tPERKS: %s\n", userPerks);
    system("pause");
    system("cls");
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
void saveUser_Flights(char *username, char *flightNumber, char *origin, char *destination, char *travelDate, char *departureTime, char *travelClass, int *ticketCount) {
    FILE *file = fopen("user_bookings.txt", "a+");
    if (file == NULL) {
        printf("ERROR: Could not open file for writing.\n");
        return;
    }
    fprintf(file, "%s: Flight Number: %s, From: %s, To: %s, On: %s, At: %s, Class: %s, No of Tickets: %d\n", 
            username, flightNumber, origin, destination, travelDate, departureTime, travelClass, *ticketCount);
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
    while (fgets(line, sizeof(line), file)) {
        strcpy(allBookings[bookingCount], line);
        bookingCount++;
    }
    fclose(file);
    char userBookings[MAX_BOOKINGS][256];
    int userBookingIndices[MAX_BOOKINGS];
    int userBookingCount = 0;
    
     while (fgets(line, sizeof(line), file)) {
        char *trimmedLine = line;
        while (*trimmedLine == ' ' || *trimmedLine == '\t') trimmedLine++; // Skip leading whitespace
        if (trimmedLine[0] == '\0' || trimmedLine[0] == '\n') continue;   // Skip empty lines

        strcpy(allBookings[bookingCount], line);
        bookingCount++;
    }
    fclose(file);

    for (int i = 0; i < bookingCount; i++) {
        char username[50];
        sscanf(allBookings[i], "%[^:]:", username);
        if (strcmp(username, currentUser) == 0) {
            strcpy(userBookings[userBookingCount], allBookings[i]);
            userBookingIndices[userBookingCount] = i; 
            userBookingCount++;
        }
    }

    if (userBookingCount == 0) {
        printf("You have no bookings to modify.\n");
        return;
    }
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
        strcpy(allBookings[userBookingIndices[bookingChoice - 1]], updatedBooking);
    } else {
        printf("\nError: Could not find class or ticket information in the booking.\n");
        return;
    }
    file = fopen(UB, "w+");
    for (int i = 0; i < bookingCount; i++) {
    	if (strlen(allBookings[i]) > 1)
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
    	if (strlen(line) <= 1) continue; 
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
    int i=0;
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

            int dateModified = 0;
            int timeModified = 0;
            if (strstr(line, "[Departure Date Changed]")) {
                dateModified = 1;
            }
            if (strstr(line, "[Departure Time Changed]")) {
                timeModified = 1;
            }
            printf("%d.%s\n",i+1, bookingDetails);
            i++;
            if (dateModified || timeModified) {
                printf("Note: ");
                if (dateModified && timeModified) {
                    printf("Departure time and date for flight (%s) changed", flightNumber);
                } else {
                    if (dateModified) {
                        printf("Departure date for flight (%s) changed", flightNumber);
                    }
                    if (timeModified) {
                        if (dateModified) {
                            printf(" and ");
                        }
                        printf("Departure time for flight (%s) changed", flightNumber);
                    }
                }
                printf(".\n");
            }
            char *modifiedPos = strstr(line, "[Departure Date Changed]");
            if (modifiedPos) {
                *modifiedPos = '\0'; 
            }
            modifiedPos = strstr(line, "[Departure Time Changed]");
            if (modifiedPos) {
                *modifiedPos = '\0'; 
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