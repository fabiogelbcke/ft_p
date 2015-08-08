#include "server.h"



void                            file_transfers(int sock, char **cmd)
{
    if (!ft_strcmp(cmd[0], "get"))
        if (cmd[1])
            get(sock, cmd[1]);
    else
        ;
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
        char                    buff[256];
        int                     bytesread;

	entries = NULL;
 	while (1)
	{
		if (!entries || (!*(entries)))
			ft_putstr("$> ");
		entries = get_entry();
		while (*entries)
		{
			cmd = ft_strsplit(*entries, ' ');
			write(sock, *entries, ft_strlen(*entries));
                        if (!ft_strcmp(cmd[0], "get") || !ft_strcmp(cmd[0], "put"))
                            file_transfers(cmd);
                        else
                        {
                            while((bytesread = read(sock, buff, 256)) > 0
                                  && (buff[0] != '\0' || buff[1] != '\0'))
                            {
                                write(1, buff, bytesread);
                                ft_memset(buff, 0, 256);
                            }
                        }
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
	client_shell(port, sock);
        close(sock);
	return (0);
}

