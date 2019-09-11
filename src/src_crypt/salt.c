#include "ft_ssl_crypt.h"
#include "ft_ssl_hash.h"

static int check_salt(t_des_flags *f)
{
    char *tmp;
    
    if (!f->salt)
    {
        if (!(f->salt = (char *)malloc(9)))
            return (0);
        if  (getentropy(f->salt, 8) == -1)
        {
            free(f->salt);
            return (0);
        }
        f->salt[8] = '\0';
    }
    else
    {
        if (ft_strlen(f->salt) > 16 || !hex_expr(f->salt))
        {
            ft_putstr_fd("Problem with salt expression!", 2);
            return (0);
        }
        if (ft_strlen(f->salt) < 16)
        {
            while (ft_strlen(f->salt) < 16)
            {
                tmp = ft_strjoin(f->salt, "0");
                free(f->salt);
                f->salt = tmp; 
            }
        }
        f->salt = convert_2_char(f->salt, 8);
    }
    return (1);

}  

static int pbkdf2(t_des_flags *f)
{
    char            *res;
    t_md5_context	c;

    if (!(res = ft_strjoin(f->passwd, f->salt)))
        return (0);
    c = treat_md5(res, ft_strlen(res));
    free(res);
    res = str_msg_md5(c);
    if (!(f->key = (char*)malloc(17)))
        return (0);
    if (!(f->iv = (char*)malloc(17)))
    {
        free(f->key);
        return (0);
    }   
    ft_memcpy(f->key, res, 16);
    ft_memcpy(f->iv, res + 16, 16);
    f->key[16] = '\0';
    f->iv[16] = '\0';
    free(res);
    if (!f->key || !f->iv)
        return (0);
    return (1);
}

int         ft_generate_iv_keys(t_des_flags *f)
{
    if (!check_salt(f))
        return (0);
    f->tmp = ft_strjoin("Salted__", f->salt);
    return (pbkdf2(f));
}