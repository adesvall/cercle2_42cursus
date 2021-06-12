/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:16:52 by user42            #+#    #+#             */
/*   Updated: 2021/06/12 20:04:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int		mouse_press(int button, int x, int y, t_info *info)
{
	printf("---click !---\n%d\n[%d, %d]\n", button, x, y);
	if (button == 1)// zooom
	{
		info->zoom *= 2;
		info->offset = add(info->offset, (t_cplx){(x - info->resw / 2) / info->zoom , (info->resh / 2 - y) / info->zoom });
	}
	else if (button == 3)// dezoom
	{
		info->zoom /= 2;
		info->offset = add(info->offset, (t_cplx){(info->resw / 2 - x) / info->zoom , (y - info->resh / 2) / info->zoom });
	}
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->data->img, 0, 0);
	return (0);
}
