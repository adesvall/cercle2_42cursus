/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:37:30 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/27 15:16:05 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			xpm_to_data(t_scn *scn, t_data *tex, char *path)
{
	if (!(tex->img = mlx_xpm_file_to_image(scn->mlx, path,
		&tex->w, &tex->h)))
		return (IMG_FAIL);
	if (!(tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
		&tex->line_length, &tex->endian)))
		return (IMG_FAIL);
	ft_lstadd_front(&scn->texs, ft_lstnew(tex));
	return (0);
}

t_rgb		get_sky_color(t_data sky, double x, double y, t_couple start_img)
{
	int		column;
	int		row;
	int		trgb;
	t_rgb	color;

	column = start_img.w + (int)(sky.h / 3.0 * (1 + x) / 2.0);
	row = start_img.h + (int)(sky.h / 3.0 * (1 + y) / 2.0);
	trgb = *((unsigned int*)(sky.addr + (row * sky.line_length + column
												* (sky.bits_per_pixel / 8))));
	color.b = trgb & 0xFF;
	color.g = (trgb >> 8) & 0xFF;
	color.r = (trgb >> 16) & 0xFF;
	return (color);
}

t_rgb		get_sky_coord(t_scn *scn, t_ray ray)
{
	int		start_img;

	ray.dir = normalize(ray.dir);
	if (fabs(ray.dir.z) >= fabs(ray.dir.y)
			&& fabs(ray.dir.z) >= fabs(ray.dir.x))
	{
		start_img = ray.dir.z >= 0 ? 0 : scn->sky.h * 2 / 3;
		return (get_sky_color(scn->sky, -ray.dir.x / fabs(ray.dir.z),
			-ray.dir.y / ray.dir.z, (t_couple){scn->sky.w / 4, start_img}));
	}
	else if (fabs(ray.dir.x) >= fabs(ray.dir.y)
			&& fabs(ray.dir.x) >= fabs(ray.dir.z))
	{
		start_img = ray.dir.x >= 0 ? 0 : scn->sky.w / 2;
		return (get_sky_color(scn->sky, -ray.dir.y / ray.dir.x,
		-ray.dir.z / fabs(ray.dir.x), (t_couple){start_img, scn->sky.h / 3}));
	}
	else
	{
		start_img = ray.dir.y < 0 ? scn->sky.w / 4 : scn->sky.w * 3 / 4;
		return (get_sky_color(scn->sky, ray.dir.x / ray.dir.y,
		-ray.dir.z / fabs(ray.dir.y), (t_couple){start_img, scn->sky.h / 3}));
	}
}
