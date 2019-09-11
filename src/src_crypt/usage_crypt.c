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

void	usage_des(void)
{
	ft_putstr_fd("Usage: des [OPTION] -k=KEY FILE\n"
	"Encrypt or Descrypt with DES.\n\n"
	" -k, --key=KEY     required 64bits key\n"
    " -d, --decrypt     decrypt DES from input file\n"
    " -e, --encrypt     encrypt DES from input file\n"
	" -o, --output=FILE write result to FILE\n", 2);
	exit(-1);
}