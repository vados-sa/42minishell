#include <stdio.h>
#include <stdlib.h>

void print_environment(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
}

int main(int argc, char **argv, char **envp)
{
    print_environment(envp);
    return 0;
}
