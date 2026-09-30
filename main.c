// Create a Morse code coder-decoder program.
#include <stdio.h>
#include <string.h>
#define CSIZE 10

typedef struct Dictionary
{

    int dictionary_id;
    int size;
    char symbol[36];
    const char *morse[36];

} dict;

void code(char encrypt[], dict dictionary)
{

    if (encrypt == NULL)
    {
        printf("Error: No input was given, please try again.");
        return;
    }

    for (size_t i = 0; i < strlen(encrypt); ++i)
    {
        for(size_t j = 0; j < strlen(dictionary.symbol); ++j){
            strcmp(encrypt[i], dictionary.symbol[j]);
            if(strcmp(encrypt[i], dictionary.symbol[j]) == 0){
                
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
    user_command[strcspn(user_command, "\n")] = "\0";

    // Compare commands given:

    // Command: Help:
    if (strcmp(user_command, "help") || strcmp(user_command, "Help"))
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
    if (strcmp(user_command, "code") || strcmp(user_command, "Code"))
    {
        printf("Enter what you want to code (You can only code letters and numbers):\n");
        fgets(user_input, sizeof(user_input), stdin);
        code(user_input, dictionary);
    }

    return 0;
}