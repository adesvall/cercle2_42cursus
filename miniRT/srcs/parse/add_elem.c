/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:36:56 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/20 18:17:54 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		set_res(char **split, t_scn *scn)
{
	int	newW;
	int	newH;
	
	if (ft_tablen(split) != 3)
		return (WRONG_LINE);
	newW = ft_atoi(split[1]);
	newH = ft_atoi(split[2]);
	if (scn->res.H != 0 && (newW != scn->res.W || newH != scn->res.H))
		return (WRONG_LINE);
	scn->res.W = newW;
	scn->res.H = newH;
	if (scn->res.W < 1 || scn->res.H < 1)
		return (WRONG_LINE);
	return (0);
}

int		set_amblum(char **split, t_scn *scn)
{
	char **splitcol;

	if (ft_tablen(split) != 3 || scn->ambI != 0)
		return (WRONG_LINE);
	scn->ambI = ft_atod(split[1]);
	if (scn->ambI < 0 || scn->ambI > 1)
		return (WRONG_ARG);
	splitcol = ft_split(split[2], ",");
	if (ft_tablen(splitcol) != 3)
	{
		ft_abort(splitcol);
		return (WRONG_ARG);
	}
	scn->ambCol = tabto_lumrgb(splitcol);
	ft_abort(splitcol);
	return (0);
}

int		set_sky(char **split, t_scn *scn)
{
	if (scn->sky.img)
		return (WRONG_LINE);
	if (ft_tablen(split) != 2)
		return (WRONG_LINE);
	return (create_sky(scn, split[1]));
}

int		set_filter(char c, t_cam *cam)
{
	if (c != 'R' && c != 'G' && c != 'B')
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
	if ((scn->antialiasing = atoi(split[1])) >= 10 || scn->antialiasing < 0)
		return (WRONG_ARG);
	return (0);
}

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

int 	add_lum(char **split, t_scn *scn, int dir)
{
	char	**spos;
	char 	**srgb;
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

int 	add_sph(char **split, t_scn *scn)
{
	char	**spos;
	char 	**srgb;
	t_sph	*sph;

	if (ft_tablen(split) != 4)
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
	return (0);
}

int		set_disruption(char *c, t_pln *pln)
{
	if (ft_strcmp(c, "checkered"))
	{
		pln->disruption = "check";
		return (0);
	}
	if (ft_strcmp(c, "normal-disruption"))
	{
		pln->disruption = "normal";
		return (0);
	}
	if (ft_strcmp(c, ""))
	{
		//creqtetexture
		pln->disruption = "texture";
		return (WRONG_ARG);
	}
	return (WRONG_ARG);
}

int 	add_pln(char **split, t_scn *scn)
{
	char	**spos;
	char	**sdir;
	char 	**srgb;
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
	if (ft_tablen(split) == 5)
		set_disruption(split[4], pln);
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
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3 || ft_tablen(srgb) != 3 || cub->side < EPSILON)
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
	set_faces(cub, cub->sqrs);
	return (0);
}

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
	if (ft_tablen(spos) != 3 || ft_tablen(sdir) != 3 || ft_tablen(srgb) != 3
							|| cyl->radius < EPSILON || cyl->length < EPSILON)
	{
		ft_abort(spos);
		ft_abort(sdir);
		ft_abort(srgb);
		free(cyl);
		return (WRONG_ARG);
	}
	cyl->origin = tabto_vect(spos);
	cyl->dir = tabto_vect(sdir);
	cyl->color = tabto_rgb(srgb);
	ft_abort(spos);
	ft_abort(sdir);
	ft_abort(srgb);
	if (norm(cyl->dir) < EPSILON)
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
	spos = ft_split(split[1], ",");
	if (ft_tablen(spos) != 3)
	{
		ft_abort(spos);
		free(tri);
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
			free(tri);
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
	ft_lstadd_front(&(scn->tris), ft_lstnew(tri));
	return (0);
}
