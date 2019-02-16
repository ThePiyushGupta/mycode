#define append(temp, s) sprintf(temp, "%s%s", temp, s);

// This function converts the given opcode into machine code
void convertOpCode(char opCode[], char machineCode[])
{
    if (!strcmp(opCode, "MOV"))
        strcpy(machineCode, "0000");
    else if (!strcmp(opCode, "ADD"))
        strcpy(machineCode, "0001");
    else if (!strcmp(opCode, "SUB"))
        strcpy(machineCode, "0010");
    else if (!strcmp(opCode, "MUL"))
        strcpy(machineCode, "0011");
    else if (!strcmp(opCode, "CMP"))
        strcpy(machineCode, "0100");
    else if (!strcmp(opCode, "AND"))
        strcpy(machineCode, "0101");
    else if (!strcmp(opCode, "OR"))
        strcpy(machineCode, "0110");
    else if (!strcmp(opCode, "NOT"))
        strcpy(machineCode, "0111");
    else if (!strcmp(opCode, "JMP"))
        strcpy(machineCode, "1000");
    else if (!strcmp(opCode, "LOOP"))
        strcpy(machineCode, "1001");
    else if (!strcmp(opCode, "HLT"))
        strcpy(machineCode, "1010");
    else if (!strcmp(opCode, "JNZ"))
        strcpy(machineCode, "1011");
}

// This function tell how many arguments the command requires
int argReq(char opCode[])
{
    if (opCode == "JNZ" || opCode == "LOOP" || opCode == "NOT" ||
        opCode == "JMP" || opCode == "MUL")
        return 1;
    else if (opCode == "HLT")
        return 0;
    else
        return 2;
}

void dec2bin(int c, int pos, char str[])
{
    int i = 0;
    strcpy(str, "");
    for (i = pos - 1; i >= 0; i--)
    {
        if ((c & (1 << i)) != 0)
        {
            sprintf(str, "%s1", str);
        }
        else
        {
            sprintf(str, "%s0", str);
        }
    }
}

typedef struct Labels
{
    char lab[1000], address[10];
};

int findLabelAddr(char lbl[], int sz, struct Labels assLabels[])
{
    for (int c = 0; c < sz; c++)
    {
        if (!strcmp(assLabels[c].lab, lbl))
        {
            strcpy(lbl, assLabels[c].address);
            return 1;
        }
    }
    return 0;
}

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
        if (i == 2)
            append(bin, " ");
    }
}

void convertToHex(char num[])
{
    if (num[strlen(num) - 1] == 'B')
    {
    }
    else if (num[strlen(num) - 1] == 'D')
    {
    }
}

int checkSyn(char opCode[], char operand1[], char operand2[])
{
    if (!strcmp(opCode, "ADD") || !strcmp(opCode, "SUB") || !strcmp(opCode, "OR") || !strcmp(opCode, "AND") || !strcmp(opCode, "MOV"))
    {
        if (operand1[0] != 'R' || !strcmp(operand2, ""))
            return 0;
    }
    else if (!strcmp("CMP", opCode))
    {
        if (!strcmp(operand1, "") || !strcmp(operand2, ""))
            return 0;
    }

    else if (!strcmp("MUL", opCode))
    {
        if (!strcmp(operand1, "") || strcmp(operand2, ""))
            return 0;
    }

    else if (!strcmp("NOT", opCode))
    {
        if (operand1[0] != 'R' || strcmp(operand2, ""))
            return 0;
    }

    else if (!strcmp("JMP", opCode) || !strcmp(opCode, "JNZ") || !strcmp(opCode, "LOOP"))
    {
        if (!strcmp(operand1,"") || strcmp(operand2, ""))
            return 0;
    }

    else if (!strcmp("HLT", opCode))
    {
        if (strcmp(operand1, "") || strcmp(operand2, ""))
            return 0;
    }
    return 1;
}
