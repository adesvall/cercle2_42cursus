/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:15:50 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/19 23:20:46 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "elems.h"

void 	add_caps(t_cyl *cyl, t_scn *scn, int caps);
void	set_caps(t_cyl *cyl, t_dsk *dsk1, t_dsk *dsk2);
int		set_res(char **split, t_scn *scn);
int		set_amblum(char **split, t_scn *scn);
int		set_sky(char **split, t_scn *scn);
int 	add_cam(char **split, t_scn *scn);
int 	add_lum(char **split, t_scn *scn);
int 	add_sph(char **split, t_scn *scn);
int 	add_pln(char **split, t_scn *scn);
int 	add_sqr(char **split, t_scn *scn);
int 	add_cyl(char **split, t_scn *scn , int caps);
int 	add_tri(char **split, t_scn *scn);
int		add_cub(char **split, t_scn *scn);
void	set_faces(t_cub *cub, t_sqr *sqrs[6]);

#endif