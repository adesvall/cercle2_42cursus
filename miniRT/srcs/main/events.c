/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/17 09:43:15 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_cams_img(t_list *cams, void *mlx)
{
	void	*ptr;

	while (cams)
	{
		ptr = ((t_cam*)cams->content)->data.img;
		if (ptr)
			mlx_destroy_image(mlx, ptr);
		cams = cams->next;
	}
}

void	clean_scene(t_scn *scn)
{
	free_cams_img(scn->cams, scn->mlx);
	if (scn->sky.img)
			mlx_destroy_image(scn->mlx, scn->sky.img);
	ft_lstclear(&scn->cams, free);
	ft_lstclear(&scn->sphs, free);
	ft_lstclear(&scn->lums, free);
	ft_lstclear(&scn->plns, free);
	ft_lstclear(&scn->tris, free);
	ft_lstclear(&scn->cyls, free);
	ft_lstclear(&scn->dsks, free);
	ft_lstclear(&scn->sqrs, free);
}

int		handle_error(char *msg, int err, t_scn *scn)
{
	printf("Error %d: %s\n", err, msg);
	clean_scene(scn);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(err);
	return (err);
}

int		exit_and_free(t_scn *scn)
{
	clean_scene(scn);
	if (scn->mlx_win)
	{
		mlx_clear_window(scn->mlx, scn->mlx_win);
		mlx_destroy_window(scn->mlx, scn->mlx_win);
	}
	exit(0);
	return (0);
}

void	reload_scn(t_scn *scn)
{
	t_cam	*cam;
	
	clean_scene(scn);
	scn->ambI = 0;
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
	printf("The actual Camera is selected.\n");
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
}

void	select_lum(t_scn *scn)
{
	t_lum	*lum;

	if ((scn->actuallum = scn->actuallum->next) == NULL)
		scn->actuallum = scn->lums;
	lum = scn->actuallum->content;
	scn->sl_obj.pos = &lum->pos;
	scn->sl_obj.dir = NULL;
	scn->sl_obj.type = NULL;
	printf("You selected Light at (%.0f,%.0f,%.0f).\n",
				scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
}

void	move_vect(int key, t_vect *pos, t_vect *dir)
{
	if (dir && (key == 65361 || key == 65363 || key == 65364 || key == 65362))
		*dir = turn_vect(*dir, M_PI/12 * ((key == 65361) - (key == 65363)),
								M_PI/20 * ((key == 65364) - (key == 65362)));
	else
		translate(pos, 5 * ((key == 122) - (key == 115)),
						5 * ((key == 113) - (key == 100)),
						5 * ((key == 120) - (key == 119)));
}

void	move_selection(int key, t_scn *scn)
{
	t_cam	*cam;
	t_cub	*cub;
	t_cyl	*cyl;
	
	if (key != 100 && key != 122 && key != 115 && key != 65361 && key != 65363
		&& key != 65364 && key != 65362 && key != 113 && key != 120 && key != 119) //zqsdwx<>^v
		return ;
	move_vect(key, scn->sl_obj.pos, scn->sl_obj.dir);
	if (!ft_strcmp(scn->sl_obj.type, "Cylinder"))
	{	
		cyl = scn->sl_obj.elem;
		if (cyl->dsks[0])
			set_caps(cyl, cyl->dsks[0], cyl->dsks[1]);
	}
	if (!ft_strcmp(scn->sl_obj.type, "Cube"))
	{	
		cub = scn->sl_obj.elem;
		set_faces(cub, cub->sqrs);
	}
	create_img((cam = scn->actualcam->content), scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win, cam->data.img, 0, 0);
}

int		get_keypress(int key, t_scn *scn)
{
	//printf("%d\n", key);
	if (key == 65307) //ESC
		exit_and_free(scn);
	else if (key == 108) //L
		select_lum(scn);
	else if (key == 99) //C
		change_cam(scn);
	else if (key == 114) //R
		reload_scn(scn);
	else
		move_selection(key, scn);	
	return (1);
}

int		mouse_press(int button, int x, int y, t_scn *scn)
{
	t_rescl	res;
	t_cam 	*cam;
	t_dsk	*dsk;
	t_sqr	*sqr;
	
	cam = scn->actualcam->content;
	if (button == Button1 && (res = collision_any(find_ray(cam, y, x, scn), scn, NULL, -1)).elem != NULL)
	{
		scn->sl_obj.type = res.type;
		scn->sl_obj.elem = res.elem;
		scn->sl_obj.pos = res.pos;
		scn->sl_obj.dir = res.dir;
		if (!ft_strcmp(scn->sl_obj.type, "Cylinder (Disk)"))
		{
			dsk = scn->sl_obj.elem;
			scn->sl_obj.pos = &dsk->cyl->origin;
			scn->sl_obj.dir = &dsk->cyl->dir;
			scn->sl_obj.type = "Cylinder";
			scn->sl_obj.elem = dsk->cyl;
		}
		if (!ft_strcmp(scn->sl_obj.type, "Cube (Square)"))
		{
			sqr = scn->sl_obj.elem;
			scn->sl_obj.pos = &sqr->cub->origin;
			scn->sl_obj.dir = &sqr->cub->dirs[0];
			scn->sl_obj.type = "Cube";
			scn->sl_obj.elem = sqr->cub;
		}
		if (res.dir)
			printf("You selected %s at (%.0f,%.0f,%.0f) with direction (%.2f,%.2f,%.2f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
					scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
		else
			printf("You selected %s at (%.0f,%.0f,%.0f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
	}
	else
	{
		scn->sl_obj.pos = &cam->origin;
		scn->sl_obj.dir = &cam->dir;
		scn->sl_obj.type = NULL;
		printf("You selected the actual Camera at (%.0f,%.0f,%.0f) with direction (%.2f,%.2f,%.2f).\n",
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
					scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
	}
	return (1);
}