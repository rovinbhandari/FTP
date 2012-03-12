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
void command_lcd(char*);
void command_cd(struct packet*, struct packet*, int, char*);
void command_lls(char*);
void command_ls(struct packet*, struct packet*, int);
void command_get(struct packet*, struct packet*, int, char*);
void command_put(struct packet*, struct packet*, int, char*);
void command_mget(struct packet*, struct packet*, int, int, char**);
void command_mput(struct packet*, struct packet*, int, int, char**);
void command_mgetwild(struct packet*, struct packet*, int);
void command_mputwild(struct packet*, struct packet*, int, char*);
void command_lmkdir(char*);
void command_mkdir(struct packet*, struct packet*, int, char*);
void command_rget(struct packet*, struct packet*, int);
void command_rput(struct packet*, struct packet*, int);

