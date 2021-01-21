/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/20 19:57:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_rgb	filter(t_rgb rgb, char filter)
{
	if (filter == 0)
		return (rgb);
	rgb.r = filter == 'R' ? rgb.r : 0;
	rgb.g = filter == 'G' ? rgb.g : 0;
	rgb.b = filter == 'B' ? rgb.b : 0;
	return (rgb);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_rgb	get_color(t_scn *scn, t_ray ray, int rfi)
{
	t_vect	coli;
	t_rgb	color;
	t_vect	coef;
	double	c;
	t_rescl	res;
	t_list	*ite;
	t_lum	*lum;

	t_vect	lumdir;
	double	dmax;
	double	coefdist;

	res = collision_any(ray, scn, &coli, -1);
	if (res.elem == NULL)
		return (scn->sky.img ? get_sky_coord(scn, ray) : (t_rgb){0, 0, 0});
	color = res.color;
	coef = mult(scn->ambI/255, scn->ambCol);
	ite = scn->lums;
	while (ite)
	{
		lum = (t_lum*)ite->content;
		lumdir = lum->dir ? mult(-1, lum->vec) : normalize(diff(lum->vec, coli));
		dmax = lum->dir ? -1 : norm(diff(lum->vec, coli));
		coefdist = (dmax == -1) ? 1 : 1000 / pow(dmax, 2);
		if (collision_any((t_ray){coli, lumdir}, scn, 0, dmax).elem == NULL)
		{
			c = lum->I/255 * dot(res.normale, lumdir) * coefdist;
			c = (c > 0) ? c : 0;
			coef = sum(coef, mult(c, lum->color));
		}
		ite = ite->next;
	}
	color = mult_col(5, coef, color);
	if (REFLECT > EPSILON && rfi > 0)
	{
		ray = (t_ray){coli, normalize(sum(ray.dir, mult(-2 * dot(ray.dir, res.normale), res.normale)))};
		color = add_reflect(REFLECT, color, get_color(scn, ray, rfi - 1));
	}
	return (color);
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
		ray = find_ray(cam, (double)i + (nr / anti - anti/2) / (double)anti,
							(double)j + (nr % anti - anti/2) / (double)anti, scn);
		sumrgb = sum_col(sumrgb, get_color(scn, ray, R_DEPTH));
		nr++;
	}
	return (mult_col(1.0 / nr, (t_vect){1, 1, 1}, sumrgb));
}

void		fill_img(t_targs *args)
{
	t_rgb	color;
	int j;
	int i;

	i=0;
	while (i + args->i < args->scn->res.H && i < args->scn->res.H/4)
	{
		j=0;
		while (j < args->scn->res.W)
		{
			color = filter(raytrace(args->scn, args->cam, i + args->i, j), args->cam->filter);
			my_mlx_pixel_put(&args->cam->data, j, i + args->i , create_trgb(0, color.r, color.g, color.b));
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
}

void	create_img(t_cam *cam, t_scn *scn)
{
	int	nthr;
	pthread_t	t[4];
	t_targs		arg[4];
	
	set_cam(cam, scn->res.W);
	//fill_img(&(t_targs){0, cam, scn});
	nthr = 0;
	while (nthr < 4)
	{
		arg[nthr] = (t_targs){nthr * scn->res.H/4, cam, scn};
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
