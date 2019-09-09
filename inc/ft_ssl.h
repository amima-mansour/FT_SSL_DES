#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define BUF			10000

typedef uint8_t			t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;

t_u64					read_stdin(int fd, char **str);

void					usage(void);
void					file_error(char *cmd, char *str);
void					s_error(char *cmd);
void					flag_error(char c, char *cmd);
void					errors(char *str);
#endif