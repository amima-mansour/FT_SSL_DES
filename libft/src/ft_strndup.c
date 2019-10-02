#include "libft.h"

char	*ft_strndup(char const *s, int len)
{
	char *str;

	str = ft_strnew(len);
	if (str)
		ft_strncpy(str, s, len);
	return (str);
}