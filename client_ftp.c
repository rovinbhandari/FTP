#include <client_ftp.h>

int main(int argc, char* argv[])
{
	//BEGIN: initialization
	struct sockaddr_in sin_server;
	int sfd_client, x;
	size_t size_sockaddr = sizeof(struct sockaddr), size_packet = sizeof(struct packet);
	short int connection_id;
	struct packet* chp = (struct packet*) malloc(size_packet);		// client host packet
	set0(chp);
	struct packet* data;							// network packet
	
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

	
	//int command = -1;
	char lpwd[LENBUFFER], pwd[LENBUFFER], path[LENBUFFER];
	char userinput[LENUSERINPUT];
	char* paths[LENBUFFER];
	while(1)
	{
		printf("\t> ");
		fgets(userinput, LENUSERINPUT, stdin);
		cmd = userinputtocommand(userinput);
		// switch case on command
	}
	
	/*
	chp->type = REQU;
	chp->conid = -1;
	strcpy(path, argv[1]);
	strcpy(chp->buffer, argv[1]);
	//printpacket(chp, HP);
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
			printf(ID "Server says: %s\n", chp->buffer);
		else if(chp->type == DATA)
		{
			//printpacket(chp, HP);
			receive_file(extract_filename(path), sfd_client, chp);
		}
	}
	while(chp->type != TERM);
	
	fprintf(stderr, "TERM received; exiting...\n");
	*/

	close(sfd_client);
	printf(ID "Done.\n");
	fflush(stdout);
	
	return 0;
}

