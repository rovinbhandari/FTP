#include <client_ftp.h>

int main(int argc, char* argv[])
{
	struct sockaddr_in sin_server;
	int socket_fd, x;
	size_t size_sockaddr = sizeof(struct sockaddr), size_packet = sizeof(struct packet);
	short int connection_id;
	struct packet* chp = (struct packet*) malloc(size_packet);		// client host packet
	struct packet* data;							// network packet
	
	if((x = socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		er("socket()", x);
	
	memset((char*) &sin_server, 0, sizeof(struct sockaddr_in));
	sin_server.sin_family = AF_INET;
	sin_server.sin_addr.s_addr = inet_addr(IPSERVER);
	sin_server.sin_port = htons(PORTSERVER);
	
	if((x = connect(socket_fd, (struct sockaddr*) &sin_server, size_sockaddr)) < 0)
		er("connect()", x);
			
	printf(ID "FTP Client started up. Attempting communication with server @ %s:%d...\n\n", IPSERVER, PORTSERVER);
		
	set0(chp);
	chp->type = REQU;
	chp->conid = -1;
	strcpy(chp->buffer, argv[1]);
	printpacket(chp, HP);
	int i;
	for(i = 0; i < NPACKETS; i++)
	{
		chp->status = i;
		data = htonp(chp);
		if((x = send(socket_fd, data, size_packet, 0)) != size_packet)
			er("send()", x);
		set0(data);
		sleep(2);
		if((x = recv(socket_fd, data, size_packet, 0)) <= 0)
			er("recv()", x);
		printpacket(ntohp(data), HP);
	}
	
	close(socket_fd);
	printf(ID "Done.\n");
	fflush(stdout);
	
	return 0;
}

