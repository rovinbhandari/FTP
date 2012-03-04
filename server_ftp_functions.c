#include <server_ftp.h>

static size_t size_packet = sizeof(struct packet);

struct client_info* client_info_alloc(int s, int c)
{
	struct client_info* ci = (struct client_info*) malloc(sizeof(struct client_info));
	ci->sfd = s;
	ci->cid = c;
	return ci;
}

void send_file(char* path, int sfd_client, struct packet* shp)
{
	int x;
	strcpy(shp->buffer, "test");
	shp->type = DATA;
	if((x = send(sfd_client, htonp(shp), size_packet, 0)) != size_packet)
		er("send()", x);
	send_EOT(sfd_client, shp);		
}

