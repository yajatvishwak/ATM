#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long amount, deposit, withdraw;
int choice, pin, k;
long card;
char name[50];
char transaction = 'y';

char *getfield(char *line, int num)
{
    char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
int str2int(char *s)
{
    int i, n;
    for (n = 0, i = 0; s[i] != '\0'; i++)
        n = n * 10 + (s[i] - '0');
    return n;
}

void main()
{
    FILE *fp;
    int count = 0;
    char c;
    fp = fopen("input.txt", "r");
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;
    fclose(fp);
    int chk = 0;
    FILE *stream = fopen("input.txt", "r");
    FILE *fptr;
    int PIN[100];
    long DEP[100];
    long CARD[100];
    char NAMES[100][50];
    int i = 0;
    char line[1024];

    i = 0;
    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);
        char *tmp1 = strdup(line);
        char *tmp2 = strdup(line);
        char *tmp3 = strdup(line);
        PIN[i] = str2int(getfield(tmp, 1));
        DEP[i] = atol(getfield(tmp1, 2));

        strcpy(NAMES[i], getfield(tmp2, 3));
        CARD[i] = atol(getfield(tmp3, 4));
        i++;
        free(tmp);
    }

    while (chk != 1)
    {
        printf("ENTER YOUR CARD NUMBER:");
        scanf("%ld", &card);
        printf("ENTER YOUR SECRET PIN NUMBER:");
        scanf("%d", &pin);
        for (i = 0; i < count; i++)
        {
            if (CARD[i] == card && PIN[i] == pin)
            {
                printf("\n!!AUTHENTICATION SUCCESSFUL!!\n");
                amount = DEP[i];
                strcpy(name, NAMES[i]);
                chk = 1;
                break;
            }
        }

        if (chk != 1)
        {
            printf("\n!!AUTHENTICATION UNSUCCESSFUL.TRY AGAIN!!\n");
        }
    }

    do
    {
        printf("***Welcome to ATM Service*****\n");
        printf("1. Account Details\n");
        printf("2. Withdraw Cash\n");
        printf("3. Deposit Cash\n");
        printf("4. Quit\n");
        printf("******************************\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("USER NAME: %s\n", name);
            printf("\n YOUR BALANCE IS Rs : %lu\n ", amount);
            printf("\n YOUR ACCOUNT NUMBER IS : %lu ", card);
            break;
        case 2:
            printf("\n ENTER THE AMOUNT TO WITHDRAW: ");
            scanf("%lu", &withdraw);
            if (withdraw % 100 != 0)
            {
                printf("\n PLEASE ENTER THE AMOUNT IN MULTIPLES OF 100");
            }
            else if (withdraw > amount)
            {
                printf("\n INSUFFICENT BALANCE");
            }
            else
            {
                amount = amount - withdraw;
                printf("\n\n PLEASE COLLECT CASH");
                printf("\n YOUR CURRENT BALANCE IS%lu", amount);
            }
            break;
        case 3:
            printf("\n ENTER THE AMOUNT TO DEPOSIT: ");
            scanf("%lu", &deposit);
            amount = amount + deposit;
            printf("YOUR BALANCE IS %lu", amount);
            break;
        case 4:
            printf("\n THANK U USING ATM");
            break;
        default:
            printf("\n INVALID CHOICE");
        }
        printf("\n\n\n DO U WISH TO HAVE ANOTHER TRANSCATION?(y/n): \n");
        fflush(stdin);
        scanf(" %c", &transaction);
        if (transaction == 'n' || transaction == 'N')
            k = 1;
    } while (!k);

    int del = remove("input.txt");
    fptr = fopen("input.txt", "w");

    for (i = 0; i < count; i++)
    {
        if (CARD[i] == card && PIN[i] == pin)
        {
            fprintf(fptr, "%d,%lu,%s,%lu\n", PIN[i], amount, name, card);
        }
        else
        {
            fprintf(fptr, "%d,%lu,%s,%lu\n", PIN[i], DEP[i], NAMES[i], CARD[i]);
        }
    }

    printf("\n\n THANKS FOR USING OUT ATM SERVICE");
    fclose(stream);
    fclose(fptr);
}