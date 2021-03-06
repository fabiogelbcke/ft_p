#include "client.h"



void                            file_transfers(int sock, char **cmd, char *command)
{
    if (!ft_strcmp(cmd[0], "get"))
	{
        if (cmd[1])
            get(sock, cmd[1]);
	}
    else
        if (cmd[1])
            put(sock, cmd[1], command);
}

char				**get_entry(void)
{
	int			n;
	char		*str;
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
	{
		ft_putstr("Connection error\n");
		return (-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connection error\n");
		exit(1);
	}
	listen(sock, 50);
	return (sock);
}

void	client_shell(int sock)
{
	char			**cmd;
	char			**entries;
        char                    buf[257];
        int                     bytesread;

	entries = NULL;
 	while (1)
	{
		if (!entries || (!*(entries)))
			ft_putstr("$> ");
		entries = get_entry();
		while (*entries)
		{
			ft_memset(buf, 0, 257);
			cmd = ft_strsplit(*entries, ' ');
                        ft_putendl(cmd[0]);
			if (ft_strcmp(cmd[0], "put") && ft_strcmp(cmd[0], "lcd") && ft_strcmp(cmd[0], "lls") && ft_strcmp(cmd[0], "lpwd"))
				write(sock, *entries, ft_strlen(*entries));
			if (!ft_strcmp(cmd[0], "get") || !ft_strcmp(cmd[0], "put"))
				file_transfers(sock, cmd, *entries);
			else if (!ft_strcmp(cmd[0], "lcd") || !ft_strcmp(cmd[0], "lls") || !ft_strcmp(cmd[0], "lpwd"))
				local_commands(cmd);
			else
			{
				while((bytesread = read(sock, buf, 256)) > 0
					  && (buf[0] != '\0' || buf[1] != '\0'))
				{
					write(1, buf, bytesread);
					ft_memset(buf, 0, 257);
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

	if (ac != 3)
        {
		ft_putendl("Usage: ./client [server ip] [port]");
                return (1);
        }
        if (!ft_strcmp(av[1], "localhost"))
            av[1] = ft_strdup("127.0.0.1");
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	client_shell(sock);
        close(sock);
	return (0);
}

