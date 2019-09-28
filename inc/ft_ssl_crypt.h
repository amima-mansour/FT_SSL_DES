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
	char				a;		
}						t_des_flags;

typedef struct			s_key
{
	char				*right;
	char				*left;
}						t_key;

typedef struct			s_block
{
	char				*right;
	char				*left;
}						t_block;

typedef struct			s_array
{
	int 				row;
	int 				col;
    int                 val;
}						t_array;


void					base64(int argc, char **argv);
int						base64_encode(char *in, t_u64 len, char **out, t_u64 *outlen);
int						base64_decode(char *in, t_u64 len, char	**out, t_u64 *outlen);
void					usage_base64(void);
void					des(int argc, char **argv);
void					usage_des(void);
int         			ft_generate_iv_keys(t_des_flags *f, char **str, int *len);
char					*convert_2_char(char *str, int size);
int     				hex_expr(char *hex);
char					*hex2bin(char *s);
char					*bin2dec(char *s);
char					*dec2bin(char *s);
char 					*bin2hex(char *s);
char					*encrypt_des(char *pt, char *key);
char					*decrypt_des(char *ct, char *key);
int     				crypt_function(char *round_key, t_block *bk, int i);
int         			init_block(char *pt, t_block *block);
char        			*final_text(t_block *bk);
int             		s_boxes(char *x, char **op);
/*
**	tools function
**/
char					*xor_function(char *a, char *b);
char					*permute(char *key, int* arr, int n);
char					*shift_left(char *k, int shifts);
int						split(char *str, char **left, char **right, int size);
void    				print_result(char *text, int fd);
char					*round_key_function(char **leftkey, char **rightkey, int shift);
int						keygen(char **key);
char					*short_key(char *key);
#endif