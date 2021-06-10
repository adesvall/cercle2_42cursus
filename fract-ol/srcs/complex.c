/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:54:23 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 14:54:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

double  sqlength(t_cplx z)
{
	return (z.re * z.re + z.im * z.im);
}

t_cplx	add(t_cplx z1, t_cplx z2)
{
	return ((t_cplx){z1.re + z2.re, z1.im + z2.im});
}

t_cplx  square(t_cplx z)
{
	t_cplx  res;

	res.re = z.re * z.re - z.im * z.im;
	res.im = 2 * z.re * z.im;
	return (res);
}

t_cplx	next_iter(t_cplx z, t_cplx c)
{
	return (add(square(z), c));
}
