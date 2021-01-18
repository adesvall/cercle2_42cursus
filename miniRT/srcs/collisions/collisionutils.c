/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisionutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:00:18 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/15 18:57:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int		in_square(t_vect col, t_sqr sqr)
{
	double X, Y;
	t_vect v;

	v = diff(col, sqr.origin);
	X = dot(v, sqr.right);
	Y = dot(v, sqr.down);
	return (fabs(X) <= sqr.side / 2 && fabs(Y) <= sqr.side / 2);
}

t_abc	abc_solve(double a, double b, double c)
{
	t_abc	res;

	res.delta = pow(b, 2) - 4 * a * c;
	if (res.delta > EPSILON)
	{
		res.x2_x1 = sqrt(res.delta) / a;;
		res.x1 = -b / (2 * a) - res.x2_x1 / 2;
	}
	return (res);
}