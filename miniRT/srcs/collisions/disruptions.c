/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruptions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:59:03 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/21 22:09:37 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	apply_texture(t_vect coli, t_pln *pln)
{
	double	x;
	double	y;

	x = dot(pln->right, diff(coli, pln->origin)) / 10;
	y = dot(pln->down, diff(coli, pln->origin)) / 10;
	if (pln->disruption == 'c' && ((int)floor(x) % 2) ^ ((int)floor(y) % 2))
		return ((t_rgb){0, 0, 0});
	else if (pln->disruption == 't')
		return (get_xpm_color(pln->texture, x - floor(x), y - floor(y)));
	return (pln->color);
}

t_vect	apply_normal_disruption(t_vect coli, t_pln *pln)
{
	double	x;
	
	if (pln->disruption == 'n')
	{
		x = sin(dot(pln->right, diff(coli, pln->origin)));
		return (normalize(sum(pln->normale, mult(x, pln->right))));
	}
	return (pln->normale);
}

t_rgb		get_xpm_color(t_data xpm, double x, double y)
{
	int		column;
	int		row;
	int		trgb;
	t_rgb	color;

	if (x < 0)
		x++;
	if (y < 0)
		y++;
	column = (int)(xpm.H * y);
	row = (int)(xpm.H * x);
	trgb = *((unsigned int*)(xpm.addr + (row * xpm.line_length + column * (xpm.bits_per_pixel / 8))));
	color.b = trgb & 0xFF;
	color.g = (trgb >> 8) & 0xFF;
	color.r = (trgb >> 16) & 0xFF;
	return (color);
}
