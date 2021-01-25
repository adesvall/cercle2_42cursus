/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:27:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 19:45:52 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		*collision_list_elem(t_ray ray, t_list *elem, t_vect *closest,
						int (*collision) (t_ray ray, void *elem, t_vect *coli))
{
	t_vect	col;
	t_vect	best;
	t_cam	*res;
	t_list	*ite;

	res = NULL;
	best = (t_vect){0, 0, 0};
	ite = elem;
	while (ite)
	{
		if (collision(ray, ite->content, &col))
		{
			if (res == NULL ||
				norm(diff(col, ray.origin)) < norm(diff(best, ray.origin)))
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

t_vect		fill_res_sqr(t_rescl *res, t_sqr *sqr, t_ray ray, t_vect col)
{
	res->elem = sqr;
	res->type = (sqr->cub) ? "Cube (Square)" : "Square";
	res->normale = sqr->normale;
	res->color = sqr->color;
	res->pos = &sqr->origin;
	res->dir = &sqr->normale;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

t_rescl		collision_any(t_ray ray, t_scn *scn, t_vect *closest, double dmax)
{
	void	*elem;
	t_rescl	res;
	t_vect	col;
	t_vect	best;

	res.elem = NULL;
	res.normale = (t_vect){-1, 0, 0};
	if ((elem = collision_list_elem(ray, scn->sphs, &col, &collision_sph)) != NULL)
		best = fill_res_sph(&res, elem, ray, col);
	if ((elem = collision_list_elem(ray, scn->plns, &col, &collision_pln)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
		best = fill_res_pln(&res, elem, ray, col);
	if ((elem = collision_list_elem(ray, scn->tris, &col, &collision_tri)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
		best = fill_res_tri(&res, elem, ray, col);
	if ((elem = collision_list_elem(ray, scn->cyls, &col, &collision_cyl)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
		best = fill_res_cyl(&res, elem, ray, col);
	if ((elem = collision_list_elem(ray, scn->dsks, &col, &collision_dsk)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
		best = fill_res_dsk(&res, elem, ray, col);
	if ((elem = collision_list_elem(ray, scn->sqrs, &col, &collision_sqr)) != NULL && (res.elem == NULL || norm(diff(ray.origin, col)) < norm(diff(ray.origin, best))))
		best = fill_res_sqr(&res, elem, ray, col);
	if (res.elem != NULL && dmax != -1 && norm(diff(best, ray.origin)) > dmax)
		res.elem = NULL;
	if (res.elem != NULL && closest)
		*closest = best;
	return (res);
}
