#include <client_ftp.h>

//static size_t size_packet = sizeof(struct packet);

static const char commandlist[NCOMMANDS][10] =
	{
		"get",
		"put",

		"mget",
		"mput",
		
		"cd",
		"lcd",
		
		"mgetwild",
		"mputwild",
		
		"dir",
		"ldir",

		"ls",
		"lls",
		
		"rget",
		"rput",
		
		"pwd",
		"lpwd",
		
		"exit"
	};			// any change made here should also be \
				replicated accordingly in the COMMANDS \
				enum in commons.h

static void append_path(struct command* c, char* s)
{
	char** temppaths = (char**) malloc(c->npaths * sizeof(char*));
	if(c->npaths < 1)
		memcpy(temppaths, c->paths, (c->npaths - 1) * sizeof(char*));

	char* temps = (char*) malloc((strlen(s) + 1) * sizeof(char));
	strcpy(temps, s);

	*(temppaths + c->npaths - 1) = temps;

	c->paths = temppaths;
}


struct command* userinputtocommand(char s[LENUSERINPUT])
{
	struct command* cmd = (struct command*) malloc(sizeof(struct command));
	cmd->id = -1;
	cmd->npaths = 0;
	cmd->paths = NULL;
	char* savestate;
	char* token;
	int i, j;
	for(i = 0; ; i++, s = NULL)
	{
		token = strtok_r(s, " \t", &savestate);
		if(token == NULL)
			break;
		if(i == 0)
			for(j = 0; j < NCOMMANDS; j++)
				if(!strcmp(token, commandlist[j]))
				{
					cmd->id = j;
					break;
				}
		else
		{
			cmd->npaths++;
			append_path(cmd, token);
		}
	}
	if(cmd->id != -1)
		return cmd;
	else
	{
		fprintf(stderr, "Error parsing command");
		return NULL;
	}
}

void printcommand(struct command* c)
{
	if(!DEBUG)
		return;
	
	printf("\t\tPrinting contents of the above command...\n");
	printf("\t\tid = %d\n", c->id);
	printf("\t\tnpaths = %d\n", c->npaths);
	printf("\t\tpaths =\n");
	int i;
	for(i = 0; i < c->npaths; i++)
		printf("\t\t\t%s\n", c->paths[i]);
	printf("\n");
}

