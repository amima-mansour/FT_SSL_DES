/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:36:20 by amansour          #+#    #+#             */
/*   Updated: 2019/09/01 16:43:05 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

static	t_u64 base64_trim(char *str)
{
    t_u64   start;
    t_u64   end;

    start = 0;
    end = 0;
    while (str[end])
    {
        if (str[end] != ' ' && str[end] != '\n' && str[end] != '\t' && str[end] != '\r')
        {
            str[start] = str[end];
            start++;
        }
        end++;
    }
    return (start);
}

static int		copy_over(char *c, char *e, char *s)
{
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < 4)
		if (e[i] == '=')
		{
			ret++;
			c[i] = 0;
		}
	s[0] = (c[0] << 2) | (c[1] >> 4);
	s[1] = ((c[1] & 15) << 4) | (c[2] >> 2);
	s[2] = ((c[2] & 3) << 6) | c[3];
	return (ret);
}

static int				four_to_three(char *str, char *enc, char *key)
{
	int		i;
	int		j;
	char	c[4];

	i = -1;
	while (++i < 4)
	{
		if (!(ft_isalpha(enc[i]) || ft_isdigit(enc[i]) || enc[i] == '+' ||
					enc[i] == '/' || enc[i] == '='))
			return (-1);
	}
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 4)
			if (enc[j] == key[i])
				c[j] = i;
	}
	return (copy_over(c, enc, str));
}


char					*base64_decode(char *in, t_u64 len, t_u64 *outlen)
{
	char	*out;
	t_u64	i;
	int		ret;

	//outlen = size_base64_decode(in, len);
	len = base64_trim(in);
	*outlen = (len / 4) * 3;
	if (!(out = malloc(*outlen)))
		return (NULL);
	i = 0;
	while (i < *outlen)
	{
		if ((ret = four_to_three(&(out[i]), in, BASE64_KEY)) == -1)
		{
			errors("Invalid character in input stream.");
			free(out);
			return (NULL);
		}
		i += 3;
		in += 4;
	}
	*outlen -= ret;
	/*treat_base_encode(&out, in, len);
	out[outlen - 1] = '\0';*/
	return (out);
}
