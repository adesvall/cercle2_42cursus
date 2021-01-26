/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:11:53 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 18:52:32 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_r_and_d(t_vect dir, t_vect *right, t_vect *down)
{
	if (fabs(dir.x) < EPSILON && fabs(dir.y) < EPSILON)
		*right = (t_vect){1, 0, 0};
	else
		*right = normalize((t_vect){10 * dir.y, -10 * dir.x, 0});
	*down = normalize(prod_vect(dir, *right));
}

void	set_pln(t_pln *pln)
{
	if (fabs(pln->normale.x) < EPSILON && fabs(pln->normale.y) < EPSILON)
		pln->right = (t_vect){1, 0, 0};
	else
		pln->right = normalize((t_vect){10 * pln->normale.y,
													-10 * pln->normale.x, 0});
	pln->down = normalize(prod_vect(pln->normale, pln->right));
}

void	set_sqr(t_sqr *sqr)
{
	if (fabs(sqr->normale.x) < EPSILON && fabs(sqr->normale.y) < EPSILON)
		sqr->right = (t_vect){1, 0, 0};
	else
		sqr->right = normalize((t_vect){10 * sqr->normale.y,
													-10 * sqr->normale.x, 0});
	sqr->down = normalize(prod_vect(sqr->normale, sqr->right));
}

void	set_cam(t_cam *cam, int res_w)
{
	cam->coef_fov = tan(cam->fov * M_PI / 360) / res_w;
	if (fabs(cam->dir.x) < EPSILON && fabs(cam->dir.y) < EPSILON)
		cam->right = normalize((t_vect){0, -1, 0});
	else
		cam->right = normalize((t_vect){10 * cam->dir.y, -10 * cam->dir.x, 0});
	cam->down = normalize(prod_vect(cam->dir, cam->right));
}
