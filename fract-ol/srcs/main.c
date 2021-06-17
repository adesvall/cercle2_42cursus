/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:36:21 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 18:40:22 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int	print_examples( void )
{
	printf("Wrong arguments.\n");
	printf("Try for example :\n");
	printf("   ./fractol -mandel\n");
	printf("   ./fractol -julia 0.285 0.013\n");
	return (WRONG_ARGUMENT);
}

void	create_window(t_info *info)
{
	t_data	*data;

	printf("\033[0;32mCreating window...\n\033[0m");
	info->resw = 1280;
	info->resh = 720;
	info->mlx_win = mlx_new_window(info->mlx, info->resw, \
										info->resh, "frat-ol");
	if (!info->mlx_win)
		handle_error("Fail to create Minilibx window", WINDOW_FAIL, info);
	mlx_mouse_hook(info->mlx_win, mouse_press, info);
	mlx_hook(info->mlx_win, ClientMessage, NoEventMask, exit_and_free, info);
	mlx_key_hook(info->mlx_win, get_keypress, info);
	data = info->data;
	data->img = mlx_new_image(info->mlx, info->resw, info->resh);
	if (!data->img)
		handle_error("failed to create img.", IMG_FAIL, info);
	data->addr = mlx_get_data_addr(data->img, \
		&data->bits_per_pixel, &data->line_length, &data->endian);
	create_img(info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, \
						info->data->img, 0, 0);
	mlx_loop(info->mlx);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_data	data;
	t_cplx	julia;

	ft_bzero(&info, sizeof(t_info));
	if (!ft_strcmp(argv[1], "-mandel"))
		printf("Mandelbrot Set\n");
	else if (!ft_strcmp(argv[1], "-julia"))
	{
		if (argc > 3)
			julia = (t_cplx){ft_atod(argv[2]), ft_atod(argv[3])};
		else
			julia = (t_cplx){-1.310, 0};
		info.julia = &julia;
		printf("Julia Set for c = %f + %f i\n", info.julia->re, info.julia->im);
	}
	else
		return (print_examples());
	info.mlx = mlx_init();
	data.img = NULL;
	info.data = &data;
	info.zoom = 300;
	info.color_range = 1;
	create_window(&info);
	return (0);
}
