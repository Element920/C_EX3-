#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./StrList.h"
#include <math.h>


#define MAX_SIZE 2


char *input_string()
{

    int num = 0;
    int counter = 0;
    char *str = malloc(sizeof(char) * (MAX_SIZE + 1));
    char *addr = str;

    while (1)
    {
        if (counter == MAX_SIZE)
        {
            counter = 0;
            char *new = malloc(sizeof(char) * (num + MAX_SIZE + 1));
            strcpy(new, str);
            free(str);
            str = new;
            addr = new + num;
        }
        char t;
        scanf("%c", &t);
        if (t == '\n')
            break;
        *addr = t;
        addr += 1;
        counter += 1;
        num += 1;
    }

    return str;
}


int input_number() {
    char buffer[100];
    fgets(buffer, 100, stdin);
    int number;
    sscanf(buffer, "%d", &number);
    return number;
}

StrList* Choice_one()
{
    printf("please enter the number of words ");
    StrList* list = StrList_alloc();
    int numberOfWords = input_number();

    list->size = numberOfWords;
    list->data = (char**)malloc(sizeof(void*)*numberOfWords);

    char ** wordsPtr = list->data;
    char * input = input_string();
    char* token = strtok(input, " ");
    while (token != NULL) {
        size_t length = strlen(token);
        char* word = malloc(length+1);
        strcpy(word, token);
        *wordsPtr = word;
        wordsPtr += 1;
        token = strtok(NULL, " ");
    }
    free(input);
    return list;
}



int main()
{
    int index = 0;
    char* data = ""; 
    int choice = 14;
    StrList* list = NULL;
    while (choice != 0)
    {
        //   printf("Enter 0 to exit the loop: ");
        //         scanf("%d", &flag);

        printf("Please choose a number between 1-13 ");
        char buffer[3];
        fgets(buffer, 3, stdin);
        sscanf(buffer, "%d", &choice);
        printf("you chose option %d\n", choice);
        switch (choice)
        {
            case 1:
                list = Choice_one();
                break;
            case 2:
                printf("Enter an index number");
                scanf("%d", &index);
                printf("Enter a String");
                scanf("%s", data);
                StrList_insertAt(list, data, index);
                break;
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%zu", list->size);
                break;
            case 5:
                printf("Enter an index number");
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            
            case 6:
                printf("%d", StrList_printLen(list));
                break;
            case 7:
                printf("Enter a String");
                scanf("%s", data);
                StrList_count(list, data);
                break;
            case 8:
                printf("Enter a String");
                scanf("%s", data);      
                StrList_remove(list, data);
                break;
            case 9:
                printf("Enter an index number");
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
    
            case 11:
                StrList_free(list);
                break;
            
            case 12:
                StrList_sort(list);
                break;
            case 13:
                StrList_isSorted(list);
                break;
        }
    }

    StrList_free(list);

    return 0;
}