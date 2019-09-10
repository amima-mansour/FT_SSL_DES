#include "ft_ssl_crypt.h"
#include "ft_ssl_hash.h" 

char	*getsalt(void)
{
	FILE	*f;
    char    *salt;

	if (!(salt = (char *)malloc(9)))
        exit(-1);
    if ((f = fopen("/dev/urandom","r")) == NULL) {
        ft_putstr_fd("probleme fopen\n", 2);
        exit(1);
    }
    fread(salt, sizeof(salt), 8, f);
    salt[8] = '\0';
	fclose(f);
	return (salt);
}

static void PBDKF2(t_des_flags *f)
{
    char            *concat;
    t_md5_context	c;

    if (!(concat = ft_strjoin_16(f->passwd, f->salt)) || \
        !(f->key = malloc(17)) || !(f->iv = malloc(17)))
        return ;
    c = treat_md5(concat, ft_strlen(f->salt) + ft_strlen(f->passwd));
    free(concat);
    concat = str_msg_md5(c);
    f->key[16] = '\0';
    f->iv[16] = '\0';
    f->key = ft_strncpy(f->key, concat, 16);
    f->iv = ft_strncpy(f->iv, concat + 16, 16);
    
    free(concat);
}

void    ft_generate_keys(t_des_flags *flags)
{

    if (!flags->salt)
        flags->salt = getsalt();
    flags->salt = convert_2_char(flags->salt);
    flags->tmp = ft_strjoin("Salted__", flags->salt);
    PBDKF2(flags);
}