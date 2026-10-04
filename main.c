// Create a morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10   // Command size
#define ISIZE 1000 // Input size

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

// Code from symbol to morse code function;
void code(char encrypt[], dict dictionary)
{

    // Check if input is NULL.
    if (encrypt == NULL)
    {
        printf("Error: No input was given, please try again.\n");
        return;
    }

    // Run through the user input, comparing symbols with morse code.
    for (size_t i = 0; i < strlen(encrypt); ++i)
    {
        // Make every letter lowercase so if user enters uppercase, it gets solved.
        encrypt[i] = tolower(encrypt[i]);

        printf("The ")
        for (size_t j = 0; j < dictionary.size; ++j)
        {
            if(encrypt[i] == ' '){
                printf(" ");
                break;
            }
            else if (encrypt[i] == dictionary.symbol[j])
            {
                printf("%s ", dictionary.morse[j]);
                break;
            }

        }
        
    }
    printf("\n");
}

// Decode, go from morse to symbols.
void decode(char decrypt[], dict dictionary)
{

    // Check if input is NULL.
    if (decrypt == NULL)
    {
        printf("Error: No input was given, please try again.\n");
        return;
    }

    // Create a temporary array to store one morse code at a time.
    // needed, because otherwise user input cant be compared with dictionary.morse[].
    // User input array of char
    // dictionary.morse array of pointers
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
                if (strcmp(morse, dictionary.morse[j]) == 0)
                {
                    printf("%c \n", dictionary.symbol[j]);
                    break;
                }
            }
        }
    }

    // Decode the last morse code, because last code doesnt end in space, it is handled seperatly.
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

void search(char search, dict dictionary)
{

    // Check if input is NULL.
    if (search == '\0')
    {
        printf("Error: No input was given, please try again.\n");
        return;
    }

    for (size_t i = 0; i < dictionary.size; ++i)
    {
        if (search == dictionary.symbol[i])
        {
            printf("The Morse code representation of %c is: %s \n",
                   search, dictionary.morse[i]);
            break;
        }
    }
}

int main(void)
{
    // Initilize the morsecode from a-z then 0-9 in that order.
    dict dictionary = {
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
    char user_input_symbol[2] = "";
    char user_decision[2] = "";

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
        printf("Input a valid command:\n");
        fgets(user_command, sizeof(user_command), stdin);

        // Because fgets() saves \n, find it and change it to \0.
        user_command[strcspn(user_command, "\n")] = '\0';

        // Command: Help:
        if (strcmp(user_command, "help") == 0 || strcmp(user_command, "Help") == 0)
        {
            printf("COMMAND LIST:\n");
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
            printf("Enter what you want to code (You can only code letters and numbers):\n");
            fgets(user_input, sizeof(user_input), stdin);

            user_input[strcspn(user_input, "\n")] = '\0'; // This changes the newline that gets inputted from fgets() to \0.
            code(user_input, dictionary);
            printf("=======================================================\n");
            printf("\n\n");
        }

        // Command: Decode.
        else if (strcmp(user_command, "decode") == 0 || strcmp(user_command, "Decode") == 0)
        {
            printf("Enter the morse code you want to decode (You can only decode letters and numbers):\n");
            fgets(user_input, sizeof(user_input), stdin);

            user_input[strcspn(user_input, "\n")] = '\0';
            decode(user_input, dictionary);
        }

        // Command: Search.
        // else if (strcmp(user_command, "search") == 0 || strcmp(user_command, "Search") == 0)
        // {
        //     printf("Enter a symbol to see its morse representation (You can only enter letters and numbers):\n");
        //     scanf("%c", user_input_symbol);

        //     search(user_input_symbol, dictionary);
        // }
        


        // Command: Exit.
        if (strcmp(user_command, "exit") == 0 || strcmp(user_command, "Exit") == 0)
        {

            printf("Are you sure you want to exit? [Y/N]\n");
            scanf("%c", user_decision);

            if (user_decision == 'y' || user_decision == 'Y')
            {
                printf("Goodbye!");
                break;
            }
            else if (user_decision == 'n' || user_decision == 'N')
            {
                printf("Program will keep running!\n");
            }
            else
            {
                printf("Are you sure you want to exit? [Y/N]\n");
                scanf("%c", user_decision);

            }
        }
    }
    return 0;
}