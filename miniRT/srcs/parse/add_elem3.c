/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:13:10 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/27 15:39:39 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		add_cam(char **split, t_scn *scn)
{
	t_cam	*cam;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(cam = malloc(sizeof(t_cam))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cams), ft_lstnew(cam));
	ft_bzero(cam, sizeof(t_cam));
	cam->fov = ft_atod(split[3]);
	if (strto_vect(&cam->origin, split[1], 0) ||
			strto_vect(&cam->dir, split[2], 0))
		return (WRONG_ARG);
	if (norm(cam->dir) < EPSILON)
		return (WRONG_ARG);
	cam->dir = normalize(cam->dir);
	if (cam->fov < EPSILON || cam->fov >= 180 - EPSILON)
		return (WRONG_ARG);
	if (ft_tablen(split) == 5)
		return (set_filter(split[4][0], cam));
	return (0);
}

int		add_sqr(char **split, t_scn *scn)
{
	t_sqr	*sqr;

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(sqr = malloc(sizeof(t_sqr))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->sqrs), ft_lstnew(sqr));
	ft_bzero(sqr, sizeof(t_sqr));
	sqr->side = ft_atod(split[3]);
	if (strto_vect(&sqr->origin, split[1], 0) ||
			strto_vect(&sqr->normale, split[2], 0) ||
			strto_rgb(&sqr->color, split[4]))
		return (WRONG_ARG);
	if (norm(sqr->normale) < EPSILON)
		return (WRONG_ARG);
	sqr->normale = normalize(sqr->normale);
	set_sqr(sqr);
	return (0);
}

int		add_cub(char **split, t_scn *scn)
{
	t_cub	*cub;
	int		i;

	if (!(cub = malloc(sizeof(t_cub))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cubs), ft_lstnew(cub));
	ft_bzero(cub, sizeof(t_cub));
	i = 0;
	while (i < 6)
	{
		if (!(cub->sqrs[i] = malloc(sizeof(t_sqr))))
			handle_error("Malloc failed", MALLOC_FAIL, scn);
		ft_lstadd_front(&(scn->sqrs), ft_lstnew(cub->sqrs[i]));
		ft_bzero(cub->sqrs[i++], sizeof(t_sqr));
	}
	cub->side = ft_atod(split[3]);
	if (strto_vect(&cub->origin, split[1], 0) ||
			strto_vect(&cub->dirs[0], split[2], 0) ||
			strto_rgb(&cub->sqrs[0]->color, split[4]))
		return (WRONG_ARG);
	if (norm(cub->dirs[0]) < EPSILON)
		return (WRONG_ARG);
	cub->dirs[0] = normalize(cub->dirs[0]);
	set_faces(cub);
	return (0);
}
