#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copy(char* source, char*destination)
{
    char content[128];

    //Step 1: Open text files and check that they open//
    FILE *fp1, *fp2;
    fp1 = fopen(source,"r");
    fp2 = fopen(destination,"a");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("\nError reading file\n");
        exit(0);
    }
    printf("\nFiles open correctly\n");

    //Step 2: Get text from original file//
    while(fgets(content, sizeof(content), fp1) !=NULL)
    {
        fprintf(fp2, "%s", content);
    }

    printf("File created and text copied to it\n\n");

    //Step 4: Close both files and end program//
    fclose(fp1);
    fclose(fp2);

}