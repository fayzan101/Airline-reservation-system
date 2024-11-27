#include<stdio.h>
#include <time.h>
#include<string.h>
#include<stdlib.h>

#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 10
#define F "user_info.txt"
#define FL "flight.txt"
#define UB "user_bookings.txt"

void adminmenu() {
     int admin_choice;
    printf("\t\t------------ADMIN MENU------------------\n");
    printf("1. ADD FLIGHT\n");
    printf("2. DELETE FLIGHT\n");
    printf("3  MODIFIY FLIGHTS\n");
    printf("4. VIEW ALL BOOKINGS\n");
    printf("5. SEARCH BOOKINGS\n");
    printf("6. LOGOUT\n");
    printf("\n\t\tENTER YOUR CHOICE: ");
    scanf("%d", &admin_choice);
        switch (admin_choice) {
        case 1:system("cls"); 
               addFlight();
            	break;
        case 2: system("cls");
                deleteFlight();
                break;
        case 3:system("cls"); 
    		   modify_flights();
               break;
        case 4:system("cls");
		   deleteExpiredFlights(); 
    		   view_all_bookings();
                break;
        case 5: 
		    system("cls");
        	deleteExpiredFlights();
            searchbookings();
            break;
        case 6:islogin = 0;
            isadmin = 0;
            system("cls");
            return;
        default:
        	printf("INVALID CHOICE\n");
        	system("pause");
        	system("cls");
            break;
    }
}
void addFlight() {
    int count = 1;
    char line[200];
    FILE *file = fopen(FL, "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }
        fclose(file);
    }
    Flight newFlight;
    file = fopen(FL, "a");
    if (file == NULL) {
        printf("ERROR: Could not open file for writing.\n");
        return;
    }
    fflush(stdin);
    int current_day, current_month, current_year, current_hour, current_minute;
    getCurrentDate(&current_day, &current_month, &current_year);
    getCurrentTime(&current_hour, &current_minute);
    printf("Enter Flight Number: ");
    gets(newFlight.flightNumber);
    fflush(stdin);
    FILE *readFile = fopen(FL, "r");
    if (readFile != NULL) {
        while (fgets(line, sizeof(line), readFile) != NULL) {
            char existingFlightNumber[20];
            sscanf(line, "%*d,%[^,]", existingFlightNumber);

            if (strcmp(existingFlightNumber, newFlight.flightNumber) == 0) {
                printf("This flight is already added. Cannot add the same flight twice!\n");
                fclose(readFile);
                fclose(file);
                return;
            }
        }
        fclose(readFile);
    }
    printf("Enter Origin: ");
    gets(newFlight.origin);
    fflush(stdin);
    printf("Enter Destination: ");
    gets(newFlight.destination);
    fflush(stdin);
    int day, month, year;
    printf("Enter Departure Date (dd-mm-yyyy): ");
    gets(newFlight.travelDate);
    sscanf(newFlight.travelDate, "%d-%d-%d", &day, &month, &year);

    while (!validDepartureDate(day, month, year, current_day, current_month, current_year)) {
        printf("The Flight Departure Date cannot be in the past! Please enter a valid date.\n");
        printf("Enter Departure Date (dd-mm-yyyy): ");
        gets(newFlight.travelDate);
        sscanf(newFlight.travelDate, "%d-%d-%d", &day, &month, &year);
    }

    int hour, minute;
    printf("Enter Departure Time (hh:mm): ");
    gets(newFlight.departureTime);
    sscanf(newFlight.departureTime, "%d:%d", &hour, &minute);

    while (!validDepartureTime(hour, minute, day, month, year, current_day, current_month, current_year)) {
        printf("The Flight Departure Time cannot be in the past! Please enter a valid time.\n");
        printf("Enter Departure Time (hh:mm): ");
        gets(newFlight.departureTime);
        sscanf(newFlight.departureTime, "%d:%d", &hour, &minute);
    }

    fprintf(file, "%d,%s,%s,%s,%s,%s\n", count, newFlight.flightNumber, newFlight.origin, newFlight.destination, newFlight.travelDate, newFlight.departureTime);
    fclose(file);

    printf("Flight added successfully!\n");
    system("pause");
    system("cls");
}
void deleteFlight() {
    loadAvailableFlights();
    if (availableFlightCount == 0) {
        printf("No flights available to delete\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\t\t---------------Available Flights---------------------------\n");
    for (int i = 0; i < availableFlightCount; i++) {
        printf("%d. Flight Number: %s, From: %s, To: %s, Departure On: %s, At: %s\n",
               i + 1, availableFlights[i].flightNumber, availableFlights[i].origin,
               availableFlights[i].destination, availableFlights[i].travelDate, availableFlights[i].departureTime);
    }
    printf("\n");
    int serialNumber;
    printf("Enter The Serial Number Of Flight: ");
    scanf("%d", &serialNumber);
    if (serialNumber < 1 || serialNumber > availableFlightCount) {
        printf("Invalid serial number. Please try again.\n");
        system("pause");
        system("cls");
        return;
    }
    int flightIndex = serialNumber - 1;
    Flight deletedFlight = availableFlights[flightIndex];
    Flight updatedFlights[MAX_FLIGHTS];
    int updatedFlightCount = 0;

    for (int i = 0; i < availableFlightCount; i++) {
        if (i != flightIndex) {
            updatedFlights[updatedFlightCount++] = availableFlights[i];
        }
    }
    FILE *file = fopen(FL, "w");
    if (file == NULL) {
        printf("Could not open flight file for writing.\n");
        return;
    }
    for (int i = 0; i < updatedFlightCount; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
                updatedFlights[i].no, updatedFlights[i].flightNumber,
                updatedFlights[i].origin, updatedFlights[i].destination,
                updatedFlights[i].travelDate, updatedFlights[i].departureTime);
    }
    fclose(file);
    file = fopen(UB, "r");
    FILE *tempfile = fopen("temp_bookings.txt", "w");
    if (file == NULL || tempfile == NULL) {
        printf("Could not open bookings file.\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, deletedFlight.flightNumber)) {
            fprintf(tempfile, "%s (CANCELED)\n", strtok(line, "\n"));
        } else {
            fputs(line, tempfile);
        }
    }
    fclose(file);
    fclose(tempfile);
    remove(UB);
    rename("temp_bookings.txt", UB);
    printf("Flight and associated bookings updated successfully.\n");
    system("pause");
    system("cls");
}
void modify_flights() {
    loadAvailableFlights();
    if (availableFlightCount == 0) {
        printf("No flights available to modify\n");
        system("pause");
        system("cls");
        return;
    }
    printf("\t\t---------------Available Flights---------------------------\n");
    for (int i = 0; i < availableFlightCount; i++) {
        printf("Flight Number: %s, From: %s, To: %s, Departure On: %s, At: %s\n"
               , availableFlights[i].flightNumber, availableFlights[i].origin,
               availableFlights[i].destination, availableFlights[i].travelDate, availableFlights[i].departureTime);
    }
    printf("\n");
    char flightNumber[50], newDetails[256];
    printf("\nEnter the Flight Number to Modify: ");
    scanf("%s", flightNumber);

    FILE *file = fopen(FL, "r");
    if (file == NULL) {
        printf("No flight records found.\n");
        return;
    }
    FILE *tempFile = fopen("t.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }
    char line[256];
    int found = 0;
    char updatedDate[20], updatedTime[10];
    updatedDate[0] = '\0'; 
    updatedTime[0] = '\0'; 
    while (fgets(line, sizeof(line), file)) {
        char flightNum[50], origin[50], destination[50], travelDate[20], departureTime[10];
        int flightNumField;
        sscanf(line, "%d, %49[^,], %49[^,], %49[^,], %19[^,], %9[^\n]",
               &flightNumField, flightNum, origin, destination, travelDate, departureTime);

        if (strstr(line, flightNumber) && !found) { 
            found = 1;
            int choice;
            printf("\nWhat do you want to modify?\n");
            printf("1. Departure Date\n");
            printf("2. Departure Time\n");
            printf("Enter your choice (1 or 2): ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Enter New Departure Date (dd-mm-yy): ");
                getchar(); 
                fgets(newDetails, sizeof(newDetails), stdin);
                newDetails[strcspn(newDetails, "\n")] = 0;
                snprintf(updatedDate, sizeof(updatedDate), "%s", newDetails);
                snprintf(travelDate, sizeof(travelDate), "%s", updatedDate);
            } else if (choice == 2) {
                printf("Enter New Departure Time (hh:mm): ");
                getchar(); 
                fgets(newDetails, sizeof(newDetails), stdin);
                newDetails[strcspn(newDetails, "\n")] = 0;
                snprintf(updatedTime, sizeof(updatedTime), "%s", newDetails);
                snprintf(departureTime, sizeof(departureTime), "%s", updatedTime);
            } else {
                printf("Invalid choice.\n");
                fclose(file);
                fclose(tempFile);
                return;
            }

            fprintf(tempFile, "%d,%s,%s,%s,%s,%s\n", flightNumField, flightNum, origin, destination, travelDate, departureTime);
        } else {
        	
            fprintf(tempFile, "%d,%s,%s,%s,%s,%s\n", flightNumField, flightNum, origin, destination, travelDate, departureTime);
            
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("flight.txt");
    rename("t.txt", "flight.txt");

    if (found) {
        printf("\nFlight modified successfully!\n");
        update_user_bookings(flightNumber, updatedDate, updatedTime);
    } else {
        printf("\nFlight Number not found.\n");
    }
    system("pause");
    system("cls");
}
void update_user_bookings(const char *flightNumber, const char *newDate, const char *newTime) {
    FILE *file = fopen(UB, "r+");
    if (file == NULL) {
        printf("No Bookings Available to Update.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }
    char line[256];
    int foundBookings = 0;
    char trimmedFlightNumber[50];
    snprintf(trimmedFlightNumber, sizeof(trimmedFlightNumber), "%s", flightNumber);
    trimmedFlightNumber[strcspn(trimmedFlightNumber, "\n")] = 0;
    trimmedFlightNumber[strcspn(trimmedFlightNumber, " ")] = 0;

    while (fgets(line, sizeof(line), file)) {
        char username[50], flightNum[50], from[50], to[50], travelDate[20], departureTime[10], flightClass[20];
        int numTickets;

        sscanf(line, "%[^:]: Flight Number: %[^,], From: %[^,], To: %[^,], On: %[^,], At: %[^,], Class: %[^,], No of Tickets: %d",
               username, flightNum, from, to, travelDate, departureTime, flightClass, &numTickets);

        if (strcmp(flightNum, trimmedFlightNumber) == 0) {
            foundBookings = 1;
            int dateChanged = 0, timeChanged = 0;
            char modificationMessage[100] = "";

            // Check and apply changes to the date and time
            if (newDate[0] != '\0' && strcmp(newDate, travelDate) != 0) {
                snprintf(travelDate, sizeof(travelDate), "%s", newDate);
                dateChanged = 1;
            }
            if (newTime[0] != '\0' && strcmp(newTime, departureTime) != 0) {
                snprintf(departureTime, sizeof(departureTime), "%s", newTime);
                timeChanged = 1;
            }

            if (dateChanged || timeChanged) {
                // Build modification message based on changes
                if (dateChanged) {
                    strcat(modificationMessage, " [Modified: Departure Date Changed]");
                }
                if (timeChanged) {
                    if (strlen(modificationMessage) > 0) {
                        strcat(modificationMessage, ", ");
                    }
                    strcat(modificationMessage, " [Modified: Departure Time Changed]");
                }
                // Write the updated booking with modification message
                fprintf(tempFile, "%s: Flight Number: %s, From: %s, To: %s, On: %s, At: %s, Class: %s, No of Tickets: %d%s\n",
                        username, flightNum, from, to, travelDate, departureTime, flightClass, numTickets, modificationMessage);
            } else {
                // Write the booking as is (no modification message)
                fprintf(tempFile, "%s: Flight Number: %s, From: %s, To: %s, On: %s, At: %s, Class: %s, No of Tickets: %d\n",
                        username, flightNum, from, to, travelDate, departureTime, flightClass, numTickets);
            }
        } else {
            // Write the booking as is for users who are not modifying the flight
            fprintf(tempFile, "%s: Flight Number: %s, From: %s, To: %s, On: %s, At: %s, Class: %s, No of Tickets: %d\n",
                    username, flightNum, from, to, travelDate, departureTime, flightClass, numTickets);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(UB);
    rename("temp.txt", UB);

    if (!foundBookings) {
        printf("\nNo bookings found for the specified flight.\n");
    }
}

void view_all_bookings() {
    FILE *file = fopen("user_bookings.txt", "r"); 
    if (file == NULL) {
        printf("NO BOOKINGS CURRENTLY\n");
        return;
    }

    char line[256]; 
    printf("\t\t----------------ALL BOOKINGS---------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        int isBlank = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isspace(line[i])) {
                isBlank = 0; 
                break;
            }
        }
        if (isBlank) {
            continue; 
        }
        printf("%s", line);
    }

    fclose(file); 
    system("pause");
    system("cls");
}

void searchbookings()
{
	FILE *file = fopen(UB,"r");
	if(file==NULL)
	{
		printf("NO BOOKINGS CURRENTLY");
		return ;
	}
	int found = 0;
	char search[20];
	printf("Enter booking details(Name,destination ,origin etc):");
	scanf("%s",search);
	char line[256];
	while(fgets(line,sizeof(line),file))
	{
		if(strstr(line,search)!=NULL)
		{
			printf(" %s",line);
			found =1;
		}
	}
	fclose(file);
	system("pause");
	system("cls");
	if(!found)
	{
		printf("NO BOOKING FOUND WITH THIS DETAIL\n");
		system("pause");
		system("cls");
		return;
	}
}
