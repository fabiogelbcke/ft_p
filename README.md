# ft_p
ft_p project from 42

Project consists of writing in C a server and a client which allows file uploading and dowloading from the server using a TCP/IP communication.
Allowed functions:

◦ socket(2), open(2), close(2), setsockopt(2), getsockname(2)

◦ getprotobyname(3), gethostbyname(3), getaddrinfo(3)

◦ bind(2), connect(2), listen(2), accept(2)

◦ htons(3), htonl(3), ntohs(3), ntohl(3)

◦ inet_addr(3), inet_ntoa(3)

◦ send(2), recv(2), execv(2), execl(2), dup2(2), wait4(2)

◦ fork(2), getcwd(3), exit(3), printf(3), signal(3)

◦ mmap(2), munmap(2), lseek(2), fstat(2)

◦ opendir(3), readdir(3), closedir(3)

◦ chdir(2), mkdir(2), unlink(2)

◦ les fonctions autorisées dans le cadre de votre libft (read(2), write(2), malloc(3),free(3), etc... par exemple ;-) )

◦ select(2), FD_CLR, FD_COPY, FD_ISSET, FD_SET, FD_ZERO mais uniquement si c’est pour faire quelque chose de correct!

Server must allow for commands ls, cd, get (file), put (file), pwd and quit

It must also use fork to allow for more than one client connected at a time and show error/success message when you upload/download files

Bonuses:

lcd, lls and lpwd for local comands in client.
