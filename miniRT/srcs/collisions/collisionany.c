/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:27:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/22 13:02:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	*collision_list_elem(t_ray ray, t_list *elem, t_vect *closest, int (*collision) (t_ray ray, void *elem, t_vect *coli))
{
	t_vect	col, best;
	t_cam	*res;
	t_list	*ite;
	
	res = NULL;
	best = (t_vect){0, 0, 0};
	ite = elem;
	while(ite)
	{
		if (collision(ray, ite->content, &col))
		{
			if (res == NULL || (norm(diff(col, ray.origin)) < norm(diff(best, ray.origin))))
			{
				best = col;
				res = ite->content;
			}
		}
		ite = ite->next;
	}
	if (res != 0 && closest)
		*closest = best;
	return (res);
}

t_rescl		collision_any(t_ray ray, t_scn *scn, t_vect *closest, double dmax)
{
	void	*elem;
	t_rescl	res;
	t_vect	col;
	t_vect	best;

	res.elem = NULL;
	res.type = 0;
	res.normale = (t_vect){-1, 0, 0};
	if ((elem = collision_list_elem(ray, scn->sphs, &col, &collision_sph)) != NULL)
	{
		best = col;
		res.elem = elem;
		res.type = "Sphere";
		res.normale = normalize(diff(col, ((t_sph*)elem)->center));
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
		res.color = apply_color_disruption(res.normale, elem);
		res.pos = &((t_sph*)elem)->center;
		res.dir = NULL;
	}
	if ((elem = collision_list_elem(ray, scn->plns, &col, &collision_pln)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = "Plane";
		res.normale = ((t_pln*)elem)->normale;
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
		res.normale = apply_normal_disruption(col, elem);
		res.color = apply_texture(col, elem);
		res.pos = &((t_pln*)elem)->origin;
		res.dir = &((t_pln*)elem)->normale;
	}
	if ((elem = collision_list_elem(ray, scn->tris, &col, &collision_tri)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = "Triangle";
		res.normale = normalize(prod_vect(((t_tri*)elem)->p[0], ((t_tri*)elem)->p[1]));
		res.color = ((t_tri*)elem)->color;
		res.pos = &((t_tri*)elem)->origin;
		res.dir = NULL;
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
	}
	if ((elem = collision_list_elem(ray, scn->cyls, &col, &collision_cyl)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = "Cylinder";
		res.normale = normalize(diff(col, sum(((t_cyl*)elem)->origin, mult(dot(((t_cyl*)elem)->dir, diff(col, ((t_cyl*)elem)->origin)), ((t_cyl*)elem)->dir))));
		res.color = ((t_cyl*)elem)->color;
		res.pos = &((t_cyl*)elem)->origin;
		res.dir = &((t_cyl*)elem)->dir;
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
	}
	if ((elem = collision_list_elem(ray, scn->dsks, &col, &collision_dsk)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = "Cylinder (Disk)";
		res.normale = ((t_dsk*)elem)->normale;
		res.color = ((t_dsk*)elem)->color;
		res.pos = &((t_dsk*)elem)->origin;
		res.dir = &((t_dsk*)elem)->normale;
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
	}
	if ((elem = collision_list_elem(ray, scn->sqrs, &col, &collision_sqr)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
	{
		best = col;
		res.elem = elem;
		res.type = (((t_sqr*)elem)->cub) ? "Cube (Square)" : "Square";
		res.normale = ((t_sqr*)elem)->normale;
		res.color = ((t_sqr*)elem)->color;
		res.pos = &((t_sqr*)elem)->origin;
		res.dir = &((t_sqr*)elem)->normale;
		if (dot(res.normale, ray.dir) > 0)
			res.normale = mult(-1, res.normale);
	}
	if (res.elem != NULL && dmax != -1 && norm(diff(best, ray.origin)) > dmax)
	{
		res.elem = NULL;
		res.type = "Nothing";
	}
	if (res.elem != NULL && closest)
		*closest = best;
	return (res);
}
