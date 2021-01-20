/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:37:30 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/19 23:31:19 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			create_sky(t_scn *scn, char *sky_path)
{
	t_data tex;

	if (!(tex.img = mlx_xpm_file_to_image(scn->mlx, sky_path,
		&tex.W, &tex.H)))
		return (IMG_FAIL);
	if (!(tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel,
		&tex.line_length, &tex.endian)))
		return (IMG_FAIL);
	scn->sky = tex;
	return (0);
}

t_rgb		get_sky_color(t_data sky, double x, double y, t_couple start_img)
{
	int		column;
	int		row;
	int		trgb;
	t_rgb	color;

	column = start_img.W + (int)(sky.H/3.0 * (1 + x) / 2.0);
	row = start_img.H + (int)(sky.H/3.0 * (1 + y) / 2.0);
	trgb = *((unsigned int*)(sky.addr + (row * sky.line_length + column * (sky.bits_per_pixel / 8))));
	color.b = trgb & 0xFF;
	color.g = (trgb >> 8) & 0xFF;
	color.r = (trgb >> 16) & 0xFF;
	return (color);
}

t_rgb		get_sky_coord(t_scn *scn, t_ray ray)
{
	t_rgb	color;
	int		start_img;

	ft_bzero(&color, sizeof(t_rgb));
	ray.dir = normalize(ray.dir);
	if (fabs(ray.dir.z) >= fabs(ray.dir.y) && fabs(ray.dir.z) >= fabs(ray.dir.x))
	{
		start_img = ray.dir.z >= 0 ? 0 : scn->sky.H * 2 / 3;
		color = get_sky_color(scn->sky, -ray.dir.x / fabs(ray.dir.z),
					-ray.dir.y / ray.dir.z, (t_couple){scn->sky.W / 4, start_img});
	}
	else if (fabs(ray.dir.x) >= fabs(ray.dir.y) && fabs(ray.dir.x) >= fabs(ray.dir.z))
	{
		start_img = ray.dir.x >= 0 ? 0 : scn->sky.W / 2;
		color = get_sky_color(scn->sky, -ray.dir.y / ray.dir.x,
					-ray.dir.z / fabs(ray.dir.x), (t_couple){start_img, scn->sky.H / 3});
	}
	else if (fabs(ray.dir.y) >= fabs(ray.dir.z) && fabs(ray.dir.y) >= fabs(ray.dir.x))
	{
		start_img = ray.dir.y < 0 ? scn->sky.W / 4 : scn->sky.W * 3 / 4;
		color = get_sky_color(scn->sky, ray.dir.x / ray.dir.y,
					-ray.dir.z / fabs(ray.dir.y), (t_couple){start_img, scn->sky.H / 3});
	}
	return (color);
}
