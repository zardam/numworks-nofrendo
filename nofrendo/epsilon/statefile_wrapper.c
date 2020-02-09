#include "statefile_wrapper.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STATEFILE_SIZE 1<<15

extern bool file_exists(const char * filename);
extern bool erase_file(const char * filename);
extern const char * read_file(const char * filename);
extern bool write_file(const char * filename, const char * s, size_t len);

typedef struct {
	char content[STATEFILE_SIZE];
	size_t pos;
} statefile_desc_t;

static statefile_desc_t statefile;

FILE *statefile_fopen(const char *pathname, const char *mode) {
	statefile.pos = 0;
	return (FILE *) 1;
}

int statefile_fclose(FILE *stream) {
	return 0;
}

size_t statefile_fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	if (size * nmemb == 0) return nmemb;
	memcpy(ptr, statefile.content + statefile.pos, size * nmemb);
	statefile.pos += (size*nmemb);
	return nmemb;
}

size_t statefile_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	if (size * nmemb == 0) return nmemb;
	if (statefile.pos + size * nmemb > STATEFILE_SIZE) return 0;
	memcpy(statefile.content + statefile.pos, ptr, size * nmemb);
	statefile.pos += (size * nmemb);
	return nmemb;
}

int statefile_fseek(FILE *stream, long offset, int whence) {
	if (whence == SEEK_SET) {
		statefile.pos = offset;
	} else if (whence == SEEK_CUR) {
		statefile.pos += offset;
	} else if (whence == SEEK_END) {
		abort();
	}
	return 0;
}
