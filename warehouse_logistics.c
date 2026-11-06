#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define numOfZones 4   
#define numOfItems 5    

// Structure 
typedef struct {
    char  itemName[50];
    char  supplier[50];
    int   cargoID;
    float zoneWeights[numOfZones]; 
    int   totalWeight;               
    char  status[12];               
} CargoRecord;

// Function prototypes for Warehouse Logistics 
void registerCargo(CargoRecord database[], int *count, int maxCap);
void searchUpdateCargo(CargoRecord database[], int count);
void topCargoItems(CargoRecord database[], int count);

// Q1: Array Processing 
// Low Level Processing Functions utilize the tracking IDs from the Warehouse Cargo Management System and performs the operations
// Function prototypes for Array Proccessing 
void set_array(int arr[], int length);
bool rem_align(int arr[], int *length, int pos);
bool insert_align(int arr[], int *length, int pos, int value, int maxCap);
bool reshape(int arr[], int length, int r, int c, int arr2d[r][c]);
void print_trans_matrix(int r, int c, int arr2d[r][c]);
bool found_duplicate(int arr[], int length);
bool flip_array(int arr[], int length, int flipped[]);

// Week 7 integration with the Warehouse Cargo Management System 
void print_array(int arr[], int length);
void arrayOperations(CargoRecord database[], int count);

// Main 
// Q2: Warehouse Cargo Management System 
int main() {
    int maxCap = numOfItems * 2;       
    CargoRecord database[maxCap];
    int count = numOfItems;
    int choice;

    for (int i = 0; i < count; i++) {
        database[i].cargoID = 101 + i;
        sprintf(database[i].itemName, "Cargo_%d", i + 1);
        sprintf(database[i].supplier, "Supplier_%c", 'A' + i);
        
        for (int z = 0; z < numOfZones; z++) {
            database[i].zoneWeights[z] = -1;
        }
        database[i].totalWeight = -1;
        strcpy(database[i].status, "undefined");
    }

    do {
        // Main System Menu 
        printf("----------------------------------------------------------------------\n");
        printf("                          MAIN SYSTEM MENU                            \n");
        printf("----------------------------------------------------------------------\n");

        printf("1. Register Cargo Item (Register Zone Weights)\n");
        printf("2. Search & Update Cargo Item (by ID or Supplier)\n");
        printf("3. Display Top Weight Cargo Item(s)\n");
        printf("4. Display ALL Warehouse Cargo Records\n");
        printf("5. Low-Level Processing Array Functions\n");
        printf("0. Exit Application\n");

        printf("----------------------------------------------------------------------\n");
        printf("Enter option (0-5):");
        
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5) {
            while (getchar() != '\n');
            printf("[ERROR] Enter a number from 0 to 5: ");
        }

        if (choice == 1) {
            registerCargo(database, &count, maxCap);
        } 
        
        else if (choice == 2) {
            searchUpdateCargo(database, count);
        } 
        
        else if (choice == 3) {
            topCargoItems(database, count);
        } 
        
        else if (choice == 4) {
            // Displaying ALL Warehouse Cargo Records 
            printf("\n=========================================================================\n");
            printf("                     CURRENT WAREHOUSE FREIGHT DATABASE\n");
            printf("=========================================================================\n");
            printf("  %-5s | %-12s | %-12s | %-8s | %-9s | %s\n",
                   "ID", "Item Name", "Supplier", "Total Wt", "Status", "Zone Weights");
            printf("-------------------------------------------------------------------------\n");
            for (int i = 0; i < count; i++) {
                printf("  %-5d | %-12s | %-12.10s | %-8d | %-9s | [",
                       database[i].cargoID, database[i].itemName, database[i].supplier,
                       database[i].totalWeight, database[i].status);
                for (int z = 0; z < numOfZones; z++) {
                    if (database[i].zoneWeights[z] < 0) {
                        printf(" N/A");
                    } else {
                        printf(" %.1f", database[i].zoneWeights[z]);
                    }
                }
                printf(" ]\n");
            }
            printf("=========================================================================\n");
        }

        else if (choice == 5) {
            arrayOperations(database, count);
        }
    }while (choice != 0); 

    printf("Exiting Application...\n");
    return 0;
}

void registerCargo(CargoRecord database[], int *count, int maxCap) {
    int id, found = -1, answer;
    float sum = 0;
    int allEntered = 1;

    printf("\n--- CARGO REGISTRATION (ZONE WEIGHTS ENTRY) ---\n");
    printf("Enter Cargo Item ID to register: ");
    while (scanf("%d", &id) != 1 || id < 1) {
        while (getchar() != '\n');
        printf("Invalid. Enter a positive whole number: ");
    }

    for (int i = 0; i < *count; i++) {
        if (database[i].cargoID == id) {
            found = i;
        }
    }

    if (found == -1) {
        if (*count >= maxCap) {
            printf("Database is full.\n");
            return;
        }
        found = *count;
        database[found].cargoID = id;
        printf("Enter Item Name: ");
        scanf(" %49[^\n]", database[found].itemName);
        printf("Enter Supplier Name: ");
        scanf(" %49[^\n]", database[found].supplier);
        (*count)++;
    }

    printf("Selected Cargo: ID=%d, Name=%s, Supplier=%s\n",
           database[found].cargoID, database[found].itemName, database[found].supplier);

    for (int i = 0; i < numOfZones; i++) {
        printf("Do you want to input weight for Zone %d? (1 = Yes, 0 = No): ", i);
        while (scanf("%d", &answer) != 1 || (answer != 0 && answer != 1)) {
            while (getchar() != '\n');
            printf("Invalid. Enter 1 (Yes) or 0 (No): ");
        }

        if (answer == 1) {
            printf("Enter weight for Zone %d (kg): ", i);
            while (scanf("%f", &database[found].zoneWeights[i]) != 1 ||
                   database[found].zoneWeights[i] < 0) {
                while (getchar() != '\n');
                printf("Invalid. Enter a weight of 0 or more: ");
            }
            sum += database[found].zoneWeights[i];
        } 
        
        else {
            database[found].zoneWeights[i] = -1;
            allEntered = 0;
        }
    }

    if (allEntered) {
        database[found].totalWeight = (int)(sum + 0.5);     
        if (database[found].totalWeight >= 85) 
            strcpy(database[found].status, "HD");

        else if (database[found].totalWeight >= 75) 
            strcpy(database[found].status, "D");

        else if (database[found].totalWeight >= 65) 
            strcpy(database[found].status, "C");

        else if (database[found].totalWeight >= 50) 
            strcpy(database[found].status, "P");

        else                                        
            strcpy(database[found].status, "F");
    } 
    
    else {
        database[found].totalWeight = -1;
        strcpy(database[found].status, "undefined");
    }

    printf("[SUCCESS] Updated Record: Total Weight = %d kg, Status = %s\n",
           database[found].totalWeight, database[found].status);
}


void searchUpdateCargo(CargoRecord database[], int count) {
    int choice, found = -1, update, answer;
    float sum = 0;
    int allEntered = 1;

    printf("\n--- SEARCH & UPDATE CARGO RECORDS ---\n");
    printf("Search by: 1. Item ID   2. Supplier / Item Name\n");
    printf("Select choice (1-2): ");
    while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        while (getchar() != '\n');
        printf("Invalid. Enter 1 or 2: ");
    }

    if (choice == 1) {
        int id;
        printf("Enter Item ID: ");

        while (scanf("%d", &id) != 1 || id < 1) {
            while (getchar() != '\n');
            printf("Invalid. Enter a positive whole number: ");
        }
        for (int i = 0; i < count; i++) {
            if (database[i].cargoID == id) {
                found = i;
            }
        }
    } else {
        char term[50];
        printf("Enter Supplier or Item Name (case-insensitive): ");
        scanf(" %49[^\n]", term);
        
        for (int i = 0; i < count; i++) {
            if (strcasecmp(database[i].supplier, term) == 0 ||
                strcasecmp(database[i].itemName, term) == 0) {
                found = i;
            }
        }
    }

    if (found == -1) {
        printf("unfound\n");
        return;
    }

    printf("\n[MATCH FOUND] ItemID: %d | Name: %s | Supplier: %s | Total Weight: %d kg | Status: %s\n",
           database[found].cargoID, database[found].itemName, database[found].supplier,
           database[found].totalWeight, database[found].status);

    printf("\nDo you want to update this record? (1 = Yes, 0 = No): ");
    while (scanf("%d", &update) != 1 || (update != 0 && update != 1)) {
        while (getchar() != '\n');
        printf("Invalid. Enter 1 (Yes) or 0 (No): ");
    }

    if (update == 0) {
        return;
    }

    printf("Enter new Item Name: ");
    scanf(" %49[^\n]", database[found].itemName);

    printf("Enter new Supplier Name: ");
    scanf(" %49[^\n]", database[found].supplier);

    int id, used;
    do {
        used = 0;
        printf("Enter new Item ID: ");
        while (scanf("%d", &id) != 1 || id < 1) {
            while (getchar() != '\n');
            printf("Invalid. Enter a positive whole number: ");
        }
        for (int i = 0; i < count; i++) {
            if (i != found && database[i].cargoID == id) {
                used = 1;
            }
        }
        if (used) {
            printf("That ID is already used.\n");
        }
    } while (used);

    database[found].cargoID = id;

    printf("Do you want to update zone weights? (1 = Yes, 0 = No): ");
    while (scanf("%d", &update) != 1 || (update != 0 && update != 1)) {
        while (getchar() != '\n');
        printf("Invalid. Enter 1 (Yes) or 0 (No): ");
    }

    if (update == 1) {
        for (int i = 0; i < numOfZones; i++) {
            printf("Do you want to input weight for Zone %d? (1 = Yes, 0 = No): ", i);

            while (scanf("%d", &answer) != 1 || (answer != 0 && answer != 1)) {
                while (getchar() != '\n');
                printf("Invalid. Enter 1 (Yes) or 0 (No): ");
            }

            if (answer == 1) {
                printf("Enter weight for Zone %d (kg): ", i);

                while (scanf("%f", &database[found].zoneWeights[i]) != 1 || database[found].zoneWeights[i] < 0) {

                    while (getchar() != '\n');
                    printf("Invalid. Enter a weight of 0 or more: ");
                }
                sum += database[found].zoneWeights[i];
            }

            else {
                database[found].zoneWeights[i] = -1;
                allEntered = 0;
            }
        }

        if (allEntered) {
            database[found].totalWeight = (int)(sum + 0.5);
            if (database[found].totalWeight >= 85)
                strcpy(database[found].status, "HD");

            else if (database[found].totalWeight >= 75)
                strcpy(database[found].status, "D");

            else if (database[found].totalWeight >= 65)
                strcpy(database[found].status, "C");

            else if (database[found].totalWeight >= 50)
                strcpy(database[found].status, "P");

            else
                strcpy(database[found].status, "F");

        }

        else {
            database[found].totalWeight = -1;
            strcpy(database[found].status, "undefined");
        }
    }

    printf("[SUCCESS] Record updated successfully.\n");
}

void topCargoItems(CargoRecord database[], int count) {
    int max = -1;

    for (int i = 0; i < count; i++) {
        if (database[i].totalWeight > max) {
            max = database[i].totalWeight;
        }
    }

    if (max == -1) {
        printf("No record has a complete total weight yet.\n");
        return;
    }

    printf("Highest total weight: %d kg\n", max);
    
    for (int i = 0; i < count; i++) {
        
        if (database[i].totalWeight == max) {
            printf("ID: %d | Name: %s | Supplier: %s | Total: %d | Status: %s | Zones:",
                   database[i].cargoID, database[i].itemName, database[i].supplier,
                   database[i].totalWeight, database[i].status);
            
                   for (int z = 0; z < numOfZones; z++) {
                printf(" %.1f", database[i].zoneWeights[z]);
            }
            printf("\n");
        }
    }
}

// ======================= Q1: ARRAY FUNCTIONS =======================

// arr[i] = i for 0 <= i < length
void set_array(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = i;
    }
}

// Deletes element at pos by shifting left, then decrements *length
bool rem_align(int arr[], int *length, int pos) {
    if (pos < 0 || pos >= *length) {
        return false;
    }
    for (int i = pos; i < *length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*length)--;
    return true;
}

// Inserts value at pos by shifting right, then increments *length
bool insert_align(int arr[], int *length, int pos, int value, int maxCap) {
    if (pos < 0 || pos > *length || *length >= maxCap) {
        return false;
    }
    for (int i = *length; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    (*length)++;
    return true;
}

// Copies 1D array into r x c grid, row by row
bool reshape(int arr[], int length, int r, int c, int arr2d[r][c]) {
    if (length != r * c) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        arr2d[i / c][i % c] = arr[i];
    }
    return true;
}

// Prints grid column by column
void print_trans_matrix(int r, int c, int arr2d[r][c]) {
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            printf("%5d", arr2d[i][j]);
        }
        printf("\n");
    }
}

// Returns true if any value appears more than once
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

// flipped[i] = arr[length - 1 - i]
bool flip_array(int arr[], int length, int flipped[]) {
    for (int i = 0; i < length; i++) {
        flipped[i] = arr[length - 1 - i];
    }
    return true;
}


// Week 7 Additions

void print_array(int arr[], int length) {
    printf("[");
    for (int i = 0; i < length; i++) {
        printf(" %d", arr[i]);
    }
    printf(" ]  (length %d)\n", length);
}

// Applies the Q1 array functions to the cargo ID tracking stream
void arrayOperations(CargoRecord database[], int count) {
    int maxCap = numOfItems * 2;
    int stream[numOfItems * 2];
    int length = count;
    int choice, pos, value;

    // Build the stream from the cargo IDs in the database
    for (int i = 0; i < count; i++) {
        stream[i] = database[i].cargoID;
    }

    do {
        printf("\n--- ARRAY OPERATIONS (CARGO ID TRACKING STREAM) ---\n");
        printf("Current stream: ");
        print_array(stream, length);
        printf("1. Reset stream to index values (set_array)\n");
        printf("2. Delete element at position (rem_align)\n");
        printf("3. Insert element at position (insert_align)\n");
        printf("4. Flip stream (flip_array)\n");
        printf("5. Check for duplicate IDs (found_duplicate)\n");
        printf("6. Reshape into aisle x shelf grid (reshape, print_trans_matrix)\n");
        printf("0. Back to main menu\n");
        printf("Select option (0-6): ");

        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 6) {
            while (getchar() != '\n');
            printf("[ERROR] Enter a number from 0 to 6: ");
        }

        if (choice == 1) {
            set_array(stream, length);
            printf("[SUCCESS] Stream reset: ");
            print_array(stream, length);
        }

        else if (choice == 2) {
            printf("Enter position to delete (0-%d): ", length - 1);
            while (scanf("%d", &pos) != 1) {
                while (getchar() != '\n');
                printf("Invalid. Enter a whole number: ");
            }
            if (rem_align(stream, &length, pos)) {
                printf("[SUCCESS] Element at position %d deleted: ", pos);
                print_array(stream, length);
            } else {
                printf("[ERROR] Position %d is out of bounds. Stream unchanged.\n", pos);
            }
        }

        else if (choice == 3) {
            printf("Enter position to insert at (0-%d): ", length);
            while (scanf("%d", &pos) != 1) {
                while (getchar() != '\n');
                printf("Invalid. Enter a whole number: ");
            }
            printf("Enter value to insert: ");
            while (scanf("%d", &value) != 1) {
                while (getchar() != '\n');
                printf("Invalid. Enter a whole number: ");
            }
            if (insert_align(stream, &length, pos, value, maxCap)) {
                printf("[SUCCESS] %d inserted at position %d: ", value, pos);
                print_array(stream, length);
            } else {
                printf("[ERROR] Cannot insert: invalid position or stream is full (max %d).\n", maxCap);
            }
        }

        else if (choice == 4) {
            int flipped[numOfItems * 2];
            flip_array(stream, length, flipped);
            printf("Original: ");
            print_array(stream, length);
            printf("Flipped:  ");
            print_array(flipped, length);
        }

        else if (choice == 5) {
            if (found_duplicate(stream, length)) {
                printf("[WARNING] Duplicate tracking ID found in the stream.\n");
            } else {
                printf("[OK] No duplicate tracking IDs found.\n");
            }
        }

        else if (choice == 6) {
            int r, c;
            printf("Enter number of aisles (rows): ");
            while (scanf("%d", &r) != 1 || r < 1) {
                while (getchar() != '\n');
                printf("Invalid. Enter a positive whole number: ");
            }
            printf("Enter number of shelves (columns): ");
            while (scanf("%d", &c) != 1 || c < 1) {
                while (getchar() != '\n');
                printf("Invalid. Enter a positive whole number: ");
            }

            int grid[r][c];
            if (reshape(stream, length, r, c, grid)) {
                printf("[SUCCESS] Stream reshaped into %d x %d grid.\n", r, c);
                printf("Transposed layout (column by column):\n");
                print_trans_matrix(r, c, grid);
            } else {
                printf("[ERROR] Cannot reshape: %d items do not fit a %d x %d grid.\n", length, r, c);
            }
        }
    } while (choice != 0);
}
