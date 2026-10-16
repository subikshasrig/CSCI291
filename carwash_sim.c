#include <stdio.h>

// Wash Package Specifications and Resource Requirements

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

// Safety Thresholds for Each Resource

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

float water_level = WATER_SUPPLY_INITIAL_INVENTORY;
float soap_level = SOAP_CONCENTRATE_INITIAL_INVENTORY;
float wax_level = LIQUID_WAX_INITIAL_INVENTORY;

float basic_price = 15.0;
float deluxe_price = 25.0;
float premium_price = 40.0;

float total_sales_revenue = 0.0;

// Function Prototypes 

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

// Main Menu

int main(void)
{
    int choice;

    while (1)
    {
        displayMainMenu();

        printf("Enter your choice: ");

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
                printf("\nThank you for using the Automated Car Wash System!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void displayMainMenu(void)
{
    printf("\n============================================\n");
    printf("       AUTOMATED CAR WASH SYSTEM\n");
    printf("============================================\n");
    printf("1. Purchase Wash\n");
    printf("2. Admin Operations\n");
    printf("3. Exit\n");
    printf("============================================\n");
}

void customerMode(void)
{
    int choice;
    int confirm;

    while (1)
    {
        printf("\n============================================\n");
        printf("             WASH PACKAGES\n");
        printf("============================================\n");

        printf("1. Basic Eco Wash       - AED %.2f", basic_price);

        if (isPackageAvailable(1))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf("2. Deluxe Foam Wash     - AED %.2f", deluxe_price);

        if (isPackageAvailable(2))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf("3. Premium Shine & Wax - AED %.2f", premium_price);

        if (isPackageAvailable(3))
            printf("\n");
        else
            printf(" [UNAVAILABLE - Low Supplies]\n");

        printf("4. Return to Main Menu\n");
        printf("============================================\n");
        printf("Select a package: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        if (choice == 4)
            return;

        if (choice < 1 || choice > 3)
        {
            printf("Invalid package selection.\n");
            continue;
        }

        if (!isPackageAvailable(choice))
        {
            printf("Sorry, this package is unavailable due to low supplies.\n");
            continue;
        }

        printf("\nConfirm your wash purchase? (1 = Yes, 0 = No): ");

        if (scanf("%d", &confirm) != 1)
        {
            printf("Invalid input.\n");

            while (getchar() != '\n');
            continue;
        }

        if (confirm != 1)
        {
            printf("Purchase cancelled.\n");
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

void processPayment(float price, float reqWater, float reqSoap, float reqWax, int packageType)
{
    float coin;
    float totalInserted = 0.0;
    float remaining;
    float change;

    printf("\n============================================\n");
    printf("              PAYMENT SYSTEM\n");
    printf("============================================\n");
    printf("Total Amount Due: AED %.2f\n", price);
    printf("Accepted Coins: AED 1.00, 0.50, 0.25\n");

    while (totalInserted < price)
    {
        remaining = price - totalInserted;

        printf("\nAmount Remaining: AED %.2f\n", remaining);
        printf("Insert coin: AED ");

        if (scanf("%f", &coin) != 1)
        {
            printf("Invalid input. Coin rejected.\n");

            while (getchar() != '\n');
            continue;
        }

        if (coin != 1.00 && coin != 0.50 && coin != 0.25)
        {
            printf("Invalid coin. Please insert AED 1.00, 0.50, or 0.25.\n");
            continue;
        }

        totalInserted += coin;

        printf("Coin accepted. Total inserted: AED %.2f\n", totalInserted);
    }

    change = totalInserted - price;

    water_level -= reqWater;
    soap_level -= reqSoap;
    wax_level -= reqWax;

    total_sales_revenue += price;

    printf("\n============================================\n");
    printf("             PAYMENT SUCCESSFUL\n");
    printf("============================================\n");

    switch (packageType)
    {
        case 1:
            printf("Selected Package: Basic Eco Wash\n");
            break;

        case 2:
            printf("Selected Package: Deluxe Foam Wash\n");
            break;

        case 3:
            printf("Selected Package: Premium Shine & Wax\n");
            break;
    }

    printf("Amount Paid: AED %.2f\n", totalInserted);
    printf("Wash Price: AED %.2f\n", price);
    printf("Change Returned: AED %.2f\n", change);

    printf("\nYour wash is being processed. Thank you!\n");

    checkLowResourceAlerts();
}

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

void adminMode(void)
{
    int password;
    int choice;

    printf("\n============================================\n");
    printf("              ADMIN LOGIN\n");
    printf("============================================\n");
    printf("Enter admin passcode: ");

    if (scanf("%d", &password) != 1)
    {
        printf("Invalid input.\n");

        while (getchar() != '\n');
        return;
    }

    if (password != 1357)
    {
        printf("Incorrect passcode. Access denied.\n");
        return;
    }

    printf("\nAccess granted. Welcome, Administrator!\n");

    while (1)
    {
        printf("\n============================================\n");
        printf("             ADMIN MENU\n");
        printf("============================================\n");
        printf("1. Display Inventory and Sales\n");
        printf("2. Replenish Ingredients\n");
        printf("3. Change Package Prices\n");
        printf("4. Reset Sales Revenue\n");
        printf("5. Return to Main Menu\n");
        printf("============================================\n");
        printf("Enter your choice: ");

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

            case 5:
                return;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void displayInventoryAndSales(void)
{
    printf("\n============================================\n");
    printf("          INVENTORY AND SALES\n");
    printf("============================================\n");

    printf("Water Supply       : %.1f L / %.1f L\n", water_level, WATER_SUPPLY_MAX_CAPACITY);

    printf("Soap Concentrate   : %.1f mL / %.1f mL\n", soap_level, SOAP_CONCENTRATE_MAX_CAPACITY);

    printf("Liquid Wax         : %.1f mL / %.1f mL\n", wax_level, LIQUID_WAX_MAX_CAPACITY);

    printf("--------------------------------------------\n");
    printf("Basic Eco Wash     : AED %.2f\n", basic_price);
    printf("Deluxe Foam Wash   : AED %.2f\n", deluxe_price);
    printf("Premium Shine & Wax: AED %.2f\n", premium_price);

    printf("--------------------------------------------\n");
    printf("Total Sales Revenue: AED %.2f\n", total_sales_revenue);

    printf("============================================\n");
}

void replenishIngredients(void)
{
    float addWater;
    float addSoap;
    float addWax;

    printf("\n============================================\n");
    printf("          REPLENISH INGREDIENTS\n");
    printf("============================================\n");

    printf("Current Water Level: %.1f L\n", water_level);
    printf("Enter amount of water to add (L): ");

    if (scanf("%f", &addWater) != 1 || addWater < 0)
    {
        printf("Invalid quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    printf("Current Soap Level: %.1f mL\n", soap_level);
    printf("Enter amount of soap to add (mL): ");

    if (scanf("%f", &addSoap) != 1 || addSoap < 0)
    {
        printf("Invalid quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    printf("Current Wax Level: %.1f mL\n", wax_level);
    printf("Enter amount of wax to add (mL): ");

    if (scanf("%f", &addWax) != 1 || addWax < 0)
    {
        printf("Invalid quantity. Replenishment cancelled.\n");

        while (getchar() != '\n');
        return;
    }

    water_level += addWater;
    soap_level += addSoap;
    wax_level += addWax;

    if (water_level > WATER_SUPPLY_MAX_CAPACITY)
        water_level = WATER_SUPPLY_MAX_CAPACITY;

    if (soap_level > SOAP_CONCENTRATE_MAX_CAPACITY)
        soap_level = SOAP_CONCENTRATE_MAX_CAPACITY;

    if (wax_level > LIQUID_WAX_MAX_CAPACITY)
        wax_level = LIQUID_WAX_MAX_CAPACITY;

    printf("\nInventory replenishment completed.\n");

    printf("Updated Water Level: %.1f L\n", water_level);
    printf("Updated Soap Level: %.1f mL\n", soap_level);
    printf("Updated Wax Level: %.1f mL\n", wax_level);
}

void changePackagePrices(void)
{
    int choice;
    float newPrice;

    while (1)
    {
        printf("\n============================================\n");
        printf("          CHANGE PACKAGE PRICES\n");
        printf("============================================\n");
        printf("1. Basic Eco Wash       (AED %.2f)\n", basic_price);
        printf("2. Deluxe Foam Wash     (AED %.2f)\n", deluxe_price);
        printf("3. Premium Shine & Wax  (AED %.2f)\n", premium_price);
        printf("4. Return to Admin Menu\n");
        printf("============================================\n");
        printf("Select package to modify: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            continue;
        }

        if (choice == 4)
            return;

        if (choice < 1 || choice > 3)
        {
            printf("Invalid package selection.\n");
            continue;
        }

        printf("Enter new price (AED): ");

        if (scanf("%f", &newPrice) != 1 || newPrice <= 0)
        {
            printf("Invalid price. Price must be greater than zero.\n");

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

        printf("Package price updated successfully.\n");
    }
}

void resetSalesRevenue(void)
{
    int confirm;

    printf("\n============================================\n");
    printf("             RESET SALES REVENUE\n");
    printf("============================================\n");

    printf("Current Sales Revenue: AED %.2f\n", total_sales_revenue);

    printf("Please collect the cash box earnings before resetting.\n");
    printf("Are you sure you want to reset revenue? (1 = Yes, 0 = No): ");

    if (scanf("%d", &confirm) != 1)
    {
        printf("Invalid input. Revenue was not reset.\n");

        while (getchar() != '\n');
        return;
    }

    if (confirm == 1)
    {
        total_sales_revenue = 0.0;
        printf("Sales revenue reset to AED 0.00.\n");
    }
    else
    {
        printf("Revenue reset cancelled.\n");
    }
}
