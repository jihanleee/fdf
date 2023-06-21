/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:52:52 by jihalee           #+#    #+#             */
/*   Updated: 2023/06/21 19:58:47 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*str;
	int				eol;
	int				size;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	find_nl(char *buf, int *i, int *j, int *eol_found);
int		add_to_list(char *buf, t_list **list, t_list **current);
int		make_list(int fd, t_list **list);
int		get_size(t_list *list);
char	*extract_line(t_list *list, t_list **first);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *str, int size);
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
