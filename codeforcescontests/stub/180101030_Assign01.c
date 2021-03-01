#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



//------------------Hash Table With Chaining-----------------------------------------------------------------------------//



struct hashUnit
{

  struct hashUnit *next;
  char name[20];
  long long int address;
};

//Function for hashing the string 
int
hashFunction (char *name)
{
  int sum = 0;
  char *s = name;
  while (*s)
  {
      sum += *s;
      s++;
  }
  return sum % 997;
}

//Searching in hash table
struct hashUnit *
search (struct hashUnit *hashTable[997], char *name)
{
  int index = hashFunction (name);
  struct hashUnit *head = hashTable[index];

  while (head != NULL)
  {
      if (strcmp (head->name, name) == 0)
	  {
	  return head;
	  }
      head = head->next;
  }
  return NULL;
}

//Inserting into Hash Table
bool
insert (struct hashUnit * hashTable[997], char *name, long long int address)
{
  int index = hashFunction (name);

  struct hashUnit *head = hashTable[index];

  if (head == NULL)
  {

      head = (struct hashUnit *) malloc (sizeof (struct hashUnit));
      strcpy (head->name, name);
      head->next = NULL;
      head->address = address;
      hashTable[index] = head;
      return 1;
   }

  struct hashUnit *prev = NULL;
  while (head->next != NULL)
  {
      if (strcmp (head->name, name) == 0)
	  {
	  return 0;
	  }
      head = head->next;
  }
  struct hashUnit *newnode =(struct hashUnit *) malloc (sizeof (struct hashUnit));

  strcpy (newnode->name, name);
  newnode->next = NULL;
  newnode->address = address;
  head->next = newnode;
  return 1;
}

//Function to display hashtable
void
display (struct hashUnit *hashTable[997])
{
  int count = 0;
  for (int i = 0; i < 997; i++)
  {
      struct hashUnit *head = hashTable[i];
      while (head != NULL)
	  {
	  count++;
	  printf ("%s : %lld\n", head->name, head->address);
	  head = head->next;
	  }
  }

  return;

}

//Deleting Hash Table
void
delete (struct hashUnit *hashTable[997])
{
  for (int i = 0; i < 997; i++)
  {
      struct hashUnit *head = hashTable[i];
      struct hashUnit *next;
      while (head != NULL)
	  {
	  next = head->next;
	  free (head);
	  head = next;
	  }
  }
  return;
}

//--------------------------------------Intitializations and other helpful functions -------------------------------//


//define hash table with predfined size as 997
struct hashUnit *opTable[997];	//to access opcodes
struct hashUnit *symTable[997];	//To access addresses of symbols
int errorFlag[3] = { 0 };	//Error in first Flag
int e[3] = { 0 };		//Error in second Flag

int programLength = 0;		//Length of program
long long int startingAddress = 0;


//Constructuing OPTABLE
void
constructOpTable ()
{

  //As given in the assignment
  insert (opTable, "LDA", 0);
  insert (opTable, "LDX", 4);
  insert (opTable, "LDL", 8);
  insert (opTable, "STA", 12);
  insert (opTable, "STX", 16);
  insert (opTable, "STL", 20);
  insert (opTable, "LDCH", 80);
  insert (opTable, "STCH", 84);
  insert (opTable, "ADD", 24);
  insert (opTable, "SUB", 28);
  insert (opTable, "MUL", 32);
  insert (opTable, "DIV", 36);
  insert (opTable, "COMP", 40);
  insert (opTable, "J", 60);
  insert (opTable, "JLT", 56);
  insert (opTable, "JGT", 52);
  insert (opTable, "JSUB", 72);
  insert (opTable, "RSUB", 76);
  insert (opTable, "TIX", 44);
  insert (opTable, "TD", 224);
  insert (opTable, "RD", 216);
  insert (opTable, "WD", 220);
  insert (opTable, "JEQ", 48);
}


//Function to convert Hexadecimal to decimal number
long long int
convertHexToDec (char *s)
{
  long long int num = 0;
  long long int power = 1;
  int n = strlen (s);
  for (int i = n - 1; i >= 0; i--)
  {
      if (s[i] >= '0' && s[i] <= '9')num += (s[i] - '0') * power;
	
      else if (s[i] >= 'a' && s[i] <= 'f')num += (s[i] - 'a' + 10) * power;
	
      else if (s[i] >= 'A' && s[i] <= 'F')num += (s[i] - 'A' + 10) * power;
	
      power *= 16;
  }
  return num;
}

//--------------------------------------------------PASS1-------------------------------------------------------------//

//Fole pointer "prog" refers to the input file
bool
PassOne (FILE * prog)
{

  //Defining variables 
  char label[20], opcode[20], operand[20];
  char *buffer = NULL;
  long long int locctor = 0;
  int retValue = 0;
  size_t len = 0;
  ssize_t read;
  FILE *finter = fopen ("Intermediate.txt", "w+");

  //Read first input line
  read = getline (&buffer, &len, prog);
  sscanf (buffer, "%s %s %s", label, opcode, operand);


  //If starting line starts with START,then save the locctr value
  if (strcmp (opcode, "START") == 0)
  {
      startingAddress = convertHexToDec (operand);
      locctor = startingAddress;
      fprintf (finter, "%04llX\t%s\t%s\t%s\n", locctor, label, opcode,
	       operand);

      //Again read the line
      read = getline (&buffer, &len, prog);
      retValue = sscanf (buffer, "%s%s%s", label, opcode, operand);
      if (retValue == 1)
	  {
	    if (label[0] != '.')
	    {
	      strcpy (opcode, label);
	      strcpy (label, "");
	      strcpy (operand, "");
	    }
	    else
	    {
	      strcpy (opcode, "");
	      strcpy (operand, "");
	    }
	  }
      else if (retValue == 2)
	  {
	    if (label[0] != '.')
	    {
	      strcpy (operand, opcode);
	      strcpy (opcode, label);
	      strcpy (label, "");
	    }
	    else
	    {
	      strcpy (operand, "");
	    }
	  }

    }
  else
    {
      locctor = 0;
    }

  long long int printlocctor = locctor;

  //Now we process the remaining lines from input file.
  while (strcmp (opcode, "END"))
    {
      //If not a comment line
      if (label[0] != '.')
	  {

	  //If it is a symbol declaration, then insert the symbol in the table
	    if (strlen (label))
	    {

	      if (search (symTable, label) == NULL)
		  {
		  insert (symTable, label, locctor);
		  }
	      else
		  {
 
		  printf ("ERROR: DUPLICATE VARIABLE:%s\n", label);
		  errorFlag[0]++;
		  }
	    }

	  //Increment locctor value accordingly
	    if (search (opTable, opcode) != NULL)
	    {
	      locctor += 3;
	    }
	    else if (strcmp (opcode, "WORD") == 0)
	    {
	      locctor += 3;
	    }
	    else if (strcmp (opcode, "RESW") == 0)
	    {
	      locctor += 3 * atoi (operand);
	    }
	    else if (strcmp (opcode, "RESB") == 0)
	    {
	      locctor += atoi (operand);
	    }
	    else if (strcmp (opcode, "BYTE") == 0)
	    {
	       if (operand[0] != 'C' && operand[0] != 'X')locctor += 1;
	       else if (operand[0] == 'C')locctor += strlen (operand) - 3;
	       else if (operand[0] == 'X')locctor +=((strlen (operand) - 3) / 2) + ((strlen (operand) - 3) % 2);
	    }
	    else
	    {
	      printf ("ERROR: INVALID OPCODE:%s \n", opcode);
	      printf ("%s\n%s\n%s\n", label, opcode, operand);
	      errorFlag[1]++;
	    }
	}

      //Print the line into intermediate file
      fprintf (finter, "%04llX\t%s\t%s\t%s\n", printlocctor, label, opcode,operand);
      printlocctor = locctor;

      //Read the next line and process it
      read = getline (&buffer, &len, prog);
      retValue = sscanf (buffer, "%s%s%s", label, opcode, operand);

      if (retValue == 1)
	  {
	    if (label[0] != '.')
	    {
	      strcpy (opcode, label);
	      strcpy (label, "");
	      strcpy (operand, "");
	    }
	    else
	    {
	      strcpy (opcode, "");
	      strcpy (operand, "");
	    }
	  }
      else if (retValue == 2)
	  {
	    if (label[0] != '.')
	    {
	      strcpy (operand, opcode);
	      strcpy (opcode, label);
	      strcpy (label, "");
	    }
	    else
	    {
	      strcpy (operand, "");
	    }
	  }

    }

  //wrute last line

  fprintf (finter, "%04X\t%s\t%s\t%s\n", 0, label, opcode, operand);
  printf ("\nPASS 1 COMPLETED\n");

  //Save lngth of the program
  programLength = locctor - startingAddress;
  printf ("\nLENGTH OF THE PROGRAM IS %d BYTES\n", programLength);

  fclose (prog);
  fclose (finter);
  return 1;
}

//-------------------------------------------PASS2-------------------------------------------------------------------------//

bool
passTwo (FILE * prog)
{

  //declare variables
  char label[20], opcode[20], operand[20], address[10], programName[10];
  char *buffer = NULL;
  long long int locctor = 0, operandAddress = 0;
  bool isWrite = 0;
  int retValue = 0;
  size_t len = 0;
  ssize_t read;

  //open files for writing 
  FILE *fassem = fopen ("Assembly_listing.txt", "w+");
  FILE *fobj = fopen ("Object_program.txt", "w+");

  //Read the first line
  read = getline (&buffer, &len, prog);
  sscanf (buffer, "%llX%s%s%s", &locctor, label, opcode, operand);
  strcpy (programName, label);

  //if it starts with "START"
  if (strcmp (opcode, "START") == 0)
  {

      //Write listing line
      fprintf (fassem, "%04llX\t%s\t%s\t%s\n", locctor, label, opcode,operand);

      //Read next line
      read = getline (&buffer, &len, prog);
      retValue =
	  sscanf (buffer, "%llX%s%s%s", &locctor, label, opcode, operand);


      if (retValue == 2)
	  { 

	    if (label[0] != '.')
	    {
	      strcpy (opcode, label);
	      strcpy (label, "");
	      strcpy (operand, "");
	    }
	    else
	    {
	      strcpy (opcode, "");
	      strcpy (operand, "");
	    }
	}
      else if (retValue == 3)
	  {
	    if (label[0] != '.')
	    {
	      strcpy (operand, opcode);
	      strcpy (opcode, label);
	      strcpy (label, "");
	    }
	    else
	    {
	      strcpy (operand, "");
	    }
	  }
    }

  int text_length = 0;
  char text_record[100] = { 0 };
  bool to_write = 1;
  int i = 0;
  long long int printedLocctor = locctor;

  //Write header line into the program
  fprintf (fobj, "H^");
  int l=0;
  int n=strlen(programName);
  while(l<n&&l<6){fprintf (fobj, "%c",programName[l]);l++;}
  while(l<6){fprintf (fobj, " ");l++;}
  fprintf (fobj, "^%06llX^%06X",  startingAddress,programLength);

  //Prcoess the further lines
  while (strcmp ("END", opcode))
  {
      char *present_record;
      int incr = 0;
      int pi = 0;

      //If not a comment line
    if (label[0] != '.')
	{

	  //search optb for opcode
	  if (search (opTable, opcode) != NULL)
	  {

	      //if there is a symbol in operand field
	    if (strlen (operand) > 0)
		{
		  char symbol_name[20];

		  bool isOperand = false;

		  int n = strlen (operand);

		  for (int i = 0; i < n - 1; i++)
		  {
		    if (operand[i] == ',' && operand[i + 1] == 'X')
			{
			  symbol_name[i] = '\0';
			  isOperand = true;
			  break;
			}
		      symbol_name[i] = operand[i];
		  }

		  //if the there is a symbol in operand field
		  if (isOperand)
		  {
		      //Search symtab for symbol
		    if (search (symTable, symbol_name))
			{
			  operandAddress =
			    search (symTable, symbol_name)->address;
			  operandAddress += 32768;
			}
		    else
			{
			  printf ("ERROR  UNDEFINED\n");
			  operandAddress = 0;
			  e[0]++;
			}
		  }
		  else if (search (symTable, operand))
		  {
		      operandAddress = search (symTable, operand)->address;
		  }
		  else
		  {
		      printf ("ERROR UNDEFINED:%s:%s:%s\n", label, opcode, operand);
		      operandAddress = 0;
		      e[0]++;
		  }

		}
	    else
		{
		  operandAddress = 0;

		}

	      //assemble the object code instruction
	    long long int opCode = search (opTable, opcode)->address;
	    sprintf (present_record, "%02llX%04llX", opCode,operandAddress);
	    incr += 3;
	    }
	    else if (!(strcmp (opcode, "BYTE") && strcmp (opcode, "WORD")))
	    {

	      //cpnvert constant to object code
	      if (operand[0] == 'C')
		  {
		    int x = 0;
		    for (int i = 2; i < strlen (operand) - 1; i++)
		    {
		      int p = (int) operand[i];

		      sprintf (present_record + x, "%X", p);
		      x = strlen (present_record);

		    }
		    incr += strlen (operand) - 3;
		  }
	      else if (operand[0] == 'X')
		  {
		    for (int i = 2; i < strlen (operand) - 1; i++)
		    {

		      sprintf (present_record + pi, "%c",
			       (char) (operand[i]));
		      pi++;
		    }

		    incr += (strlen (operand) - 3) / 2;
		  }
	      else
		  {

		  sprintf (present_record, "%06X", atoi (operand));
		  incr += 3;
		  }

	    }

	  //if object code will not fit into the current text record,then
	    if (text_length + incr > 30)
	    {
	      fprintf (fobj, "\nT^%06llX^", printedLocctor);
	      fprintf (fobj, "%02X", text_length);
	      fprintf (fobj, "%s", text_record);
	      text_length = incr;
	      printedLocctor = locctor;
	      strcpy (text_record, "^");
	      strcpy (text_record + 1, present_record);
	      isWrite = 0;

	    }
	    else
	    {
	      int n = (int) strlen (text_record);
	      if (text_record[n - 1] != '^')
		  {
		  strcpy (text_record + n, "^");
		  strcpy (text_record + n + 1, present_record);
		  }
	      else
		  {
		  strcpy (text_record + n, present_record);
		  }

	      text_length += incr;
	      isWrite = 0;
	    }
	  //wrte lisitng line
	    fprintf (fassem, "%04llX\t%s\t%s\t%s\t%s\n", locctor, label, opcode,operand, present_record);
	    }
      else
	  {
	  //write listing line
	  fprintf (fassem, ".");
	  if (strlen (opcode) > 0)fprintf (fassem, "\t%s", opcode);
	  if (strlen (operand) > 0)fprintf (fassem, "\t%s", operand);
	  fprintf (fassem, "\n");

	  }

      //read next line
      read = getline (&buffer, &len, prog);
      retValue =
	  sscanf (buffer, "%llX%s%s%s", &locctor, label, opcode, operand);


    if (retValue == 2)
	{

	    if (label[0] != '.')
	    {
	      strcpy (opcode, label);
	      strcpy (label, "");
	      strcpy (operand, "");
	    }
	    else
	    {
	      strcpy (opcode, "");
	      strcpy (operand, "");
	    }
	}
    else if (retValue == 3)
	{
	    if (label[0] != '.')
	    {
	      strcpy (operand, opcode);
	      strcpy (opcode, label);
	      strcpy (label, "");
	    }
	    else
	    {
	      strcpy (operand, "");
	    }
	}


    if ((!strcmp (opcode, "RESW")) || (!strcmp (opcode, "RESB")))
	{
	  fprintf (fobj, "\nT^%06llX^", printedLocctor);
	  fprintf (fobj, "%02X", text_length);
	  if (text_length > 0)
	  {
	      fprintf (fobj, "%s", text_record);
	      text_length = 0;
	  }
	  printedLocctor = locctor;
	  strcpy (text_record, "^");

	  isWrite = 1;
	}
    bool res = 0;

    while (!strcmp (opcode, "RESW") || !strcmp (opcode, "RESB"))
	{
	  fprintf (fassem, "%04llX\t%s\t%s\t%s\n", locctor, label, opcode,operand);
	  read = getline (&buffer, &len, prog);
	  retValue =sscanf (buffer, "%llX%s%s%s", &locctor, label, opcode, operand);
	  
	  res = 1;
	  if (retValue == 2)
	  {

	      if (label[0] != '.')
		  {
		  strcpy (opcode, label);
		  strcpy (label, "");
		  strcpy (operand, "");
		  }
	      else
		  {
		  strcpy (opcode, "");
		  strcpy (operand, "");
		  }
	  }
	  else if (retValue == 3)
	  {
	      if (label[0] != '.')
		  {
		  strcpy (operand, opcode);
		  strcpy (opcode, label);
		  strcpy (label, "");
		  }
	      else
		  {
		  strcpy (operand, "");
		  }
	  }
	}
    if (res)printedLocctor = locctor;

    }
  //write last text record to object program
    if (text_length > 0)
    {

      fprintf (fobj, "\nT^%06llX^", printedLocctor);
      fprintf (fobj, "%02X", text_length);
      fprintf (fobj, "%s", text_record);

    }
  //write end record
  fprintf (fobj, "\nE^%06llX", startingAddress);


  fprintf (fassem, "\t%s\t%s\t%s\n", label, opcode, operand);
  printf ("\nPASS 2 COMPLETED\n");


  fclose (prog);
  fclose (fassem);
  fclose (fobj);
  return 1;


}

int
main (int argc, char **argv)
{

  for (int i = 0; i < 997; i++)
  {
      opTable[i] = NULL;
  }
  constructOpTable ();

  //open input file
  if (argc == 1)
  {
      printf("Please pass the name of input file as an argument while executing the program\n");
      return 0;
  }
  FILE *fProg = fopen (argv[1], "r");


  if (fProg == NULL)
  {
      printf ("Can't Open the program file\n");
      return 0;
  }

  PassOne (fProg);

  fProg = fopen ("Intermediate.txt", "r");
  if (fProg == NULL)
  {
      printf ("Can't Open the File generaed by pass1\n");
      return 0;
  }
  passTwo (fProg);

  printf ("\nTHE SYMTABLE IS :\n");
  display (symTable);


  delete (symTable);
  delete (opTable);

  return 0;

}

