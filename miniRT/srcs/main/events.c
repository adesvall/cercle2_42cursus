/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 17:09:28 by adesvall         ###   ########.fr       */
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
