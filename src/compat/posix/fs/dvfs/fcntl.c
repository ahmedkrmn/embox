/**
 * @file
 * @brief Implementation of the POSIX fcntl function
 * @date 3 Apr 2015
 * @author Denis Deryugin
 */

#include <fcntl.h>
#include <kernel/task/resource/file_table.h>

int fcntl(int fd, int cmd, ...) {
	va_list args;
	int i;
	switch (cmd) {
	case F_DUPFD:
		va_start(args, cmd);
		i = va_arg(args, int);
		va_end(args);
		return file_table_dupfd(fd, i);
	}

	return 0;
}
