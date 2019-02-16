#include <stdio.h>
int main(int argc, char const *argv[]) {
    if (argc != 2) return printf("Please give 1 file input");

    FILE *inputFile = fopen(argv[1], "r");
    char a[10],b[10],c[10];
    fscanf(inputFile, "%s %s , %s\n",a,b,c );
    printf("%s\n",a);
    printf("%s\n", b);
    printf("%s\n", c);
    
    return 0;
}