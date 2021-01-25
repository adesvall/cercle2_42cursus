/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:00:18 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 19:50:53 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
