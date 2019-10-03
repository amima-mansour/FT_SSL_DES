/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_crypt.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:40:50 by amansour          #+#    #+#             */
/*   Updated: 2019/10/02 13:52:59 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CRYPT_H
# define FT_SSL_CRYPT_H

# include "ft_ssl.h"

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
	char				*mode;
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
	int					row;
	int					col;
	int					val;
}						t_array;

void					base64(int argc, char **argv);
int						base64_encode(char *in, t_u64 len, char **out,\
						t_u64 *ol);
int						base64_decode(char *in, t_u64 len, char **out,\
						t_u64 *ol);
void					usage_base64(void);
void					print_base64(char *out, t_u64 outlen, int fd);
void					des(int argc, char **argv);
void					usage_des(void);
int						ft_generate_iv_keys(t_des_flags *f, char **s, int *l);
int						hex_expr(char *hex);
char					*hex2dec(char *str, int size);
char					*hex2bin(char *s);
char					*bin2dec(char *s);
char					*dec2bin(char *s);
char					*bin2hex(char *s);
char					*encrypt_des(char *pt, char *key, t_des_flags *f);
char					*decrypt_des(char *ct, char *key, t_des_flags *f);
int						decrypt_base64(char **str, int *len, t_des_flags *f);
int						decrypt_salt(t_des_flags *f, char **s, int *len);
int						crypt_function(char *round_key, t_block *bk, int i);
int						init_block(char *pt, t_block *block, char *iv);
char					*final_text(t_block *bk, t_key k);
int						s_boxes(char *x, char **op);
int						pretreat_des(t_des_flags *flags, char **s, int *l);
void					encrypt_base64(t_des_flags *flags, char *s, int l);
void					crypt_des(t_des_flags *flags, char *str, int len);
/*
**	tools function
*/
char					*xor_function(char *a, char *b);
char					*permute(char *key, int *arr, int n);
char					*shift_left(char *k, int shifts);
int						split(char *str, char **left, char **right, int size);
char					*round_key_function(char **left, char **right,\
						int shift);
int						keygen(char **key);
char					*short_key(char *key);
#endif
