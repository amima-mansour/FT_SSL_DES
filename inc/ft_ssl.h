#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"

# define BUF			10000

typedef uint8_t			t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;

t_u64					read_function(int fd, char **str);
void					usage(void);
void					file_error(char *cmd, char *str);
void					flag_error(char c, char *cmd);
void					errors(char *str);
char					*ft_strjoin_s(char const *s1, char const *s2, t_u64 l);
void					ft_putstr_size(char *s, size_t size);
void					*ft_memcpy_64(void *dest, const void *src, t_u64 len);
void					*ft_calloc(t_u64 nmemb, size_t size);
int		                ft_strcmp(char const *str1, char const *str2);

#endif