#include "ft_ssl.h"
#include "../libft/libft.h"

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int b64invs[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };

static int b64_isvalidchar(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '+' || c == '/' || c == '=')
		return (1);
	errors("Invalid character in input.");
	return (0);
}

void b64_generate_decode_table()
{
	int    inv[80];
	size_t i;

	memset(inv, -1, sizeof(inv));
	for (i=0; i<sizeof(b64chars)-1; i++) {
		inv[b64chars[i]-43] = i;
	}
}

static t_u64	size_base64_decode(char *src, t_u64 slen)
{
    t_u64 i;
	t_u64 n;
    t_u64 j;
	t_u64 x;

    /* First pass: check for validity and get output length */
    j = 0;
	n = 0;
	i = -1;
	while (++i < slen)
    {
        /* Skip spaces before checking for EOL */
        x = 0;
        while(i < slen && src[i] == ' ')
        {
            ++i;
            ++x;
        }
        /* Spaces at end of buffer are OK */
        if(i == slen)
            break;
        /*to check this */
		if((slen - i) >= 2 && src[i] == '\r' && src[i + 1] == '\n')
            continue;
        if(src[i] == '\n')
            continue;
        /* Space inside a line is an error */
        if( x != 0 )
            errors("Invalid character in input.");;
        if( src[i] == '=' && ++j > 2 )
            errors("Invalid character in input.");
		b64_isvalidchar(src[i]);
        n++;
	}
	if (!n)
		return (n);
    /* The following expression is to calculate the following formula without
     * risk of integer overflow in n:
     *     n = ( ( n * 6 ) + 7 ) >> 3;
     */
    n = ( 6 * ( n >> 3 ) ) + ( ( 6 * ( n & 0x7 ) + 7 ) >> 3 );
    n -= j;
	return (n);
}

char 			*base64_decode(char *in, t_u64 len)
{
	t_u64	outlen;
	char	*out;
	t_u64	i;
	t_u64	j;
	int		v;

	if (len % 4 != 0)
		return (NULL);
	outlen = size_base64_decode(in, len); 
	if (!(out = malloc(outlen)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		v = b64invs[in[i]-43];
		v = (v << 6) | b64invs[in[i+1]-43];
		v = in[i+2]=='=' ? v << 6 : (v << 6) | b64invs[in[i+2]-43];
		v = in[i+3]=='=' ? v << 6 : (v << 6) | b64invs[in[i+3]-43];

		out[j] = (v >> 16) & 0xFF;
		if (in[i+2] != '=')
			out[j+1] = (v >> 8) & 0xFF;
		if (in[i+3] != '=')
			out[j+2] = v & 0xFF;
		i+= 4;
		j+= 3;
	}
	return (out);
}