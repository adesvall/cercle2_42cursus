/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftutils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:48:52 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/22 12:33:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H


# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_bzero(void *s, size_t n);
char			**ft_abort(char **res);
char			**ft_split(const char *s, char *c);
int				ft_strcmp(const char *s1, const char *s2);
int   			ft_strend_is(char *str, char *end);
int				ft_isin(char c, const char *str);
int				ft_atoi(const char *str);
double			ft_atod(const char *str);
int				ft_tablen(char **tab);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstadd_front(t_list **alst, t_list *nw);

#endif