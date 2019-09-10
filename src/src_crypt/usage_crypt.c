#include "ft_ssl_crypt.h"

void	usage_base64(void)
{
	ft_putstr_fd("Usage:	base64 [-ed] [-i in_file] [-o out_file]\n\
	-d, decode mode\n\
	-e, encode mode (default)\n\
	-i, input file\n\
	-o, output file\n", 2);
	exit(-1);
}