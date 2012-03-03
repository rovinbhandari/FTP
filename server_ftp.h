#include <commons.h>

#include <time.h>
/*
	for:
		ctime()
*/

#include <sys/stat.h>
/*
	for:
		stat()
*/

#define	ID	"SERVER=> "

struct client_info
{
	int sfd;
	int cid;
};

struct client_info* client_info_alloc(int, int);

