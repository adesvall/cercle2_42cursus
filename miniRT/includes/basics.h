/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:04:45 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/15 19:40:31 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

typedef struct  s_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
	int		W;
	int		H;
}               t_data;

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_couple
{
	int	W;
	int	H;
}				t_couple;

typedef struct	s_abc
{
	double	x1;
	double	x2_x1;
	double	delta;
}				t_abc;

typedef	struct	s_rgb
{
	int	r;
	int	g;
	int b;
}				t_rgb;

typedef struct	s_ray
{
	t_vect	origin;
	t_vect	dir;
}				t_ray;

typedef struct	s_rescl
{
	char	*type;
	void	*elem;
	t_vect	*pos;
	t_vect	*dir;
	t_vect	normale;
	t_rgb	color;
}				t_rescl;

#endif