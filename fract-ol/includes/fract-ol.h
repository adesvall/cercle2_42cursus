/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:39:07 by user42            #+#    #+#             */
/*   Updated: 2021/06/10 12:53:04 by user42           ###   ########.fr       */
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
}               t_info;

typedef struct	s_cplx
{
	double	re;
	double	im;
}				t_cplx;

void    create_img(t_info *info);

#endif