#ifndef CLIENT_H
# define CLIENT_H

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

void    get(int sock, char *filename);
void	put(int sock, char *filename, char *command);

#endif
