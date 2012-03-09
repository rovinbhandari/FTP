#include <file_transfer_functions.h>

static size_t size_packet = sizeof(struct packet);

void send_EOT(struct packet* hp, struct packet* data, int sfd)
{
	int x;
	hp->type = EOT;
	data = htonp(hp);
	if((x = send(sfd, data, size_packet, 0)) != size_packet)
		er("send()", x);
}

void send_TERM(struct packet* hp, struct packet* data, int sfd)
{
	int x;
	hp->type = TERM;
	data = htonp(hp);
	if((x = send(sfd, data, size_packet, 0)) != size_packet)
		er("send()", x);
}

void send_file(struct packet* hp, struct packet* data, int sfd, char* filename)
{
	int x;
	strcpy(hp->buffer, "test");
	hp->type = DATA;
	data = htonp(hp);
	if((x = send(sfd, data, size_packet, 0)) != size_packet)
		er("send()", x);
	send_EOT(hp, data, sfd);		
}

void receive_file(struct packet* hp, struct packet* data, int sfd, char* filename)
{
	int x;
	FILE* fp = fopen(filename, "wb");
	if(!fp)
		er("fopen()", (int) fp);
	while(hp->type == DATA)
	{
		fwrite(hp->buffer, 1, strlen(hp->buffer), fp);
		if((x = recv(sfd, data, size_packet, 0)) <= 0)
			er("recv()", x);
		hp = ntohp(data);
	}
	if(hp->type == EOT)
		fclose(fp);
	else
	{
		fprintf(stderr, "Error occured while writing to file. Exiting...\n");
		exit(2);
	}
}

