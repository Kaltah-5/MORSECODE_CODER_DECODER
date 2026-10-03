// Create a morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10 // Command size
#define ISIZE 1000 // Input size

// My dictionary structure. Morse is an array of pointers, which lets me store strings in each element.
typedef struct Dictionary
{

    int dictionary_id;
    int size;
    char symbol[36];
    const char *morse[36];

} dict;

// Code from symbol to morse code function;
void code(char encrypt[], dict dictionary)
{

    // Check if input is NULL.
    if (encrypt == NULL)
    {
        printf("Error: No input was given, please try again.");
        return;
    }

    // Run through the user input, comparing symbols with morse code.
    for (size_t i = 0; i < strlen(encrypt); ++i)
    {
        // Make every letter lowercase so if user enters uppercase, it gets solved.
        encrypt[i] = tolower(encrypt[i]);

        for (size_t j = 0; j < dictionary.size; ++j)
        {
            if (encrypt[i] == dictionary.symbol[j])
            {
                printf("%s ", dictionary.morse[j]);
                break;
            }
        }
    }
}


// Decode, go from morse to symbols.
void decode(char decrypt[], dict dictionary)
{


    // Check if input is NULL.
    if (decrypt == NULL)
    {
        printf("Error: No input was given, please try again.");
        return;
    }


    // Create a temporary array to store one morse code at a time.
    // needed, because otherwise i cant compare with dictionary.morse[]
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
        

        //IF decrypt[i] == ' ' a space, set the last element to \0, 
        // then search for the matching morse code in the dictionary.
        else
        {

            morse[k] = '\0';
            k = 0;
            for (int j = 0; j < dictionary.size; ++j)
            {
                if (strcmp(morse, dictionary.morse[j]) == 0)
                {
                    printf("%c", dictionary.symbol[j]);
                    break;
                }
            }
        }
    }


    // Decode the last morse code, because last code doesnt end in space, it is handled seperatly.
    if (k > 0)
    {
        morse[k] = '\0';
        for (int j = 0; j < dictionary.size; ++j)
        {
            if (strcmp(morse, dictionary.morse[j]) == 0)
            {
                printf("%c", dictionary.symbol[j]);
                break;
            }
        }
    }
}

int main(void)
{
    // Initilize the morsecode from a-z then 0-9 in that order.
    dict dictionary = {
        .size = 36,
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

    // Let user input one of the commands:
    printf("Input a valid command:\n");
    fgets(user_command, sizeof(user_command), stdin);

    // Because fgets() saves \n, find it and change it to \0.
    user_command[strcspn(user_command, "\n")] = '\0';

    // Compare commands given

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
    // Command: Code
    else if (strcmp(user_command, "code") == 0 || strcmp(user_command, "Code") == 0)
    {
        printf("Enter what you want to code (You can only code letters and numbers):\n");
        fgets(user_input, sizeof(user_input), stdin);

        user_input[strcspn(user_input, "\n")] = '\0'; // This changes the newline that gets inputted from fgets() to a terminator
        code(user_input, dictionary);
    }
    else if (strcmp(user_command, "decode") == 0 || strcmp(user_command, "Decode") == 0)
    {
        printf("Enter the morse code you want to decode (You can only decode letters and numbers):\n");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0';
        decode(user_input, dictionary);
    }

    return 0;
}