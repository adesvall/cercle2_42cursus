/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:08:07 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 17:40:04 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** ESC  65307
** L	108
** C	99
** R	114
*/

int		get_keypress(int key, t_scn *scn)
{
	if (key == 65307)
		exit_and_free(scn);
	else if (key == 108)
		select_lum(scn);
	else if (key == 99)
		change_cam(scn);
	else if (key == 114)
		reload_scn(scn);
	else
		move_selection(key, scn);
	return (1);
}

void	select_obj(t_scn *scn, t_rescl res)
{
	t_dsk	*dsk;
	t_sqr	*sqr;

	scn->sl_obj.type = res.type;
	scn->sl_obj.elem = res.elem;
	scn->sl_obj.pos = res.pos;
	scn->sl_obj.dir = res.dir;
	if (!ft_strcmp(scn->sl_obj.type, "Cylinder (Disk)"))
	{
		dsk = scn->sl_obj.elem;
		scn->sl_obj.type = "Cylinder";
		scn->sl_obj.elem = dsk->cyl;
	}
	if (!ft_strcmp(scn->sl_obj.type, "Cube (Square)"))
	{
		sqr = scn->sl_obj.elem;
		scn->sl_obj.type = "Cube";
		scn->sl_obj.elem = sqr->cub;
	}
}

int		mouse_press(int button, int x, int y, t_scn *scn)
{
	t_rescl	res;

	if (button == Button1 && (res = collision_any(find_ray(
		scn->actualcam->content, y, x, scn), scn, NULL, -1)).elem != NULL)
	{
		select_obj(scn, res);
		if (res.dir)
			printf("You selected %s at (%.0f,%.0f,%.0f) "
					"with direction (%.2f,%.2f,%.2f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
					scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
		else
			printf("You selected %s at (%.0f,%.0f,%.0f).\n", res.type,
					scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z);
		return (1);
	}
	scn->sl_obj.pos = &((t_cam*)scn->actualcam->content)->origin;
	scn->sl_obj.dir = &((t_cam*)scn->actualcam->content)->dir;
	scn->sl_obj.type = NULL;
	printf("You selected the actual Camera at (%.0f,%.0f,%.0f) "
			"with direction (%.2f,%.2f,%.2f).\n",
				scn->sl_obj.pos->x, scn->sl_obj.pos->y, scn->sl_obj.pos->z,
				scn->sl_obj.dir->x, scn->sl_obj.dir->y, scn->sl_obj.dir->z);
	return (1);
}
