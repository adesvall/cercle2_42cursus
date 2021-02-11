/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:15:03 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 13:27:44 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		vect_check(char **vect)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while (vect[j])
	{
		str = vect[j];
		i = 0;
		while (str[i])
		{
			if (!ft_isin(str[i], "-+0123456789."))
				return (WRONG_ARG);
			i++;
		}
		j++;
	}
	return (0);
}

int		strto_vect(t_vect *dst, char *str, int isrgb)
{
	char	**tab;

	tab = ft_split(str, ",");
	if (ft_tablen(tab) != 3 || vect_check(tab))
	{
		ft_abort(tab);
		return (WRONG_ARG);
	}
	if (isrgb)
		*dst = tabto_lumrgb(tab);
	else
		*dst = tabto_vect(tab);
	ft_abort(tab);
	return (0);
}

int		strto_rgb(t_rgb *dst, char *str)
{
	char	**tab;

	tab = ft_split(str, ",");
	if (ft_tablen(tab) != 3 || vect_check(tab))
	{
		ft_abort(tab);
		return (WRONG_ARG);
	}
	*dst = tabto_rgb(tab);
	ft_abort(tab);
	return (0);
}
