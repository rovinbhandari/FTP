#include <commons.h>

#define extract_filename(filepath) ((strrchr(filepath, '/') != NULL) ? (strrchr(filepath, '/') + 1) : filepath)

void send_EOT(struct packet*, struct packet*, int);
void send_TERM(struct packet*, struct packet* , int);

void send_file(struct packet*, struct packet*, int, FILE*);
void receive_file(struct packet*, struct packet*, int, FILE*);

