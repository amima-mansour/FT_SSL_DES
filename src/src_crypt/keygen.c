#include "ft_ssl_crypt.h"
# include "crypt.h"

int keygen(char **key)
{
    char *binkey;

    if (!(binkey = hex_2_bin(*key)))
        return (0);
    free(*key);
    *key = permute(binkey, g_keyp, 56);
    return (1);
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
