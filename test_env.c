#include <stdio.h>

/* extern char **environ;

int main() {
	for (int i = 0; environ[i] != NULL; i++) {
		printf("%s\n", environ[i]);
	}
	return 0;
} */

int main(int ac, char *av[], char **env)
{
	for (int i = 0; env[i] != NULL; i++) {
		printf("%s\n", env[i]);
	}
	return 0;
}