// Functions file.

#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CSIZE 10   // Command size.
#define ISIZE 1000 // Input size.
#define SSIZE 3    // Single char size.

// Code function: code letters and numbers to their morse codes representation.
void code(char encrypt[], dict dictionary)
{
    // Keep asking for input until the user enters valid text.
    while (1)
    {
        // Check if input is NULL or empty.
        if (encrypt == NULL || encrypt[0] == '\0')
        {
            printf("ERROR: No input was given, please try again.\n");
        }
        else
        {
            int valid = 1;

            // Validate the input.
            for (size_t i = 0; i < strlen(encrypt); ++i)
            {
                int found = 0;

                if (encrypt[i] == ' ')
                {
                    found = 1;
                }

                for (size_t j = 0; j < dictionary.size; ++j)
                {
                    if (tolower(encrypt[i]) == dictionary.symbol[j])
                    {
                        found = 1;
                        break;
                    }
                }

                if (found == 0)
                {
                    printf("ERROR: Invalid input. Please only enter letters and numbers.\n");
                    valid = 0;
                    break;
                }
            }

            // Encode and return if the input is valid.
            if (valid)
            {
                printf("The morse code representation of \"%s\" is:\n", encrypt);

                for (size_t i = 0; i < strlen(encrypt); ++i)
                {
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

                printf("\n");
                return;
            }
        }

        // Ask for new input after an error.
        printf("\nEnter what you want to code (You can only code letters and numbers):\n");

        if (fgets(encrypt, ISIZE, stdin) == NULL)
        {
            printf("ERROR: Failed to read input.\n");
            return;
        }

        encrypt[strcspn(encrypt, "\n")] = '\0';
    }
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
        if (decrypt[i] != '-' && decrypt[i] != '.' && decrypt[i] != ' ')
        {
            printf("ERROR: Invalid character(s) detected. Make sure you only enter dots, dashes and spaces\n");
            return;
        }

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
            if (decrypt[i + 1] == ' ')
            {
                ++i;
                k = 0;
                for (size_t j = 0; j < dictionary.size; ++j)
                {
                    if (strcmp(morse, dictionary.morse[j]) == 0)
                    {
                        printf("%c", dictionary.symbol[j]);
                        break;
                    }
                }
                printf(" ");
            }
            else
            {
                k = 0;
                for (size_t j = 0; j < dictionary.size; ++j)
                {
                    if (strcmp(morse, dictionary.morse[j]) == 0)
                    {
                        printf("%c", dictionary.symbol[j]);

                        break;
                    }
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
                printf("%c", dictionary.symbol[j]);
                break;
            }
        }
    }
};

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
            search(find, dictionary);
            break;
        }
    }
}

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