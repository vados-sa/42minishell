#include "../../includes/minishell.h"

int print_exit_code(char *message, char tkn, int exit_code)
{
    printf("%s'%c'\n", message, tkn);
    return(exit_code);
}

/* #define TOKEN_SINTAX_ERROR "syntax error near unexpected token "
#define ERROR_EXIT 1
int main(void)
{
    char tkn = '|';
    return(print_exit_code(TOKEN_SINTAX_ERROR, tkn, ERROR_EXIT));
} */