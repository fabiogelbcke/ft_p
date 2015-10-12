#include "client.h"

void get_error(int sock)
{
	char buf[257];

	ft_memset(buf, 0, 257);
	read(sock, buf, 256);
	ft_putstr(&buf[2]);
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
		ft_putstr(&buf[2]);
		get_error(sock);		
		return ;
	}
	fd = open(filename, O_WRONLY|O_CREAT|O_EXCL, 0777);
    if (fd == -1)
    {
        if (errno == EEXIST)
            ft_putstr("ERROR. A file with this name already exists locally\n");
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
		if (bytesread < 256)
			break;
		bytesread = read(sock, buf, 256);
    }
	close(fd);
	ft_putstr("SUCCESS File received\n");
}

void put(int sock, char *filename, char *command)
{
    int fd;
    struct stat statbuf;
    int bytesread;
    char buf[257];
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr("ERROR couldn't open file\n");
        return ;
    }
    fstat(fd, &statbuf);
    if (S_ISDIR(statbuf.st_mode))
    {
        ft_putstr("ERROR can't send directory\n");
        return ; 
    }
    write(sock, command, ft_strlen(command));
    ft_memset(buf, 0, 257);
    while ((bytesread = read(fd, buf, 256)) > 0)
    {
        write(sock, buf, bytesread);
        ft_memset(buf, 0, 257);
        if (bytesread != 256)
            break ;
    }
    if (bytesread == -1)
        ft_putstr("error during file read\n");
    read(sock, buf, 256);
    ft_putstr(buf);
}
