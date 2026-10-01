// Create a Morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10

// My dictionary structure. Morse is a array of pointers, which lets me store strings in each element.
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

    // Check for NULL case.
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

    // Check for NULL case.
    if (decrypt == NULL)
    {
        printf("Error: No input was given, please try again.");
        return;
    }

    // Run through the user input, comparing symbols with morse code.
    for (size_t i = 0; i < strlen(decrypt); ++i)
    {

        for (size_t j = 0; j < dictionary.size; ++j)
        {
            if (decrypt[i] == dictionary.morse[j])
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
    char user_input[1000] = "";

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
    printf("Input a valid cogmmand:\n");
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
        code(user_input, dictionary);
    }
    else if (strcmp(user_command, "decode") == 0 || strcmp(user_command, "Decode") == 0)
    {
        printf("Enter the morse code you want to decode (You can only decode letters and numbers):\n");
        fgets(user_input, sizeof(user_input), stdin);
    }

    return 0;
}