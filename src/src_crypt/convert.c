#include "ft_ssl_crypt.h"

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
        return (c - 48);
    return (c - 55);
} 

char *convert_2_char(char *str)
{
    size_t  i;
    size_t  j;
    char    *s;
    int     nbr;

    if (!(s = (char*)malloc(ft_strlen(str) / 2 + 1)))
        return (NULL);
    i = -1;
    j = 0;
    while (++i <= ft_strlen(str))
    {
        nbr = convert_a_hex(str[i]);
        nbr = nbr * 16 + convert_a_hex(str[++i]); 
        s[j] = nbr;
        j += 1;
    }
    s[ft_strlen(str) / 2] = '\0';
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