/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:17:24 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 14:51:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    create_img(t_info *info)
{
    t_data *data;
    int     i, j;
    int     color;

    data = info->data;
    i = 0;
    while (i < info->resh)
    {
        j=0;
        while (j < info->resw)
        {
            color = getcolor(j - info->resw / 2, i - info->resh / 2, info);
            my_mlx_pixel_put(data, j, i, color);
            j++;
        }
        i++;
    }
}