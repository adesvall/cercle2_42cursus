/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:02:16 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 14:33:49 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reload_scn(t_scn *scn)
{
	t_cam	*cam;

	clean_scene(scn);
	parse_file(scn);
	scn->actualcam = scn->cams;
	cam = scn->actualcam->content;
	scn->actuallum = scn->lums;
	scn->sl_obj.pos = &cam->origin;
	scn->sl_obj.dir = &cam->dir;
	create_all_img(scn);
	scn->actualcam = scn->cams;
	scn->actuallum = scn->lums;
	printf("The actual Camera is selected.\n");
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
}

void	change_cam(t_scn *scn)
{
	t_cam	*cam;

	if ((scn->actualcam = scn->actualcam->next) == NULL)
		scn->actualcam = scn->cams;
	cam = scn->actualcam->content;
	scn->sl_obj.pos = &cam->origin;
	scn->sl_obj.dir = &cam->dir;
	create_img(cam, scn);
	printf("You selected Camera at (%.0f,%.0f,%.0f) "
			"with direction (%.2f,%.2f,%.2f).\n",
			scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
			scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
}

void	select_lum(t_scn *scn)
{
	t_lum	*lum;

	if ((scn->actuallum = scn->actuallum->next) == NULL)
		scn->actuallum = scn->lums;
	lum = scn->actuallum->content;
	scn->sl_obj.pos = &lum->vec;
	scn->sl_obj.dir = NULL;
	scn->sl_obj.type = NULL;
	printf("You selected Light at (%.0f,%.0f,%.0f).\n",
				scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
}

void	move_vect(int key, t_vect *pos, t_vect *dir)
{
	if (dir && (key == 65361 || key == 65363 || key == 65364 || key == 65362))
		*dir = turn_vect(*dir, M_PI / 12 * ((key == 65361) - (key == 65363)),
								M_PI / 20 * ((key == 65364) - (key == 65362)));
	else
		translate(pos, 5.05 * ((key == 122) - (key == 115)),
						5.05 * ((key == 113) - (key == 100)),
						5.05 * ((key == 120) - (key == 119)));
}

void	move_selection(int key, t_scn *scn)
{
	t_cam	*cam;
	t_cyl	*cyl;

	if (key != 100 && key != 122 && key != 115 && key != 65361 && key != 65363
	&& key != 65364 && key != 65362 && key != 113 && key != 120 && key != 119)
		return ;
	move_vect(key, scn->sl_obj.pos, scn->sl_obj.dir);
	if (!ft_strcmp(scn->sl_obj.type, "Cylinder"))
	{
		cyl = scn->sl_obj.elem;
		if (cyl->dsks[0])
			set_caps(cyl, cyl->dsks[0], cyl->dsks[1]);
	}
	if (!ft_strcmp(scn->sl_obj.type, "Cube"))
		set_faces(scn->sl_obj.elem);
	if (!ft_strcmp(scn->sl_obj.type, "Plane"))
		set_pln(scn->sl_obj.elem);
	if (!ft_strcmp(scn->sl_obj.type, "Square"))
		set_sqr(scn->sl_obj.elem);
	create_img((cam = scn->actualcam->content), scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
}
