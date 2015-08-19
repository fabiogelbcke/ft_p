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
        if (errno == EADDRINUSE)
        {
            ft_putstr("Port is already in use\n");
            exit(10);
        }
	if (bind < 0)
		ft_putstr("Bind error");
	listen(sock, 50);
	return (sock);
}

void    handle_connection(int cs, char **envp, char *ip)
{
    char buf[257];
    char **cmd;
    int status;
    int pid;

    while (1)
    {
        ft_memset(buf, 0, 257);
        recv(cs, buf, 256, 0);
        remove_tabs(buf);
        cmd = ft_strsplit(buf, ' ');
        if ((pid = fork()) == -1)
        {
            write(cs, "FORK ERROR", 10);
        }
        else if (pid > 0)
        {
            wait(&status);
            if (status == 256)
                cd(cs, cmd[1], envp);
            write(cs, "\0\0", 2);
        }
        else if (pid == 0)
        {
            if (cmd && cmd[0])
            {
                if (!ft_strcmp(cmd[0], "ls"))
                    ls(cs, cmd);
                else if (!ft_strcmp(cmd[0], "cd"))
                    exit(1);
                else if (!ft_strcmp(cmd[0], "get"))
                    get(cs, cmd, ip);
                else if (!ft_strcmp(cmd[0], "put"))
                    put(cs, cmd, ip);
                else if (!ft_strcmp(cmd[0], "pwd"))
                    pwd(cs, envp);
                else if (!ft_strcmp(cmd[0], "quit"))
                    exit(0);
            }
            ft_memset(buf, 0, 257);
            exit(0);
        }
    }
}

char    *new_connection_msg(int cs)
{
    socklen_t len;
    struct sockaddr_storage addr;
    char *ipstr;
    int port;

    ipstr = malloc(sizeof(char) * INET6_ADDRSTRLEN);
    len = sizeof addr;
    getpeername(cs, (struct sockaddr*)&addr, &len);
// deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(char) * INET6_ADDRSTRLEN);
    }
    else { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof(char) * INET6_ADDRSTRLEN);
    }
    printf("New connection from IP address: %s\n", ipstr);
    return (ipstr);
}

void    handle_processes(unsigned int cslen, struct sockaddr_in csin, int sock, char** envp)
{
    int cs;
    int pid;
    char *ip;
    
    while (1)
    {
        cs = accept(sock, (struct sockaddr*)&csin, &cslen);
        if ((pid = fork()) == -1)
        {
            close(cs);
            continue;
        }
        else if (pid > 0)
            continue;
        else if (pid == 0)
        {
            ip = new_connection_msg(cs);
            handle_connection(cs, envp, ip);
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
    
    cslen = 0;
    if (ac == 1)
        return (1);
    port = ft_atoi(av[1]);
    sock = create_server(port);
    handle_processes(cslen, csin, sock, envp);
    close(sock);
    return (0);
}

