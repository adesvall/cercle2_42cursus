/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:37:30 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/17 13:58:00 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_data	create_sky(t_scn *scn, char *sky_path)
{
	t_data tex;

	if (!(tex.img = mlx_xpm_file_to_image(scn->mlx, sky_path,
		&tex.W, &tex.H)))
		handle_error("fail creating skybox", IMG_FAIL, scn);
	if (!(tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel,
		&tex.line_length, &tex.endian)))
		handle_error("fail creating skybox", IMG_FAIL, scn);
	return (tex);
}

t_rgb		get_sky_color(t_data sky, float x, float y, float max)
{
	//int		i;
	int		column;
	int		row;
	int		trgb;
	t_rgb	color;

	max = fabs(max);
	column = (int)(sky.H * (0.5 * (x / max + 1)));
	row = (int)(sky.H * (0.5 * (y / max + 1)));
	//i = row * sky.line_length + sky.bits_per_pixel / 8 * column;
	trgb = *(unsigned int*)(sky.addr + (row * sky.line_length + column * (sky.bits_per_pixel / 8)));
	color.b = trgb & 0xFF;
	color.g = trgb >> 8 & 0xFF;
	color.r = trgb >> 16 & 0xFF;
	return (color);
}

t_rgb		get_sky_coord(t_scn *scn, t_ray ray)
{
	t_rgb	color;
	float	m;

	ft_bzero(&color, sizeof(t_rgb));
	ray.dir = normalize(ray.dir);
	if (fabs(ray.dir.z) >= fabs(ray.dir.y) && fabs(ray.dir.z)
	>= fabs(ray.dir.x) && ray.dir.z < 0 && (m = ray.dir.z) > -10)
		color = get_sky_color(scn->sky, -ray.dir.x, -ray.dir.y, m);
	else if (fabs(ray.dir.z) >= fabs(ray.dir.y) && fabs(ray.dir.z)
	>= fabs(ray.dir.x) && ray.dir.z > 0 && (m = ray.dir.z) > -10)
		color = get_sky_color(scn->sky, ray.dir.x, -ray.dir.y, m);
	else if (fabs(ray.dir.x) > fabs(ray.dir.z) && fabs(ray.dir.x)
	> fabs(ray.dir.y) && ray.dir.x < 0 && (m = ray.dir.x) > -10)
		color = get_sky_color(scn->sky, ray.dir.z, -ray.dir.y, m);
	else if (fabs(ray.dir.x) > fabs(ray.dir.z) && fabs(ray.dir.x)
	> fabs(ray.dir.y) && ray.dir.x > 0 && (m = ray.dir.x) > -10)
		color = get_sky_color(scn->sky, -ray.dir.z, -ray.dir.y, m);
	else if (fabs(ray.dir.y) >= fabs(ray.dir.z) && fabs(ray.dir.y)
	>= fabs(ray.dir.x) && ray.dir.y < 0 && (m = ray.dir.y) > -10)
		color = get_sky_color(scn->sky, -ray.dir.x, ray.dir.z, m);
	else if (fabs(ray.dir.y) >= fabs(ray.dir.z) && fabs(ray.dir.y)
	>= fabs(ray.dir.x) && ray.dir.y > 0 && (m = ray.dir.y) > -10)
		color = get_sky_color(scn->sky, ray.dir.x, ray.dir.z, m);
	return (color);
}
