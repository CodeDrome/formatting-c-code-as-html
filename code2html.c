#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
void generate_html(char* inputfile);
void populate_mappings(char** mappings);
void set_value(char** array, int index, char* value);

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(int argc, char* argv[])
{
    puts("-----------------");
    puts("| codedrome.com |");
    puts("| Py2HTML       |");
    puts("-----------------\n");

    printf("argc %d\n", argc);

    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d]\t%s\n", i, argv[i]);
    }

    if(argc != 2)
    {
        printf("input file must be specified");
    }
    else
    {
        generate_html(argv[1]);
    }

    return EXIT_SUCCESS;
}

//--------------------------------------------------------
// FUNCTION populate_mappings
//--------------------------------------------------------
void populate_mappings(char** mappings)
{
    // initialize to default values
    for(int i = 0; i <= 127; i++)
    {
        mappings[i] = malloc(2);

        sprintf(mappings[i], "%c", i);
    }

    // overwrite values we want to replace

    // tab
    set_value(mappings, 9, "&nbsp;&nbsp;&nbsp;&nbsp;");

    // linefeed
    set_value(mappings, 10, "</br>\n");

    // carriage return
    set_value(mappings, 13, "");

    // space
    set_value(mappings, 32, "&nbsp;");

    // <
    set_value(mappings, 60, "&lt;");

    // >
    set_value(mappings, 62, "&gt;");
}

//--------------------------------------------------------
// FUNCTION set_value
//--------------------------------------------------------
void set_value(char** array, int index, char* value)
{
    array[index] = realloc(array[index], strlen(value) + 1);

    if(array[index] != NULL)
    {
        strcpy(array[index], value);
    }
    else
    {
        puts("Cannot allocate memory");

        exit(EXIT_FAILURE);
    }
}

//--------------------------------------------------------
// FUNCTION generate_html
//--------------------------------------------------------
void generate_html(char* inputfile)
{
    char* outputfile = malloc(strlen(inputfile) + 6);

    strcpy(outputfile, inputfile);

    strcat(outputfile, ".html\0");

    printf("outputfile: %s\n", outputfile);

    char* mappings[128];

    populate_mappings(mappings);

    // attempt to open files
    FILE* fpinput;
    FILE* fpoutput;
	fpinput = fopen(inputfile, "r");
    fpoutput = fopen(outputfile, "w");

	char c;

    int position = 0;

	if(fpinput != NULL && fpoutput != NULL)
	{
        // iterate input file,
        // writing corresponding values from mappings array to output file
		while((c = fgetc(fpinput)) != EOF)
		{
    		fputs(mappings[c], fpoutput);
            if(c < 0 || c > 127)
            {
               printf("%d\t%c\t%d\n", position, c, c);
            }

            position++;
		}

		fclose(fpinput);

		fclose(fpoutput);

        printf("%s created\n", outputfile);
	}
    else
    {
        puts("Cannot open input or output files");
    }

    // free up malloc'ed memory
    for(int i = 0; i < 128; i++)
    {
        free(mappings[i]);
    }

    free(outputfile);
}
