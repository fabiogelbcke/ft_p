#include "server.h"

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

int	main(int ac, char ** av)
{
	int port;
	int sock;

	if (ac < 3)
		ft_putendl("usage");
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	write(sock, "bonjour\n", 8);

	close(sock);
	return (0);
}

