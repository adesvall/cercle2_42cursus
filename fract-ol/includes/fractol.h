/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:39:07 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 17:40:28 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define WRONG_ARGUMENT 1
# define IMG_FAIL 2
# define WINDOW_FAIL 3

typedef struct s_cplx
{
	double	re;
	double	im;
}				t_cplx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}				t_data;

typedef struct s_info
{
	void	*mlx;
	int		resw;
	int		resh;
	void	*mlx_win;
	t_data	*data;
	double	zoom;
	t_cplx	offset;
	int		color_range;
	t_cplx	*julia;
}				t_info;

int		ft_strcmp(const char *s1, const char *s2);
double	ft_atod(const char *str);

void	create_img(t_info *info);
double	sqlength(t_cplx z);
t_cplx	add(t_cplx z1, t_cplx z2);
t_cplx	next_iter(t_cplx z, t_cplx c);
int		getcolor(int j, int i, t_info *info);

int		mouse_press(int button, int x, int y, t_info *info);
int		get_keypress(int key, t_info *info);

int		exit_and_free(t_info *info, int code);
int		handle_error(char *msg, int err, t_info *info);

#endif
