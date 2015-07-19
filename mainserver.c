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

int	main(int ac, char ** av)
{
	int port;
	int sock;
	int cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	char	buf[1024];
	int	r;

	FILE *outputFile = fopen("output.txt", "wb");
	port = ft_atoi(av[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while (1)
	{
		char recvBuff[10];
		
		int bytesReceived = recv(cs, recvBuff, 10, 0);
		while(bytesReceived != 0)
		{
			
			// you should add error checking here
			fwrite(recvBuff, bytesReceived, 1, outputFile);
			
			bytesReceived = recv(cs, recvBuff, 10, 0);
		}
		close(cs);
	}
	close(cs);
	close(sock);
	return (0);
}

