#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t l1, size_t l2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	str = ft_strnew(ft_strlen(s2) + ft_strlen(s1) + 1);
	if (str)
	{
		i = 0;
		j = 0;
		while (i < l1)
		{
			str[i] = s1[i];
			++i;
		}
		while (j < l2)
		{
			str[i + j] = s2[j];
			++j;
		}
		str[i + j] = '\0';
	}
	return (str);
}
