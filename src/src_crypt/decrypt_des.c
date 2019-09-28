#include "ft_ssl_crypt.h"
#include "crypt.h"

char		*decrypt_des(char *ct, char *key)
{
    t_block bk;
    t_key   k;
    int     i;
    char    *keys[16];

    if (!keygen(&key) || !(split(key, &(k.left), &(k.right), 28)) || !init_block(dec2bin(ct), &bk))
        return (NULL);
    i = -1;
    while (++i < 16)
        keys[i] = round_key_function(&(k.left), &(k.right), g_shift_table[i]);
    i = -1;
    while (++i < 16)
        if (!crypt_function(keys[15 - i], &bk, i))
            return (NULL);
    return (final_text(&bk));
}