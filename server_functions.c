#include "server.h"

void    pwd(int cs, char **envp)
{
    char cwd[200];
    char *relcwd;
    char *home;

    getcwd(cwd, 200);
    home = get_env("PWD", envp);
    relcwd = ft_strsub(cwd, ft_strlen(home), ft_strlen(cwd) - ft_strlen(home));
//    ft_putstr(relcwd);
    if (ft_strlen(relcwd) == 0)
        write(cs, "/\n", 2);
    else
        write(cs, ft_strjoin(relcwd, "\n"), ft_strlen(relcwd) + 1);
    ft_putstr("oi");

}
void    ls(int cs, char **cmd)
{
    int pid;
    char buf[256];
    int size;

    ft_putstr("oae");
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
