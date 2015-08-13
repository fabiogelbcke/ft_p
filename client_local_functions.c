#include "client.h"

void lcd(char **cmd)
{
	int i;

	i = chdir(cmd[1]);
	if (i == -1)
		ft_putstr("ERROR couldnt lcd to that address\n");
}

void local_commands(char **cmd)
{
	int pid;
	int status;

	pid = fork();
	if (pid == -1)
		ft_putstr("ERROR fork error\n");
	if (pid > 0)
	{
		wait(&status);
		if (status == 256)
			lcd(cmd);
	}
	if (pid == 0)
	{
		if (!ft_strcmp(cmd[0], "lls"))
			execv("/bin/ls", cmd);
		else if (!ft_strcmp(cmd[0], "lpwd"))
			execv("/bin/pwd", NULL);
		else if (!ft_strcmp(cmd[0], "lcd"))
			exit(1);
		exit(0);
	}
}
