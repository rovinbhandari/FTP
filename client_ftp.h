#include <commons.h>
#include <file_transfer_functions.h>

#define IPSERVER	"127.0.0.1"
#define	ID		"CLIENT=> "

#define LENUSERINPUT	1024

struct command
{
	short int id;
	int npaths;
	char** paths;
};

struct command* userinputtocommand(char [LENUSERINPUT]);

void printcommand(struct command*);

void command_pwd(struct packet*, struct packet*, int);
void command_cd(struct packet*, struct packet*, int, char*);
void command_ls(char*);

