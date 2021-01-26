/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 16:57:17 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vect	get_lum_coef(t_scn *scn, t_vect coli, t_vect normale)
{
	t_list	*ite;
	t_lum	*lum;
	t_vect	lumdir;
	double	c;
	t_vect	coef;

	coef = mult(scn->ambI / 255, scn->ambCol);
	ite = scn->lums;
	while (ite)
	{
		lum = (t_lum*)ite->content;
		lumdir = lum->dir ?
				mult(-1, lum->vec) : normalize(diff(lum->vec, coli));
		c = lum->dir ? -1 : norm(diff(lum->vec, coli));
		if (collision_any((t_ray){coli, lumdir}, scn, 0, c).elem == NULL)
		{
			c = lum->I / 255 * dot(normale, lumdir);
			if (lum->dir)
				c *= 1000 / pow(norm(diff(lum->vec, coli)), 2);
			c = (c > 0) ? c : 0;
			coef = sum(coef, mult(c, lum->color));
		}
		ite = ite->next;
	}
	return (coef);
}

t_rgb	get_color(t_scn *scn, t_ray ray, int rfi)
{
	t_vect	coli;
	t_vect	coef;
	t_rescl	res;

	res = collision_any(ray, scn, &coli, -1);
	if (res.elem == NULL)
		return (scn->sky.img ? get_sky_coord(scn, ray) : (t_rgb){0, 0, 0});
	coef = get_lum_coef(scn, coli, res.normale);
	res.color = mult_col(5, coef, res.color);
	if (REFLECT > EPSILON && rfi > 0)
	{
		ray = (t_ray){coli, normalize(sum(ray.dir,
						mult(-2 * dot(ray.dir, res.normale), res.normale)))};
		res.color = add_reflect(REFLECT, res.color,
												get_color(scn, ray, rfi - 1));
	}
	return (res.color);
}
