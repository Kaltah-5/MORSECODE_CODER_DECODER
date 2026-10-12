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
            // If valid != 1, this is skipped, and we loop through the while loop.
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
        encrypt[strcspn(encrypt, "\n")] = '\0';
    }
}

// Decode function: Decode morse code to letters and numbers.
void decode(char decrypt[], dict dictionary)
{
    while (1)
    {
        // Check if input is NULL.
        if (decrypt == NULL || decrypt[0] == '\0')
        {
            printf("ERROR: No input was given, please try again!\n");
        }

        else
        {
            // Assume the input was valid.
            int valid = 1;

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

            if (valid)
            {

                // Create a temporary array to store one morse code at a time.
                // needed, because otherwise user input cant be compared with dictionary.morse[].
                // User input array of char
                // dictionary.morse is an array of pointers
                char morse[10];

                // Keeps track of next pos in morse[] array.
                size_t k = 0;

                for (size_t i = 0; i < strlen(decrypt); ++i)
                {

                    // IF no space is found, save the morse code in the morse[] array
                    if (decrypt[i] != ' ' && decrypt[i] != '\0')
                    {
                        morse[k] = decrypt[i];
                        ++k;
                        if (k >= sizeof(morse) - 1)
                        {
                            valid = 0;
                            printf("ERROR: Invalid morse code length!");
                            break;
                        }
                    }
                    else
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
                            break;
                        }
                        else if (decrypt[i + 1] == ' ')
                        {
                            printf(" ");
                            i++;
                        }

                        k = 0;
                    }
                }
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
                        if (found == 0)
                        {
                            valid = 0;
                            printf("ERROR: Morse code not found in the dictionary.");
                            break;
                        }
                    }
                }
            }

            if (valid)
            {
                return;
            }
            else
            {
                // If the if statement above is skipped, we ask the user to write something again.
                printf("\nEnter what you want to decode (You can only code letters and numbers):\n");
                fgets(decrypt, ISIZE, stdin);
                decrypt[strcspn(decrypt, "\n")] = '\0';
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