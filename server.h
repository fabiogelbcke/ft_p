#ifndef SERVER_H
# define SERVER_H

# define BUFF_SIZE 1024

# include <stdio.h>
# include <stdlib.h>
# include "libft/Includes/libft.h"
# include <unistd.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>

void    set_env(char ***envpptr, char *var, char *value);
char    *get_env(char *var, char **envp);
void    remove_tabs(char *buf);
void    pwd(int cs, char **envp);
void    ls(int cs, char**cmd);
void    cd(int cs, char *dir, char **envp);
void	get(int cs, char **cmd);
void	put(int cs, char **cmd);

#endif
