#ifndef FT_SSL_CRYPT_H
# define FT_SSL_CRYPT_H

# include "ft_ssl.h"
# include <sys/random.h>

# define KY64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define BASE64 KY64
# define BASE16			"0123456789ABCDEF"
typedef uint8_t			t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;

typedef struct			s_b64_flags
{
	char				encrypt;
	char				o;
	char				i;
	char				decrypt;
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
	char				*passwd;
	char				*salt;
	char				*key;
	char				*iv;
	char				*tmp;		
}						t_des_flags;

void					base64(int argc, char **argv);
void					base64_encode(char *in, t_u64 len, int fd);
void					base64_decode(char *in, t_u64 len, int fd);
void					usage_base64(void);
void					des(int argc, char **argv);
int         			ft_generate_iv_keys(t_des_flags *f);
char					*convert_2_char(char *str, int size);
char					*ft_strjoin_16(char const *s1, char const *s2);
int     				hex_expr(char *hex);
char 					*convert_2_hex(char *str);
char					*hex_2_bin(char *s);
char					*bin_2_decimal(char *s);
char					*algo_des(char *pt, char *key);
/*
**	tools function
**/
char					*xor_function(char *a, char *b);
char					*permute(char *key, int* arr, int n);
char					*shift_left(char *k, int shifts);
int						split(char *str, char **left, char **right, int size);

char					*round_key_function(char **leftkey, char **rightkey, int shift);
int						keygen(char **key);
#endif