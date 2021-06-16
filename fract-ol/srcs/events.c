/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:16:52 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 18:18:57 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int		exit_and_free(t_info *info, int code)
{
	mlx_destroy_image(info->mlx, info->data->img);
	if (info->mlx_win)
	{
		mlx_clear_window(info->mlx, info->mlx_win);
		mlx_destroy_window(info->mlx, info->mlx_win);
	}
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	//free(info->julia);
	exit(code);
	return (0);
}

int     handle_error(char *msg, int err, t_info *info)
{
    printf("Error %d: %s\n", err, msg);
    return (exit_and_free(info, err));
}

int		mouse_press(int button, int x, int y, t_info *info)
{
	// printf("---click !---\n%d : [%d, %d]\n", button, x, y);
	if (button == 4)
	{
		info->zoom *= 1.5;
		info->offset = add(info->offset, (t_cplx){(x - info->resw / 2) / info->zoom * 0.5, (info->resh / 2 - y) / info->zoom * 0.5});
	}
	else if (button == 5)
	{
		info->offset = add(info->offset, (t_cplx){(info->resw / 2 - x) / info->zoom , (y - info->resh / 2) / info->zoom });
		info->zoom /= 2;
	}
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->data->img, 0, 0);
	return (0);
}

#define ESC 65307
#define LEFT 65361
#define RIGHT 65363
#define DOWN 65364
#define UP 65362

int		get_keypress(int key, t_info *info)
{
	if (key == ESC)
		exit_and_free(info, 0);
	else if (key == LEFT)
		info->offset.re -= info->resh * 0.1 / info->zoom;
	else if (key == RIGHT)
		info->offset.re += info->resh * 0.1 / info->zoom;
	else if (key == UP)
		info->offset.im += info->resh * 0.1 / info->zoom;
	else if (key == DOWN)
		info->offset.im -= info->resh * 0.1 / info->zoom;
	else if (key == 99)
		info->color_range = (info->color_range + 1) % 9;
	// printf("---Appuyation !---\n%d\n", key);
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->data->img, 0, 0);
	return (0);
}