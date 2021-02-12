/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruptions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:59:03 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 14:59:35 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	apply_color_disruption(t_vect normale, t_sph *sph)
{
	t_rgb	rgb;
	double	b;

	if (sph->disruption == 'c')
	{
		rgb.r = fabs(normale.x) * 255;
		rgb.g = fabs(normale.y) * 255;
		rgb.b = fabs(normale.z) * 255;
		return (rgb);
	}
	else if (sph->disruption == 't')
	{
		b = sqrt(normale.y * normale.y + normale.x * normale.x);
		return (get_xpm_color(sph->texture,
								-atan(normale.z / b) / M_PI + 0.5,
								-atan2(normale.x, normale.y) / M_PI + 0.5));
	}
	return (sph->color);
}

t_rgb	apply_texture(t_vect coli, t_pln *pln)
{
	double	x;
	double	y;

	x = dot(pln->right, diff(coli, pln->origin)) / 10;
	y = dot(pln->down, diff(coli, pln->origin)) / 10;
	if (pln->disruption == 'c' &&
						(abs((int)floor(x) % 2) ^ abs((int)floor(y) % 2)))
		return ((t_rgb){0, 0, 0});
	else if (pln->disruption == 't')
		return (get_xpm_color(pln->texture, x - floor(x), y - floor(y)));
	return (pln->color);
}

t_vect	apply_normal_disruption(t_vect coli, t_pln *pln, t_vect normale)
{
	double	x;

	if (pln->disruption == 'n')
	{
		x = 0.05 * sin(dot(pln->right, diff(coli, pln->origin)));
		return (normalize(sum(normale, mult(x, pln->right))));
	}
	return (normale);
}

t_rgb	get_xpm_color(t_data xpm, double x, double y)
{
	int		column;
	int		row;
	int		trgb;
	t_rgb	color;

	column = (int)(xpm.h * y);
	row = (int)(xpm.h * x);
	trgb = *((unsigned int*)(xpm.addr +
			(row * xpm.line_length + column * (xpm.bits_per_pixel / 8))));
	color.b = trgb & 0xFF;
	color.g = (trgb >> 8) & 0xFF;
	color.r = (trgb >> 16) & 0xFF;
	return (color);
}
