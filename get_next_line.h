/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msubtil- <msubtil-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:29:24 by msubtil-          #+#    #+#             */
/*   Updated: 2022/06/27 22:12:48 by msubtil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define NULLPTR (void *) 0
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct s_file
{
	char	buf[BUFFER_SIZE];
	t_bool	newline_flg;
	size_t	idx;
	size_t	read_bytes;
}				t_file;

typedef struct s_list
{
	char			substr[BUFFER_SIZE];
	size_t			bytes;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);

int		parse_for_newline(t_file *fdata);
void	allocate_and_cpy(t_list **outlst, size_t bytes, t_file *fdata);
char	*lstjoin(t_list *outlst, size_t total_bytes);

#endif
