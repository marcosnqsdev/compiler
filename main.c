#include <stdio.h>
#include <stdlib.h>

#include "resources/memory.c"
#include "resources/utils.c"
#include "resources/logs.c"
#include "resources/symbtab.c"
#include "plataform/analyzer.c"

int main(void) 
{
    printf("\nIniciando leitura do arquivo...");

    /*Transfer codes to array*/
    file_to_array();

    printf("\nIniciando analise do arquivo...");

    /*Code Parsing*/
    analyzer();

    printf("\nAnalise realizada com sucesso!\n");

    print_symbtab();

    printf("\n\nMemoria -> Maximo Alocado: %zu bytes\n\n", max_allocated);

    free_all_memory();

    return 0;
}