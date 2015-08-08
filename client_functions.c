#include "client.h"

void get(int sock, char *filename)
{
    int bytesread;
    char buf[257];
    int fd;

    ft_memset(buf, 0, 257);
    fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC);
    if (fd == -1)
    {
        if (errno == EEXIST)
            ft_putstr("ERROR. A file with this name already exists. Change that file's name or change directory\n");
        else
            ft_putstr("ERROR couldnt create file\n");
        return ;
    }
    while ((bytesread = read(sock, buf, 256)) > 0)
    {
        
    }
}
