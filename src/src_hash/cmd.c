
#include "ft_ssl_hash.h"

static void	cmd_array(t_hash_functions *hash[])
{
	(*hash)[0].name = "md5";
	(*hash)[0].cmd = &md5;
	(*hash)[1].name = "sha256";
	(*hash)[1].cmd = &sha256;
	(*hash)[3].name = "sha512";
	(*hash)[3].cmd = &sha512;
	(*hash)[2].name = "sha224";
	(*hash)[2].cmd = &sha224;
	(*hash)[4].name = "sha384";
	(*hash)[4].cmd = &sha384;
	(*hash)[5].name = "sha512256";
	(*hash)[5].cmd = &sha512256;
	(*hash)[6].name = "sha512224";
	(*hash)[6].cmd = &sha512224;
	(*hash)[7].name = "base64";
	(*hash)[8].name = "des-ecb";
	(*hash)[9].name = "des-cbc";
}

void		cmd_check(char *s, void (**cmd)(char*, t_flags, char*, t_u64))
{
	t_hash_functions	*hash[NB_FUNCTIONS];
	int					i;

	cmd_array(hash);
	i = -1;
	*cmd = NULL;
	while (++i < NB_FUNCTIONS)
	{
		if (ft_strcmp(s, (*hash)[i].name) == 0)
			*cmd = (*hash)[i].cmd;
	}
	if (*cmd == NULL && ft_strcmp(s, "base64") && ft_strcmp(s, "des"))
		cmd_error(hash, s);
}
