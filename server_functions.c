#include "server.h"

void    pwd(int cs, char **envp)
{
    char cwd[200];
    char *relcwd;
    char *home;

    getcwd(cwd, 200);
    home = get_env("PWD", envp);
    relcwd = ft_strsub(cwd, ft_strlen(home), ft_strlen(cwd) - ft_strlen(home));
    if (ft_strlen(relcwd) == 0)
        write(cs, "/\n", 2);
    else
        write(cs, ft_strjoin(relcwd, "\n"), ft_strlen(relcwd) + 1);

}
void    ls(int cs, char **cmd)
{
    int pid;
    char buf[256];
    int size;

    cmd[1] = NULL;
    if (dup2(cs, 1) > 0)
        execv("/bin/ls", cmd);
    else
        printf("ERROR Couldn't redirect file descriptor");
}

void    cd(int cs, char *dir, char **envp)
{
    char cwd[256];
    char *home;
    
    

    ft_putstr(dir);
        ft_putchar('\n');
    if (chdir(dir) == -1)
        write(cs, "No such file or directory\n", 26);
    else
    {
        getcwd(cwd, 256);
        ft_putstr(cwd);
        home = get_env("PWD", envp);
        if (!ft_strstr(cwd, home))
            chdir(home);
    }
}

void	get_error(int error)
{
	write(cs, "\0\0", 2);
	if (error == 1)
		write(cs, "ERROR file not specified\n", 25);
	if (error == 1)
		write(cs, "ERROR server could not open file\n", 29);
	if (error == 1)
		write(cs, "ERROR file is directory, cant copy directory\n", 45);
	if (error == 1)
		write(cs, "ERROR error reading file", 25);
	return (1);
}

void    get(int cs, char **cmd)
{
    int fd;
    struct stat statbuf;
    int bytesRead;
    char buf[257];
	int error;
	
    error = 0;
    if (!cmd[1])
    {
		error = get_error(1);
        return;
    }
    fd = open(cmd[1], O_RDONLY);
    if (fd == -1)
    {
		error = get_error(2);
        return;
    }
	fstat(fd, &statbuf);
    if (S_ISDIR(statbuf.st_mode))
    {
		error = get_error(3);
        return;
    }
    ft_memset(buf, 0, 257);
    bytesRead = read(fd, buf, 256);
    while (bytesRead > 0)
    {
        write(cs, buf, bytesRead);
        bytesRead = read(fd, buf, 256);
		ft_memset(buf, 0, 257);
    }
    if (bytesRead == -1)
		get_error(4);
}
