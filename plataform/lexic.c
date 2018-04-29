#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexic.h"

void lexic() {
    char_index = 0;

    for (char_index; char_index <= strlen(file_array); char_index++) 
    {
        switch (((int)file_array[char_index]))
        {
            case 32: // espaço
                break;
            case 10: // LF
                line_index++;
                break;
            case 112: // p
                verify_principal();
                break;
            case 123: // {
                scope_state = 1;
                break;
            case 125: // }
                scope_state = 0;
                break;
            case 105: // i
                verify_inteiro();
                break;
            case 100: // d
                verify_decimal();
                break;
            case 99: // c
                verify_caractere();
                break;
        }
    }
};

void verify_principal() {
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (int i = 0; i < strlen(reserved_words[0]); i++, mem++) // principal
    {
        next_wout_space();
        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[0], strlen(reserved_words[0])) == 0) // principal
    {
        scope = malloc(strlen(reserved_words[0]) * sizeof(char));
        strcpy(scope, reserved_words[0]);
        log_success("principal Scope");
    } else {
        log_error(word);
        exit(0);
    }

    control_memory(-sizeof(word));
    free(word);
};

void verify_inteiro() {
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (int i = 0; i < strlen(reserved_words[7]); i++, mem++) // inteiro
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[7], strlen(reserved_words[7])) == 0) // inteiro
    {
        log_success("inteiro type");
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(INTEIRO);
        }
        else
        {
            log_error("Declaracao de Variavel");
            exit(0);
        }
    } else {
        log_error(word);
        exit(0);
    }

    control_memory(-sizeof(word));
    free(word);
}

void verify_decimal() {
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (int i = 0; i < strlen(reserved_words[9]); i++, mem++) // decimal
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[9], strlen(reserved_words[9])) == 0) // decimal
    {
        log_success("decimal type");
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(DECIMAL);
        }
        else
        {
            log_error("Declaracao de Variavel");
            exit(0);
        }
    } else {
        log_error(word);
        exit(0);
    }

    control_memory(-sizeof(word));
    free(word);
}

void verify_caractere() {
    int mem = 1;
    char *word;

    // Catch the first word's caracter
    char_index--;

    word = malloc(mem * sizeof(char));
    control_memory(sizeof(word));

    for (int i = 0; i < strlen(reserved_words[8]); i++, mem++) // caractere
    {
        next_wout_space();

        word[i] = file_array[char_index];
        word = (char *) realloc(word, mem * sizeof(char));
        control_memory(sizeof(word));
    }

    // String final "\0"
    word[mem-1] = 00;

    if(strncmp(word, reserved_words[8], strlen(reserved_words[8])) == 0) // caractere
    {
        log_success("caractere type");
        next_wout_space();
        if ((int)file_array[char_index] == 38) // &
        {
            validate_variable(CARACTERE);
        }
        else
        {
            log_error("Declaracao de Variavel");
            exit(0);
        }
    } else {
        log_error(word);
        exit(0);
    }

    control_memory(-sizeof(word));
    free(word);
}

void validate_variable(int type) {
    int mem = 1;
    char *word;

    word = malloc((mem*2) * sizeof(char));
    control_memory(sizeof(word));

    if (type == INTEIRO) {
        next_wout_space();
        if ((int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122) // a..z
        {
            word[mem-1] = file_array[char_index-1]; // &
            word[mem] = file_array[char_index];
            next_wout_space();
            while ((int)file_array[char_index] != 59 && (int)file_array[char_index] != 44) // ; ou ,
            {
                mem++;
                word = (char *) realloc(word, mem * sizeof(char));
                control_memory(sizeof(word));

                if (
                    (int)file_array[char_index] >= 97 && (int)file_array[char_index] <= 122 // a..z
                    ||
                    (int)file_array[char_index] >= 65 && (int)file_array[char_index] <= 90 // A..Z
                    ||
                    (int)file_array[char_index] >= 48 && (int)file_array[char_index] <= 57 // 0..9
                    )
                {
                    word[mem] = file_array[char_index];
                }
                else
                {
                    log_error("Variavel: Caractere Invalido");
                    exit(0);
                }
                
                next_wout_space();
            }

            // String final "\0"
            word[mem+1] = 00;

            save_to_symbtab(word, "inteiro", NULL, scope);  

            if ((int)file_array[char_index] == 44) // ,
            {
                next_wout_space();
                if ((int)file_array[char_index] == 38) // &
                {
                    validate_variable(INTEIRO);
                }
                else
                {
                    log_error("Declaracao de Variavel");
                    exit(0);
                }
            }
        }
        else
        {
            log_error("Variavel: caractere Inicial Nao Esta Entre a..z");
            exit(0);
        }
    }
}