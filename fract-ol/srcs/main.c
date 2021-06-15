/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:36:21 by user42            #+#    #+#             */
/*   Updated: 2021/06/15 17:49:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int		exit_and_free(t_info *info, int code)
{
	if (info->mlx_win)
	{
		mlx_clear_window(info->mlx, info->mlx_win);
		mlx_destroy_window(info->mlx, info->mlx_win);
	}
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	free(info->julia);
	exit(code);
	return (0);
}

int     handle_error(char *msg, int err, t_info *info)
{
    printf("Error %d: %s\n", err, msg);
    return (exit_and_free(info, err));
}

void	create_window(t_info *info)
{
	int	size_w;
	int	size_h;
    t_data *data;

	printf("\033[0;32mCreating window...\n\033[0m");
	mlx_get_screen_size(info->mlx, &size_w, &size_h);
    info->resw = size_w;
    info->resh = size_h;
	if (!(info->mlx_win = mlx_new_window(info->mlx,
										info->resw, info->resh, "frat-ol")))
		handle_error("Fail to create Minilibx window", WINDOW_FAIL, info);
	mlx_mouse_hook(info->mlx_win, mouse_press, info);
	mlx_hook(info->mlx_win, ClientMessage, NoEventMask, exit_and_free, info);
	// mlx_key_hook(info->mlx_win, get_keypress, info);
	
    data = info->data;
    if (!(data->img = mlx_new_image(info->mlx, info->resw, info->resh)))
		handle_error("failed to create img.", IMG_FAIL, info);
    data->addr = mlx_get_data_addr(data->img,
		&data->bits_per_pixel, &data->line_length, &data->endian);
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win,
						info->data->img, 0, 0);
	mlx_loop(info->mlx);
}

int main(int argc, char **argv)
{
    t_info info;
    t_data  data;

	if (!ft_strcmp(argv[1], "-mandel") && argc == 2)
	{
		info.julia = NULL;
		printf("Mandelbrot Set\n");
	}
	else if (!ft_strcmp(argv[1], "-julia") && argc == 4)
	{
		info.julia = malloc(sizeof(t_cplx));
		info.julia->re = ft_atod(argv[2]);
		info.julia->im = ft_atod(argv[3]);
		printf("Julia's Set for c = %f + %f i\n", info.julia->re, info.julia->im);
	}
	else
	{
		printf("Wrong arguments.\n");
		printf("Try for example :\n");
		printf("   ./fract-ol -mandel\n");
		printf("   ./fract-ol -julia 0.285 0.013\n");
		return (1);
	}
	
	info.mlx = mlx_init();
    info.data = &data;

	info.zoom = 500;
	info.offset = (t_cplx){0, 0};

    create_window(&info);
    return (0);
}