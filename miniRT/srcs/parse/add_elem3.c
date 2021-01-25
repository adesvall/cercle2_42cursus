/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:13:10 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 18:13:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		add_cam(char **split, t_scn *scn)
{
	char	**spos;
	char 	**sdir;
	t_cam	*cam;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(cam = malloc(sizeof(t_cam))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cams), ft_lstnew(cam));
	spos = ft_split(split[1], ",");
	sdir = ft_split(split[2], ",");
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3)
	{
		ft_abort(spos);
		ft_abort(sdir);
		return (WRONG_ARG);
	}
	cam->origin = tabto_vect(spos);
	cam->dir = tabto_vect(sdir);
	ft_abort(spos);
	ft_abort(sdir);
	cam->fov = ft_atod(split[3]);
	if (norm(cam->dir) < EPSILON || cam->fov < EPSILON || cam->fov >= 180 - EPSILON)
		return (WRONG_ARG);
	if (ft_tablen(split) == 5)
		return (set_filter(split[4][0], cam));
	return (0);
}

int 	add_sqr(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_sqr	*sqr;

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(sqr = malloc(sizeof(t_sqr))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->sqrs), ft_lstnew(sqr));
	spos = ft_split(split[1], ",");
	sdir = ft_split(split[2], ",");
	sqr->side = ft_atod(split[3]);
	srgb = ft_split(split[4], ",");
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3 || ft_tablen(srgb) != 3 || sqr->side < EPSILON)
	{
		ft_abort(spos);
		ft_abort(sdir);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	sqr->origin = tabto_vect(spos);
	sqr->normale = normalize(tabto_vect(sdir));
	sqr->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_abort(sdir);
	ft_abort(spos);
	set_sqr(sqr);
	return (0);
}

int		add_cub(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_cub	*cub;
	int		i;
	
	if (!(cub = malloc(sizeof(t_cub))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cubs), ft_lstnew(cub));
	i = 0;
	while (i < 6)
	{
		if (!(cub->sqrs[i] = malloc(sizeof(t_sqr))))
			handle_error("Malloc failed", MALLOC_FAIL, scn);
		ft_lstadd_front(&(scn->sqrs), ft_lstnew(cub->sqrs[i]));
		i++;
	}
	spos = ft_split(split[1], ",");
	sdir = ft_split(split[2], ",");
	cub->side = ft_atod(split[3]);
	srgb = ft_split(split[4], ",");
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3
				|| ft_tablen(srgb) != 3 || cub->side < EPSILON)
	{
		ft_abort(spos);
		ft_abort(sdir);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	cub->origin = tabto_vect(spos);
	cub->dirs[0] = tabto_vect(sdir);
	cub->sqrs[0]->color = tabto_rgb(srgb);
	ft_abort(srgb);
	ft_abort(sdir);
	ft_abort(spos);
	if (norm(cub->dirs[0]) < EPSILON)
		return (WRONG_ARG);
	cub->dirs[0] = normalize(cub->dirs[0]);
	set_faces(cub);
	return (0);
}
