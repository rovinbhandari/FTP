#include <server_ftp.h>

static size_t size_packet = sizeof(struct packet);

struct client_info* client_info_alloc(int s, int c)
{
	struct client_info* ci = (struct client_info*) malloc(sizeof(struct client_info));
	ci->sfd = s;
	ci->cid = c;
	return ci;
}

void command_pwd(struct packet* shp, struct packet* data, int sfd_client, char* lpwd)
{
	int x;
	shp->type = DATA;
	strcpy(shp->buffer, lpwd);
	data = htonp(shp);
	if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		er("send()", x);
}

