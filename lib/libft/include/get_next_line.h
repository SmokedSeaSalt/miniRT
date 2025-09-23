/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:15:34 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/23 11:14:21 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 112
# endif

# include <stdlib.h> //to use size_t

typedef struct s_gnl_list
{
	char				*line;
	int					fd;
	int					hasnl;
	struct s_gnl_list	*next;
	struct s_gnl_list	*prev;
}						t_gnl_list;

//get next line
char		*free_all(t_gnl_list **head);
char		*get_next_line(int fd);
char		*return_line(t_gnl_list **head, int fd);
void		delnode(t_gnl_list *node, t_gnl_list **head);
int			fill_node(t_gnl_list *head, int fd, char *buffer);

//utils
void		*gnl_calloc(size_t nmemb, size_t size);
t_gnl_list	*get_fd_node(t_gnl_list *head, int fd);
char		*gnl_substr(char const *s, unsigned int start, size_t len);
ssize_t		charpos(char *s, char c);
int			create_node(t_gnl_list **head, char *buffer, int fd);

#endif
