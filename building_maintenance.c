#include <stdio.h>
#include <stdlib.h>

struct owner
{
    int flatNo;
    char ownerName[50];
    char paymentDate[15];
    float amountPaid;
};

struct expense
{
    char date[15];
    char expenseType[50];
    float amount;
    char description[100];
};

void addPayment();
void displayPayments();
void searchOwner();
void addExpense();
void displayExpenses();
float totalCollection();
float totalExpense();
void financialSummary();

void addPayment()
{
    FILE *fp;
    struct owner o;

    fp = fopen("payments.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Flat Number: ");
    scanf("%d", &o.flatNo);

    printf("Enter Owner Name: ");
    scanf(" %49[^\n]", o.ownerName);

    printf("Enter Amount Paid: ");
    scanf("%f", &o.amountPaid);

    printf("Enter Payment Date (DD/MM/YYYY): ");
    scanf(" %14s", o.paymentDate);

    fprintf(fp,"%d|%s|%s|%.2f\n",
            o.flatNo,
            o.ownerName,
            o.paymentDate,
            o.amountPaid);

    fclose(fp);

    printf("Payment Saved Successfully!\n");
}

void displayPayments()
{
    FILE *fp;
    struct owner o;

    fp = fopen("payments.txt", "r");

    if(fp == NULL)
    {
        printf("No Payment Records Found!\n");
        return;
    }

    printf("\nFlatNo\tOwner Name\t\tDate\t\tAmount\n");

    while(fscanf(fp,
                 "%d|%49[^|]|%14[^|]|%f\n",
                 &o.flatNo,
                 o.ownerName,
                 o.paymentDate,
                 &o.amountPaid) == 4)
    {
        printf("%d\t%-20s\t%-12s\t%.2f\n",
               o.flatNo,
               o.ownerName,
               o.paymentDate,
               o.amountPaid);
    }

    fclose(fp);
}
void searchOwner()
{
    FILE *fp;
    struct owner o;
    int flat, found = 0;

    printf("\nEnter Flat Number to Search: ");
    scanf("%d", &flat);

    fp = fopen("payments.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    while(fscanf(fp,
                 "%d|%49[^|]|%14[^|]|%f\n",
                 &o.flatNo,
                 o.ownerName,
                 o.paymentDate,
                 &o.amountPaid) == 4)
    {
        if(o.flatNo == flat)
        {
            printf("\n========== RECORD FOUND ==========");
            printf("\nFlat Number : %d", o.flatNo);
            printf("\nOwner Name  : %s", o.ownerName);
            printf("\nAmount Paid : %.2f\n", o.amountPaid);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nOwner Record Not Found!\n");
    }

    fclose(fp);
}

void addExpense()
{
    FILE *fp;
    struct expense e;

    fp = fopen("expenses.txt", "a");

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Expense Date (DD/MM/YYYY): ");
    scanf(" %14s", e.date);

    printf("Enter Expense Type: ");
    scanf(" %49[^\n]", e.expenseType);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    printf("Enter Description: ");
    scanf(" %99[^\n]", e.description);

    fprintf(fp, "%s|%s|%.2f|%s\n",
            e.date,
            e.expenseType,
            e.amount,
            e.description);

    fclose(fp);

    printf("Expense Saved Successfully!\n");
}

void displayExpenses()
{
    FILE *fp;
    struct expense e;

    fp = fopen("expenses.txt", "r");

    if(fp == NULL)
    {
        printf("No Expense Records Found!\n");
        return;
    }

    printf("\nDate         Expense Type         Amount     Description\n");

    while(fscanf(fp,
                 "%14[^|]|%49[^|]|%f|%99[^\n]\n",
                 e.date,
                 e.expenseType,
                 &e.amount,
                 e.description) == 4)
    {
        printf("%-12s %-20s %-10.2f %s\n",
               e.date,
               e.expenseType,
               e.amount,
               e.description);
    }

    fclose(fp);
}

float totalCollection()
{
    FILE *fp;
    struct owner o;
    float total = 0;

    fp = fopen("payments.txt", "r");

    if(fp == NULL)
        return 0;

    while(fscanf(fp,
                 "%d|%49[^|]|%14[^|]|%f\n",
                 &o.flatNo,
                 o.ownerName,
                 o.paymentDate,
                 &o.amountPaid) == 4)
    {
        total += o.amountPaid;
    }

    fclose(fp);

    return total;
}

float totalExpense()
{
    FILE *fp;
    struct expense e;
    float total = 0;

    fp = fopen("expenses.txt", "r");

    if(fp == NULL)
        return 0;

    while(fscanf(fp,
                 "%14[^|]|%49[^|]|%f|%99[^\n]\n",
                 e.date,
                 e.expenseType,
                 &e.amount,
                 e.description) == 4)
    {
        total += e.amount;
    }

    fclose(fp);

    return total;
}

void financialSummary()
{
    float collection = totalCollection();
    float expense = totalExpense();

    printf("\n==================================");
    printf("\n      FINANCIAL SUMMARY");
    printf("\n==================================");
    printf("\nTotal Collection : %.2f", collection);
    printf("\nTotal Expense    : %.2f", expense);
    printf("\nBalance          : %.2f", collection - expense);
    printf("\n==================================\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n======================================");
        printf("\n BUILDING MAINTENANCE SYSTEM");
        printf("\n======================================");
        printf("\n1. Add Maintenance Payment");
        printf("\n2. Display Payments");
        printf("\n3. Search Flat Owner");
        printf("\n4. Add Expense");
        printf("\n5. Display Expenses");
        printf("\n6. Financial Summary");
        printf("\n7. Exit");
        printf("\n======================================");
        printf("\nEnter Your Choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addPayment();
                break;

            case 2:
                displayPayments();
                break;

            case 3:
                searchOwner();
                break;

            case 4:
                addExpense();
                break;

            case 5:
                displayExpenses();
                break;

            case 6:
                financialSummary();
                break;

            case 7:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);

    return 0;
}