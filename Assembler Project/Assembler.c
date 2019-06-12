#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define check(s) printf("%d\n", s);
#define checks(s) printf("%s\n", s);
#define append(temp, s) sprintf(temp, "%s%s", temp, s)
typedef struct Labels Labels;

// Data Structures
struct Labels
{
    char lab[1000], address[10];
};

// Global declarations
Labels assLabels[1000];
char opCode[12][10] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011"};
char opCodeLabel[12][10] = {"MOV", "ADD", "SUB", "MUL", "CMP", "AND", "OR", "NOT", "JMP", "LOOP", "HLT", "JNZ"};

void Stoupper(char str[])
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = toupper(str[i]);
}

// Fetch OpCode from the source file
void fetchOpCode()
{
    FILE *inputFile = fopen("opcode.txt", "r");
    char oc[10], mapping[10];
    for (int i = 0; i < 12; i++)
    {
        fseek(inputFile, 0, SEEK_SET);
        while (fscanf(inputFile, " %s %s \n", oc, mapping))
        {
            Stoupper(oc);
            if (!strcmp(opCodeLabel[i], oc))
            {
                strcpy(opCode[i], mapping);
                break;
            }
        }
    }
}

// Make opcode Table
void makeOpCodeTable(char code[])
{
    FILE *opFile = fopen("opTable.txt", "r");
    char oc[100] = "", mc[100] = "";

    while (opFile != NULL && fscanf(opFile, " %s %s\n", oc, mc) != -1)
    {
        if (!strcmp(code, oc))
            return;
    }

    fclose(opFile);
    opFile = fopen("opTable.txt", "a");
    for (int i = 0; i < 12; i++)
    {
        if (!strcmp(code, opCodeLabel[i]))
        {
            fprintf(opFile, "%s\t%s\n", code, opCode[i]);
        }
    }
    fclose(opFile);
}

// This function converts the given opcode into machine code
void convertOpCode(char oc[], char machineCode[])
{
    for (int i = 0; i < 12; i++)
    {
        if (!strcmp(oc, opCodeLabel[i]))
        {
            strcpy(machineCode, opCode[i]);
            return;
        }
    }
}

// converts a decimal number to binary
void dec2bin(int c, int pos, char str[])
{
    int i = 0;
    strcpy(str, "");
    for (i = pos - 1; i >= 0; i--)
    {
        if ((c & (1 << i)) != 0)
            sprintf(str, "%s1", str);
        else
            sprintf(str, "%s0", str);
    }
}

// Get Address of the Label .The Addresses are computed and stored in the First Pass
// This function makes use of those stored get Address of a Label defined by the user
int findLabelAddr(char lbl[], int sz, struct Labels assLabels[])
{
    for (int c = 0; c < sz; c++)
    {
        if (!strcmp(assLabels[c].lab, lbl))
        {
            strcpy(lbl, assLabels[c].address); // Copy the Address the label
            return 1;
        }
    }
    return 0; // Return 0 if Label not found
}

// Convert Hexadecimal number to binary and return in 16 bit format
void HexToBin(char hexdec[], char bin[])
{
    long int i = 0;
    strcpy(bin, "");

    while (hexdec[i] != '\0' && i < 4)
    {
        switch (hexdec[i])
        {
        case '0':
            append(bin, "0000");
            break;
        case '1':
            append(bin, "0001");
            break;
        case '2':
            append(bin, "0010");
            break;
        case '3':
            append(bin, "0011");
            break;
        case '4':
            append(bin, "0100");
            break;
        case '5':
            append(bin, "0101");
            break;
        case '6':
            append(bin, "0110");
            break;
        case '7':
            append(bin, "0111");
            break;
        case '8':
            append(bin, "1000");
            break;
        case '9':
            append(bin, "1001");
            break;
        case 'A':
        case 'a':
            append(bin, "1010");
            break;
        case 'B':
        case 'b':
            append(bin, "1011");
            break;
        case 'C':
        case 'c':
            append(bin, "1100");
            break;
        case 'D':
        case 'd':
            append(bin, "1101");
            break;
        case 'E':
        case 'e':
            append(bin, "1110");
            break;
        case 'F':
        case 'f':
            append(bin, "1111");
            break;
        }
        i++;
    }

    char tmp[100];
    long long t;
    sscanf(bin, "%lld", &t);
    sprintf(bin, "%016lld", t); //append zeroes in the begining to get it in 16 bit format
}

// function to convert decimal number to binary
void decToHexa(char num[])
{
    long long n = atoi(num);
    strcpy(num, "");
    int i = 0;
    char ch;
    char tmp[100] = "";

    while (n != 0)
    {
        int temp = 0;
        temp = n % 16;

        if (temp < 10)
            ch = temp + 48;
        else
            ch = temp + 55;
        i++;
        n = n / 16;
        sprintf(tmp, "%c%s", ch, num);
        strcpy(num, tmp);
    }
}

// Function to find which which base is the input number in and to convert it to a more
// suitable format for conversion
void convertToHex(char num[])
{
    if (num[strlen(num) - 1] == 'B') // If number is Binary then remove the ending 'B' and
    {                                // append zeroes to it so that it becomes a 16 bit number
        char tmp[100] = "";
        strncpy(tmp, num, strlen(num) - 1);
        long long n;
        sscanf(tmp, "%lld", &n);
        sprintf(num, "%016lld", n);
    }
    else if (num[strlen(num) - 1] == 'D') // Convert Number to hexadecimal for further processing
    {
        char tmp[100] = "";
        strncpy(tmp, num, strlen(num) - 1);
        decToHexa(tmp);
        strcpy(num, tmp);
    }
    else if (num[strlen(num) - 1] == 'H') // Remove the ending 'H'
    {
        char tmp[100] = "";
        strncpy(tmp, num, strlen(num) - 1);
        strcpy(num, tmp);
    }
}

// Function to pretty print 16 bit numbers
void split(char str[])
{
    char tmp[10] = "", tmp2[10] = "";
    strncpy(tmp, str, 8); // Split string into 2 and reconverge adding a space between them
    strncpy(tmp2, str + 8, 8);
    sprintf(str, "%s %s", tmp, tmp2);
}

int main(int argc, char const *argv[])
{

    // Create new file for opCode Table
    FILE *tempFile = fopen("opTable.txt", "w");
    fclose(tempFile);

    // Open input file
    FILE *inputFile = fopen(argv[1], "r");
    if (argc != 2)
        inputFile = fopen("input.asm", "r");
    else
        inputFile = fopen(argv[1], "r");
    fetchOpCode();

    // Declare local variables
    char line[1000], a[1000] = "", b[1000] = "", c[1000] = "", d[1000] = "", t;
    int lblCount = 0, addr = 0, temp, k;

    // Search for start symbol in file
    while (fscanf(inputFile, " %s ", line))
    {
        Stoupper(line);
        if (!strcmp(line, "START"))
            break;
    }
    fscanf(inputFile, "\n");

    while (fscanf(inputFile, "%[ ^\n:]", line) != NULL && !feof(inputFile))
    {
        Stoupper(line);
        if (!strcmp(line, "END"))
            break;

        // Scan inputs from the line
        k = sscanf(line, " %[^;\t ] %[^,;\t ] , %[^;\t ] %s ", a, b, c, d);

        if (k == -1 || k == 0)
        {
            fscanf(inputFile, "%[\n:]", line);
            continue;
        }

        if (k == 1 && strcmp(a, "HLT"))
        {
            if (a[0] == ';')
            {
                continue;
            }
            //Create a new Label
            strcpy(assLabels[lblCount].lab, a);
            sprintf(assLabels[lblCount].address, "%04x", addr);
            lblCount++;
        }
        else
            temp = 4;

        if (k >= 2)
        {
            if (b[0] == 'R')
                temp += 5;
            else
                temp += 16;
        }

        if (k >= 3)
        {
            if (c[0] == 'R')
                temp += 5;
            else
                temp += 16;
        }

        if (!strcmp(a, "LOOP"))
        {
            addr += 7;
            strcpy(a, "JNZ");
            char tmp[10] = "SUB";
            makeOpCodeTable(tmp);
        }
        else if (temp % 8)
            addr += temp / 8 + 1;
        else
            addr += temp / 8;

        fscanf(inputFile, "%[\n:]", line);
        temp = 0;
        makeOpCodeTable(a);
        strcpy(a, "");
        strcpy(c, "");
        strcpy(b, "");
    }

    // Put all the above symbols in a file
    char symtable[2000];
    strcpy(symtable, "");
    for (int i = 0; i < lblCount; i++)
        sprintf(symtable, "%s%s \t %s\n", symtable, assLabels[i].lab, assLabels[i].address);
    printf(symtable);
    FILE *machineCodeFile = fopen("symTable.txt", "w");
    fprintf(machineCodeFile, "%s", symtable);
    fclose(machineCodeFile);

    // First Pass Completed
    // Reset variables
    k = temp = addr = 0;
    fseek(inputFile, 0, SEEK_SET);

    // Second Pass Begins**********************************************************
    while (fscanf(inputFile, "%s", line))
    {
        Stoupper(line);
        if (!strcmp(line, "START"))
            break;
    }
    fscanf(inputFile, "\n");

    char machineCode[10000] = "", opCode[1000], operand1[1000], operand2[1000];

    while (fscanf(inputFile, "%[^\n:]", line) != NULL && !feof(inputFile))

    {
        Stoupper(line);
        if (!strcmp(line, "END"))
            break;

        k = sscanf(line, " %[^;\t ] %[^,;\t ] , %[^;\t ] %s ", a, b, c, d);
        if (!strcmp(a, "LOOP"))
        {
            sprintf(machineCode, "%s\n%04x\t%s\t%s\t\t\t%s", machineCode, addr, "0010", "11111", "00000000 00000001");
            addr += 4;
            strcpy(a, "JNZ");
        }
        if (k == -1 || k == 0)
        {
            fscanf(inputFile, "%[\n:]", line);
            continue;
        }
        if (k == 1 && strcmp(a, "HLT"))
        {
            fscanf(inputFile, "%[\n:]", line);
            continue;
        }
        else if (!strcmp(a, "JNZ") || !strcmp(a, "JMP"))
        {
            // find label and convert
            if (!findLabelAddr(b, lblCount, assLabels))
            {
                printf("UNKNOWN lABEL FOUND\nProgramme Assembly failed\n");
                return 0;
            }
        }

        convertOpCode(a, opCode);
        temp = 4;
        // If it has 2 inputs
        if (k >= 2)
        {
            if (b[0] == 'R')
            {
                temp += 5;
                dec2bin(atoi(b + 1), 5, operand1);
            }
            else
            {
                char ch = b[strlen(b) - 1];
                convertToHex(b);
                temp += 16;
                if (ch != 'B')
                    HexToBin(b, operand1);
                else
                    strcpy(operand1, b);
                split(operand1);
            }
        }
        // If it has 3 inputs
        if (k >= 3)
        {
            if (c[0] == 'R')
            {
                temp += 5;
                dec2bin(atoi(c + 1), 5, operand2);
            }
            else
            {
                char ch = c[strlen(c) - 1];
                convertToHex(c);
                temp += 16;
                if (ch != 'B')
                    HexToBin(c, operand2);
                else
                    strcpy(operand2, c);
                split(operand2);
            }
        }

        if (!strcmp(a, "MUL"))
        {
            strcpy(operand2, operand1);
            strcpy(operand1, "00001");
        }

        sprintf(machineCode, "%s\n%04x\t%s\t%s\t\t\t%s", machineCode, addr, opCode, operand1, operand2);
        if (temp % 8)
            addr += temp / 8 + 1;
        else
            addr += temp / 8;

        fscanf(inputFile, "%[\n:]", line);
        strcpy(operand1, "");
        strcpy(operand2, "");
        strcpy(a, "");
        strcpy(c, "");
        strcpy(b, "");

        temp = 0;
    }

    // Print the res on the outputFile
    machineCodeFile = fopen("output.o", "w");
    fprintf(machineCodeFile, "%s", machineCode);
    printf(machineCode);
    fclose(machineCodeFile);
    return 0;
}
