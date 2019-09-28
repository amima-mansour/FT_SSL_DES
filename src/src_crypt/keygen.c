#include "ft_ssl_crypt.h"
# include "crypt.h"

int keygen(char **key)
{
    char    *binkey;

    if (!(binkey = hex2bin(*key)))
        return (0);
    *key = permute(binkey, g_keyp, 56);
    return (1);
}

char    *short_key(char *key)
{
    int     len;
    char    *new;

    len = ft_strlen(key);
    if (len >= 16)
        return (key);
    if (!(new = malloc(17)))
        return (NULL);
    new[16] = '\0';
    ft_strcpy(new, key);
    free(key);
    while (len < 16)
        new[len++] = '0';
    return (new);
}

char *round_key_function(char **leftkey, char **rightkey, int shift)
{
    char    *concat;
    char    *round_key;

    //Shifting 
    *leftkey = shift_left(*leftkey, shift); 
    *rightkey = shift_left(*rightkey, shift); 
    //Combining
    concat = ft_strjoin(*leftkey, *rightkey);
    //Key Compression
    round_key = permute(concat, g_key_comp, 48);
    return (round_key);
}
