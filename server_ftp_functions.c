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

void command_cd(struct packet* shp, struct packet* data, int sfd_client, char* message)
{
	int x;
	shp->type = INFO;
	strcpy(shp->buffer, message);
	data = htonp(shp);
	if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		er("send()", x);
}

void command_ls(struct packet* shp, struct packet* data, int sfd_client, char* lpwd)
{
	int x;
	shp->type = DATA;
	DIR* d = opendir(lpwd);
	if(!d)
		er("opendir()", (int) d);
	struct dirent* e;
	while(e = readdir(d))
	{
		sprintf(shp->buffer, "%s\t%s", e->d_type == 4 ? "DIR:" : "FILE:", e->d_name);
		data = htonp(shp);
		if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
			er("send()", x);
	}
	send_EOT(shp, data, sfd_client);
}

void command_get(struct packet* shp, struct packet* data, int sfd_client)
{
	int x;
	FILE* f = fopen(shp->buffer, "rb");	// Yo!
	shp->type = INFO;
	shp->comid = GET;
	strcpy(shp->buffer, f ? "File found; processing" : "Error opening file.");
	printpacket(shp, HP);
	data = htonp(shp);
	if((x = send(sfd_client, data, size_packet, 0)) != size_packet)
		er("send()", x);
	if(f)
	{
		shp->type = DATA;
		send_file(shp, data, sfd_client, f);
		fclose(f);
	}
	send_EOT(shp, data, sfd_client);
}

