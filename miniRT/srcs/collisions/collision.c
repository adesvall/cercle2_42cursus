/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:31:37 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	collision_pln(t_ray ray, void *elem, t_vect *coli)
{
	double	a;
	double	dt;
	t_pln	*pln;

	pln = (t_pln *)elem;
	a = dot(ray.dir, pln->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = -dot(diff(ray.origin, pln->origin), pln->normale) / a;
	if (dt > EPSILON)
	{
		if (coli)
			*coli = sum(ray.origin, mult(dt, ray.dir));
		return (1);
	}
	return (0);
}

int	collision_sph(t_ray ray, void *elem, t_vect *coli)
{
	t_abc	res;
	t_sph	*sph;

	sph = (t_sph *)elem;
	res = abc_solve(dot(ray.dir, ray.dir),
					2 * dot(ray.dir, diff(ray.origin, sph->center)),
					pow(ray.origin.x - sph->center.x, 2) +
					pow(ray.origin.y - sph->center.y, 2) +
					pow(ray.origin.z - sph->center.z, 2) - pow(sph->radius, 2));
	if (res.delta > EPSILON)
	{
		if (res.x1 <= EPSILON)
			res.x1 += res.x2_x1;
		if (res.x1 > EPSILON)
		{
			if (coli)
				*coli = sum(ray.origin, mult(res.x1, ray.dir));
			return (1);
		}
	}
	return (0);
}

int	collision_tri(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	h;
	t_vect	q;
	double	a;
	double	u;
	t_tri	*tri;

	tri = (t_tri *)elem;
	h = prod_vect(ray.dir, tri->p[1]);
	a = dot(tri->p[0], h);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	u = 1.0 / a * dot(diff(ray.origin, tri->origin), h);
	if (u < 0.0 || u > 1.0)
		return (0);
	q = prod_vect(diff(ray.origin, tri->origin), tri->p[0]);
	if (1.0 / a * dot(ray.dir, q) < 0 || u + 1.0 / a * dot(ray.dir, q) > 1.0)
		return (0);
	if (1.0 / a * dot(tri->p[1], q) > EPSILON)
	{
		if (coli)
			*coli = sum(ray.origin, mult(1.0 / a * dot(tri->p[1], q), ray.dir));
		return (1);
	}
	return (0);
}

int	collision_cyl(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	u;
	t_vect	v;
	t_vect	col;
	t_abc	res;
	t_cyl	*cyl;

	cyl = (t_cyl *)elem;
	u = diff(ray.dir, mult(dot(cyl->dir, ray.dir), cyl->dir));
	v = diff(diff(ray.origin, cyl->origin),
			mult(dot(cyl->dir, diff(ray.origin, cyl->origin)), cyl->dir));
	if ((res = abc_solve(dot(u, u), 2 * dot(u, v),
						dot(v, v) - pow(cyl->radius, 2))).delta > EPSILON)
	{
		if (res.x1 <= EPSILON || fabs(dot(cyl->dir, diff(sum(ray.origin,
					mult(res.x1, ray.dir)), cyl->origin))) > cyl->length / 2)
			res.x1 += res.x2_x1;
		if (res.x1 > EPSILON && fabs(dot(cyl->dir, diff(col = sum(ray.origin,
					mult(res.x1, ray.dir)), cyl->origin))) < cyl->length / 2)
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}

int	collision_dsk(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	col;
	double	a;
	double	dt;
	t_dsk	*dsk;

	dsk = (t_dsk *)elem;
	a = dot(ray.dir, dsk->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = -dot(diff(ray.origin, dsk->origin), dsk->normale) / a;
	if (dt > EPSILON)
	{
		col = sum(ray.origin, mult(dt, ray.dir));
		if (norm(diff(col, dsk->origin)) < dsk->radius)
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}
