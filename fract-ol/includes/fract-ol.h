/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:39:07 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 15:41:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>


# define IMG_FAIL 2
# define WINDOW_FAIL 3

typedef struct	s_cplx
{
	double	re;
	double	im;
}				t_cplx;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}				t_data;

typedef struct  s_info
{
    void    *mlx;
    void    *mlx_win;
	t_data	*data;
	int		resw;
	int		resh;
	double	zoom;
	t_cplx	offset;
}               t_info;

void    create_img(t_info *info);
double  sqlength(t_cplx z);
t_cplx	add(t_cplx z1, t_cplx z2);
t_cplx	next_iter(t_cplx z, t_cplx c);
int		getcolor(int j, int i, t_info *info);

int		mouse_press(int button, int x, int y, t_info *info);


#endif