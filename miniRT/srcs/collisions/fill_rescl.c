/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rescl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:03:48 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect		fill_res_sph(t_rescl *res, t_ray ray, t_vect col)
{
	t_sph	*sph;

	sph = res->elem;
	res->type = "Sphere";
	res->dist = norm(diff(ray.origin, col));
	res->normale = normalize(diff(col, sph->center));
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	res->color = apply_color_disruption(res->normale, sph);
	res->pos = &sph->center;
	res->dir = NULL;
	return (col);
}

t_vect		fill_res_pln(t_rescl *res, t_ray ray, t_vect col)
{
	t_pln	*pln;

	pln = res->elem;
	res->type = "Plane";
	res->dist = norm(diff(ray.origin, col));
	res->normale = pln->normale;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	res->normale = apply_normal_disruption(col, pln);
	res->color = apply_texture(col, pln);
	res->pos = &pln->origin;
	res->dir = &pln->normale;
	return (col);
}

t_vect		fill_res_tri(t_rescl *res, t_ray ray, t_vect col)
{
	t_tri	*tri;

	tri = res->elem;
	res->type = "Triangle";
	res->dist = norm(diff(ray.origin, col));
	res->normale = normalize(prod_vect(tri->p[0], tri->p[1]));
	res->color = tri->color;
	res->pos = &tri->origin;
	res->dir = NULL;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

t_vect		fill_res_cyl(t_rescl *res, t_ray ray, t_vect col)
{
	t_cyl	*cyl;

	cyl = res->elem;
	res->type = "Cylinder";
	res->dist = norm(diff(ray.origin, col));
	res->normale = normalize(diff(col, sum(cyl->origin, mult(dot(cyl->dir,
									diff(col, cyl->origin)), cyl->dir))));
	res->color = cyl->color;
	res->pos = &cyl->origin;
	res->dir = &cyl->dir;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

t_vect		fill_res_dsk(t_rescl *res, t_ray ray, t_vect col)
{
	t_dsk	*dsk;

	dsk = res->elem;
	res->type = "Cylinder (Disk)";
	res->dist = norm(diff(ray.origin, col));
	res->normale = dsk->normale;
	res->color = dsk->color;
	res->pos = &dsk->cyl->origin;
	res->dir = &dsk->cyl->dir;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}
