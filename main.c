// Create a morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#include "morse.h"
#define CSIZE 10   // Command size.
#define ISIZE 1000 // Input size.
#define SSIZE 3    // Single char size.

int exit_program(char user_char[])
{
    if (user_char[0] == '\0')
    {
        printf("ERROR: No input was given, please try again.\n");
        return 0;
    }

    while (1)
    {
        if (strcmp(user_char, "y") == 0 || strcmp(user_char, "Y") == 0)
        {
            printf("Goodbye!");
            return 1;
        }
        else if (strcmp(user_char, "n") == 0 || strcmp(user_char, "N") == 0)
        {
            printf("Program will keep running!\n");
            return 0;

            // Keep the program running, go back to the beginning of the while loop.
        }
        else
        {

            printf("ERROR: Please enter Y or N \n");
            fgets(user_char, SSIZE, stdin);
            user_char[strcspn(user_char, "\n")] = '\0';
        }
    }
}

int main(void)
{
    // Initilize the morsecode from a-z then 0-9 in that order.
    dict dictionary = {
        .dictionary_id = 1,
        .size = 36,

        // Array of pointers:
        .morse = {
            ".-", "-...", "-.-.", "-..", ".",
            "..-.", "--.", "....", "..", ".---",
            "-.-", ".-..", "--", "-.", "---",
            ".--.", "--.-", ".-.", "...", "-",
            "..-", "...-", ".--", "-..-", "-.--",
            "--..", "-----", ".----", "..---",
            "...--", "....-", ".....", "-....",
            "--...", "---..", "----."}};

    // Store user input.
    char user_command[CSIZE] = "";
    char user_input[ISIZE] = "";
    char user_input_symbol[SSIZE] = "";
    char user_decision[SSIZE] = "";

    // Loop to fill up the array from a-z then 0-9 in that order.
    for (int i = 0; i < 36; i++)
    {

        if (i >= 26)
        {
            dictionary.symbol[i] = '0' + (i - 26);
        }
        else
        {
            dictionary.symbol[i] = 'a' + i;
        }
    }

    // Menu at start.
    printf("=====================================================\n");
    printf("============= MORSE CODE: CODER-DECODER =============\n");
    printf("=====================================================\n\n");

    // Commands provided immediately for better user experience.
    printf("COMMAND LIST:\n");
    printf("-------------------------------------------------------\n");
    printf("help - shows the list of commands and what they do.\n");
    printf("code - code the input text in Morse code\n");
    printf("decode - decode the entered Morse code.\n");
    printf("search - shows Morse code for the specified symbol\n");
    printf("show - Shows a table with Morse code\n");
    printf("exit - exit the program\n");
    printf("-------------------------------------------------------\n");

    while (1)
    {
        // Let user input one of the commands:
        printf("\nInput a valid command:\n");
        fgets(user_command, CSIZE, stdin);

        // Because fgets() saves \n, find it and change it to \0.
        user_command[strcspn(user_command, "\n")] = '\0';

        // Command: Help:
        if (strcmp(user_command, "help") == 0 || strcmp(user_command, "Help") == 0)
        {
            printf("\nCOMMAND LIST:\n");
            printf("-------------------------------------------------------\n");
            printf("help - shows the list of commands and what they do.\n");
            printf("code - code the input text in Morse code\n");
            printf("decode - decode the entered Morse code.\n");
            printf("search - shows Morse code for the specified symbol\n");
            printf("show - Shows a table with Morse code\n");
            printf("exit - exit the program\n");
            printf("-------------------------------------------------------\n");
        }

        // Command: Code.
        else if (strcmp(user_command, "code") == 0 || strcmp(user_command, "Code") == 0)
        {
            printf("\nEnter what you want to code (You can only code letters and numbers):\n");
            fgets(user_input, ISIZE, stdin);

            user_input[strcspn(user_input, "\n")] = '\0'; // This changes the newline that gets inputted from fgets() to \0.
            code(user_input, dictionary);
            printf("=======================================================\n");
            printf("\n\n");
        }

        // Command: Decode.
        else if (strcmp(user_command, "decode") == 0 || strcmp(user_command, "Decode") == 0)
        {
            printf("\nEnter the morse code you want to decode (You can only decode letters and numbers):\n");
            fgets(user_input, ISIZE, stdin);

            user_input[strcspn(user_input, "\n")] = '\0';
            decode(user_input, dictionary);
        }

        // Command: Search.
        else if (strcmp(user_command, "search") == 0 || strcmp(user_command, "Search") == 0)
        {
            printf("\nEnter a symbol to see its morse representation (You can only enter letters and numbers):\n");
            fgets(user_input_symbol, SSIZE, stdin);
            user_input_symbol[strcspn(user_input_symbol, "\n")] = '\0';

            search(user_input_symbol, dictionary);
        }

        // Command: Exit.
        else if (strcmp(user_command, "exit") == 0 || strcmp(user_command, "Exit") == 0)
        {
            printf("\nAre you sure you want to exit? [Y/N]\n");
            fgets(user_decision, SSIZE, stdin);
            user_decision[strcspn(user_decision, "\n")] = '\0';

            if (exit_program(user_decision) == 1)
            {
                break;
            }
        }

        // Command: Show.
        else if (strcmp(user_command, "show") == 0 || strcmp(user_command, "Show") == 0)
        {
            show(dictionary);
        }
    }

    return 0;
}