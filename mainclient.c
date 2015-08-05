#include "server.h"


void				handle_command(char **cmd, char **entries)
{
	
}

char				**get_entry(void)
{
	int			n;
	char		*str;
	int			size;
	char		**entries;

	n = 1;
	str = malloc(sizeof(char) * BUFF_SIZE);
	n = read(0, str, BUFF_SIZE);
	str[ft_strlen(str) - 1] = '\0';
	entries = ft_strsplit(str, ';');
	if (entries[0] == NULL)
	{
		entries = malloc(sizeof(char*) * 2);
		entries[0] = NULL;
		entries[1] = NULL;
	}
	return (entries);
}

int	create_client(char *addr, int port)
{
	int sock;
	struct protoent *proto;
	struct sockaddr_in sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		ft_putstr("Connect error");

	listen(sock, 50);
	return (sock);
}

void	client_shell(int port, int sock)
{
	char			**cmd;
	char			**entries;

	entries = NULL;
 	 while (1)
	{
		if (!entries || (!*(entries)))
			ft_putstr("$> ");
		entries = get_entry();
		while (*entries)
		{
			cmd = ft_strsplit(*entries, ' ');
			if (cmd[0] && !ft_strcmp(cmd[0], "exit"))
				return ;
			handle_command(cmd, entries);
			write(sock, cmd[0], ft_strlen(cmd[0]) + 1);
			entries++;
		}
	}
}

int	main(int ac, char ** av)
{
	int port;
	int sock;
	char buffer[256];

	if (ac < 3)
        {
		ft_putendl("usage");
                return (1);
        }
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
        int fd = open("inputFile.txt", O_RDONLY);
	
	if(fd < 0)
	{
		fprintf(stderr, "oh no!");
		return 1;
	}
	/*
	char sendBuffer[100];
	
// TODO: Check for errors here
	int bytesRead = fread(sendBuffer, sizeof(sendBuffer), 1, inputFile);
	
	while(!feof(inputFile))
	{
		//TODO: check for errors here
		send(sock, sendBuffer, bytesRead, 0);
		bytesRead = fread(sendBuffer, sizeof(sendBuffer), 1, inputFile);
	} 
        */
        int bytesread = read(fd, buffer, 256);
        while (bytesread > 0)
        {
            send(sock, buffer, bytesread, 0);
            bytesread = read(fd,buffer,256);
        }
//        close(sock);
//	client_shell(port, sock);
        close(sock);
	return (0);
}

