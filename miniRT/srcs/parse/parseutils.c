/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:55:11 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/21 18:53:32 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vect	tabto_vect(char **s)
{
	t_vect v;

	v.x = ft_atod(s[0]);
	v.y = ft_atod(s[1]);
	v.z = ft_atod(s[2]);
	return (v);
}

t_vect	tabto_lumrgb(char **s)
{
	t_vect v;

	v.x = limit_color(ft_atod(s[0]));
	v.y = limit_color(ft_atod(s[1]));
	v.z = limit_color(ft_atod(s[2]));
	return (v);
}

t_rgb	tabto_rgb(char **s)
{
	t_rgb v;

	v.r = (int)limit_color(ft_atod(s[0]));
	v.g = (int)limit_color(ft_atod(s[1]));
	v.b = (int)limit_color(ft_atod(s[2]));
	return (v);
}

void	set_caps(t_cyl *cyl, t_dsk *dsk1, t_dsk *dsk2)
{
	dsk1->origin = sum(cyl->origin, mult(cyl->length / 2, cyl->dir));
	dsk2->origin = sum(cyl->origin, mult(-cyl->length / 2, cyl->dir));
	dsk1->normale = cyl->dir;
	dsk2->normale = cyl->dir;
}

void	set_faces(t_cub *cub)
{
	int		i;
	t_sqr	**sqrs;

	sqrs = cub->sqrs;
	if (cub->dirs[0].x == 0 && cub->dirs[0].y == 0)
		cub->dirs[1] = (t_vect){1, 0, 0};
	else
		cub->dirs[1] = normalize((t_vect){100 * cub->dirs[0].y, -100 * cub->dirs[0].x, 0});
	cub->dirs[2] = normalize(prod_vect(cub->dirs[0], cub->dirs[1]));
	i = 0;
	while (i < 3)
	{
		sqrs[2 * i]->origin = sum(cub->origin, mult(cub->side / 2, cub->dirs[i]));
		sqrs[2 * i]->normale = cub->dirs[i];
		sqrs[2 * i]->right = cub->dirs[(i + 1) % 3];
		sqrs[2 * i]->down = cub->dirs[(i + 2) % 3];
		sqrs[2 * i]->side = cub->side;
		sqrs[2 * i]->cub = cub;
		sqrs[2 * i]->color = cub->sqrs[0]->color;
		sqrs[2 * i + 1]->origin = sum(cub->origin, mult(-cub->side / 2, cub->dirs[i]));
		sqrs[2 * i + 1]->normale = cub->dirs[i];
		sqrs[2 * i + 1]->right = cub->dirs[(i + 1) % 3];
		sqrs[2 * i + 1]->down = cub->dirs[(i + 2) % 3];
		sqrs[2 * i + 1]->color = cub->sqrs[0]->color;
		sqrs[2 * i + 1]->side = cub->side;
		sqrs[2 * i + 1]->cub = cub;
		i++;
	}
}