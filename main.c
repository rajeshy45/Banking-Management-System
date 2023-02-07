#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to store account details
struct Account
{
    char *firstName;
    char *lastName;
    char *accountNumber;
    unsigned int pin;
    double balance;
};

int createAccount();
int loginAccount();
void dashboard();
int numLen(long n);
void writeFile(struct Account *account, FILE *file); // Writes file
void pause();
void allocateMemory(struct Account *account); // Allocates memory
void freeMemory(struct Account *account);     // Frees memory
void addAccount(struct Account *account);
void printDetails(struct Account *account); // Prints output

const char filename[] = "accounts.txt";

int main()
{
    srand(time(NULL)); // Seed to generate random account numbers
    int choice;
    int count = 0;

    while (1)
    {
        count++;
        if (count == 5)
        {
            system("clear"); // Clear console
            printf("\n\t=====================================================\n");
            printf("\t\t\tSIMPLE BANKING SYSTEM");
            printf("\n\t=====================================================\n");
            printf("\n\t\t\tSession Expired..!\n");
            printf("\n\t-----------------------------------------------------\n\n");
            pause();
            system("clear");
            break;
        }
        system("clear");
        printf("\n\t=====================================================\n");
        printf("\t\t\tSIMPLE BANKING SYSTEM");
        printf("\n\t=====================================================\n");
        printf("\t\t\t     WELCOME!!!");
        printf("\n\t-----------------------------------------------------\n\n");
        printf("\t\t     Enter 1 -> Create Account\n");
        printf("\t\t     Enter 2 -> Login\n");
        printf("\t\t     Enter 3 -> Add Account\n");
        printf("\t\t     Enter 4 -> View Accounts\n");
        printf("\t\t     Enter 5 -> Search Account\n");
        printf("\t\t     Enter 0 -> Exit\n");
        printf("\n\t-----------------------------------------------------\n\n");
        printf("\t\tEnter choice : ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            system("clear");
            printf("\n\t=====================================================\n");
            printf("\t\t\tSIMPLE BANKING SYSTEM");
            printf("\n\t=====================================================\n");
            printf("\n\t\t\t    Thank you..!\n");
            printf("\n\t-----------------------------------------------------\n\n");
            pause();
            system("clear");
            break;
        }
        else if (choice == 1)
        {
            if (createAccount())
            {
                printf("\n\t\tAccount successfully created!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
            }
            else
            {
                printf("\n\t\tSorry, something went wrong. Please try again!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
            }
        }
        else if (choice == 2)
        {
            if (loginAccount())
            {
                printf("\n\t\tLogin Successful!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
                dashboard();
            }
            else
            {
                printf("\n\t\tInvalid details!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
            }
        }
        else if (choice == 3)
        {
            struct Account account, *pAccount;
            pAccount = &account;
            allocateMemory(pAccount);
            addAccount(pAccount);
            freeMemory(pAccount);
        }
        else if (choice == 4)
        {
            system("clear");
            printf("\n\t==============================================================================\n");
            printf("\t\t\t\t    SIMPLE BANKING SYSTEM");
            printf("\n\t==============================================================================\n");
            printf("\t\tAccount Number\t\t Balance\t\tName");
            printf("\n\t------------------------------------------------------------------------------\n\n");
            struct Account account, *pAccount;
            pAccount = &account;
            allocateMemory(pAccount);
            FILE *pFile = fopen(filename, "r+");
            while (fscanf(pFile, "%s", pAccount->accountNumber) != EOF)
            {
                fscanf(pFile, "%d", &pAccount->pin);
                fscanf(pFile, "%lf", &pAccount->balance);
                fscanf(pFile, "%s", pAccount->firstName);
                fscanf(pFile, "%s", pAccount->lastName);
                printDetails(pAccount);
            }
            printf("\n\t------------------------------------------------------------------------------\n\n");
            fclose(pFile);
            freeMemory(pAccount);
            pause();
        }
        else if (choice == 5)
        {
            system("clear");
            printf("\n\t-----------------------------------------------------\n");
            printf("\t\t\t   SEARCH ACCOUNT");
            printf("\n\t-----------------------------------------------------\n");

            struct Account account, *pAccount;
            pAccount = &account;
            char fName[30];
            char lName[30];
            allocateMemory(pAccount);
            printf("\n\t\tEnter First Name : ");
            scanf(" ");
            scanf("%s", fName);
            printf("\t\tEnter Last Name  : ");
            scanf(" ");
            scanf("%s", lName);
            FILE *pFile = fopen(filename, "r+");

            system("clear");
            printf("\n\t==============================================================================\n");
            printf("\t\t\t\t    SIMPLE BANKING SYSTEM");
            printf("\n\t==============================================================================\n");
            printf("\t\tAccount Number\t\t Balance\t\tName");
            printf("\n\t------------------------------------------------------------------------------\n\n");

            while (fscanf(pFile, "%s", pAccount->accountNumber) != EOF)
            {
                fscanf(pFile, "%d", &pAccount->pin);
                fscanf(pFile, "%lf", &pAccount->balance);
                fscanf(pFile, "%s", pAccount->firstName);
                fscanf(pFile, "%s", pAccount->lastName);
                if ((strcmp(fName, pAccount->firstName) == 0) || (strcmp(lName, pAccount->lastName) == 0))
                {
                    printDetails(pAccount);
                }
            }

            printf("\n\t------------------------------------------------------------------------------\n\n");
            fclose(pFile);
            freeMemory(pAccount);
            pause();
        }
        else
        {
            printf("\n\t\tInvalid Choice!\n");
            pause();
        }
    }
    return 0;
}

int createAccount()
{
    struct Account account, *pAccount;
    pAccount = &account;
    allocateMemory(pAccount);
    pAccount->pin = ((rand() % 8997) + 1001);
    pAccount->balance = 500.00;
    *(pAccount->accountNumber) = '4';

    system("clear");
    printf("\n\t-----------------------------------------------------\n");
    printf("\t\t\t   CREATE ACCOUNT");
    printf("\n\t-----------------------------------------------------\n");
    printf("\n\t\tEnter First Name : ");
    scanf(" "); // Pauses the program to take input
    scanf("%s", pAccount->firstName);
    printf("\t\tEnter Last Name  : ");
    scanf(" ");
    scanf("%s", pAccount->lastName);

    for (int i = 1; i < 16; i++)
    {
        if (i <= 5)
        {
            *(pAccount->accountNumber + i) = '0';
        }
        else
        {
            *(pAccount->accountNumber + i) = (rand() % 8) + 1 + '0';
        }
    }

    FILE *pFile = fopen(filename, "a+");
    if (pFile == NULL)
    {
        return 0;
    }
    writeFile(pAccount, pFile);
    fclose(pFile);

    printf("\n\t\tName           : %s %s", pAccount->firstName, pAccount->lastName);
    printf("\n\t\tAccount number : %s", pAccount->accountNumber);
    printf("\n\t\tPin            : %d\n", pAccount->pin);

    freeMemory(pAccount);
    return 1;
}

int loginAccount()
{
    struct Account account, *pAccount;
    pAccount = &account;

    system("clear");
    printf("\n\t-----------------------------------------------------\n");
    printf("\t\t\t    LOGIN ACCOUNT");
    printf("\n\t-----------------------------------------------------\n");
    pAccount->accountNumber = (char *)malloc(19 * sizeof(char));
    printf("\n\t\tEnter Account number : ");
    scanf("%s", pAccount->accountNumber);
    printf("\t\tEnter Account pin    : ");
    scanf("%d", &pAccount->pin);

    FILE *pFile = fopen(filename, "r+");
    int isExist = 0;
    char acNumber[30];
    int acPin;

    while (fscanf(pFile, "%s", acNumber) != EOF)
    {
        if (strcmp(pAccount->accountNumber, acNumber) == 0)
        {
            fscanf(pFile, "%d", &acPin);
            if (pAccount->pin == acPin)
            {
                isExist = 1;
            }
            break;
        }
    }
    fclose(pFile);

    if (isExist)
    {
        pFile = fopen("login.txt", "w");
        fprintf(pFile, "%s", acNumber);
        fclose(pFile);
    }
    free(pAccount->accountNumber);
    return isExist;
}

void dashboard()
{
    int isDeleted = 0;
    struct Account account, *pAccount;
    pAccount = &account;
    allocateMemory(pAccount);
    char acNumber[30];
    FILE *pFile = fopen("login.txt", "r+");
    fscanf(pFile, "%s", acNumber);
    fclose(pFile);
    remove("login.txt");
    pFile = fopen(filename, "r+");

    while (fscanf(pFile, "%s", pAccount->accountNumber) != EOF)
    {
        if (strcmp(pAccount->accountNumber, acNumber) == 0)
        {
            fscanf(pFile, "%d", &pAccount->pin);
            fscanf(pFile, "%lf", &pAccount->balance);
            fscanf(pFile, "%s", pAccount->firstName);
            fscanf(pFile, "%s", pAccount->lastName);
            break;
        }
    }
    fclose(pFile);

    int choice;
    while (1)
    {
        if (isDeleted)
        {
            break;
        }
        system("clear");
        printf("\n\t=====================================================\n");
        printf("\t\t\tSIMPLE BANKING SYSTEM");
        printf("\n\t=====================================================\n");
        printf("\t");
        for (int i = 0; i < (45 - strlen(pAccount->firstName)) / 2; i++)
        {
            printf(" ");
        }
        printf("WELCOME %s", pAccount->firstName);
        printf("\n\t-----------------------------------------------------\n\n");
        printf("\t\t     Enter 1 -> View Account\n");
        printf("\t\t     Enter 2 -> Deposit\n");
        printf("\t\t     Enter 3 -> Withdraw\n");
        printf("\t\t     Enter 4 -> Transfer\n");
        printf("\t\t     Enter 5 -> Settings\n");
        printf("\t\t     Enter 0 -> Logout\n");
        printf("\n\t-----------------------------------------------------\n\n");
        printf("\t\tEnter choice : ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            system("clear");
            printf("\n\t=====================================================\n");
            printf("\t\t\tSIMPLE BANKING SYSTEM");
            printf("\n\t=====================================================\n");
            printf("\n\t\t\tLogout Successful!\n");
            printf("\n\t-----------------------------------------------------\n\n");
            pause();
            break;
        }
        else if (choice == 1)
        {
            system("clear");
            printf("\n\t-----------------------------------------------------\n");
            printf("\t\t\t   VIEW ACCOUNT");
            printf("\n\t-----------------------------------------------------\n");
            printf("\n\t\tName           : %s %s\n", pAccount->firstName, pAccount->lastName);
            printf("\t\tAccount Number : %s\n", pAccount->accountNumber);
            printf("\t\tBalance        : %.2lf\n", pAccount->balance);
            printf("\n\t-----------------------------------------------------\n");
            pause();
        }
        else if (choice == 2)
        {
            system("clear");
            double amount;
            printf("\n\t-----------------------------------------------------\n");
            printf("\t\t\t      DEPOSIT");
            printf("\n\t-----------------------------------------------------\n");
            printf("\n\t\tEnter Amount : ");
            scanf("%lf", &amount);

            pAccount->balance += amount;
            pFile = fopen(filename, "r+");
            FILE *pTempFile = fopen("temp.txt", "w");
            struct Account tempAccount, *pTempAccount;
            pTempAccount = &tempAccount;
            allocateMemory(pTempAccount);

            while (fscanf(pFile, "%s", pTempAccount->accountNumber) != EOF)
            {
                fscanf(pFile, "%d", &pTempAccount->pin);
                fscanf(pFile, "%lf", &pTempAccount->balance);
                fscanf(pFile, "%s", pTempAccount->firstName);
                fscanf(pFile, "%s", pTempAccount->lastName);
                if (strcmp(pAccount->accountNumber, pTempAccount->accountNumber) == 0)
                {
                    pTempAccount->balance = pAccount->balance;
                    writeFile(pTempAccount, pTempFile);
                }
                else
                {
                    writeFile(pTempAccount, pTempFile);
                }
            }

            printf("\n\t\tDeposit Successful!\n");
            printf("\n\t-----------------------------------------------------\n");

            fclose(pFile);
            fclose(pTempFile);
            remove(filename);
            rename("temp.txt", filename);
            freeMemory(pTempAccount);
            pause();
        }
        else if (choice == 3)
        {
            system("clear");
            double amount;
            printf("\n\t-----------------------------------------------------\n");
            printf("\t\t\t      WITHDRAW");
            printf("\n\t-----------------------------------------------------\n");
            printf("\n\t\tEnter Amount : ");
            scanf("%lf", &amount);
            if (amount > pAccount->balance)
            {
                printf("\n\t\tInsufficient Balance!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
            }
            else
            {
                pAccount->balance -= amount;
                pFile = fopen(filename, "r+");
                FILE *pTempFile = fopen("temp.txt", "w");
                struct Account tempAccount, *pTempAccount;
                pTempAccount = &tempAccount;
                allocateMemory(pTempAccount);
                while (fscanf(pFile, "%s", pTempAccount->accountNumber) != EOF)
                {
                    fscanf(pFile, "%d", &pTempAccount->pin);
                    fscanf(pFile, "%lf", &pTempAccount->balance);
                    fscanf(pFile, "%s", pTempAccount->firstName);
                    fscanf(pFile, "%s", pTempAccount->lastName);
                    if (strcmp(pAccount->accountNumber, pTempAccount->accountNumber) == 0)
                    {
                        pTempAccount->balance = pAccount->balance;
                        writeFile(pTempAccount, pTempFile);
                    }
                    else
                    {
                        writeFile(pTempAccount, pTempFile);
                    }
                }
                printf("\n\t\tWithdrawal Successful!\n");
                printf("\n\t-----------------------------------------------------\n");

                fclose(pFile);
                fclose(pTempFile);
                remove(filename);
                rename("temp.txt", filename);
                freeMemory(pTempAccount);
                pause();
            }
        }
        else if (choice == 4)
        {
            system("clear");
            double amount;
            printf("\n\t-----------------------------------------------------\n");
            printf("\t\t\t      TRANSFER");
            printf("\n\t-----------------------------------------------------\n");

            struct Account tempAccount, *pTempAccount;
            pTempAccount = &tempAccount;
            char tempAcNumber[30];
            allocateMemory(pTempAccount);
            printf("\n\t\tEnter Account Number : ");
            scanf("%s", pTempAccount->accountNumber);
            strcpy(tempAcNumber, pTempAccount->accountNumber);
            int isExist = 0;
            pFile = fopen(filename, "r+");

            while (fscanf(pFile, "%s", acNumber) != EOF)
            {
                if (strcmp(pTempAccount->accountNumber, acNumber) == 0)
                {
                    fscanf(pFile, "%d", &pTempAccount->pin);
                    fscanf(pFile, "%lf", &pTempAccount->balance);
                    fscanf(pFile, "%s", pTempAccount->firstName);
                    fscanf(pFile, "%s", pTempAccount->lastName);
                    isExist = 1;
                }
            }
            fclose(pFile);
            if (isExist)
            {
                printf("\n\t\tEnter Amount : ");
                scanf("%lf", &amount);
                if (amount > pAccount->balance)
                {
                    printf("\n\t\tInsufficient Balance!\n");
                    printf("\n\t-----------------------------------------------------\n");
                    pause();
                }
                else
                {
                    pFile = fopen(filename, "r+");
                    FILE *pTempFile = fopen("temp.txt", "w");
                    while (fscanf(pFile, "%s", acNumber) != EOF)
                    {
                        fscanf(pFile, "%d", &pTempAccount->pin);
                        fscanf(pFile, "%lf", &pTempAccount->balance);
                        fscanf(pFile, "%s", pTempAccount->firstName);
                        fscanf(pFile, "%s", pTempAccount->lastName);
                        if (strcmp(acNumber, pTempAccount->accountNumber) == 0)
                        {
                            pTempAccount->balance += amount;
                            writeFile(pTempAccount, pTempFile);
                        }
                        else if (strcmp(acNumber, pAccount->accountNumber) == 0)
                        {
                            pAccount->balance -= amount;
                            writeFile(pAccount, pTempFile);
                        }
                        else
                        {
                            strcpy(pTempAccount->accountNumber, acNumber);
                            writeFile(pTempAccount, pTempFile);
                            strcpy(pTempAccount->accountNumber, tempAcNumber);
                        }
                    }
                    printf("\n\t\tTransfer Successful!\n");
                    printf("\n\t-----------------------------------------------------\n");

                    fclose(pTempFile);
                    remove(filename);
                    rename("temp.txt", filename);
                    pause();
                }
            }
            else
            {
                printf("\n\t\tInvalid details!\n");
                printf("\n\t-----------------------------------------------------\n");
                pause();
            }
            fclose(pFile);
            freeMemory(pTempAccount);
        }
        else if (choice == 5)
        {
            while (1)
            {
                system("clear");
                printf("\n\t-----------------------------------------------------\n");
                printf("\t\t\t      SETTINGS");
                printf("\n\t-----------------------------------------------------\n\n");
                printf("\t\t     Enter 1 -> Change Name\n");
                printf("\t\t     Enter 2 -> Change Pin\n");
                printf("\t\t     Enter 3 -> Delete Account\n");
                printf("\t\t     Enter 0 -> Back\n");
                printf("\n\t-----------------------------------------------------\n\n");
                printf("\t\tEnter choice : ");
                scanf("%d", &choice);

                if (choice == 0)
                {
                    break;
                }
                else if (choice == 1)
                {
                    system("clear");
                    printf("\n\t-----------------------------------------------------\n");
                    printf("\t\t\t     CHANGE NAME");
                    printf("\n\t-----------------------------------------------------\n\n");
                    int pin;
                    printf("\t\tEnter Account Pin : ");
                    scanf("%d", &pin);
                    if (pin != pAccount->pin)
                    {
                        printf("\n\t\tInvalid details!\n");
                        printf("\n\t-----------------------------------------------------\n");
                        pause();
                    }
                    else
                    {
                        printf("\n\t\tEnter new First Name : ");
                        scanf("%s", pAccount->firstName);
                        printf("\t\tEnter new Last Name  : ");
                        scanf("%s", pAccount->lastName);
                        pFile = fopen(filename, "r+");
                        FILE *pTempFile = fopen("temp.txt", "w");

                        struct Account tempAccount, *pTempAccount;
                        pTempAccount = &tempAccount;
                        allocateMemory(pTempAccount);

                        while (fscanf(pFile, "%s", pTempAccount->accountNumber) != EOF)
                        {
                            fscanf(pFile, "%d", &pTempAccount->pin);
                            fscanf(pFile, "%lf", &pTempAccount->balance);
                            fscanf(pFile, "%s", pTempAccount->firstName);
                            fscanf(pFile, "%s", pTempAccount->lastName);
                            if (strcmp(pAccount->accountNumber, pTempAccount->accountNumber) == 0)
                            {
                                writeFile(pAccount, pTempFile);
                            }
                            else
                            {
                                writeFile(pTempAccount, pTempFile);
                            }
                        }
                        printf("\n\t\tChanges Saved!\n");
                        printf("\n\t-----------------------------------------------------\n");

                        fclose(pFile);
                        fclose(pTempFile);
                        remove(filename);
                        rename("temp.txt", filename);
                        freeMemory(pTempAccount);
                        pause();
                    }
                }
                else if (choice == 2)
                {
                    system("clear");
                    printf("\n\t-----------------------------------------------------\n");
                    printf("\t\t\t     CHANGE PIN");
                    printf("\n\t-----------------------------------------------------\n\n");
                    int pin;
                    printf("\t\tEnter Account Pin : ");
                    scanf("%d", &pin);
                    if (pin != pAccount->pin)
                    {
                        printf("\n\t\tInvalid details!\n");
                        printf("\n\t-----------------------------------------------------\n");
                        pause();
                    }
                    else
                    {
                        printf("\n\t\tEnter new Pin : ");
                        scanf("%d", &pAccount->pin);
                        pFile = fopen(filename, "r+");
                        FILE *pTempFile = fopen("temp.txt", "w");

                        struct Account tempAccount, *pTempAccount;
                        pTempAccount = &tempAccount;
                        allocateMemory(pTempAccount);

                        while (fscanf(pFile, "%s", pTempAccount->accountNumber) != EOF)
                        {
                            fscanf(pFile, "%d", &pTempAccount->pin);
                            fscanf(pFile, "%lf", &pTempAccount->balance);
                            fscanf(pFile, "%s", pTempAccount->firstName);
                            fscanf(pFile, "%s", pTempAccount->lastName);
                            if (strcmp(pAccount->accountNumber, pTempAccount->accountNumber) == 0)
                            {
                                writeFile(pAccount, pTempFile);
                            }
                            else
                            {
                                writeFile(pTempAccount, pTempFile);
                            }
                        }

                        printf("\n\t\tChanges Saved!\n");
                        printf("\n\t-----------------------------------------------------\n");

                        fclose(pFile);
                        fclose(pTempFile);
                        remove(filename);
                        rename("temp.txt", filename);
                        freeMemory(pTempAccount);
                        pause();
                    }
                }
                else if (choice == 3)
                {
                    system("clear");
                    printf("\n\t-----------------------------------------------------\n");
                    printf("\t\t\t    DELETE ACCOUNT");
                    printf("\n\t-----------------------------------------------------\n\n");
                    int pin;
                    printf("\t\tEnter Account Pin : ");
                    scanf("%d", &pin);
                    if (pin != pAccount->pin)
                    {
                        printf("\n\t\tInvalid details!\n");
                        printf("\n\t-----------------------------------------------------\n");
                        pause();
                    }
                    else
                    {
                        printf("\n\t\tAre you sure? All your data will be lost!\n");
                        printf("\t\tY -> YES\tN -> NO");
                        char decision;
                        printf("\n\t\tEnter Choice : ");
                        scanf(" ");
                        scanf("%c", &decision);

                        if (decision == 'Y' || decision == 'y')
                        {
                            pFile = fopen(filename, "r+");
                            FILE *pTempFile = fopen("temp.txt", "w");
                            struct Account tempAccount, *pTempAccount;
                            pTempAccount = &tempAccount;
                            allocateMemory(pTempAccount);

                            while (fscanf(pFile, "%s", pTempAccount->accountNumber) != EOF)
                            {
                                fscanf(pFile, "%d", &pTempAccount->pin);
                                fscanf(pFile, "%lf", &pTempAccount->balance);
                                fscanf(pFile, "%s", pTempAccount->firstName);
                                fscanf(pFile, "%s", pTempAccount->lastName);
                                if (strcmp(pAccount->accountNumber, pTempAccount->accountNumber) == 0)
                                {
                                    continue;
                                }
                                else
                                {
                                    writeFile(pTempAccount, pTempFile);
                                }
                            }

                            printf("\n\t\tAccount Deleted!\n");
                            printf("\n\t-----------------------------------------------------\n");

                            fclose(pFile);
                            fclose(pTempFile);
                            remove(filename);
                            rename("temp.txt", filename);
                            freeMemory(pTempAccount);
                            pause();
                            isDeleted = 1;
                            break;
                        }
                    }
                }
                else
                {
                    printf("\n\t\tInvalid Choice!\n");
                    pause();
                }
            }
        }
        else
        {
            printf("\n\t\tInvalid Choice!\n");
            pause();
        }
    }
    freeMemory(pAccount);
}

int numLen(long n)
{
    int count = 0;
    while (n != 0)
    {
        count++;
        n /= 10;
    }
    return count;
}

void writeFile(struct Account *account, FILE *file)
{
    fprintf(file, "%s", account->accountNumber);
    for (int i = 0; i < 25 - strlen(account->accountNumber); i++)
    {
        fputc(' ', file);
    }
    fprintf(file, "%d", account->pin);
    for (int i = 0; i < 10 - numLen(account->pin); i++)
    {
        fputc(' ', file);
    }
    fprintf(file, "%.2lf", account->balance);
    for (int i = 0; i < 20 - numLen(account->balance); i++)
    {
        fputc(' ', file);
    }
    fprintf(file, "%s %s\n", account->firstName, account->lastName);
}

void pause()
{
    printf("\nEnter any character to continue...\n");
    scanf(" ");
    getchar();
}

void allocateMemory(struct Account *account)
{
    account->firstName = (char *)malloc(30 * sizeof(char));
    account->lastName = (char *)malloc(30 * sizeof(char));
    account->accountNumber = (char *)malloc(30 * sizeof(char));
}

void freeMemory(struct Account *account)
{
    free(account->accountNumber);
    free(account->lastName);
    free(account->firstName);
}

void addAccount(struct Account *account)
{
    system("clear");
    printf("\n\t-----------------------------------------------------\n");
    printf("\t\t\t    ADD ACCOUNT");
    printf("\n\t-----------------------------------------------------\n");
    printf("\n\t\tEnter First Name : ");
    scanf("%s", account->firstName);
    printf("\t\tEnter Last Name  : ");
    scanf("%s", account->lastName);
    printf("\n\t\tEnter Account Number : ");
    scanf("%s", account->accountNumber);
    printf("\t\tEnter Account Pin    : ");
    scanf("%d", &account->pin);
    account->balance = 500;

    FILE *pFile = fopen(filename, "a+");
    writeFile(account, pFile);
    fclose(pFile);

    printf("\n\t\tAccount added successfully!\n");
    printf("\n\t-----------------------------------------------------\n");
    pause();
}

void printDetails(struct Account *account)
{
    printf("\t\t");
    printf("%s", account->accountNumber);
    for (int i = 0; i < 25 - strlen(account->accountNumber); i++)
    {
        printf(" ");
    }
    printf("%.2lf", account->balance);
    for (int i = 0; i < 20 - numLen(account->balance); i++)
    {
        printf(" ");
    }
    printf("%s %s", account->firstName, account->lastName);
    printf("\n");
}
// END OF FILE