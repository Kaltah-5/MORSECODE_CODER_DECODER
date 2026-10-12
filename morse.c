// Functions file.

#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10   // Command size.
#define ISIZE 1000 // Input size.

// Command help: Display valid commands.

void help(void)
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

// Check if user input is too long, clears input buffer.
int input_checker(char input[], int size)
{

    if (strchr(input, '\n') == NULL)
    {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            // This will 'eat' the letters until it reaches \n.
        }
        if (size == ISIZE)
        {
            printf("ERROR: Your input is too long, maximum length is 999 characters.\n");
            return 0;
        }
        else if (size == CSIZE)
        {
            printf("ERROR: Your input is too long, maximum length is 9 characters.\n");
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// Code function: code letters and numbers to their morse codes representation.
void code(char encrypt[], dict dictionary)
{
    // Keep asking for input until the user enters valid text.
    while (1)
    {
        printf("=======================================================\n");
        // Check if input is NULL or empty.
        if (encrypt == NULL || encrypt[0] == '\0')
        {
            printf("ERROR: No input was given, please try again.\n");
        }
        else
        {
            // Assume that the input is valid.
            int valid = 1;

            // Check if a the encrypt is built of letters and numbers
            for (size_t i = 0; i < strlen(encrypt); ++i)
            {
                // Add a variable to control if a symbol is found or not.
                int found = 0;

                // If element is a space, mark it as found.
                if (encrypt[i] == ' ')
                {
                    found = 1;
                }

                for (size_t j = 0; j < dictionary.size; ++j)
                {
                    // dictionary.symbol contains lowercase letters, compare encrypt with dictionary.
                    if (tolower(encrypt[i]) == dictionary.symbol[j])
                    {
                        // Found is 1, break out of the loop.
                        found = 1;
                        break;
                    }
                }

                // If letter or number havent been found, set valid to 0.
                if (found == 0)
                {
                    printf("ERROR: Invalid input. Please only enter letters and numbers!\n");
                    valid = 0;
                    break;
                }
            }

            // If valid == 1, this check is done, and the we exit this function.
            if (valid)
            {
                printf("The morse code representation of \"%s\" is:\n", encrypt);

                for (size_t i = 0; i < strlen(encrypt); ++i)
                {

                    // If the element is a space, print a space and continue to next element.
                    if (encrypt[i] == ' ')
                    {
                        printf(" ");
                        continue;
                    }

                    for (size_t j = 0; j < dictionary.size; ++j)
                    {
                        if (tolower(encrypt[i]) == dictionary.symbol[j])
                        {
                            printf("%s ", dictionary.morse[j]);
                            break;
                        }
                    }
                }

                // Print a new line and return.
                printf("\n");
                return;
            }
        }

        // If the if statement above is skipped, we ask the user to write something again.
        printf("\nEnter what you want to code (You can only code letters and numbers):\n");
        fgets(encrypt, ISIZE, stdin);
        if (input_checker(encrypt, ISIZE) == 0)
        {
            continue;
        }
        else
        {
            encrypt[strcspn(encrypt, "\n")] = '\0';
        }
    }
}

// Decode function: Decode morse code to letters and numbers.
void decode(char decrypt[], dict dictionary)
{
    while (1)
    {
        printf("=======================================================\n");
        int valid = 0;
        // Check if input is NULL.
        if (decrypt == NULL || decrypt[0] == '\0')
        {
            printf("ERROR: No input was given, please try again!\n");
        }

        else
        {
            // Assume the input was valid.
            valid = 1;

            // Run through the user input:
            for (size_t i = 0; i < strlen(decrypt); ++i)
            {
                // Since input has to be a dot, dash or space. produce an error if otherwise.
                if (decrypt[i] != '-' && decrypt[i] != '.' && decrypt[i] != ' ')
                {
                    printf("ERROR: Invalid character(s) detected. Make sure you only enter dots, dashes and spaces!\n");
                    valid = 0;
                    break;
                }
            }

            // A check so that input doesnt end with space.
            if (strlen(decrypt) > 0 && decrypt[strlen(decrypt) - 1] == ' ')
            {
                printf("ERROR: Morse code can't end with a space!");
                valid = 0;
            }
            if (valid)
            {

                // Create a temporary array to store one morse code at a time.
                // needed, because otherwise user input cant be compared with dictionary.morse[].
                // User input array of char.
                // dictionary.morse is an array of pointers.
                // Size is 6, because longest morse code is 5 dashes, for 0.
                char morse[6];

                // Keeps track of element in morse[] array.
                size_t k = 0;

                for (size_t i = 0; i < strlen(decrypt); ++i)
                {

                    // IF no space is found, save the morse code in the morse[] array
                    if (decrypt[i] == '.' || decrypt[i] == '-')
                    {
                        if (k >= sizeof(morse) - 1)
                        {
                            valid = 0;
                            printf("ERROR: Invalid morse code length!");
                            break;
                        }
                        morse[k] = decrypt[i];
                        ++k;
                    }

                    else
                    {
                        // Variable to check if the morse code is found in dictionary.
                        int found = 0;

                        if (k > 0)
                        {
                            // Set last element to \0
                            morse[k] = '\0';

                            for (size_t j = 0; j < dictionary.size; ++j)
                            {

                                if (strcmp(morse, dictionary.morse[j]) == 0)
                                {
                                    found = 1;
                                    printf("%c", dictionary.symbol[j]);
                                    break;
                                }
                            }
                            if (found == 0)
                            {
                                valid = 0;
                                printf("ERROR: Morse code not found in the dictionary.");
                            }
                        }

                        // Reset the counter for morse[].
                        k = 0;
                    }
                    // A check for double space, print space when another word is detected.
                    if (decrypt[i] == ' ' && decrypt[i + 1] == ' ')
                    {
                        printf(" ");
                        ++i;
                    }
                }

                // This checks the last word since it doesnt end in space.
                if (k > 0)
                {
                    // Set last element to \0.
                    morse[k] = '\0';

                    // Variable to check if the morse code is found in dictionary.
                    int found = 0;
                    for (size_t j = 0; j < dictionary.size; ++j)
                    {

                        if (strcmp(morse, dictionary.morse[j]) == 0)
                        {
                            found = 1;
                            printf("%c", dictionary.symbol[j]);
                            break;
                        }
                    }
                    if (found == 0)
                    {
                        valid = 0;
                        printf("ERROR: Morse code not found in the dictionary.");
                    }
                }
            }

            // Exit this function when valid at the end.
            if (valid)
            {
                printf("\n");
                return;
            }
        }

        // Request new input when an error is found.
        printf("\nEnter the morse code you to decode (You can only code letters and numbers):\n");

        fgets(decrypt, ISIZE, stdin);
        if (input_checker(decrypt, ISIZE) == 0)
        {
            continue;
        }
        else
        {
            decrypt[strcspn(decrypt, "\n")] = '\0';
        }
    }
}

// Search function: Find the morse code representation of a singel letter or number
void search(char find[], dict dictionary)
{

    while (1)
    {
        printf("=======================================================\n");
        int valid = 1;
        // Check if input is NULL.
        if (find == NULL || find[0] == '\0')
        {
            printf("ERROR: No input was given, please try again.\n");
            valid = 0;
        }
        // Search() only checks for 1 letter, this checks if that is the case.
        else if (strlen(find) != 1)
        {
            printf("ERROR: Enter ONE letter or number!\n");
            valid = 0;
        }

        else
        {
            // Variable to check if symbol is found in dictionary.
            int found = 0;

            // Check if user input is a symbol in dictionary.symbol
            for (size_t i = 0; i < dictionary.size; ++i)
            {
                if (tolower(find[0]) == dictionary.symbol[i])
                {
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                printf("ERROR: Invalid input! Enter a letter or number. \n");
                valid = 0;
            }

            // Print morse code if valid.
            if (valid)
            {

                for (size_t i = 0; i < dictionary.size; ++i)
                {

                    // If the first element is found, print the morse code representation.
                    if (tolower(find[0]) == dictionary.symbol[i])
                    {
                        printf("The Morse code representation of %c is: %s\n", find[0], dictionary.morse[i]);
                        return;
                    }
                }
            }
        }

        // Request new input if error is found:
        printf("\nEnter one letter or number:\n");
        fgets(find, ISIZE, stdin);
        if (input_checker(find, ISIZE) == 0)
        {
            continue;
        }
        else
        {
            find[strcspn(find, "\n")] = '\0';
        }
    }
}

// Show function: displays all letters and numbers and gives their morse code representation.
void show(dict dictionary)
{

    printf("\n=========================================\n");
    printf("\n=========== MORSE CODE TABLE ============\n");
    printf("\n=========================================\n");
    for (int i = 0; i < dictionary.size; ++i)
    {
        printf("%c: %s \n", dictionary.symbol[i], dictionary.morse[i]);
    }
}

// Exit function: Makes user confirm exit.
int exit_program(char user_char[])
{

    while (1)
    {

        if (user_char == NULL || user_char[0] == '\0')
        {
            printf("ERROR: No input was given, please try again.\n");
            return 0;
        }
        else if (strcmp(user_char, "y") == 0 || strcmp(user_char, "Y") == 0)
        {
            printf("Goodbye!");
            return 1;
        }
        else if (strcmp(user_char, "n") == 0 || strcmp(user_char, "N") == 0)
        {
            printf("Program will keep running!\n");
            printf("=======================================================\n");
            return 0;

            // Keep the program running, go back to the beginning of the while loop.
        }
        else
        {

            printf("ERROR: Please enter Y or N! \n");
            fgets(user_char, ISIZE, stdin);
            if (input_checker(user_char, ISIZE) == 0)
            {
                continue;
            }
            else
            {
                user_char[strcspn(user_char, "\n")] = '\0';
            }
        }
    }
}