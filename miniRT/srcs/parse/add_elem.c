/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:36:56 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 14:00:46 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		set_res(char **split, t_scn *scn)
{
	int	new_w;
	int	new_h;

	if (ft_tablen(split) != 3)
		return (WRONG_LINE);
	new_w = ft_atoi(split[1]);
	new_h = ft_atoi(split[2]);
	if (scn->res.h != 0 && (new_w != scn->res.w || new_h != scn->res.h))
		return (WRONG_LINE);
	scn->res.w = new_w;
	scn->res.h = new_h;
	if (scn->res.w < 1 || scn->res.h < 1)
		return (WRONG_LINE);
	return (0);
}

int		set_amblum(char **split, t_scn *scn)
{
	char **splitcol;

	if (ft_tablen(split) != 3 || scn->amb_i != 0)
		return (WRONG_LINE);
	scn->amb_i = ft_atod(split[1]);
	if (scn->amb_i < 0 || scn->amb_i > 1)
		return (WRONG_ARG);
	splitcol = ft_split(split[2], ",");
	if (ft_tablen(splitcol) != 3)
	{
		ft_abort(splitcol);
		return (WRONG_ARG);
	}
	scn->amb_rgb = tabto_lumrgb(splitcol);
	ft_abort(splitcol);
	return (0);
}

int		set_sky(char **split, t_scn *scn)
{
	if (scn->sky.img)
		return (WRONG_LINE);
	if (ft_tablen(split) != 2)
		return (WRONG_LINE);
	return (xpm_to_data(scn, &scn->sky, split[1]));
}

int		set_filter(char c, t_cam *cam)
{
	if (c != 'R' && c != 'G' && c != 'B' && c != 'S')
		return (WRONG_ARG);
	cam->filter = c;
	return (0);
}

int		set_anti(char **split, t_scn *scn)
{
	if (scn->sky.img)
		return (WRONG_LINE);
	if (ft_tablen(split) != 2)
		return (WRONG_LINE);
	if ((scn->antialiasing = ft_atoi(split[1])) >= 10 || scn->antialiasing < 0)
		return (WRONG_ARG);
	return (0);
}
