// CS Airline
// cs_airline.c
//
// This program was written by Liren Ding (z5369144).
// on 2022-4-5.
//
// Version 1.0.0 2022-04-02: Initial Release.
//
// Description : Build a booking system capable of 
// managing a single flight with multiple stops, (actually is a Queue).

#include "manifest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// The buffer length is used for reading a single line
#define MAX_STRING_LEN 100

#define COMMAND_PRINT_HELP "help"
#define COMMAND_PRINT_ROUTE "print"
#define COMMAND_SUBROUTE "subroute"
#define COMMAND_CHANGE_ORIGIN "change_origin"
#define COMMAND_BYPASS "bypass"
#define COMMAND_EMERGENCY "emergency"
#define COMMAND_CANCEL "cancel"
#define COMMAND_REVERSE "reverse"
#define COMMAND_ADD_PERSON "add_person"
#define COMMAND_PRINT_MANIFEST "print_manifest"
#define COMMAND_FLIGHT_STATS "stats"

// TODO: you may choose to add additional #defines here.
#define str_are_same 0
#define rate_min_to_hour 60
#define rate_1_to_100 100
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Airports represent 'stops' along the flight path
// These are the 'nodes' of the linked list
struct airport {
    char code[MAX_STRING_LEN];
    int arrival_time;
    int departure_time;
    struct airport *next_airport;
    struct manifest *manifest;
};

// Root flight structure
// This stores the state of the current flight
// (i.e. the head and tail of the linked list)
struct flight {
    struct airport *origin_airport;
    struct airport *dest_airport;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Functions
void remove_newline(char input[MAX_STRING_LEN]);
void do_print_help(void);

void interpret_line(
    char buffer[MAX_STRING_LEN],
    int *val0,
    int *val1,
    char word[MAX_STRING_LEN]
);

// Stage 1 Functions
struct flight *setup_flight(void);
void do_print_airports(struct flight *flight);
void print_one_airport(struct airport *ap);
struct airport *create_airport(
    char code[MAX_STRING_LEN],
    int arrival_time,
    int departure
);

// Stage 2 Functions
void do_subroute(struct flight *flight);
void do_change_origin(struct flight *flight);

// TODO: Your functions prototypes here
int get_one_number(void);
struct airport *get_new_airport(void);
void get_new_airport_code(char airport_code[MAX_STRING_LEN]);


int cal_minute_diff(int start, int end);
// Stage 2.3 Function --- by pass airport
void do_bypass(struct flight *flight);
// Stage 3
void do_emergency(struct flight *flight);
void do_cancel(struct flight *flight);
void do_reverse(struct flight *flight);

// Stage 4
void do_add_person(struct flight *flight);
void do_print_manifest(struct flight *flight);
void do_stats(struct flight *flight);

// free function
void free_curr_airport(struct airport *ap);
void free_flight(struct flight *ap);
void free_next_airport(struct airport *ap);


////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // Stage 1.1
    // TODO: Complete the setup_flight function below
    struct flight *flight = setup_flight();
    // TODO: Fill out the while loop with relevant commands & functions
    // Move into and stay in operational mode until CTRL+D
    printf("Enter Command: ");
    char command_line[MAX_STRING_LEN];
    while (fgets(command_line, MAX_STRING_LEN, stdin) != NULL) {

        remove_newline(command_line);
        if (strcmp(COMMAND_PRINT_HELP, command_line) == str_are_same) {
            // A help command we have implemented for you.
            do_print_help();
        } else if (strcmp(COMMAND_PRINT_ROUTE, command_line) == str_are_same) {
            // Stage 1.2 - TODO: Complete this function below
            do_print_airports(flight);
        } else if (strcmp(COMMAND_SUBROUTE, command_line) == str_are_same) {
            // Stage 2.1 - TODO: Complete this function below
            do_subroute(flight);
        } else if (strcmp(COMMAND_CHANGE_ORIGIN, command_line) == str_are_same) {
            // Stage 2.2 - TODO: Complete this function below
            do_change_origin(flight);
        } else if (strcmp(COMMAND_BYPASS, command_line) == str_are_same) {
            do_bypass(flight);
        } else if (strcmp(COMMAND_EMERGENCY, command_line) == str_are_same) {
            do_emergency(flight);
        } else if (strcmp(COMMAND_CANCEL, command_line) == str_are_same) {
            do_cancel(flight);
            flight = setup_flight();
        } else if (strcmp(COMMAND_REVERSE, command_line) == str_are_same) {
            do_reverse(flight);
        } else if (strcmp(COMMAND_ADD_PERSON, command_line) == str_are_same) {
            do_add_person(flight);
        } else if (strcmp(COMMAND_PRINT_MANIFEST, command_line) == str_are_same) {
            do_print_manifest(flight);
        } else if (strcmp(COMMAND_FLIGHT_STATS, command_line) == str_are_same) {
            do_stats(flight);
        }
        // TODO: Add more conditions here for the remaining commands
        printf("Enter Command: ");
    }
    printf("Goodbye!\n");
    free_flight(flight);
    return 0;
}

// Stage 1.1
// Creates and initialises a flight by asking the user for input.
// Parameters:
//    NONE
//
// Returns:
//     Pointer to the malloc'd flight -- new_flight

struct flight *setup_flight(void) {
    // Create a new, empty flight
    struct flight *new_flight = malloc(sizeof(struct flight));
    new_flight->origin_airport = NULL;
    new_flight->dest_airport = NULL;

    // Read number of stops using fgets
    printf("How many stops will be enroute? ");

    // get number stops
    int num_stops = get_one_number();
    // TODO: For each airport Use fgets to read a line and then use the
    //       provided interpret_line() function to extract information
    for (int i = 0; i < num_stops; i++) {
        // get a new airport 
        struct airport *new = get_new_airport();
        // push back
        // arrival_time check
        if (new->arrival_time > new->departure_time) {
            printf("Departure time cannot be before the arrival time!\n");
            free_curr_airport(new);
        } else if (new_flight->dest_airport != NULL &&
        new->arrival_time < new_flight->dest_airport->departure_time) {
            printf("New arrival time cannot be");
            printf(" before the previous departure time\n");
            free_curr_airport(new);
        } else {
            // case 1 : head insert
            // case 2 : tail insert
            if (new_flight->origin_airport == NULL) {
                new_flight->origin_airport = new_flight->dest_airport = new;
            } else {
                new_flight->dest_airport->next_airport = new;
                new_flight->dest_airport = new;
            }
        }
    }
    return new_flight;
}

// Stage 1.2
// Given a pointer to a flight struct, prints all the info about the route
// Parameters:
//     flight = the flight which contains the flight route to print
// Returns:
//     None
void do_print_airports(struct flight *flight) {

    // TODO: Loop through the flight route and call
    //       the provided print_one_airport function
    printf("ROUTE:\n");
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        print_one_airport(curr);
        curr = curr->next_airport;
    }
    
}

// Stage 1.2
// PROVIDED FUNCTION - DO NOT CHANGE
// Given a pointer to an airport struct,
// prints all the info about the airport
// Parameters:
//     ap = the airport to print
// Returns:
//     None
void print_one_airport(struct airport *ap) {
    printf(
        "%8s:    %04d -> %04d\n",
        ap->code,
        ap->arrival_time,
        ap->departure_time
    );
}

// Stage 1.1
// Given the information about a new airport,
// Uses `malloc` to create memory for it and returns a pointer to
// that memory.
// Parameters:
//     code            = the airport ICAO code
//     arrival_time    = the arrival time of the new airport
//     departure_time  = the departure time of the new airport
// Returns:
//     A pointer to the malloc'd struct airport -- new_airport
struct airport *create_airport(
    char code[MAX_STRING_LEN],
    int arrival_time,
    int departure_time)
{
    // Malloc new struct
    struct airport *new_airport = malloc(sizeof(struct airport));
    struct manifest *new_manifest = create_manifest();
    // initialise airport fields
    strcpy(new_airport->code, code);
    new_airport->arrival_time = arrival_time;
    new_airport->departure_time = departure_time;
    new_airport->next_airport = NULL;
    new_airport->manifest = new_manifest;

    return new_airport;
}

// Stage 2.1
// Calculate Subroute
// Parameters:
//     flight = the flight which contains 
//     the flight subroute to calculate
// Returns:
//     NONE
void do_subroute(struct flight *flight) {
    // get the airport code
    char airport_code[MAX_STRING_LEN];
    printf("Enter airport code: ");
    get_new_airport_code(airport_code);
    int start;
    if (flight->origin_airport != NULL) {
        start = flight->origin_airport->departure_time;
    }
    int end = 0;
    int flag = 0;
    // use the loop to find 
    // if one of the airport has the code
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        if (strcmp(curr->code, airport_code) == str_are_same) {
            end = curr->arrival_time;
            flag = 1;
        }
        curr = curr->next_airport;
    }
    // case : find the same code in airport
    // continue to calculate
    // use var flag to become condition
    if (flag) {
        
        int minute_diff = cal_minute_diff(start, end);
        int hours = minute_diff / rate_min_to_hour;
        int mins = minute_diff % rate_min_to_hour;
        printf("Time for subroute: %d hrs & %d mins\n", hours, mins);
    } else {
        // case : not find the same code in airport
        printf("Desired subroute destination does not exist!\n");
    }
}

// Stage 2.2
// Change Origin
// Parameters:
//     flight = the flight which contains 
//     the flight subroute that can change the origin
// Returns:
//     NONE
void do_change_origin(struct flight *flight) {
    printf("Enter new origin info: ");
    // create new airport 
    struct airport *new = get_new_airport();

    // consider case the flight has no airport
    // insert and terminate function
    if (flight->origin_airport == NULL) {
        printf("Added: %s\n", new->code);
        flight->origin_airport = flight->dest_airport = new;
        return;
    }

    // use loop
    // case : if the code is not unique
    // use return to terminate function
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        if (strcmp(new->code, curr->code) == str_are_same) {
            printf("New airport code is not unique!\n");
            free_curr_airport(new);
            return;
        }
        curr = curr->next_airport;
    }
    // case 1 : the new arrival time is bigger than
    // the new departure time.
    // case 2 : the new departure time is bigger than
    // the original arrival time.
    // case 3 : no error about time order,
    // successful added.
    if (new->arrival_time > new->departure_time) {
        printf("Departure time cannot be before the arrival time!\n");
        free_curr_airport(new);
    } else if (new->departure_time > flight->origin_airport->arrival_time) {
        printf("Departure of new origin cannot be after the arrival");
        printf(" time of the next airport!\n");
        free_curr_airport(new);
    } else {
        printf("Added: %s\n", new->code);
        new->next_airport = flight->origin_airport;
        flight->origin_airport = new;
    }
}

// Stage 2.3
// bypass airport
// Parameters:
//     flight = the flight which contains 
//     the flight to delete input flight
// Returns:
//     NONE
void do_bypass(struct flight *flight) {
    // get one new aiport code
    char airport_code[MAX_STRING_LEN];
    printf("Enter airport code: ");
    get_new_airport_code(airport_code);

    // use loop to find the same name airport
    struct airport *prev = NULL;
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        if (strcmp(curr->code, airport_code) == str_are_same) {
            break;
        } else {
            prev = curr;
            curr = curr->next_airport;
        }
    }
    // connect the curr->next_airport(next) and prev node
    // case 1 : not find
    // case 2 : only one airport
    // case 3 : delete the head node
    // case 4 : delete the tail node
    // case 5 : delete the node in the list
    if (curr == NULL) {
        printf("No airport of that code exists!\n");
    } else if (curr == flight->origin_airport && curr == flight->dest_airport) {
        flight->origin_airport = NULL;
        flight->dest_airport = NULL;
    } else if (curr == flight->origin_airport) {
        flight->origin_airport = curr->next_airport;
        curr->next_airport = NULL;
    } else if (curr == flight->dest_airport) {
        flight->dest_airport = prev;
    } else {
        prev->next_airport = curr->next_airport;
        curr->next_airport = NULL;
    }
    free_curr_airport(curr);
}


// Stage 3.1
// use two parameter hours and emergency hours
// to avoid overdeep nesting
// Parameters:
//     flight = the flight which contains 
//     the flight to run emergency
// Returns:
//     NONE
void do_emergency(struct flight *flight) {
    if (flight->origin_airport == NULL) {
        return;
    }
    // read hour
    printf("How long until emergency: ");
    int hours = get_one_number();
    // case 1 : hours equal to 0, delete all airport 
    // after the head airport, terminate function
    // case 2 : em_hours is bigger than final airport
    // departure_time --- safe
    // case 3 : em_hours is between head and tail airport
    struct airport *curr = flight->origin_airport;
    int emergency_hours = hours * rate_1_to_100;
    emergency_hours += curr->departure_time;
    if (hours == 0) {
        curr->departure_time = 0;
        flight->dest_airport = flight->origin_airport;
        // cancel link and free
        free_next_airport(curr);
        return;
    }
    if (emergency_hours > flight->dest_airport->arrival_time) {
        printf("Flight was safe!\n");
    } else {
        while (curr != NULL) {
            if (curr->arrival_time >= emergency_hours) {
                strcpy(curr->code, "ALT0");
                curr->departure_time = 0;
                curr->arrival_time = emergency_hours;
                flight->dest_airport = curr;
                free_next_airport(curr);
            }
            curr = curr->next_airport;
        }
    }
}

// Stage 3.2
// realize free function
void do_cancel(struct flight *flight) {
    
    //free(flight);
    //flight = NULL;
    free_flight(flight);
    printf("Flight cancelled. Now accepting a new flight:\n");
}

// Stage 3.3
// reverse list
// Equivalent to reversing a singly linked list(in problem set)
// use three pointer --- current, previous, next 
// time complexity O(n)
// Parameters:
//     flight = the flight which contains 
//     the flight to turn back
// Returns:
//     NONE
void do_reverse(struct flight *flight) {
    if (flight->origin_airport == NULL) {
        return;
    }
    if (flight->origin_airport->next_airport == NULL) {
        return;
    }
    struct airport *curr = flight->origin_airport;
    struct airport *next = curr->next_airport;
    struct airport *prev = NULL;
    flight->dest_airport = curr;
    while (curr != NULL) {
        curr->next_airport = prev;

        prev = curr;
        curr = next;
        // because NULL has no NULL->next
        if (next != NULL) {
            next = next->next_airport;
        }
    }
    flight->origin_airport = prev;
}


// Stage 4.1
// input two string, airport_code and person_name(equal to the airport code)
// and one double(using scanf)
// use loop to find the same airport code
// use add_person function to add passenger
void do_add_person(struct flight *flight) {

    printf("Enter the airport code: ");
    char airport_code[MAX_STRING_LEN];
    get_new_airport_code(airport_code);

    printf("Enter the passenger name: ");
    char passeneger_name[MAX_STRING_LEN];
    get_new_airport_code(passeneger_name);

    printf("Enter the passenger weight: ");
    double weight;
    scanf("%lf", &weight);
    getchar();
    if (flight->origin_airport == NULL) {
        printf("No airport of that code exists!\n");
        return;
    }
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        if (strcmp(curr->code, airport_code) == str_are_same) {
            add_person(curr->manifest, passeneger_name, weight);
        }
        curr = curr->next_airport;
    }
}

// Stage 4.2
// use loop to find the same name airport
// if find then use print_manifest to print and then
// terminate the function
// if not find then print No airport of that code exists!
void do_print_manifest(struct flight *flight) {
    printf("Enter the airport code: ");
    char airport_code[MAX_STRING_LEN];
    get_new_airport_code(airport_code);
    struct airport *curr = flight->origin_airport;
    while (curr != NULL) {
        if (strcmp(curr->code, airport_code) == str_are_same) {
            print_manifest(curr->manifest);
            return;
        }
        curr = curr->next_airport;
    }
    printf("No airport of that code exists!\n");
}

// Stage 4.3
// do stats
// union all the people to the final airport
void do_stats(struct flight *flight) {
    if (flight->origin_airport == NULL) {
        return;
    }
    struct airport *curr = flight->origin_airport;
    struct airport *next = curr->next_airport;
    while (next != NULL) {
        join_manifest(curr->manifest, next->manifest);
        curr = curr->next_airport;
        next = next->next_airport;
    }
    printf("Final manifest:\n");
    print_manifest(curr->manifest);
    printf("Total weight: %f\n", manifest_weight(curr->manifest));


}


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////  HELPER FUNCTIONS  //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will remove and first newline it sees.
// The newline character wil be replaced with a null terminator ('\0')
// Parameters:
//     flight  = the flight to move people along of
// Returns:
//     None
void remove_newline(char input[MAX_STRING_LEN]) {

    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0') {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}


// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the following foramt: [integer0] [integer1] [string]
// This function will extract the relevant values into the given pointer variables.
// The function will also remove any newline characters.
//
// For example, if given: "0135 0545 YSSY"
// The function will put the integer values
//     135 into the val1 pointer
//     545 into the val2 pointer
// And will copy a null terminated string
//     "YSSY" into the 'word' array
//
// If you are interested, `strtok` is a function which takes a string,
// and splits it up into before and after a "token" (the second argument)
//
// Parameters:
//     buffer  = A null terminated string in the following format
//               [integer0] [integer1] [string]
//     val0    = A pointer to where [integer0] should be stored
//     val1    = A pointer to where [integer1] should be stored
//     word    = An array for the [string] to be copied into
// Returns:
//     None
void interpret_line(
    char buffer[MAX_STRING_LEN],
    int *val0,
    int *val1,
    char word[MAX_STRING_LEN]
) {

    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as int
    char *val0_str = strtok(buffer, " ");
    if (val0_str != NULL) {
        *val0 = atoi(val0_str);
    } else {
        *val0 = -1;
    }

    // Extract value 2 as int
    char *val1_str = strtok(NULL, " ");
    if (val1_str != NULL) {
        *val1 = atoi(val1_str);
    } else {
        *val1 = -1;
    }

    char *word_str = strtok(NULL, " ");
    if (word_str != NULL) {
        // Extract word
        strcpy(word, word_str);
    }

    if (val0_str == NULL || val1_str == NULL || word_str == NULL) {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }

}

// help menu
void do_print_help(void) {
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| Command Name      | How to Use                                                             |\n");
    printf("+===================+========================================================================+\n");
    printf("| PRINT ROUTE       | Enter command: print                                                   |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| SUBROUTE          | Enter command: subroute                                                |\n");
    printf("|                   | Enter airport code: [AIRPORT CODE]                                     |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| CHANGE ORIGIN     | Enter command: change_origin                                           |\n");
    printf("|                   | Enter new origin info: [ARRIVAL TIME] [DEPARTURE TIME] [AIRPORT CODE]  |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| BYPASS            | Enter command: bypass                                                  |\n");
    printf("|                   | Enter airport code: [AIRPORT CODE]                                     |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| EMERGENCY         | Enter command: emergency                                               |\n");
    printf("|                   | How long until emergency: [TIME IN HOURS]                              |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| CANCEL            | Enter command: cancel                                                  |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| REVERSE           | Enter command: reverse                                                 |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("|                   | Enter command: add_person                                              |\n");
    printf("| ADD PERSON        | Enter the airport code: [AIRPORT CODE]                                 |\n");
    printf("|                   | Enter the passenger name: [NAME]                                       |\n");
    printf("|                   | Enter the passenger weight: [WEIGHT]                                   |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| PRINT MANIFEST    | Enter command: print_manifest                                          |\n");
    printf("|                   | Enter the airport code: [AIRPORT CODE]                                 |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
    printf("| FLIGHT STATISTICS | Enter command: stats                                                   |\n");
    printf("+-------------------+------------------------------------------------------------------------+\n");
}

// too many repetitive places in the assignment so I extract
// input one sentence to get
// get a new airport
// Parameters:
//     NONE
// Returns:
//     A pointer to the malloc'd struct airport
struct airport *get_new_airport(void) {
    char sentence[MAX_STRING_LEN] = {0};
    fgets(sentence, MAX_STRING_LEN, stdin);
    // printf("%s", words);
    // initial data 
    int val0 = 0;
    int val1 = 0;
    char word[MAX_STRING_LEN] = {0};
    // interpret sentence and extract data
    // feed actual parameter into it
    interpret_line(sentence, &val0, &val1, word);
    // initial struct airport and remove the data into it
    struct airport *new = create_airport(word, val0, val1);
    return new;
}

// too many repetitive places in the assignment so I extract
// input the the code and use fgets to 
// modify the aiport_code
void get_new_airport_code(char airport_code[MAX_STRING_LEN]) {
    fgets(airport_code, MAX_STRING_LEN, stdin);
    remove_newline(airport_code);
}

// get one number 
// there are many places need the it(all them are same)
// so I extract it
int get_one_number(void) {
    char input_line[MAX_STRING_LEN] = {0};
    fgets(input_line, MAX_STRING_LEN, stdin);

    return atoi(input_line);
}


// use start and end parameter to calculate
// the minute difference and return it
int cal_minute_diff(int start, int end) {
    int hours = (end / rate_1_to_100) - (start / rate_1_to_100);
    int mins = (end % rate_1_to_100) - (start % rate_1_to_100);
    int minute_diff = hours * rate_min_to_hour + mins;
    if (minute_diff < 0) {
        minute_diff *= -1;
    }
    return minute_diff;
}

// free current airport
// free all the airport after the input airport
// include the input airport
// Equivalent to the slow and fast pointer (pointer to same)
// by the fast pointer go first and free the
// slow pointer and then let slow pointer points to which 
// faster pointer points to.(This is one cycle)
void free_curr_airport(struct airport *curr) {
    if (curr != NULL) {
        struct airport *prev = curr;
        while (curr != NULL) {
            prev = curr;
            curr = curr->next_airport;
            delete_manifest(prev->manifest);
            free(prev);
            prev = NULL;
        }
    }
}
// free next airport 
// free all the airport after the input airport
// except the input airport
// using the free_curr_airport
void free_next_airport(struct airport *ap) {
    if (ap->next_airport != NULL) {
        struct airport *next = ap->next_airport;
        ap->next_airport = NULL;
        free_curr_airport(next);
    }
}

// free the flight
// use the free_curr_airport to free all node in the
// flight and then free the flight
void free_flight(struct flight *ap) {
    if (ap != NULL) {
        if (ap->origin_airport == NULL) {
            free(ap->origin_airport);
            free(ap->dest_airport);
        } else {
            free_curr_airport(ap->origin_airport);
        }
        free(ap);
        ap = NULL;
    }
}



