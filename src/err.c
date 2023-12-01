#include "err.h"

void err_sys(const char *err_msg, const char *file_name, int line_no) {
	if (file_name != NULL && line_no != 0)
		fprintf(stderr, "In %s Line %d: %s\n", file_name, line_no, err_msg);
	else
		fprintf(stderr, "%s\n", err_msg);
	fflush(stderr);
	exit(1);
}