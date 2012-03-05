#include <file_transfer_functions.h>

static size_t size_packet = sizeof(struct packet);

void send_EOT(int sfd, struct packet* hp)
{
	int x;
	hp->type = EOT;
	if((x = send(sfd, htonp(hp), size_packet, 0)) != size_packet)
		er("send()", x);
}

void send_TERM(int sfd, struct packet* hp)
{
	int x;
	hp->type = TERM;
	if((x = send(sfd, htonp(hp), size_packet, 0)) != size_packet)
		er("send()", x);
}

void send_file(char* path, int sfd, struct packet* hp)
{
	int x;
	strcpy(hp->buffer, "test");
	hp->type = DATA;
	if((x = send(sfd, htonp(hp), size_packet, 0)) != size_packet)
		er("send()", x);
	send_EOT(sfd, hp);		
}

void receive_file(char* filename, int sfd, struct packet* hp)
{
	int x;
	struct packet* data = (struct packet*) malloc(size_packet);
	set0(data);
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

