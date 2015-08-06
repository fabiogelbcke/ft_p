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

void    handle_processes(unsigned int cslen, struct sockaddr_in csin, int sock)
{
    int cs;
    char buf[257];
    int pid;

    ft_memset(buf, 0, 257);
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
//            wait(&status);
            close(cs);
            ft_putstr("parent");
            continue;
            //parent process
        }
        else if (pid == 0)
        {
            int bytesReceived = recv(cs, buf, 1000, 0);
            
            if (bytesReceived != 0)
                ft_putstr(buf);
            ft_putstr("child");
            close(cs);
//            exit(0);
//            handle_command(char *
            //execute
            break;
        }
    }
}
int	main(int ac, char ** av)
{
    int port;
    int sock;
    unsigned int		cslen;
    struct sockaddr_in	csin;
    
    if (ac == 1)
        return (1);
    port = ft_atoi(av[1]);
    sock = create_server(port);
    handle_processes(cslen, csin, sock);
    close(sock);
    return (0);
}

