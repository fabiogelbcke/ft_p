#include "client.h"

void get_error(int sock)
{
	char buf[257];

	ft_memset(buf, 0, 257);
	read(sock, buf, 256);
	ft_putstr(buf);
}

void get(int sock, char *filename)
{
    int bytesread;
    char buf[257];
    int fd;

    ft_memset(buf, 0, 257);
	bytesread = read(sock, buf, 256);
	if (buf[0] == '\0' && buf[1] == '\0')
	{
		get_error(sock);
		return ;
	}
	fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC);
    if (fd == -1)
    {
        if (errno == EEXIST)
            ft_putstr("ERROR. A file with this name already exists. Change that file's name or change directory\n");
        else
            ft_putstr("ERROR couldnt create file\n");
		while ((bytesread = read(sock, buf, 256)) > 0
			   && (buf[0] != '\0' || buf[1] != '\0'));
		return ;
    }
	while (bytesread > 0 && (buf[0] != '\0' || buf[1] != '\0'))
    {
        write(fd, buf, bytesread);
		ft_memset(buf, 0, 257);
		bytesread = read(sock, buf, 256);
    }
	close(fd);
	ft_putstr("SUCCESS File received\n");
}
