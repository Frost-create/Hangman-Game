#include "hangman_strings.h"

/*
* Purpose:          Determine whether a char is lower-case.
*
* Parameter:        c   - A character.  Literally any byte value 0 to 255.
*
* Return value:     1 (true) if c is a lower-case letter (between 'a' and 'z').
*                   0 (false) otherwise.
*/
bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z'){
        return 1;
    }
    else {
        return 0;
    }  
}

/*
* Purpose:          Determine whether a string contains a character.
*                 
* Parameters:       string  - the string to search within
*                   ch      - the character to search for
*
* Return value:     1 if the string contains the character.
*                   0 otherwise
*/
bool string_contains_character(const char *string, char ch) {
    int length = strlen(string);
    for (int i = 0; i < length; ++i){
        if (string[i] == ch){
            return 1;
        }
    }
    return 0;
}

/*
* Purpose:          Determine whether the length and contents of a secret
*                   are valid.  
*
* Parameter:        secret  - A string that represents the secret to test.
*
* Return Value:     If the secret is valid, then return true.
*                   Otherwise return false.
*/
bool is_valid_secret(const char *secret) {
    int length = strlen(secret);
    if (length > MAX_LENGTH){
        printf(MSG_LONG_SECRET_d, MAX_LENGTH);
        return 0;
    }

    for (int i = 0; i < length; ++i){
        if (is_lowercase_letter(secret[i]) == 0 && string_contains_character(punctuation, secret[i]) == 0){
            printf(MSG_INVALID_CHAR_c, secret[i]);
        return 0;
        }
    }
    return 1;
}

/*
* Purpose:          (1) Prompt for a character.
*                   (2) Read characters from stdin until one is read
*                       that is not '\n'.
*                   (3) If EOF is received, then call exit(1).
*
* Parameter:        None.
*
* Return value:     A character.
*/
char prompt_for_and_read_character(void) {
    printf(MSG_PROMPT);
    char ch;

    do{
        ch = getchar();
    } while (ch == '\n');

    if (ch == EOF){
        exit(1);
    }

    return ch;
}

/*
* Purpose:          Run the hangman game logic.
*
*
* Parameters:       secret - the pointer to the secret word the
*                            user has to guess
*
* Return value:     nothing
*/
void run_hangman(const char *secret) {
    int num_wrong_guesses = 0;
    int length = strlen(secret);
    int set[256] = {0};

    printf("%s", arts[num_wrong_guesses]);
    printf("   Phrase: ");
    for (int i = 0; i < length; ++i){
        if(is_lowercase_letter(secret[i]) == 1){
            printf("_");
        }
        else if(secret[i] == ' '){
            printf(" ");
        }
        else if(secret[i] == '\''){
            printf("'");
        }
        else if(secret[i] == '-'){
            printf("-");
        }
    }
    printf("\nEliminated: \n");

    int init_punc = 0;
    for (int i = 0; i < length; ++i){
        if (secret[i] == ' '){
            init_punc += 1;
        }
        else if (secret[i] == '\''){
            init_punc += 1;
        }
        else if (secret[i] == '-'){
            init_punc += 1;
        }
    }

    if (init_punc == length){
       printf(MSG_WIN_s, secret);
        exit(1); 
    }

    while (num_wrong_guesses < LOSING_MISTAKE){
        char character;
        while (1){
            character = prompt_for_and_read_character();
            if (set[(unsigned char)character] == 0 && character >= 'a' && character <= 'z'){
                set[(unsigned char)character] = 1;
                break;
            }
        }

        if(string_contains_character(secret, character) == 0){
            num_wrong_guesses++;
        }

        printf("%s", arts[num_wrong_guesses]);
        printf("   Phrase: ");
        int correct_guesses = 0;

        for (int i = 0; i < length; ++i){
            if(is_lowercase_letter(secret[i]) == 1){
                if(set[(unsigned char)secret[i]] == 1){
                printf("%c", secret[i]);
                correct_guesses += 1;
            }
            else{
                printf("_");
            }
        }
            else if(secret[i] == ' '){
                printf(" ");
                correct_guesses += 1;
            }
            else if(secret[i] == '\''){
                printf("'");
                correct_guesses += 1;
            }
            else if(secret[i] == '-'){
                printf("-");
                correct_guesses += 1;
            }
        }
        printf("\n");

        printf("Eliminated: ");
        for (int c = 'a'; c <= 'z'; c++){
            if(set[c] == 1 && string_contains_character(secret, c) == 0){
            printf("%c", c);
            }
        }
        printf("\n");


        if(correct_guesses == length){
            printf(MSG_WIN_s, secret);
            exit(0);
        }

    }  

    printf(MSG_LOSE_s, secret);
    exit(1);
}

/*
* Purpose:          Run the hangman game.
*
*                     1. Check the value of argc to confirm that the user
*                        runs hangman with a "secret" on the command line.
*                        If the user puts the wrong number of arguments on
*                        the command line, then using printf() and
*                        MSG_WRONG_NUM_ARGS to report an error, and then
*                        "return 1".
*                     2. Call is_valid_secret().  If the function
*                        returns false, then "return 1;".
*                     3. Call run_hangman(secret).
*                     4. Return 0.
*
* Parameters:       argc    - The number of command-line arguments from main().
*                   argv    - An array of strings from main().
*
* Return value:     0 if no error.  1 otherwise.
*/
int main(int argc, char **argv) {
    if (argc  != 2){
        printf(MSG_WRONG_NUM_ARGS);
        return 1;
    }
    if (is_valid_secret(argv[1]) == 0){
        return 1;
    }
    run_hangman(argv[1]);
    return 0;
}
