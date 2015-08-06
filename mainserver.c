#include "server.h"

int	create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	if (bind < 0)
		ft_putstr("Bind error");
	listen(sock, 50);
	return (sock);
}

void    handle_connection(int cs)
{
    char buf[257];
    char **cmd;

    ft_memset(buf, 0, 257);
    while (1)
    {
        recv(cs, buf, 256, );
        cmd = ft_strsplit(buf, ' ');
        if (ft_strcmp && ft_strcmp[0])
        {
            if (!ft_strcmp(cmd[0], "ls"))
                ;
            else if (!ft_strcmp(cmd[0], "cd"))
                ;
            else if (!ft_strcmp(cmd[0], "get"))
                ;
            else if (!ft_strcmp(cmd[0], "put"))
                ;
            else if (!ft_strcmp(cmd[0], "pwd"))
                pwd();
            else if (!ft_strcmp(cmd[0], "quit"))
                return ;
        }
    }
}

void    handle_processes(unsigned int cslen, struct sockaddr_in csin, int sock, char** envp)
{
    int cs;
    int pid;

    while (1)
    {
        ft_putstr("oi");
        cs = accept(sock, (struct sockaddr*)&csin, &cslen);
        int status;
        if ((pid = fork()) == -1)
        {
            close(cs);
            continue;
        }
        else if (pid > 0)
        {
            close(cs);
            continue;
        }
        else if (pid == 0)
        {
            handle_connection(cs, envp);
            close(cs);
            break;
        }
    }
}
int	main(int ac, char ** av, char **envp)
{
    int port;
    int sock;
    unsigned int		cslen;
    struct sockaddr_in	csin;
    
    if (ac == 1)
        return (1);
    port = ft_atoi(av[1]);
    sock = create_server(port);
    handle_processes(cslen, csin, sock, envp);
    close(sock);
    return (0);
}

