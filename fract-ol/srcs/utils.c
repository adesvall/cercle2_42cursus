/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:44:18 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 18:36:51 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}

int	ft_isin(char c, const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	i = 0;
	res = 0;
	sign = -1;
	while (ft_isin(str[i], " \t\n\v\f\r"))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (ft_isin(str[i], "0123456789"))
	{
		res *= 10;
		res -= str[i] - '0';
		i++;
	}
	return (res * sign);
}

double	getsign(const char *str)
{
	int	i;

	i = 0;
	while (ft_isin(str[i], " \t\n\v\f\r"))
		i++;
	if (str[i] == '-')
		return (-1);
	return (1);
}

double	ft_atod(const char *str)
{
	double	res;
	int		afterdot;

	res = (double)ft_atoi(str);
	afterdot = ft_isin('.', str);
	if (afterdot != 0)
		res += getsign(str) * (double)ft_atoi(&str[afterdot]) \
						/ pow(10, ft_strlen(&str[afterdot]));
	return (res);
}
