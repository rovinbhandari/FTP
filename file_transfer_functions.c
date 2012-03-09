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

void send_file(struct packet* hp, struct packet* data, int sfd, FILE* f)
{
	int x;
	while(!feof(f))
	{
		memset(hp->buffer, '\0', sizeof(char) * LENBUFFER);
		fread(hp->buffer, 1, LENBUFFER, f);
		printpacket(hp, HP);
		data = htonp(hp);
		if((x = send(sfd, data, size_packet, 0)) != size_packet)
			er("send()", x);
	}
}

void receive_file(struct packet* hp, struct packet* data, int sfd, FILE* f)
{
	int x;
	if((x = recv(sfd, data, size_packet, 0)) <= 0)
		er("recv()", x);
	hp = ntohp(data);
	printpacket(hp, HP);
	while(hp->type == DATA)
	{
		fwrite(hp->buffer, 1, strlen(hp->buffer), f);
		if((x = recv(sfd, data, size_packet, 0)) <= 0)
			er("recv()", x);
		hp = ntohp(data);
		printpacket(hp, HP);
	}
	if(hp->type == EOT)
		return;
	else
	{
		fprintf(stderr, "Error occured while downloading remote file.\n");
		exit(2);
	}
}

