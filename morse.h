// My header


#ifndef MORSE_H
#define MORSE_H

// My dictionary structure. Morse is an array of pointers, which lets me store strings in each element.
typedef struct Dictionary
{
    int dictionary_id;
    int size;
    char symbol[36];
    const char *morse[36];
} dict;

// Coder-decoder structure
typedef struct coder_decoder
{
    dict Dictionary;
    int current_dictionary_id;
} coder;


// Function declarations
void help(void);
void code(char encrypt[], dict dictionary);
void decode(char decrypt[], dict dictionary);
void search(char find[], dict dictionary);
void show(dict dictionary);
int exit_program(char user_char[]);
int input_checker(char input[], int size);

#endif

