/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:40:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/27 15:41:37 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libftutils.h"
# include "elems.h"
# include "../srcs/get_next_line/get_next_line.h"
# include "parse.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# ifndef M_PI
#  define M_PI 3.1415926535897932384626
# endif
# define EPSILON 0.00001

# define OPEN_FAIL 1
# define IMG_FAIL 2
# define WINDOW_FAIL 3
# define NO_RES 4
# define NO_CAMERA 5
# define WRONG_LINE 6
# define WRONG_ARG 7
# define MALLOC_FAIL 100

# define REFLECT 0
# define R_DEPTH 0

void		parse_file(t_scn *scn);
int			strto_vect(t_vect *dst, char *str, int isrgb);
int			strto_rgb(t_rgb *dst, char *str);
t_vect		tabto_vect(char **s);
t_vect		tabto_lumrgb(char **s);
t_rgb		tabto_rgb(char **s);
int			create_trgb(int t, int r, int g, int b);

int			exit_and_free(t_scn *scn);
int			handle_error(char *msg, int err, t_scn *scn);
int			get_keypress(int key, t_scn *scn);
int			mouse_press(int button, int x, int y, t_scn *scn);
void		select_lum(t_scn *scn);
void		change_cam(t_scn *scn);
void		clean_scene(t_scn *scn);
void		reload_scn(t_scn *scn);
void		move_selection(int key, t_scn *scn);

int			xpm_to_data(t_scn *scn, t_data *tex, char *path);
t_rgb		get_xpm_color(t_data xpm, double x, double y);
t_rgb		get_sky_color(t_data sky, double x, double y, t_couple start_img);
t_rgb		get_sky_coord(t_scn *scn, t_ray ray);

void		create_all_img(t_scn *scn);
void		create_img(t_cam *cam, t_scn *scn);
void		set_cam(t_cam *cam, int resw);
void		set_r_and_d(t_vect dir, t_vect *right, t_vect *down);
void		set_pln(t_pln *pln);
void		set_sqr(t_sqr *sqr);
t_ray		find_ray(t_cam *cam, double i, double j, t_scn *scn);
t_rgb		get_color(t_scn *scn, t_ray ray, int rfi);

void		fill_img(t_targs *args);
t_rescl		collision_any(t_ray ray, t_scn *scn, t_vect *closest, double max);
t_vect		fill_res_sph(t_rescl *res, t_ray ray, t_vect col);
t_vect		fill_res_pln(t_rescl *res, t_ray ray, t_vect col);
t_vect		fill_res_tri(t_rescl *res, t_ray ray, t_vect col);
t_vect		fill_res_cyl(t_rescl *res, t_ray ray, t_vect col);
t_vect		fill_res_dsk(t_rescl *res, t_ray ray, t_vect col);
t_vect		fill_res_sqr(t_rescl *res, t_ray ray, t_vect col);
int			collision_sph(t_ray ray, void *elem, t_vect *coli);
int			collision_pln(t_ray ray, void *elem, t_vect *coli);
int			collision_tri(t_ray ray, void *elem, t_vect *coli);
int			collision_cyl(t_ray ray, void *elem, t_vect *coli);
int			collision_dsk(t_ray ray, void *elem, t_vect *coli);
int			collision_sqr(t_ray ray, void *elem, t_vect *coli);
int			in_square(t_vect coli, t_sqr car);
t_abc		abc_solve(double a, double b, double c);

t_rgb		apply_color_disruption(t_vect normale, t_sph *sph);
t_vect		apply_normal_disruption(t_vect coli, t_pln *pln);
t_rgb		apply_texture(t_vect coli, t_pln *pln);

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		save_bmp(const char *filename, unsigned char *data, t_scn *scn);

double		limit_color(double n);
t_rgb		sum_col(t_rgb c1, t_rgb c2);
t_rgb		mult_col(double n, t_vect coef, t_rgb color);
t_rgb		add_reflect(double reflect, t_rgb color, t_rgb reflectcol);
t_vect		sum(t_vect v1, t_vect v2);
void		translate(t_vect *v, double x, double y, double z);
t_vect		diff(t_vect v1, t_vect v2);
t_vect		mult(double n, t_vect v);
double		dot(t_vect v1, t_vect v2);
double		norm(t_vect v);
t_vect		prod_vect(t_vect v1, t_vect v2);
t_vect		normalize(t_vect v);
t_vect		turn_vect(t_vect dir0, double angw, double angh);

#endif
