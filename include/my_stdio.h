#ifndef MY_STDIO_H_GUARD_BBAFB7EE_98BC_4E66_BA11_5BD632E143B6
#define MY_STDIO_H_GUARD_BBAFB7EE_98BC_4E66_BA11_5BD632E143B6

#include "my_stddef.h"

#define MY_C_LIBRARY_UNGETC_MAX 16

typedef struct {
	/* user-defined data */
	void* status;
	/* read to data, return size read */
	my_size_t (*read)(void* status, unsigned char* data, my_size_t max_size);
	/* write data, return size written */
	my_size_t (*write)(void* status, const unsigned char* data, my_size_t length);
	int (*is_eof)(void* status);
	int (*is_error)(void* status);
	int ungetc_num;
	unsigned char ungetc_buffer[MY_C_LIBRARY_UNGETC_MAX];
} my_FILE;

#define my_EOF (-1)

MY_C_LIBRARY_EXTERN_C

int my_fputc(int c, my_FILE *stream);

int my_putc(int c, my_FILE *stream);

int my_ungetc(int c, my_FILE *stream);

MY_C_LIBRARY_EXTERN_C_END

#endif

