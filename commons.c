#include <commons.h>

void set0(struct packet* p)
{
	memset(p, 0, sizeof(struct packet));
}

struct packet* ntohp(struct packet* np)
{
	size_t size_packet = sizeof(struct packet);
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
	size_t size_packet = sizeof(struct packet);
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

