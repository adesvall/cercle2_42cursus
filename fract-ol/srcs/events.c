/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:16:52 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 15:49:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int		mouse_press(int button, int x, int y, t_info *info)
{
	printf("---click !---\n%d\n[%d, %d]\n", button, x, y);
	if (button == 4)// zooom
	{
		info->zoom *= 2;
		info->offset = add(info->offset, (t_cplx){(x - info->resw / 2) / info->zoom , (info->resh / 2 - y) / info->zoom });
	}
	else if (button == 5)// dezoom
	{
		info->zoom /= 1.1;
/*		j - info->resw / 2, i - info->resh / 2

    c = info->offset;
    c.re += j / info->zoom;
    c.im += -i / info->zoom;*/
	}
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->data->img, 0, 0);
	return (0);
}
