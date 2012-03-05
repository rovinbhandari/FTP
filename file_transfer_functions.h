#include <commons.h>

#define extract_filename(filepath) ((strrchr(filepath, '/') != NULL) ? (strrchr(filepath, '/') + 1) : filepath)

void send_EOT(int, struct packet*);
void send_TERM(int, struct packet*);

void send_file(char*, int, struct packet*);
void receive_file(char*, int, struct packet*);

