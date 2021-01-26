/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionany.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:27:39 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 17:19:30 by adesvall         ###   ########.fr       */
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

t_vect		fill_res_sqr(t_rescl *res, t_ray ray, t_vect col)
{
	t_sqr	*sqr;

	sqr = res->elem;
	res->type = (sqr->cub) ? "Cube (Square)" : "Square";
	res->dist = norm(diff(ray.origin, col));
	res->normale = sqr->normale;
	res->color = sqr->color;
	res->pos = (sqr->cub) ? &sqr->cub->origin : &sqr->origin;
	res->dir = (sqr->cub) ? &sqr->cub->dirs[0] : &sqr->normale;
	if (dot(res->normale, ray.dir) > 0)
		res->normale = mult(-1, res->normale);
	return (col);
}

int			check_is_closer(t_rescl *res, t_list *list, t_ray ray,
						int (*collision) (t_ray ray, void *elem, t_vect *coli))
{
	void	*elem;
	t_vect	col;

	elem = collision_list_elem(ray, list, &col, collision);
	if (elem != NULL && (res->elem == NULL
					|| norm(diff(ray.origin, col)) < res->dist))
	{
		res->elem = elem;
		res->col = col;
		return (1);
	}
	return (0);
}

t_rescl		collision_any(t_ray ray, t_scn *scn, t_vect *closest, double dmax)
{
	t_rescl	res;
	t_vect	best;

	res.elem = NULL;
	if (check_is_closer(&res, scn->sphs, ray, &collision_sph))
		best = fill_res_sph(&res, ray, res.col);
	if (check_is_closer(&res, scn->plns, ray, &collision_pln))
		best = fill_res_pln(&res, ray, res.col);
	if (check_is_closer(&res, scn->tris, ray, &collision_tri))
		best = fill_res_tri(&res, ray, res.col);
	if (check_is_closer(&res, scn->cyls, ray, &collision_cyl))
		best = fill_res_cyl(&res, ray, res.col);
	if (check_is_closer(&res, scn->dsks, ray, &collision_dsk))
		best = fill_res_dsk(&res, ray, res.col);
	if (check_is_closer(&res, scn->sqrs, ray, &collision_sqr))
		best = fill_res_sqr(&res, ray, res.col);
	if (res.elem != NULL && dmax != -1 && norm(diff(best, ray.origin)) > dmax)
		res.elem = NULL;
	if (res.elem != NULL && closest)
		*closest = best;
	return (res);
}
