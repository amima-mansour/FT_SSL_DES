#include "../libft/inc/libft.h"
#include "ft_ssl.h"

static void check_mode(char *str, char **mode)
{
    if (ft_strcmp(str, "des-ecb") == 0)
        *mode = "des-ecb";
    if (ft_strcmp(str, "des-cbc") == 0)
        *mode = "des-cbc";
}

static  void  check_one_flag(char *value, char *flag, t_des_flags *f)
{
    if (!ft_strcmp(flag, "-o"))
        f->out = value;
    if (!ft_strcmp(flag, "-i"))
        f->in = value;
    if (!ft_strcmp(flag, "-k"))
        f->key = value;
    if (!ft_strcmp(flag, "-p"))
        f->passwd = value;
    if (!ft_strcmp(flag, "-s"))
        f->salt = value;
    if (!ft_strcmp(flag, "-v"))
        f->v = value;
}

static  void  init_flags(t_des_flags *f)
{
    f->out = NULL;
    f->fd_in = 0;
    f->fd_out = 1;
    f->in = NULL;
    f->key = NULL;
    f->passwd = NULL;
    f->salt = NULL;
    f->v = NULL;
    f->encrypt = 1;
    f->decrypt = 0;
}

static  void  parse_flags(char **av, int ac, t_des_flags *f)
{
    int     i;
    char    *str;

    i = 1;
    while (++i < ac)
    {
        if (!ft_strcmp(av[i], "-o") || !ft_strcmp(av[i], "-i") ||\
        !ft_strcmp(av[i], "-k") || !ft_strcmp(av[i], "-p") ||\
        !ft_strcmp(av[i], "-s" || !ft_strcmp(av[i], "-v")))
        {
            if (i + 1 >= ac)
                usage_base64();
            check_one_flag(av[i + 1], av[i], f);
        }
        else if (!ft_strcmp(av[i], "-d"))
            f->decrypt = 1;
        else if (!ft_strcmp(av[i], "-e"))
            f->encrypt = 1;
        else
            usage_base64();
    }
}

void                des(int argc, char **argv)
{
    char        *mode;
    t_des_flags flags;

    check_mode(argv[0], &mode);
    init_flags(&flags);
    parse_flags(argv, argc, &flags);

}