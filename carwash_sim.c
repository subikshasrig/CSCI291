#include <stdio.h>

/* Wash Package Specifications and Resource Requirements */

/* Basic Eco Wash Package */
#define BASIC_WATER 20
#define BASIC_SOAP 100
#define BASIC_WAX 0

/* Deluxe Foam Wash Package */
#define DELUXE_WATER 35
#define DELUXE_SOAP 250
#define DELUXE_WAX 50

/* Premium Shine and Wax Wash Package */
#define PREMIUM_WATER 50
#define PREMIUM_SOAP 300
#define PREMIUM_WAX 150

/* Water Supply */
#define WATER_SUPPLY_INITIAL_INVENTORY 150
#define WATER_SUPPLY_LOW_SUPPLY_THRESHOLD 30
#define WATER_SUPPLY_MAX_CAPACITY 300

/* Soap Concentrate */
#define SOAP_CONCENTRATE_INITIAL_INVENTORY 800
#define SOAP_CONCENTRATE_LOW_SUPPLY_THRESHOLD 200
#define SOAP_CONCENTRATE_MAX_CAPACITY 2000

/* Liquid Wax */
#define LIQUID_WAX_INITIAL_INVENTORY 400
#define LIQUID_WAX_LOW_SUPPLY_THRESHOLD 50
#define LIQUID_WAX_MAX_CAPACITY 1000

/* Global Variables */

float water_level = WATER_SUPPLY_INITIAL_INVENTORY;
float soap_level = SOAP_CONCENTRATE_INITIAL_INVENTORY;
float wax_level = LIQUID_WAX_INITIAL_INVENTORY;

float basic_price = 15.00;
float deluxe_price = 25.00;
float premium_price = 40.00;

float total_sales_revenue = 0.00;

/* Function Prototypes */

void displayMainMenu(void);
void customerMode(void);
int isPackageAvailable(int pkg);
void processPayment(float price, float reqWater, float reqSoap, float reqWax, int packageType);
void checkLowResourceAlerts(void);
void adminMode(void);
void displayInventoryAndSales(void);
void replenishIngredients(void);
void changePackagePrices(void);
void resetSalesRevenue(void);

/* Main Function */

int main(void)
{
    int choice;

    printf("====================================================\n");
    printf(" WELCOME TO THE AUTOMATED CAR WASH CONTROLLER SYSTEM\n");
    printf("====================================================\n");

    while (1)
    {
        displayMainMenu();

        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                customerMode();
                break;

            case 2:
                adminMode();
                break;

            case 3:
                printf("\nThank you for using the "
                       "Automated Car Wash Controller System!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

/* Display Main System Menu */

void displayMainMenu(void)
{
    printf("\n");
    printf("----------------------------------------------------\n");
    printf("                  MAIN SYSTEM MENU\n");
    printf("----------------------------------------------------\n");

    printf(" 1. Purchase a Car Wash Package (Customer Mode)\n");
    printf(" 2. Maintenance & Operations (Admin Mode)\n");
    printf(" 3. Exit Application\n");

    printf("----------------------------------------------------\n");
}

/* Customer Mode */

void customerMode(void)
{
    int choice;
    int confirm;

    while (1)
    {
        printf("\n");
        printf("----------------------------------------------------\n");
        printf("             AVAILABLE CAR WASH PACKAGES\n");
        printf("----------------------------------------------------\n");

        printf(" 1. Basic Eco Wash          : AED %.2f",
               basic_price);

        if (isPackageAvailable(1))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf(" 2. Deluxe Foam Wash        : AED %.2f",
               deluxe_price);

        if (isPackageAvailable(2))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf(" 3. Premium Shine & Wax     : AED %.2f",
               premium_price);

        if (isPackageAvailable(3))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf(" 0. Cancel & Return to Main Menu\n");

        printf("----------------------------------------------------\n");
        printf("Select a wash package (0-3): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        if (choice == 0)
            return;

        if (choice < 1 || choice > 3)
        {
            printf("Invalid package selection. Please try again.\n");
            continue;
        }

        if (!isPackageAvailable(choice))
        {
            printf("[UNAVAILABLE - Low Supplies] Please select another package.\n");
            continue;
        }

        printf("\nYou selected option %d. Confirm order? (1 = Yes, 0 = No/Re-select): ", choice);

        if (scanf("%d", &confirm) != 1)
        {
            printf("Invalid input. Please enter 1 or 0.\n");

            while (getchar() != '\n');
            continue;
        }

        if (confirm == 0)
            continue;

        if (confirm != 1)
        {
            printf("Invalid confirmation choice.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                processPayment(basic_price, BASIC_WATER, BASIC_SOAP, BASIC_WAX, 1);
                break;

            case 2:
                processPayment(deluxe_price, DELUXE_WATER, DELUXE_SOAP, DELUXE_WAX, 2);
                break;

            case 3:
                processPayment(premium_price, PREMIUM_WATER, PREMIUM_SOAP, PREMIUM_WAX, 3);
                break;
        }

        return;
    }
}

/* Check Package Availability */

int isPackageAvailable(int pkg)
{
    switch (pkg)
    {
        case 1:
            return water_level >= BASIC_WATER && soap_level >= BASIC_SOAP && wax_level >= BASIC_WAX;

        case 2:
            return water_level >= DELUXE_WATER && soap_level >= DELUXE_SOAP && wax_level >= DELUXE_WAX;

        case 3:
            return water_level >= PREMIUM_WATER && soap_level >= PREMIUM_SOAP && wax_level >= PREMIUM_WAX;

        default:
            return 0;
    }
}

/* Process Customer Payment */

void processPayment(float price, float reqWater, float reqSoap, float reqWax, int packageType)
{
    float coin;
    float totalInserted = 0.00;
    float remaining;
    float change;

    printf("\n");
    printf("====================================================\n");
    printf("PAYMENT PROCESS: ");

    switch (packageType)
    {
        case 1:
            printf("Basic Eco Wash\n");
            break;

        case 2:
            printf("Deluxe Foam Wash\n");
            break;

        case 3:
            printf("Premium Shine & Wax\n");
            break;

        default:
            printf("Unknown Package\n");
            break;
    }

    printf("TOTAL AMOUNT DUE: AED %.2f\n", price);
    printf("Accepted Coins : 1.00 AED, 0.50 AED, 0.25 AED\n");
    printf("====================================================\n");

    while (totalInserted < price)
    {
        remaining = price - totalInserted;

        printf("\nOutstanding Balance : AED %.2f\n", remaining);
        printf("Insert Coin (1.0, 0.50, 0.25): ");

        if (scanf("%f", &coin) != 1)
        {
            printf("[REJECTED] Invalid input. Please collect your coin.\n");

            while (getchar() != '\n');
            continue;
        }

        if (coin != 1.00 && coin != 0.50 && coin != 0.25)
        {
            printf("[REJECTED] Invalid coin (AED %.2f). Please collect your coin.\n", coin);
            continue;
        }

        totalInserted += coin;

        printf("[ACCEPTED] Coin AED %.2f added. Total Paid: AED %.2f\n", coin, totalInserted);
    }

    change = totalInserted - price;

    /* Deduct Resources */

    water_level -= reqWater;
    soap_level -= reqSoap;
    wax_level -= reqWax;

    /* Update Sales Revenue */

    total_sales_revenue += price;

    printf("\n\n");
    printf("====================================================\n");
    printf("SUCCESS! DISPENSING WASH SERVICE: ");

    switch (packageType)
    {
        case 1:
            printf("Basic Eco Wash\n");
            break;

        case 2:
            printf("Deluxe Foam Wash\n");
            break;

        case 3:
            printf("Premium Shine & Wax\n");
            break;

        default:
            printf("Unknown Package\n");
            break;
    }

    printf("----------------------------------------------------\n");
    printf("Package Price : AED %.2f\n", price);
    printf("Total Paid    : AED %.2f\n", totalInserted);
    printf("Change Due    : AED %.2f\n", change);
    printf("====================================================\n");

    printf("Please drive your vehicle into the bay. Thank you!\n");

    checkLowResourceAlerts();
}

/* Check Low Resource Alerts */

void checkLowResourceAlerts(void)
{
    if (water_level <= WATER_SUPPLY_LOW_SUPPLY_THRESHOLD)
    {
        printf("\n[OPERATOR ALERT] Water supply is low: %.1f L\n", water_level);
    }

    if (soap_level <= SOAP_CONCENTRATE_LOW_SUPPLY_THRESHOLD)
    {
        printf("\n[OPERATOR ALERT] Soap concentrate is low: %.1f mL\n", soap_level);
    }

    if (wax_level <= LIQUID_WAX_LOW_SUPPLY_THRESHOLD)
    {
        printf("\n[OPERATOR ALERT] Liquid wax is low: %.1f mL\n", wax_level);
    }
}

/* Administrator Mode */

void adminMode(void)
{
    int password;
    int choice;

    printf("\n");
    printf("----------------------------------------------------\n");
    printf("              ADMIN MAINTENANCE MODE ACCESS\n");
    printf("----------------------------------------------------\n");

    printf("Enter Admin Passcode: ");

    if (scanf("%d", &password) != 1)
    {
        printf("[ACCESS DENIED] Invalid passcode input!\n");

        while (getchar() != '\n');
        return;
    }

    if (password != 1357)
    {
        printf("\n[ACCESS DENIED] Incorrect passcode entered!\n");
        return;
    }

    printf("\n[ACCESS GRANTED] Welcome, System Operator.\n");

    while (1)
    {
        printf("\n");
        printf("----------------------------------------------------\n");
        printf("                 ADMIN OPERATIONS MENU\n");
        printf("----------------------------------------------------\n");

        printf(" 1. Display Inventory Levels & Sales Revenue\n");
        printf(" 2. Replenish Ingredient Inventory\n");
        printf(" 3. Change Wash Package Prices\n");
        printf(" 4. Reset Total Sales Revenue\n");
        printf(" 0. Exit Admin Mode\n");

        printf("----------------------------------------------------\n");
        printf("Select an admin operation (0-4): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                displayInventoryAndSales();
                break;

            case 2:
                replenishIngredients();
                break;

            case 3:
                changePackagePrices();
                break;

            case 4:
                resetSalesRevenue();
                break;

            case 0:
                return;

            default:
                printf("Invalid operation. Please select 0-4.\n");
        }
    }
}

/* Display Inventory Levels and Sales Revenue */

void displayInventoryAndSales(void)
{
    printf("\n");
    printf("----------------------------------------------------\n");
    printf("          INVENTORY LEVELS & SALES REVENUE\n");
    printf("----------------------------------------------------\n");

    printf("Current Water: %.1f L (Max: %.1f L)\n", water_level, (float)WATER_SUPPLY_MAX_CAPACITY);

    printf("Current Soap: %.1f mL (Max: %.1f mL)\n", soap_level, (float)SOAP_CONCENTRATE_MAX_CAPACITY);

    printf("Current Wax: %.1f mL (Max: %.1f mL)\n", wax_level, (float)LIQUID_WAX_MAX_CAPACITY);

    printf("----------------------------------------------------\n");

    printf("Basic Eco Wash Price       : AED %.2f\n", basic_price);
    printf("Deluxe Foam Wash Price     : AED %.2f\n", deluxe_price);
    printf("Premium Shine & Wax Price  : AED %.2f\n", premium_price);

    printf("----------------------------------------------------\n");
    printf("Total Sales Revenue        : AED %.2f\n", total_sales_revenue);

    printf("====================================================\n");
}

/* Replenish Ingredient Inventory */

void replenishIngredients(void)
{
    float addWater;
    float addSoap;
    float addWax;

    printf("\n");
    printf("----------------------------------------------------\n");
    printf("              REPLENISH INGREDIENT INVENTORY\n");
    printf("----------------------------------------------------\n");

    printf("Current Water: %.1f L (Max: %.1f L)\n", water_level, (float)WATER_SUPPLY_MAX_CAPACITY);

    printf("Enter Water to add (Liters): ");

    if (scanf("%f", &addWater) != 1 || addWater < 0)
    {
        printf("[ERROR] Invalid water quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    printf("Current Soap: %.1f mL (Max: %.1f mL)\n", soap_level, (float)SOAP_CONCENTRATE_MAX_CAPACITY);

    printf("Enter Soap to add (mL): ");

    if (scanf("%f", &addSoap) != 1 || addSoap < 0)
    {
        printf("[ERROR] Invalid soap quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    printf("Current Wax: %.1f mL (Max: %.1f mL)\n", wax_level, (float)LIQUID_WAX_MAX_CAPACITY);

    printf("Enter Wax to add (mL): ");

    if (scanf("%f", &addWax) != 1 || addWax < 0)
    {
        printf("[ERROR] Invalid wax quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    /* Add Resources */

    water_level += addWater;
    soap_level += addSoap;
    wax_level += addWax;

    if (water_level > WATER_SUPPLY_MAX_CAPACITY)
        water_level = WATER_SUPPLY_MAX_CAPACITY;

    if (soap_level > SOAP_CONCENTRATE_MAX_CAPACITY)
        soap_level = SOAP_CONCENTRATE_MAX_CAPACITY;

    if (wax_level > LIQUID_WAX_MAX_CAPACITY)
        wax_level = LIQUID_WAX_MAX_CAPACITY;

    printf("\n");
    printf("====================================================\n");
    printf(" [SUCCESS] INVENTORY REPLENISHED SUCCESSFULLY!\n");
    printf("----------------------------------------------------\n");

    printf(" Updated Water Level : %.1f L\n", water_level);
    printf(" Updated Soap Level  : %.1f mL\n", soap_level);
    printf(" Updated Wax Level   : %.1f mL\n", wax_level);

    printf("====================================================\n");
}

/* Change Wash Package Prices */

void changePackagePrices(void)
{
    int choice;
    float newPrice;

    while (1)
    {
        printf("\n");
        printf("----------------------------------------------------\n");
        printf("               CHANGE WASH PACKAGE PRICES\n");
        printf("----------------------------------------------------\n");

        printf("1. Basic Eco Wash       : AED %.2f\n", basic_price);
        printf("2. Deluxe Foam Wash     : AED %.2f\n", deluxe_price);
        printf("3. Premium Shine & Wax  : AED %.2f\n", premium_price);
        printf("0. Return to Admin Menu\n");

        printf("----------------------------------------------------\n");
        printf("Select a package to modify (0-3): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        if (choice == 0)
            return;

        if (choice < 1 || choice > 3)
        {
            printf("Invalid package selection. Please try again.\n");
            continue;
        }

        printf("Enter new price (AED): ");

        if (scanf("%f", &newPrice) != 1 || newPrice <= 0)
        {
            printf("[ERROR] Price must be greater than zero.\n");

            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                basic_price = newPrice;
                break;

            case 2:
                deluxe_price = newPrice;
                break;

            case 3:
                premium_price = newPrice;
                break;
        }

        printf("\n[SUCCESS] Wash package price updated successfully!\n");
    }
}

/* Reset Total Sales Revenue */

void resetSalesRevenue(void)
{
    int confirm;

    printf("\n");
    printf("----------------------------------------------------\n");
    printf("                 RESET TOTAL SALES REVENUE\n");
    printf("----------------------------------------------------\n");

    printf("Current Sales Revenue: AED %.2f\n", total_sales_revenue);

    printf("Please collect the cash box earnings before resetting.\n");
    printf("Confirm revenue reset (1 = Yes, 0 = No): ");

    if (scanf("%d", &confirm) != 1)
    {
        printf("[ERROR] Invalid input. Revenue was not reset.\n");

        while (getchar() != '\n');
        return;
    }

    if (confirm == 1)
    {
        total_sales_revenue = 0.00;

        printf("\n[SUCCESS] Total sales revenue reset to AED 0.00.\n");
    }
    else if (confirm == 0)
    {
        printf("\nRevenue reset cancelled.\n");
    }
    else
    {
        printf("\nInvalid choice. Revenue was not reset.\n");
    }
}
