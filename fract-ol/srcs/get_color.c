/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:20:48 by user42            #+#    #+#             */
/*   Updated: 2021/06/15 17:46:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

#define MAX_ITER 50

int  iter(t_cplx z, t_cplx c, int niter)
{
    int i;

    i = 0;
    while (sqlength(z) < 4 && i < niter)
    {
        z = next_iter(z, c);
        i++;
    }
    return (i);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		getcolor(int j, int i, t_info *info)
{
    t_cplx	c;
	int		steps;

    c = info->offset;
    c.re += j / info->zoom;
    c.im += -i / info->zoom;
    if (info->julia)
	    steps = iter(c, *info->julia, MAX_ITER);
    else
        steps = iter((t_cplx){0, 0}, c, MAX_ITER);
    if (steps < MAX_ITER)
        return (create_trgb(0, (steps * 3) % 256, (steps * 1) % 256, (steps * 10) % 256));
    return (create_trgb(0, 0, 0, 0));
}
