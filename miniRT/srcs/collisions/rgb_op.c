/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:29:20 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 19:31:02 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double		limit_color(double n)
{
	if (n > 255)
		return (255);
	if (n < 0)
		return (0);
	return (n);
}

t_rgb	mult_col(double n, t_vect coef, t_rgb color)
{
	color.r = (int)limit_color(color.r * n * coef.x);
	color.g = (int)limit_color(color.g * n * coef.y);
	color.b = (int)limit_color(color.b * n * coef.z);
	return (color);
}

t_rgb	sum_col(t_rgb c1, t_rgb c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return (c1);
}

t_rgb	add_reflect(double reflect, t_rgb color, t_rgb reflectcol)
{
	t_rgb res;

	res.r = (int)limit_color(color.r + reflect * reflectcol.r);
	res.g = (int)limit_color(color.g + reflect * reflectcol.g);
	res.b = (int)limit_color(color.b + reflect * reflectcol.b);
	return (res);
}
