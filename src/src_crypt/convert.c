#include "ft_ssl_crypt.h"

static char * g_mp[16] =
{
    "0000", "0001", "0010", "0011", 
    "0100", "0101", "0110", "0111", 
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

char *convert_2_hex(char *str)
{
    int     i;
    int     j;
    char    *s;

    if (!(s = (char*)malloc(2 * ft_strlen(str) + 1)))
        return (NULL);
    i = -1;
    j = 0;
    s[ft_strlen(str) * 2] = '\0';
    while (str[++i])
    {
        s[j] = BASE16[str[i] / 16];
        s[j + 1] = BASE16[str[i] % 16];
        j += 2;
    }
    return (s);
}

static int convert_a_hex(char c)
{
    if (c >= '0' && c <= '9') 
        return (c - '0');
    if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    return (c - 'A' + 10);
} 

char *convert_2_char(char *str, int size)
{
    int  i;
    int  j;
    char *s;
    int  nbr;

    if (!(s = (char*)malloc(size + 1)))
        return (NULL);
    i = -1;
    j = 0;
    while (++i <= size * 2)
    {
        nbr = convert_a_hex(str[i]);
        nbr = nbr * 16 + convert_a_hex(str[++i]); 
        s[j] = nbr;
        j++;
    }
    s[size] = '\0';
    return (s);
}

t_u64 convert_2_decimal(char *str)
{
    int     i;
    t_u64   nbr;

    i = -1;
    nbr = 0;
    while (str[++i])
    {
        nbr = nbr >> 8;
        nbr += str[i];
    }
    return (nbr);
}

char	*ft_strjoin_16(char const *s1, char const *s2)
{
	char	*str;
	size_t 	i;
    size_t	j;

	if ((str = (char*)malloc(ft_strlen(s1) + 1 + 8)))
	{
		i = -1;
		while (++i < ft_strlen(s1))
			str[i] = s1[i];
		j = -1;
        while (++j < 8)
		{
			str[i] = s2[j];
			++i;
		}
		str[i] = '\0';
	}
	return (str);
}

int     hex_expr(char *hex)
{
    int i;

    i = -1;
    while (hex[++i])
    {
        if (!((hex[i] >= '0' && hex[i] <= '9') \
        || (hex[i] >= 'A' && hex[i] <= 'F') \
        || (hex[i] >= 'a' && hex[i] <= 'f')))
            return (0);
    }
    return (1);
}

char *hex_2_bin(char *s)
{ 
    char    *str;
    size_t  i;
    int     j;
    int     index;

    if (!(str = (char*)malloc(ft_strlen(s) * 4 + 1)))
        return (NULL); 
    i = -1;
    j = 0;
    while (s[++i])
    {
        if (s[i] >= '0' && s[i] <= '9')
            index = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            index = s[i] - 'a' + 10;
        else
            index = s[i] - 'A' + 10;
        ft_memcpy(str + j, g_mp[index], 4);
        j += 4;
    }
    str[ft_strlen(s) * 4] = '\0';
    return (str); 
}

char *bin_2_decimal(char *s)
{
    char    *str;
    int     j;
    size_t  i;
    int     nbr;
    int     k;

    if (!(str = (char*)malloc(ft_strlen(s) / 8 + 1)))
        return (NULL);
    i = -1;
    j = 0;
    nbr = 0;
    k = 0;
    while(s[++i])
    {
        nbr = nbr << 1;
        if (s[i] == '1')
        {
            ft_printf("NBBBBB Avant = %d\n", nbr);
            nbr |= 1;
            ft_printf("NBBBBB Apres = %d\n", nbr);
        }
        if (++j == 8)
        {
            j = 0;
            str[k] = nbr;
            ft_printf("NBR = %d\n", nbr);
            nbr = 0;
            k++;
        }
    }
    str[k] = '\0';
    return (str);
}