#include <client_ftp.h>

static size_t size_packet = sizeof(struct packet);

/*
char* extract_filename(char* filename, char* filepath)
{
	strcpy(filename, strrchr(filepath, '/') + 1);
}
*/

void receive_file(char* filename, int sfd_client, struct packet* chp)
{
	int x;
	struct packet* data = (struct packet*) malloc(size_packet);
	set0(data);
	FILE* fp = fopen(filename, "wb");

	while(chp->type == DATA)
	{
		fwrite(&chp->buffer, 1, strlen(chp->buffer), fp);
		
		if((x = recv(sfd_client, data, size_packet, 0)) <= 0)
			er("recv()", x);
		chp = ntohp(data);
	}
	
	if(chp->type == EOT)
		fclose(fp);
	else
	{
		fprintf(stderr, "Error occured while writing to file. Exiting...\n");
		exit(2);
	}
}

