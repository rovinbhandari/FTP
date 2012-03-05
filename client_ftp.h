#include <commons.h>

#define IPSERVER	"127.0.0.1"
#define	ID		"CLIENT=> "

#define extract_filename(filepath) ((strrchr(filepath, '/') != NULL) ? (strrchr(filepath, '/') + 1) : filepath)

void receive_file(char*, int, struct packet*);


