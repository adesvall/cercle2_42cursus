/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:10:37 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 18:32:57 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void		ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char*)s)[i] = 0;
		i++;
	}
}

static int	ft_count(const char *s, char *c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	word = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (word == 0 && !ft_isin(s[i], c))
		{
			word = 1;
			count++;
		}
		else if (ft_isin(s[i], c))
			word = 0;
		i++;
	}
	return (count);
}

static char	*ft_strdup_chr(const char *str, char *c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && !ft_isin(str[i], c))
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	while (str[i] && !ft_isin(str[i], c))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char		**ft_abort(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

char		**ft_split(const char *s, char *c)
{
	char	**res;
	int		i;
	int		count;
	int		word;

	if ((!(count = ft_count(s, c)) && !s)
					|| !(res = malloc(sizeof(char*) * (count + 1))))
		return (0);
	ft_bzero(res, sizeof(char*) * (count + 1));
	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (word == 0 && !ft_isin(s[i], c))
		{
			if ((res[count++] = ft_strdup_chr(&(s[i]), c)) == 0)
				return (ft_abort(res));
			word = 1;
		}
		if (ft_isin(s[i++], c))
			word = 0;
	}
	res[count] = 0;
	return (res);
}
