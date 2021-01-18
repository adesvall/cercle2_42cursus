/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:35 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/17 13:54:33 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ray	find_ray(t_cam *cam, int i, int j, t_scn *scn)
{
	t_vect	right;
	t_vect	down;

	right = mult(tan(cam->fov * M_PI / 360) * (j - scn->res.W / 2)/scn->res.W, cam->right);
	down = mult(tan(cam->fov * M_PI / 360) * (i - scn->res.H / 2)/scn->res.W, cam->down);
	return ((t_ray){cam->origin, normalize(sum(cam->dir, sum(right, down)))});
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

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

	res = collision_any(ray, scn, &coli, -1);
	if (res.elem == NULL)
		return (get_sky_coord(scn, ray));//();(t_rgb){0, 0, 0}
	color = res.color;
	coef = mult(scn->ambI/255, scn->ambCol);
	ite = scn->lums;
	while (ite)
	{
		lum = (t_lum*)ite->content;
		if (collision_any((t_ray){coli, normalize(diff(lum->pos, coli))}, scn, 0, norm(diff(lum->pos, coli))).elem == NULL)
		{
			c = lum->I/255 * normed_dot(res.normale, diff(lum->pos, coli)) * 1000 / pow(norm(diff(lum->pos, coli)), 2);
			c = (c > 0) ? c : 0;
			coef = sum(coef, mult(c, lum->color));
		}
		ite = ite->next;
	}
	color = mult_col(5, coef, color);
	if (REFLECT > EPSILON && rfi > 0)
	{
		ray = (t_ray){coli, normalize(sum(ray.dir, mult(-2 * dot(ray.dir, res.normale), res.normale)))};
		color = mixcolor(REFLECT, color, get_color(scn, ray, rfi - 1));
	}
	return (color);
}

void		fill_img(t_targs *args)
{
	t_rgb	color;
	t_ray	ray;
	int j;
	int i;

	i=0;
	while (i + args->i < args->scn->res.H && i < args->scn->res.H/4)
	{
		j=0;
		while (j < args->scn->res.W)
		{
			ray = find_ray(args->cam, i + args->i, j, args->scn);
			color = get_color(args->scn, ray, R_DEPTH);
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
	
	set_cam(cam);
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
