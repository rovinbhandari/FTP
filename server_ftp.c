#include <server_ftp.h>

size_t size_sockaddr = sizeof(struct sockaddr), size_packet = sizeof(struct packet);

void* serve_client(void*);

int main(void)
{
	//BEGIN: initialization
	struct sockaddr_in sin_server, sin_client;
	int sfd_server, sfd_client, x;
	short int connection_id = 0;
	
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
	//END: initialization

	
	while(1)
	{
		if((x = sfd_client = accept(sfd_server, (struct sockaddr*) &sin_client, &size_sockaddr)) < 0)
			er("accept()", x);
		//port_client = ntohs(sin_client.sin_port);
		printf(ID "Communication started with %s:%d\n", inet_ntoa(sin_client.sin_addr), /*port_client*/ ntohs(sin_client.sin_port));
		fflush(stdout);
		
		struct client_info* ci = client_info_alloc(sfd_client, connection_id++);
		serve_client(ci);
	}
	
	close(sfd_server);
	printf(ID "Done.\n");
	fflush(stdout);
	
	return 0;
}

void* serve_client(void* info)
{
	int sfd_client, connection_id, x;
	struct packet* data = (struct packet*) malloc(size_packet);
	struct packet* shp;
	char path[LENBUFFER];
	struct client_info* ci = (struct client_info*) info;
	sfd_client = ci->sfd;
	connection_id = ci->cid;
	
	while(1)
	{
		if((x = recv(sfd_client, data, size_packet, 0)) == 0)
			er("recv()", x);
		
		shp = ntohp(data);
		if(shp->type == TERM)
			break;
		else if(shp->type == REQU)
		{
			//send info and then proceed to complete the request
			shp->type = INFO;
			sprintf(shp->buffer, "File found. Processing...");
			data = htonp(shp);
			if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
			er("send()", x);
		}
		else
		{
			//show error, send TERM and break
			fprintf(stderr, "packet incomprihensible. closing connection.");
			shp->type = TERM;
			data = htonp(shp);
			if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
				er("send()", x);
			break;
		}
	}

	close(sfd_client);
	fflush(stdout);
}

