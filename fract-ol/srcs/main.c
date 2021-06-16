/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:36:21 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 18:15:15 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	print_examples()
{
	printf("Wrong arguments.\n");
	printf("Try for example :\n");
	printf("   ./fract-ol -mandel\n");
	printf("   ./fract-ol -julia 0.285 0.013\n");
	return (WRONG_ARGUMENT);
}

void	create_window(t_info *info)
{
	int	size_w;
	int	size_h;
	t_data *data;

	printf("\033[0;32mCreating window...\n\033[0m");
	mlx_get_screen_size(info->mlx, &size_w, &size_h);
	info->resw = 1280;//size_w;
	info->resh = 720;//size_h;
	if (!(info->mlx_win = mlx_new_window(info->mlx,
										info->resw, info->resh, "frat-ol")))
		handle_error("Fail to create Minilibx window", WINDOW_FAIL, info);
	mlx_mouse_hook(info->mlx_win, mouse_press, info);
	mlx_hook(info->mlx_win, ClientMessage, NoEventMask, exit_and_free, info);
	mlx_key_hook(info->mlx_win, get_keypress, info);
	
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
	t_info	info;
	t_data  data;
	t_cplx	julia;

	if (!ft_strcmp(argv[1], "-mandel"))
	{
		info.julia = NULL;
		printf("Mandelbrot Set\n");
	}
	else if (!ft_strcmp(argv[1], "-julia"))
	{
		if (argc > 3)
			julia = (t_cplx){ft_atod(argv[2]), ft_atod(argv[3])};
		else
			julia = (t_cplx){-1.310, 0};
		info.julia	= &julia;
		printf("Julia Set for c = %f + %f i\n", info.julia->re, info.julia->im);
	}
	else
		return (print_examples());
	info.mlx = mlx_init();
	info.data = &data;
	info.zoom = 300;
	info.offset = (t_cplx){0, 0};
	info.color_range = 0;
	create_window(&info);
	return (0);
}