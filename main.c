#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./StrList.h"
#include <math.h>

#define BUFFER_SIZE 100
#define MAX_SIZE 2


char *input_string()
{
    int initial_size = BUFFER_SIZE;
    char *str = malloc(initial_size * sizeof(char));
    if (str == NULL)
    {
        return NULL;
    }

    int i = 0;
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i + 1 >= initial_size)
        {
            initial_size *= 2;
            str = realloc(str, initial_size * sizeof(char));
            if (str == NULL)
            {
                free(str);
                return NULL;
            }
        }
        str[i++] = ch;
    }

    str[i] = '\0';

    str = realloc(str, (i + 1) * sizeof(char));

    return str;
}

int input_number()
{
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);
    int number;
    sscanf(buffer, "%d", &number);
    return number;
}


// int input_number() {
//     char buffer[100];
//     fgets(buffer, 100, stdin);
//     int number;
//     sscanf(buffer, "%d", &number);
//     return number;
// }

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

        printf("Please choose a number between 1-13 ");
        char buffer[4];
        fgets(buffer, 4, stdin);
        sscanf(buffer, "%d", &choice);
        printf("you chose option %d\n", choice);
        switch (choice)
        {
            case 1:
            if (list != NULL) {
                    printf("Warning: You already have a list. Creating a new list.\n");
                    StrList_free(list);
            }
                list = Choice_one();
                break;
            
            case 2:
               printf("Enter an index number: ");
                index = input_number();
                printf("Enter a String: ");
                data = input_string();
                 StrList_insertAt(list, data, index);                
                break;
            
            case 3:
                StrList_print(list);
                break;
            
            case 4:
                printf("%zu\n", list->size);
                break;
            
            case 5:
                printf("Enter an index number:\n");
                index = input_number();
                StrList_printAt(list, index);
                break;
            
            case 6:
                printf("%d", StrList_printLen(list));
                break;
            
            case 7:
                printf("Enter a string:\n");
                data = input_string();
                int countResult = StrList_count(list, data);
                printf(" the number of occurences is %d\n", countResult);
                break;
            
            case 8:
                printf("Enter a String\n");
                data = input_string();      
                StrList_remove(list, data);
                break;
            
            case 9:
                printf("Enter an index");
                index = input_number();
                StrList_removeAt(list, index);
                break;
            
            case 10:
                StrList_reverse(list);
                break;
    
            case 11:
            if (list == NULL) break;
            StrList_free(list);
            list = NULL;
            break;
            
            case 12:
                StrList_sort(list);
                break;
           
            case 13:
              if(StrList_isSorted(list)) 
              {
                printf("true\n");
              }
               else 
               {
                printf("false\n");
               }

                break;
        }
    }

  if (list != NULL)
    {
        StrList_free(list);
    }

    return 0;
}
