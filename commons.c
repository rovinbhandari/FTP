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
	hp->comid = ntohs(np->comid);
	hp->datalen = ntohs(np->datalen);
	memcpy(hp->buffer, np->buffer, LENBUFFER);
	
	return hp;	
}

struct packet* htonp(struct packet* hp)
{
	struct packet* np = (struct packet*) malloc(size_packet);
	memset(np, 0, size_packet);
	
	np->conid = ntohs(hp->conid);
	np->type = ntohs(hp->type);
	np->comid = ntohs(hp->comid);
	np->datalen = ntohs(hp->datalen);
	memcpy(np->buffer, hp->buffer, LENBUFFER);
	
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
	printf("\t\tcomid = %d\n", p->comid);
	printf("\t\tdatalen = %d\n", p->datalen);
	printf("\t\tbuffer = %s\n", p->buffer);
	
	fflush(stdout);
}

