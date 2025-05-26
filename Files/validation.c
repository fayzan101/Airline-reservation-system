#include<stdio.h>
#include <time.h>
#include<string.h>
#include<stdlib.h>
int validDepartureDate(int day, int month, int year, int current_day, int current_month, int current_year) {
    if (year > current_year) {
        return 1; 
    } else if (year == current_year) {
        if (month > current_month) {
            return 1; 
        } else if (month == current_month) {
            if (day >= current_day) {
                return 1; 
            }
        }
    }
    return 0; 
}
int validDepartureTime(int hour, int minute, int day, int month, int year, int current_day, int current_month, int current_year) {
    int current_hour, current_minute;
    getCurrentTime(&current_hour, &current_minute);
    if (year > current_year || 
        (year == current_year && month > current_month) || 
        (year == current_year && month == current_month && day > current_day)) {
        return 1;  
    }
    if (day == current_day && month == current_month && year == current_year) {
        if (hour > current_hour || (hour == current_hour && minute >= current_minute)) {
            return 1; 
        }
    }
    printf("Invalid departure time: Time cannot be in the past!\n");
    return 0;
}


int calculateAge(int birth_day, int birth_month, int birth_year, int current_day, int current_month, int current_year) {
    int ageYears = current_year - birth_year;
    if (birth_month > 12 || (birth_month == 12 && birth_day > 31)) {
        printf("Invalid Birth Date\n");
        return -1; 
    }

    if (birth_month > current_month || (birth_month == current_month && birth_day > current_day)) {
        ageYears--;
    }

    return ageYears;
}
int isLeapYear(int year)
{
	return (year%4==0 && (year%100!=0 || year %400==0 ));
}
int validateBirthDate(int day, int month, int year)
{
	int current_year,current_month,current_day;
const char *month_names[] =
{
        "Invalid", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
if(day == 0 && month == 0 & year == 0)
{
	return 0;
}
    if (year < 1900 || year > 2024)
{
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (month == 2) {
        if (isLeapYear(year) && day > 29) {
            printf("\t\tSince the Birth Year is a Leap Year, February can have up to 29 days only!\n");
            return 0;
        } else if (!isLeapYear(year) && day > 28) {
            printf("\t\tSince the Birth Year is not a Leap Year, February can have up to 28 days only!\n");
            return 0;
        }
    } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        printf("\t\t%s month can have only 30 Days !\n",month_names[month]);
        return 0;
} else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||month == 10 || month == 12) && day > 31){
printf("\t\t%s month can have only 31 Days !\n",month_names[month]);
}
   getCurrentDate(&current_day,&current_month,&current_year);
    if (year > current_year || 
        (year == current_year && month > current_month) || 
        (year == current_year && month == current_month && day > current_day)) {
        return 0;
    }
return 1;
}
int calculateTravelFrequency(const char* username) {
    FILE* fp = fopen("user_bookings.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open bookings file.\n");
        return 0;
    }

    int frequency = 0;
    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, username) != NULL) {
            frequency++;
        }
    }
    fclose(fp);
    return frequency;
}
const char* getUserStatus(int age, int travelFrequency) {
	if (travelFrequency >= 10) return "Platinum";
    else if (travelFrequency >= 7) return "Gold";
    else if (travelFrequency >= 4) return "Silver";
    else return "Bronze";
}
const char* getUserPerks(const char* status) {
	if (strcmp(status, "Platinum") == 0) {
        return "Priority boarding, two extra baggages, free lounge access, cashback.";
    } else if (strcmp(status, "Gold") == 0) {
        return "Priority boarding, extra baggage, free lounge access.";
    } else if (strcmp(status, "Silver") == 0) {
        return "Priority check-in, extra baggage allowance.";
    } else {
        return "Basic perks like online check-in.";
    }
}
void getCurrentDate(int* day, int* month, int* year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *day = tm.tm_mday;
    *month = tm.tm_mon + 1; 
    *year = tm.tm_year + 1900; 
}
void getCurrentTime(int* hour, int* minute) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *hour = tm.tm_hour;
    *minute = tm.tm_min;
}
