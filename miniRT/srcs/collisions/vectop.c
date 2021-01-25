/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:51:54 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 19:33:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vect	sum(t_vect v1, t_vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

void	translate(t_vect *v, double x, double y, double z)
{
	v->x += x;
	v->y += y;
	v->z += z;
}

t_vect	diff(t_vect v1, t_vect v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vect	mult(double n, t_vect v)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

double	dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
