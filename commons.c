#include <commons.h>

static size_t size_packet = sizeof(struct packet);

void set0(struct packet* p)
{
	memset(p, 0, sizeof(struct packet));
}

struct packet* ntohp(struct packet* np)
{
	struct packet* hp = (struct packet*) malloc(size_packet);
	memset(hp, 0, size_packet);
	
	hp->conid = ntohs(np->conid);
	hp->type = ntohs(np->type);
	hp->status = ntohs(np->status);
	strcpy(hp->buffer, np->buffer);
	
	return hp;	
}

struct packet* htonp(struct packet* hp)
{
	struct packet* np = (struct packet*) malloc(size_packet);
	memset(np, 0, size_packet);
	
	np->conid = ntohs(hp->conid);
	np->type = ntohs(hp->type);
	np->status = ntohs(hp->status);
	strcpy(np->buffer, hp->buffer);
	
	return np;
}

void printpacket(struct packet* p, int ptype)
{
	if(!DEBUG)
		return;
	
	if(ptype)
		printf("\t\tHOST PACKET\n");
	else
		printf("\t\tNETWORK PACKET\n");
	
	printf("\t\tconid = %d\n", p->conid);
	printf("\t\ttype = %d\n", p->type);
	printf("\t\tstatus = %d\n", p->status);
	printf("\t\tbuffer = %s\n\n", p->buffer);
	
	fflush(stdout);
}

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

