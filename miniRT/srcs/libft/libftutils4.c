/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftutils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:24:23 by user42            #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_strend_is(char *str, char *end)
{
	int i;
	int j;

	i = ft_strlen(str) - ft_strlen(end);
	j = 0;
	while (str[i + j])
	{
		if (str[i + j] != end[j])
			return (0);
		j++;
	}
	return (!end[j]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}
