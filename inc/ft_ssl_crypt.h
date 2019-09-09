#ifndef FT_SSL_CRYPT_H
# define FT_SSL_CRYPT_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define KY64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define BASE64 KY64
typedef uint8_t			t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;

typedef struct			s_b64_flags
{
	char				encrypt;
	char				o;
	char				i;
	char				decrypt;
	char				error;
	char				*in;
	char				*out;
	int					fd_in;
	int					fd_out;
}						t_b64_flags;

typedef struct			s_des_flags
{
	char				encrypt;
	char				decrypt;
	char				*in;
	char				*out;
	int					fd_in;
	int					fd_out;
	unsigned char		*passwd;
	unsigned char		*salt;
	unsigned char		*key;
	unsigned char		*iv;			
}						t_des_flags;
void					base64(int argc, char **argv);
void					base64_encode(char *in, t_u64 len, int fd);
void					base64_decode(char *in, t_u64 len, int fd);
void					usage_base64(void);

#endif