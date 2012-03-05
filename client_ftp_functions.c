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

	fprintf(stderr, ID "strlen(chp->buffer) = %d\n", strlen(chp->buffer));
	fprintf(stderr, ID "before while loop of receive_file()\n");

	while(chp->type == DATA)
	{
		/*
		if((x = fwrite(&chp->buffer, 1, strlen(chp->buffer), fp)) <= 0);
			er("fwrite()", x);
		*/
		fwrite(&chp->buffer, 1, strlen(chp->buffer), fp);
		
		fprintf(stderr, ID "after fwrite() in while loop of receive_file()\n");

		if((x = recv(sfd_client, data, size_packet, 0)) <= 0)
			er("recv()", x);
		chp = ntohp(data);
	}
	
	fclose(fp);

	/*
	if(chp->type == EOT)
		fclose(fp);
	else
	{
		fprintf(stderr, "Error occured while writing to file. Exiting...\n");
		exit(2);
	}
	*/
}

