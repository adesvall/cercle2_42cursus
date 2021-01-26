/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectop2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:32:13 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	norm(t_vect v)
{
	return (sqrt(dot(v, v)));
}

t_vect	normalize(t_vect v)
{
	double	n;

	n = norm(v);
	if (n < EPSILON)
		return (v);
	v.x /= n;
	v.y /= n;
	v.z /= n;
	return (v);
}

t_vect	prod_vect(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vect	turn_vect(t_vect dir0, double angw, double angh)
{
	t_vect	tmp;
	t_vect	res;
	t_vect	axe;

	tmp = (t_vect){cos(angw) * dir0.x - sin(angw) * dir0.y,
					sin(angw) * dir0.x + cos(angw) * dir0.y, dir0.z};
	if (angh == 0)
		return (tmp);
	res = mult(cos(angh), tmp);
	axe = (t_vect){-tmp.y, tmp.x, 0};
	if (norm(axe) < EPSILON)
		axe = (t_vect){1, 0, 0};
	return (normalize(sum(res, mult(sin(angh),
					prod_vect(normalize(axe), tmp)))));
}
