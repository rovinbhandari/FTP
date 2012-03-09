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
	int i = 0;
	while(!feof(f))
	{
		memset(hp->buffer, '\0', sizeof(char) * LENBUFFER);
		fread(hp->buffer, 1, LENBUFFER, f);
		i++;
		//printpacket(hp, HP);
		data = htonp(hp);
		if((x = send(sfd, data, size_packet, 0)) != size_packet)
			er("send()", x);
	}
	fprintf(stderr, "\t%d bytes read.\n", i * LENBUFFER);
	fprintf(stderr, "\t%d packets sent.\n", i);
}

void receive_file(struct packet* hp, struct packet* data, int sfd, FILE* f)
{
	int x;
	int i = 0, j = 0;
	if((x = recv(sfd, data, size_packet, 0)) <= 0)
		er("recv()", x);
	j++;
	hp = ntohp(data);
	//printpacket(hp, HP);
	while(hp->type == DATA)
	{
		fwrite(hp->buffer, 1, strlen(hp->buffer), f);
		i += strlen(hp->buffer);
		if((x = recv(sfd, data, size_packet, 0)) <= 0)
			er("recv()", x);
		j++;
		hp = ntohp(data);
		//printpacket(hp, HP);
	}
	fprintf(stderr, "\t%d bytes written.\n", i);
	fprintf(stderr, "\t%d packets received.\n", j);
	if(hp->type == EOT)
		return;
	else
	{
		fprintf(stderr, "Error occured while downloading remote file.\n");
		exit(2);
	}
}

