#include <server_ftp.h>

int main(void)
{
	struct sockaddr_in sin_server, sin_client;
	int sfd_server, sfd_client, x;
	unsigned short int port_client;
	size_t size_sockaddr = sizeof(struct sockaddr), size_packet = sizeof(struct packet);
	char path[LENBUFFER];
	short int connection_id = -2;
	struct packet* shp;							// client host packet
	struct packet* data = (struct packet*) malloc(size_packet);		// network packet
	
	if((x = sfd_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		er("socket()", x);
	
	memset((char*) &sin_server, 0, sizeof(struct sockaddr_in));
	sin_server.sin_family = AF_INET;
	sin_server.sin_port = htons(PORTSERVER);
	sin_server.sin_addr.s_addr = htonl(INADDR_ANY);

	if((x = bind(sfd_server, (struct sockaddr*) &sin_server, size_sockaddr)) < 0)
		er("bind()", x);
	
	if((x = listen(sfd_server, 1)) < 0)
		er("listen()", x);
	
	printf(ID "FTP Server started up @ local:%d. Waiting for client(s)...\n\n", PORTSERVER);
	
	while(1)
	{
		if((x = sfd_client = accept(sfd_server, (struct sockaddr*) &sin_client, &size_sockaddr)) < 0)
			er("accept()", x);
		port_client = ntohs(sin_client.sin_port);
		printf(ID "Communication started with %s:%d\n", inet_ntoa(sin_client.sin_addr), port_client);
		fflush(stdout);
		
		int recvsize;
		while((recvsize = recv(sfd_client, data, size_packet, 0)) > 0)
		{
			printf(ID "recvsize = %d\n", recvsize);
			printpacket(ntohp(data), HP);
			if((x = send(sfd_client, data, size_packet, 0)) != recvsize)
				er("send()", x);
		}
	}
	
	close(sfd_client);
	close(sfd_server);
	printf(ID "Done.\n");
	fflush(stdout);
	
	return 0;
}

