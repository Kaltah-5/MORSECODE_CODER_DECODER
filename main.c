// Create a morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10   // Command size.
#define ISIZE 1000 // Input size.
#define SSIZE 3    // Single char size.

// My dictionary structure. Morse is an array of pointers, which lets me store strings in each element.
typedef struct Dictionary
{

    int dictionary_id;
    int size;
    char symbol[36];
    const char *morse[36];

} dict;

struct coder_decoder
{
    dict Dictionary;
    int current_dictionary_id;
};

// Code function: code letters and numbers to their morse codes representation.
void code(char encrypt[], dict dictionary)
{

    // Check if input is NULL.
    if (encrypt == NULL)
    {
        printf("ERROR: No input was given, please try again.\n");
        return;
    }

    printf("The morse code representation of \"%s\" is: \n", encrypt);

    // Run through the user input, comparing symbols with morse code.
    for (size_t i = 0; i < strlen(encrypt); ++i)
    {
        // Make every letter lowercase so if user enters uppercase.
        encrypt[i] = tolower(encrypt[i]);

        for (size_t j = 0; j < dictionary.size; ++j)
        {
            // If statement to help seperate words, if input contains more than 1 word.
            if (encrypt[i] == ' ')
            {
                printf(" ");
                break;
            }

            // Print the morse code representation of each symbol.
            else if (encrypt[i] == dictionary.symbol[j])
            {
                printf("%s ", dictionary.morse[j]);
                break;
            }
        }
    }
    printf("\n");
}

// Decode function: Decode morse code to letters and numbers.
void decode(char decrypt[], dict dictionary)
{

    // Check if input is NULL.
    if (decrypt == NULL)
    {
        printf("ERROR: No input was given, please try again.\n");
        return;
    }

    // Create a temporary array to store one morse code at a time.
    // needed, because otherwise user input cant be compared with dictionary.morse[].
    // User input array of char
    // dictionary.morse is an array of pointers
    char morse[10];

    // Keeps track of next pos in morse[] array.
    size_t k = 0;

    // Run through the user input:
    for (size_t i = 0; i < strlen(decrypt); ++i)
    {
        // IF no space is found, save the morse code in the morse[] array
        if (decrypt[i] != ' ')
        {
            morse[k] = decrypt[i];
            ++k;
        }

        // IF decrypt[i] == ' ' a space, set the last element in morse [] to \0,
        //  Reset k counter,
        //  then search for the matching morse code in the dictionary.
        else
        {
            
            morse[k] = '\0';
            k = 0;
            for (size_t j = 0; j < dictionary.size; ++j)
            {
                if(morse == " "){
                    printf(" ");
                }
                else if (strcmp(morse, dictionary.morse[j]) == 0)
                {
                    printf("%c", dictionary.symbol[j]);
                    break;
                }
            }
        }
    }

    // Decode the last morse code, because last code doesnt end in space, it is handled separatly.
    if (k > 0)
    {
        morse[k] = '\0';
        for (size_t j = 0; j < dictionary.size; ++j)
        {
            if (strcmp(morse, dictionary.morse[j]) == 0)
            {
                printf("%c \n", dictionary.symbol[j]);
                break;
            }
        }
    }
}

// Search function: Find the morse code representation of a singel letter or number
void search(char find[], dict dictionary)
{

    // Check if input is NULL.
    if (find == NULL)
    {
        printf("ERROR: No input was given, please try again.\n");
        return;
    }

    for (size_t i = 0; i < dictionary.size; ++i)
    {
        find[0] = tolower(find[0]);
        // If the first element is found, print the morse code representation.
        if (find[0] == dictionary.symbol[i])
        {
            printf("The Morse code representation of %c is: %s\n", find[0], dictionary.morse[i]);
            break;
        }
        else
        {
            printf("ERROR: Please enter a valid symbol (Letters or numbers).\n");
            fgets(find, SSIZE, stdin);
            find[strcspn(find, "\n")] = '\0';
            break;
            search(find, dictionary);
        }
    }
}

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
    }

    return 0;
}