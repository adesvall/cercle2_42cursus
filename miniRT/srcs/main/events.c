/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 11:29:17 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 14:41:04 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	free_texs_img(t_list *texs, void *mlx)
{
	void	*ptr;

	while (texs)
	{
		ptr = ((t_data*)texs->content)->img;
		if (ptr)
			mlx_destroy_image(mlx, ptr);
		texs = texs->next;
	}
}

void	clean_scene(t_scn *scn)
{
	free_cams_img(scn->cams, scn->mlx);
	free_texs_img(scn->texs, scn->mlx);
	ft_lstclear(&scn->cams, free);
	ft_lstclear(&scn->texs, NULL);
	ft_lstclear(&scn->sphs, free);
	ft_lstclear(&scn->lums, free);
	ft_lstclear(&scn->plns, free);
	ft_lstclear(&scn->tris, free);
	ft_lstclear(&scn->cyls, free);
	ft_lstclear(&scn->dsks, free);
	ft_lstclear(&scn->sqrs, free);
	ft_lstclear(&scn->cubs, free);

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
	mlx_destroy_display(scn->mlx);
	free(scn->mlx);
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
	mlx_destroy_display(scn->mlx);
	free(scn->mlx);
	exit(0);
	return (0);
}
