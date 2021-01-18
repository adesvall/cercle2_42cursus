/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:40:13 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/19 18:18:00 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 100

int		is_endofline(char *buf);
int		get_next_line(int fd, char **line);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*join_and_realloc(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif
