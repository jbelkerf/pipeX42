#include <stdio.h>

int main(int argc, char* argv[], char *envp[])
{
	int i = 0;
	while (envp[i])
	{
		if (!strncmp("PATH",envp[i], 4))
			printf("%s\n",envp[i]);
		i++;
	}
}
