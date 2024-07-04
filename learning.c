#include <stdio.h>
#include <stdlib.h>

/* Exemple to understand enviroment variables ********************************/
//void print_environment(char **envp)
//{
//    for (int i = 0; envp[i] != NULL; i++)
//        printf("%s\n", envp[i]);
//}
//
//int main(int argc, char **argv, char **envp)
//{
//    print_environment(envp);
//    return 0;
//}

/* Example to understand 'fflush()' ******************************************/
//int main()
//{
//    printf("Hello, ");
//    // No newline, buffer may not be flushed yet
//    fflush(stdout);
//    while(1); // Infinite loop to simulate delay
//    return 0;
//}
