#include <server_ftp.h>

int main(void)
{
	// BEGIN: initialization
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
	// END: initialization
	
	while(1)
	{
		// BEGIN: request	
		//set0(data);
		if((x = sfd_client = accept(sfd_server, (struct sockaddr*) &sin_client, &size_sockaddr)) < 0)
			er("accept()", x);
		/*
		if(connection_id == -2)
			connection_id = 0;
		else
			connection_id++;
		*/
		/*
		shp = ntohp(data);
		shp->conid = connection_id;
		printpacket(shp, HP);
		*/
		port_client = ntohs(sin_client.sin_port);
		//strcpy(path, shp->buffer);
		printf(ID "Packet received from %s:%d with data: %s\n", inet_ntoa(sin_client.sin_addr), port_client, path);
		fflush(stdout);
		// END: request
		
		/*
		// BEGIN: request acknowledgement
		shp->type = RACK;
		sprintf(shp->buffer, "Querying the timestamp of: %s", path);
		printpacket(shp, HP);
		data = htonp(shp);
		if((x = sendto(socket_fd, data, size_packet, 0, (struct sockaddr*) &sin_client, size_sockaddr)) == -1)
			er("request acknowledgement sendto()", x);
		printf(ID "Calling the timestamp function...\n");
		fflush(stdout);
		// END: request acknowledgement
		
		// BEGIN: done
		shp->type = DONE;
		sprintf(shp->buffer, "Last modified timestamp is: %s", timestamp(path));
		printpacket(shp, HP);
		data = htonp(shp);
		if((x = sendto(socket_fd, data, size_packet, 0, (struct sockaddr*) &sin_client, size_sockaddr)) == -1)
			er("done sendto()", x);
		printf(ID "Timestamp sent.\n");
		fflush(stdout);
		// END: done
		
		// BEGIN: done acknowledgement
		set0(data);
		if((x = recvfrom(socket_fd, data, size_packet, 0, (struct sockaddr*) &sin_client, &size_sockaddr)) == -1)
			er("done acknowledgement recvfrom()", x);
		shp = ntohp(data);
		printpacket(shp, HP);
		// do error checking here...
		// ...
		printf(ID "Client says: %s\n", shp->buffer);
		fflush(stdout);
		set0(shp);
		set0(data);
		// END: done acknowledgement
		*/
		
		int recvsize;
		do
		{
			if((recvsize = recv(sfd_client, data, size_packet, 0)) < 0)
				er("recv()", recvsize);
			
			if((x = send(sfd_client, data, size_packet, 0)) != recvsize)
				er("send()", x);
		}
		while(recvsize > 0);
		
	}

	// BEGIN: cleanup
	//free(shp);
	//free(data);
	//free(&sin_client);
	//free(&sin_server);
	close(sfd_client);
	close(sfd_server);
	printf(ID "Done.\n");
	fflush(stdout);
	// END: cleanup
	
	return 0;
}

