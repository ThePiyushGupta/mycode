#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Datastructures.c"
#include "supportFunctions.c"
typedef struct Labels Labels;

#define check(s) printf("%d\n", s);
#define checks(s) printf("%s\n", s);
#define append(temp, s) sprintf(temp, "%s %s", temp, s);

// Global Declarations
Labels assLabels[1000];

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return printf("Please give 1 file input");

    FILE *inputFile = fopen(argv[1], "r");
    char line[1000], a[1000] = "", b[1000] = "", c[1000] = "", d[1000]="",t;
    int lblCount = 0, addr = 0, temp, k;

    while (fscanf(inputFile, "%s", line))
    {
        if (!strcmp(line, "START"))
            break;
    }
    fscanf(inputFile, "\n");

    while (fscanf(inputFile, "%[^\n:]", line))
    {
        toupper(line);
        if (!strcmp(line, "END"))
            break;
        k = sscanf(line, " %s %[^, ] , %s", a, b, c);

        //*****************************************************
        // TODO:Check format if correct or incorrect
        // Assuming all inputs and format correct
        // ****************************************************
        if (k == -1)
            continue;
        /* if (!checkSyn(a, b, c))
        {
            printf("SYNTAX ERROR\nASSEMBLY ABORTED\n");
            return 0;
        } */


        if (k == 1 && strcmp(a, "HLT"))
        {
            // TODO: Check if label has already appeared
            strcpy(assLabels[lblCount].lab, a);
            sprintf(assLabels[lblCount].address, "%04x", addr);
            lblCount++;
        }
        else
            temp = 4;
        checks(a);
        check(k);
        if (k >= 2)
        {
            if (b[0] == 'R')
                temp += 5;
            else
                temp += 16;
        }

        if (k == 3)
        {
            if (c[0] == 'R')
                temp += 5;
            else
                temp += 16;
        }

        if (!strcmp(a, "LOOP"))
            addr += 7;
        else if (temp % 8)
            addr += temp / 8 + 1;
        else
            addr += temp / 8;

        fscanf(inputFile, "%[\n:]", line);
        temp = 0;
        strcpy(a, "");
        strcpy(c, "");
        strcpy(b, "");
    }

    char symtable[2000];
    strcpy(symtable, "");
    for (int i = 0; i < lblCount; i++)
        sprintf(symtable, "%s%s \t %s\n", symtable, assLabels[i].lab, assLabels[i].address);
    printf(symtable);

    // First Pass Completed
    k = temp = addr = 0;

    // Second Pass Begins**********************************************************
    fseek(inputFile, 0, SEEK_SET);
    while (fscanf(inputFile, "%s", line))
    {
        if (!strcmp(line, "START"))
            break;
    }
    fscanf(inputFile, "\n");

    char machineCode[10000], opCode[1000], operand1[1000], operand2[1000];

    while (fscanf(inputFile, "%[^\n:]", line))
    {
        toupper(line);
        if (!strcmp(line, "END"))
            break;
        k = sscanf(line, " %s %[^, ] , %s ", a, b, c);

        if (!strcmp(a, "LOOP"))
        {
            sprintf(machineCode, "%s\n%04x\t%s\t%s\t\t\t%s", machineCode, addr, "0010", "11111", "00000000 00000001");
            addr += 4;
            strcpy(a, "JNZ");
        }
        
        if (k == 0)
            continue;
        if (k == 1 && strcmp(a, "HLT"))
        {
            fscanf(inputFile, "%[\n:]", line);
            continue;
        }
        else if (!strcmp(a, "JNZ") || !strcmp(a, "JMP"))
        {
            // find label and convert
            if (findLabelAddr(b, lblCount, assLabels))
                strcpy(operand1, b);
            else
            {
                printf("UNKNOWN lABEL FOUND\nProgramme Assembly failed\n");
                return 0;
            }
        }

        convertOpCode(a, opCode);
        temp = 4;
        if (k >= 2)
        {
            if (b[0] == 'R')
            {
                temp += 5;
                dec2bin(atoi(b + 1), 5, operand1);
            }
            else
            {
                // convertToHex(b);
                temp += 16;
                HexToBin(b, operand1); //hexadecimal to binary
            }
        }

        if (k == 3)
        {

            if (c[0] == 'R')
            {
                temp += 5;
                dec2bin(atoi(c + 1), 5, operand2);
            }
            else
            {
                temp += 16;
                HexToBin(c, operand2);
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
        temp = 0;
    }

    // FILE *machineCodeFile = fopen("output.o", "r");
    // fprintf(machineCodeFile, machineCode);
    printf(machineCode);
    // fclose(machineCodeFile);
    return 0;
}
