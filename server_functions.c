#include "server.h"

void    pwd(int cs, char **envp)
{
    char cwd[200];
    char *relcwd;
    char *home;

    getcwd(cwd, 200);
    home = get_env("PWD", envp);
    relcwd = ft_strstr(cwd, home);
	relcwd += ft_strlen(home);
    if (ft_strlen(relcwd) == 0)
        write(cs, "/\n", 2);
    else
        write(cs, ft_strjoin(relcwd, "\n"), ft_strlen(relcwd) + 1);

}
void    ls(int cs, char **cmd)
{
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

    home = get_env("PWD", envp);
    if (!dir)
        chdir(home);
    else if (chdir(dir) == -1)
        write(cs, "No such file or directory\n", 26);
    else
    {
        getcwd(cwd, 256);
        if (!ft_strstr(cwd, home))
            chdir(home);
    }
}

int	get_error(int error, int cs)
{
    if (error == 1)
        write(cs, "\0\0ERROR file not specified\n", 27);
    if (error == 2)
        write(cs, "\0\0ERROR server could not open file\n", 36);
    if (error == 3)
        write(cs, "\0\0ERROR file is directory, cant copy directory\n", 47);
    if (error == 4)
        write(cs, "\0\0ERROR error reading file", 27);
    return (1);
}

void	put(int cs, char **cmd, char *ip)
{
    int bytesread;
    char buf[257];
    int fd;
    
    
    ft_memset(buf, 0, 257);
    printf("PUT request from %s for file %s\n", ip, cmd[1]);
    fd = open(cmd[1], O_WRONLY|O_CREAT|O_EXCL, 0777);
    if (fd == -1)
    {
        while ((bytesread = read(cs, buf, 256)) == 256)
            ;
        if (errno == EEXIST)
            write(cs, "ERROR. A file with this name already exists. Change that file's name or change directory\n", 89);
        else
            write(cs, "ERROR couldnt create file\n", 27);
        return ;
    }
    while ((bytesread = read(cs, buf, 256)) > 0)
    {
        if (fd != -1)
            write(fd, buf, bytesread);
        ft_memset(buf, 0, 257);
        if (bytesread < 256)
            break;
    }
    if (bytesread != -1)
        write(cs, "SUCCESSFUL TRANSFER\n", 20);
    else
        write(cs, "ERROR WRITING FILE\n", 18);
}

void    get(int cs, char **cmd, char *ip)
{
    int fd;
    struct stat statbuf;
    int bytesRead;
    char buf[257];
	int error;
	
    error = 0;
    if (!cmd[1])
    {
		error = get_error(1, cs);
        return;
    }
    printf("GET request from %s for file %s\n", ip, cmd[1]);
    fd = open(cmd[1], O_RDONLY);
    if (fd == -1)
    {
		error = get_error(2, cs);
        return;
    }
	fstat(fd, &statbuf);
    if (S_ISDIR(statbuf.st_mode))
    {
		error = get_error(3, cs);
        return;
    }
    ft_memset(buf, 0, 257);
    bytesRead = read(fd, buf, 256);
    while (bytesRead > 0)
    {
        write(cs, buf, bytesRead);
		ft_memset(buf, 0, 257);
        bytesRead = read(fd, buf, 256);
    }
    if (bytesRead == -1)
		get_error(4, cs);
}
