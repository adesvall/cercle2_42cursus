/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:14:09 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/25 18:14:57 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void 	add_caps(t_cyl *cyl, t_scn *scn, int caps)
{
	t_dsk	*dsk1;
	t_dsk	*dsk2;
	
	if (!caps)
	{
		cyl->dsks[0] = NULL;
		return ;
	}
	if (!(dsk1 = malloc(sizeof(t_dsk))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	if (!(dsk2 = malloc(sizeof(t_dsk))))
	{
		free(dsk1);
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	}
	dsk1->color = cyl->color;
	dsk1->radius = cyl->radius;
	dsk2->color = cyl->color;
	dsk2->radius = cyl->radius;
	set_caps(cyl, dsk1, dsk2);
	dsk1->cyl = cyl;
	dsk2->cyl = cyl;
	cyl->dsks[0] = dsk1;
	cyl->dsks[1] = dsk2;
	ft_lstadd_front(&(scn->dsks), ft_lstnew(dsk1));
	ft_lstadd_front(&(scn->dsks), ft_lstnew(dsk2));
}

int 	add_cyl(char **split, t_scn *scn, int caps)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
	t_cyl	*cyl;

	if (ft_tablen(split) != 6)
		return (WRONG_LINE);
	if (!(cyl = malloc(sizeof(t_cyl))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cyls), ft_lstnew(cyl));
	spos = ft_split(split[1], ",");
	sdir = ft_split(split[2], ",");
	srgb = ft_split(split[5], ",");
	cyl->radius = ft_atod(split[3]) / 2;
	cyl->length = ft_atod(split[4]);
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3 || ft_tablen(srgb) != 3)
	{
		ft_abort(spos);
		ft_abort(sdir);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	cyl->origin = tabto_vect(spos);
	cyl->dir = tabto_vect(sdir);
	cyl->color = tabto_rgb(srgb);
	ft_abort(spos);
	ft_abort(sdir);
	ft_abort(srgb);
	if (norm(cyl->dir) < EPSILON || cyl->radius < EPSILON || cyl->length < EPSILON)
		return (WRONG_ARG);
	cyl->dir = normalize(cyl->dir);
	add_caps(cyl, scn, caps);
	return (0);
}

int 	add_tri(char **split, t_scn *scn)
{
	int		i;
	char	**spos;
	char 	**srgb;
	t_tri	*tri;

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(tri = malloc(sizeof(t_tri))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->tris), ft_lstnew(tri));
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		return (WRONG_ARG);
	}
	tri->origin = tabto_vect(spos);
	ft_abort(spos);
	i = 0;
	while (i < 2)
	{
		spos = ft_split(split[2 + i], ",");
		if (ft_tablen(spos) != 3)
		{
			ft_abort(spos);
			return (WRONG_ARG);
		}
		tri->p[i] = diff(tabto_vect(spos), tri->origin);
		ft_abort(spos);
		i++;
	}
	srgb = ft_split(split[4], ",");
	if (ft_tablen(srgb) != 3)
	{
		ft_abort(srgb);
		free(tri);
		return (WRONG_ARG);
	}
	tri->color = tabto_rgb(srgb);
	ft_abort(srgb);
	return (0);
}
