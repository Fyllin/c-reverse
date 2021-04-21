/*
 * CT30A3370 Käyttöjärjestelmät ja systeemiohjelmointi
 * Project 1: Warmup to C and Unix programming
 * Creator: Ville Felin
 *
 * with a bit of help from https://stackoverflow.com/questions/54872583/c-linked-list-with-dynamic-node-size/54872887
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define True 1

//Creating a struct for the linked list
struct Node {
    char *line;
    struct Node* pNext;
    struct Node* pPrevious;
};
typedef struct Node Node;


int main(int argc, char *argv[]) {

    Node *pList = NULL;
    FILE *input;
    FILE *output;
    Node *ptr;
    Node *ptr2;
    size_t line;
    int isstdin = 0;

    //Checking the input and output
    switch(argc){

        case 1:

            //no arguments -> input: stdin & output: stdout

            input = stdin;
            isstdin = 1;
            output = stdout;

            printf("Using standard input, '/exit' to exit\n>");

            break;

        case 2:

            //1 argument -> input: file & output: stdout


            if ((input = fopen(argv[1], "r")) == NULL) {
                fprintf(stderr, "Error reading the input file.\n");
                exit(1);
            }
            output = stdout;

            break;

        case 3:

            //2 arguments -> input: file & output: file

            if (strcmp(argv[1], argv[2]) == 0) {

                fprintf(stderr, "Input and output file must differ.\n");
                exit(1);

            }

            if ((input = fopen(argv[1], "r")) == NULL) {
                fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
                exit(1);
            }
            if ((output = fopen(argv[2], "w")) == NULL) {
                fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
                exit(1);
            }

            break;

        default:

            //Wrong number of arguments

            printf("usage: reverse <input> <output>\n");
            exit(1);

    }

    //Reading the input file line by line
    while(True) {

        //buffer for getline
        size_t buffersize = 0;

        char *buffer = malloc(buffersize * sizeof(char));
        if (buffer == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        //Using getline() to get the whole line
        line = getline(&buffer, &buffersize, input);

        //Indicating end of file
        if (line == -1) break;

        //"/exit" is the escape command in stdin
        if (isstdin == 1 && strcmp("/exit\n", buffer) == 0 ) break;

        //removing newline from the line
        buffer[strcspn(buffer, "\n")] = 0;

        //Creating a new node for the line and inserting the line there
        Node *newNode = NULL;
        newNode = malloc(sizeof(Node));
        if (newNode == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        newNode->line = buffer;
        newNode->pNext = NULL;
        newNode->pPrevious = NULL;

        //Inserting the node to the linked list
        if (pList == NULL) {

            pList = newNode;

        } else {

            ptr = pList;

            while (ptr->pNext != NULL) ptr = ptr->pNext;

            newNode->pPrevious = ptr;
            ptr->pNext = newNode;
        }
    }

    //If there are no lines in the linked list, end here
    if (pList == NULL) return 0;

    //Otherwise go to the end of the list
    ptr = pList;
    while (ptr->pNext != NULL) ptr = ptr->pNext;

    //Printing the lines to output one by one and freeing the memory of the node after that
    fprintf(output, "\n");
    while (ptr != NULL) {

        fprintf(output, "%s\n", ptr->line);

        ptr2 = ptr;
        ptr = ptr->pPrevious;

        free(ptr2->line);
        free(ptr2);

    }


    fclose(input);
    fclose(output);

    return 0;
}


