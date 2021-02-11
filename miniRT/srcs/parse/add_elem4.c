/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:14:09 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 14:01:07 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		set_reflect(char **split, t_scn *scn)
{
	if (ft_tablen(split) != 3)
		return (WRONG_LINE);
	if ((scn->reflect = ft_atod(split[1])) > 1 || scn->reflect < 0)
		return (WRONG_ARG);
	if ((scn->rdepth = ft_atoi(split[2])) > 10 || scn->rdepth < 0)
		return (WRONG_ARG);
	return (0);
}

void	add_caps(t_cyl *cyl, t_scn *scn)
{
	t_dsk	*dsk1;
	t_dsk	*dsk2;

	if (!(dsk1 = malloc(sizeof(t_dsk))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->dsks), ft_lstnew(dsk1));
	ft_bzero(dsk1, sizeof(t_dsk));
	if (!(dsk2 = malloc(sizeof(t_dsk))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->dsks), ft_lstnew(dsk2));
	ft_bzero(dsk2, sizeof(t_dsk));
	dsk1->color = cyl->color;
	dsk1->radius = cyl->radius;
	dsk2->color = cyl->color;
	dsk2->radius = cyl->radius;
	set_caps(cyl, dsk1, dsk2);
	dsk1->cyl = cyl;
	dsk2->cyl = cyl;
	cyl->dsks[0] = dsk1;
	cyl->dsks[1] = dsk2;
}

int		add_cyl(char **split, t_scn *scn, int caps)
{
	t_cyl	*cyl;

	if (ft_tablen(split) != 6)
		return (WRONG_LINE);
	if (!(cyl = malloc(sizeof(t_cyl))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->cyls), ft_lstnew(cyl));
	ft_bzero(cyl, sizeof(t_cyl));
	cyl->radius = ft_atod(split[3]) / 2;
	cyl->length = ft_atod(split[4]);
	if (strto_vect(&cyl->origin, split[1], 0) ||
			strto_vect(&cyl->dir, split[2], 0) ||
			strto_rgb(&cyl->color, split[5]))
		return (WRONG_ARG);
	if (norm(cyl->dir) < EPSILON || cyl->radius < EPSILON ||
								cyl->length < EPSILON)
		return (WRONG_ARG);
	cyl->dir = normalize(cyl->dir);
	if (caps)
		add_caps(cyl, scn);
	return (0);
}

int		add_tri(char **split, t_scn *scn)
{
	t_tri	*tri;

	if (ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(tri = malloc(sizeof(t_tri))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->tris), ft_lstnew(tri));
	ft_bzero(tri, sizeof(t_tri));
	if (strto_vect(&tri->origin, split[1], 0) ||
			strto_vect(&tri->p[0], split[2], 0) ||
			strto_vect(&tri->p[1], split[3], 0) ||
			strto_rgb(&tri->color, split[4]))
		return (WRONG_ARG);
	tri->p[0] = diff(tri->p[0], tri->origin);
	tri->p[1] = diff(tri->p[1], tri->origin);
	return (0);
}
