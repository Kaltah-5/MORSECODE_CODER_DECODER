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
struct coder_decoder
{
    dict Dictionary;
    int current_dictionary_id;
};

// Function declarations
void code(char encrypt[], dict dictionary);
void decode(char decrypt[], dict dictionary);
void search(char find[], dict dictionary);
void show(dict dictionary);

#endif

