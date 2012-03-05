#include <client_ftp.h>

int main(int argc, char* argv[])
{
	//BEGIN: initialization
	struct sockaddr_in sin_server;
	int sfd_client, x;
	size_t size_sockaddr = sizeof(struct sockaddr), size_packet = sizeof(struct packet);
	short int connection_id;
	struct packet* chp = (struct packet*) malloc(size_packet);		// client host packet
	struct packet* data;							// network packet
	char path[LENBUFFER];
	char filename[LENBUFFER];
	
	if((x = sfd_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		er("socket()", x);
	
	memset((char*) &sin_server, 0, sizeof(struct sockaddr_in));
	sin_server.sin_family = AF_INET;
	sin_server.sin_addr.s_addr = inet_addr(IPSERVER);
	sin_server.sin_port = htons(PORTSERVER);
	
	if((x = connect(sfd_client, (struct sockaddr*) &sin_server, size_sockaddr)) < 0)
		er("connect()", x);
			
	printf(ID "FTP Client started up. Attempting communication with server @ %s:%d...\n\n", IPSERVER, PORTSERVER);
	//END: initialization


	set0(chp);
	chp->type = REQU;
	chp->conid = -1;
	strcpy(path, argv[1]);
	strcpy(chp->buffer, argv[1]);
	printpacket(chp, HP);
	data = htonp(chp);
	if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		er("send()", x);
	set0(data);
	do
	{
		if((x = recv(sfd_client, data, size_packet, 0)) <= 0)
			er("recv()", x);
		chp = htonp(data);
		if(chp->type == INFO)
			printpacket(chp, HP);
		else if(chp->type == DATA)
		{
			//receive_file(extract_filename(path), sfd_client, chp);
			printpacket(chp, HP);
		}
		else if(chp->type == EOT)
		{
			printpacket(chp, HP);
		}
	}
	while(chp->type != TERM);
	
	fprintf(stderr, "TERM received; exiting...\n");

	close(sfd_client);
	printf(ID "Done.\n");
	fflush(stdout);
	
	return 0;
}

