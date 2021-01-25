/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rescl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:03:48 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 19:25:22 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vect		fill_res_sph(t_rescl *res, t_sph *sph, t_ray ray, t_vect col)
{
	res->elem = sph;
	res->type = "Sphere";
	res->normale = normalize(diff(col, sph->center));
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	res->color = apply_color_disruption(res->normale, sph);
	res->pos = &sph->center;
	res->dir = NULL;
	return (col);
}

t_vect		fill_res_pln(t_rescl *res, t_pln *pln, t_ray ray, t_vect col)
{
	res->elem = pln;
	res->type = "Plane";
	res->normale = pln->normale;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	res->normale = apply_normal_disruption(col, pln);
	res->color = apply_texture(col, pln);
	res->pos = &pln->origin;
	res->dir = &pln->normale;
	return (col);
}

t_vect		fill_res_tri(t_rescl *res, t_tri *tri, t_ray ray, t_vect col)
{
	res->elem = tri;
	res->type = "Triangle";
	res->normale = normalize(prod_vect(tri->p[0], tri->p[1]));
	res->color = tri->color;
	res->pos = &tri->origin;
	res->dir = NULL;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

t_vect		fill_res_cyl(t_rescl *res, t_cyl *cyl, t_ray ray, t_vect col)
{
	res->elem = cyl;
	res->type = "Cylinder";
	res->normale = normalize(diff(col, sum(cyl->origin, mult(dot(cyl->dir,
									diff(col, cyl->origin)), cyl->dir))));
	res->color = cyl->color;
	res->pos = &cyl->origin;
	res->dir = &cyl->dir;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

t_vect		fill_res_dsk(t_rescl *res, t_dsk *dsk, t_ray ray, t_vect col)
{
	res->elem = dsk;
	res->type = "Cylinder (Disk)";
	res->normale = dsk->normale;
	res->color = dsk->color;
	res->pos = &dsk->origin;
	res->dir = &dsk->normale;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}
