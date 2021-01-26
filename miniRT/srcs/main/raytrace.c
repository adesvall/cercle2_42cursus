/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:22:20 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 16:29:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	filter(t_rgb rgb, char filter)
{
	if (filter == 0)
		return (rgb);
	rgb.r = filter == 'R' ? rgb.r : 0;
	rgb.g = filter == 'G' ? rgb.g : 0;
	rgb.b = filter == 'B' ? rgb.b : 0;
	return (rgb);
}

t_ray	find_ray(t_cam *cam, double i, double j, t_scn *scn)
{
	t_vect	right;
	t_vect	down;

	right = mult(cam->coef_fov * (j - scn->res.W / 2), cam->right);
	down = mult(cam->coef_fov * (i - scn->res.H / 2), cam->down);
	return ((t_ray){cam->origin, normalize(sum(cam->dir, sum(right, down)))});
}

t_rgb	raytrace(t_scn *scn, t_cam *cam, int i, int j)
{
	t_rgb	sumrgb;
	t_ray	ray;
	int		nr;
	int		anti;

	anti = scn->antialiasing + 1;
	sumrgb = (t_rgb){0, 0, 0};
	nr = 0;
	while (nr < anti * anti)
	{
		ray = find_ray(cam, (double)i + (nr / anti - anti / 2) / (double)anti,
						(double)j + (nr % anti - anti / 2) / (double)anti, scn);
		sumrgb = sum_col(sumrgb, get_color(scn, ray, R_DEPTH));
		nr++;
	}
	return (mult_col(1.0 / nr, (t_vect){1, 1, 1}, sumrgb));
}

void	fill_img(t_targs *args)
{
	t_rgb	color;
	int		j;
	int		i;

	i = 0;
	while (i + args->i < args->scn->res.H && i < args->scn->res.H / 4)
	{
		j = 0;
		while (j < args->scn->res.W)
		{
			color = filter(raytrace(args->scn, args->cam, i + args->i, j),
															args->cam->filter);
			my_mlx_pixel_put(&args->cam->data, j, i + args->i,
									create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
}

void	create_img(t_cam *cam, t_scn *scn)
{
	int			nthr;
	pthread_t	t[4];
	t_targs		arg[4];

	set_cam(cam, scn->res.W);
	nthr = 0;
	while (nthr < 4)
	{
		arg[nthr] = (t_targs){nthr * scn->res.H / 4, cam, scn};
		pthread_create(&t[nthr], NULL, (void*)fill_img, &arg[nthr]);
		nthr++;
	}
	nthr = 0;
	while (nthr < 4)
	{
		if (t[nthr])
			pthread_join(t[nthr], NULL);
		nthr++;
	}
}
