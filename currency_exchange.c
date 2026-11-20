/* currency_exchange.c - CSCI291 Lab 4, Task 2 `*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define EXC_RATE 3.67
#define AM_MAX 300.00
#define SIZE 30

void curr_change(float amCur1, float amMax, float excRate, float *amCur2, float *leftOver)
{
    if (amCur1 > amMax) { 
        *amCur2 = amMax * excRate;
        *leftOver = amCur1 - amMax;
    } 
    else { 
        *amCur2 = amCur1 * excRate;
        *leftOver = 0.0f;
    }
}

static int read_amount(const char *prompt, float *out)
{
    char buf[SIZE];
    char *end;
    double v;
    for (;;) { // ;; creates an infinite loop that continues till an external statement is placed to break 
        printf("%s", prompt);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return 0;
        buf[strcspn(buf, "\r\n")] = '\0'; /* strip newline */
        v = strtod(buf, &end);
        if (buf[0] == '\0' || *end != '\0')
            printf(" Invalid input '%s': please enter a number.\n", buf);
        else if (v <= 0.0)
            printf(" Amount must be greater than zero.\n");
        else {
            *out = (float)v;
            return 1;
        }
    }
}

int main(void)
{
    const char cur1[] = "USD"; /* Displaying the labels using C-strings */
    const char cur2[] = "AED";
    float amount, convertedAmount, leftoverAmount;

    printf("=== Bank Currency Exchange (%s -> %s) ===\n", cur1, cur2);
    printf("Rate: 1 %s = %.2f %s | Transaction cap: %.2f %s\n\n",

    cur1, EXC_RATE, cur2, AM_MAX, cur1);

    if (!read_amount("Enter amount in USD: ", &amount))
        return 1;

    curr_change(amount, AM_MAX, EXC_RATE, &convertedAmount, &leftoverAmount);
    printf("\nAmount provided : %10.2f %s\n", amount, cur1);
    printf("Converted amount : %10.2f %s\n", convertedAmount, cur2);
    printf("Left over (return): %10.2f %s\n", leftoverAmount, cur1);

    if (leftoverAmount > 0.0f)
        printf("Note: amount exceeded the %.2f %s cap.\n", AM_MAX, cur1);
        return 0;
}
