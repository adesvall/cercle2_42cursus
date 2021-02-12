/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:10:55 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/27 15:02:37 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		add_lum(char **split, t_scn *scn, int dir)
{
	t_lum	*lum;

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(lum = malloc(sizeof(t_lum))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->lums), ft_lstnew(lum));
	ft_bzero(lum, sizeof(t_lum));
	lum->i = ft_atod(split[2]);
	if (strto_vect(&lum->vec, split[1], 0) ||
					strto_vect(&lum->color, split[3], 1))
		return (WRONG_ARG);
	if (dir && norm(lum->vec) < EPSILON)
		return (WRONG_ARG);
	else if (dir)
		lum->vec = normalize(lum->vec);
	lum->dir = dir;
	return (0);
}

int		set_sph_disruption(char *c, t_sph *sph, t_scn *scn)
{
	if (!ft_strcmp(c, "color-disr"))
	{
		sph->disruption = 'c';
		return (0);
	}
	else
	{
		sph->disruption = 't';
		return (xpm_to_data(scn, &sph->texture, c));
	}
	return (WRONG_ARG);
}

int		add_sph(char **split, t_scn *scn)
{
	t_sph	*sph;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(sph = malloc(sizeof(t_sph))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->sphs), ft_lstnew(sph));
	ft_bzero(sph, sizeof(t_sph));
	sph->radius = ft_atod(split[2]) / 2;
	if (strto_vect(&sph->center, split[1], 0) ||
				strto_rgb(&sph->color, split[3]))
		return (WRONG_ARG);
	if (ft_tablen(split) == 5)
		return (set_sph_disruption(split[4], sph, scn));
	return (0);
}

int		set_pln_disruption(char *c, t_pln *pln, t_scn *scn)
{
	if (!ft_strcmp(c, "checkered"))
	{
		pln->disruption = 'c';
		return (0);
	}
	else if (!ft_strcmp(c, "normal-disr"))
	{
		pln->disruption = 'n';
		return (0);
	}
	else
	{
		pln->disruption = 't';
		return (xpm_to_data(scn, &pln->texture, c));
	}
	return (WRONG_ARG);
}

int		add_pln(char **split, t_scn *scn)
{
	t_pln	*pln;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(pln = malloc(sizeof(t_pln))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->plns), ft_lstnew(pln));
	ft_bzero(pln, sizeof(t_pln));
	if (strto_vect(&pln->origin, split[1], 0) ||
			strto_vect(&pln->normale, split[2], 0) ||
			strto_rgb(&pln->color, split[3]))
		return (WRONG_ARG);
	if (norm(pln->normale) < EPSILON)
		return (WRONG_ARG);
	else
		pln->normale = normalize(pln->normale);
	set_pln(pln);
	if (ft_tablen(split) == 5)
		set_pln_disruption(split[4], pln, scn);
	return (0);
}
