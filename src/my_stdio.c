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

int my_ungetc(int c, my_FILE *stream) {
	if (stream == my_NULL || c == my_EOF) return my_EOF;
	if (stream->ungetc_num < 0 || stream->ungetc_num >= MY_C_LIBRARY_UNGETC_MAX) return my_EOF;
	return stream->ungetc_buffer[stream->ungetc_num++] = (unsigned char)c;
}
