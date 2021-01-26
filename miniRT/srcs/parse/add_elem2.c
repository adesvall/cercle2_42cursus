/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:10:55 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:15:57 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		add_lum(char **split, t_scn *scn, int dir)
{
	char	**spos;
	char	**srgb;
	t_lum	*lum;

	if (ft_tablen(split) != 4)
		return (WRONG_LINE);
	if (!(lum = malloc(sizeof(t_lum))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->lums), ft_lstnew(lum));
	spos = ft_split(split[1], ",");
	lum->I = ft_atod(split[2]);
	srgb = ft_split(split[3], ",");
	if (ft_tablen(srgb) != 3 || ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	lum->vec = tabto_vect(spos);
	lum->color = tabto_lumrgb(srgb);
	lum->dir = dir;
	ft_abort(spos);
	ft_abort(srgb);
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
	char	**spos;
	char	**srgb;
	t_sph	*sph;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(sph = malloc(sizeof(t_sph))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->sphs), ft_lstnew(sph));
	spos = ft_split(split[1], ",");
	sph->radius = ft_atod(split[2]) / 2;
	srgb = ft_split(split[3], ",");
	if (ft_tablen(spos) != 3 || ft_tablen(srgb) != 3)
	{
		ft_abort(spos);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	sph->center = tabto_vect(spos);
	sph->color = tabto_rgb(srgb);
	ft_abort(spos);
	ft_abort(srgb);
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
	char	**spos;
	char	**sdir;
	char	**srgb;
	t_pln	*pln;

	if (ft_tablen(split) != 4 && ft_tablen(split) != 5)
		return (WRONG_LINE);
	if (!(pln = malloc(sizeof(t_pln))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_lstadd_front(&(scn->plns), ft_lstnew(pln));
	spos = ft_split(split[1], ",");
	sdir = ft_split(split[2], ",");
	srgb = ft_split(split[3], ",");
	if (ft_tablen(srgb) != 3 || ft_tablen(spos) != 3 || ft_tablen(sdir) != 3)
	{
		ft_abort(spos);
		ft_abort(sdir);
		ft_abort(srgb);
		return (WRONG_ARG);
	}
	pln->origin = tabto_vect(spos);
	pln->normale = normalize(tabto_vect(sdir));
	pln->color = tabto_rgb(srgb);
	ft_abort(spos);
	ft_abort(sdir);
	ft_abort(srgb);
	set_pln(pln);
	if (ft_tablen(split) == 5)
		set_pln_disruption(split[4], pln, scn);
	return (0);
}
