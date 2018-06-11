#include "my_stdio.h"

int my_fputc(int c, my_FILE * stream) {
	unsigned char buf = (unsigned char)c;
	if (stream == my_NULL || stream->write == my_NULL || stream->is_error == my_NULL) return my_EOF;
	stream->write(stream->status, &buf, 1);
	return stream->is_error(stream->status) ? my_EOF : buf;
}

int my_putc(int c, my_FILE *stream) {
	return my_fputc(c, stream);
}
