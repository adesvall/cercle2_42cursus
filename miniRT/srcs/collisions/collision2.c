/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:00:18 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		collision_sqr(t_ray ray, void *elem, t_vect *coli)
{
	t_vect	col;
	double	a;
	double	dt;
	t_sqr	*sqr;

	sqr = (t_sqr *)elem;
	a = dot(ray.dir, sqr->normale);
	if (a > -EPSILON && a < EPSILON)
		return (0);
	dt = -dot(diff(ray.origin, sqr->origin), sqr->normale) / a;
	if (dt > EPSILON)
	{
		col = sum(ray.origin, mult(dt, ray.dir));
		if (in_square(col, *sqr))
		{
			if (coli)
				*coli = col;
			return (1);
		}
	}
	return (0);
}

int		in_square(t_vect col, t_sqr sqr)
{
	double	x;
	double	y;
	t_vect	v;

	v = diff(col, sqr.origin);
	x = dot(v, sqr.right);
	y = dot(v, sqr.down);
	return (fabs(x) <= sqr.side / 2 && fabs(y) <= sqr.side / 2);
}

t_abc	abc_solve(double a, double b, double c)
{
	t_abc	res;

	res.delta = pow(b, 2) - 4 * a * c;
	if (res.delta > EPSILON)
	{
		res.x2_x1 = sqrt(res.delta) / a;
		res.x1 = -b / (2 * a) - res.x2_x1 / 2;
	}
	return (res);
}
