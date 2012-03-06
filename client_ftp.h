#include <commons.h>
#include <file_transfer_functions.h>

#define IPSERVER	"127.0.0.1"
#define	ID		"CLIENT=> "

#define LENUSERINPUT	1024

struct command
{
	int id;
	int npaths;
	char** paths;
};

struct command* userinputtocommand(char [LENUSERINPUT]);

