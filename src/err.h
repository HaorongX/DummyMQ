#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <stdlib.h>

void
err_sys(const char *err_msg, const char *file_name, int line_no);

#endif