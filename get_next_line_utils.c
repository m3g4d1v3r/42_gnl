/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msubtil- <msubtil-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:04:31 by msubtil-          #+#    #+#             */
/*   Updated: 2022/06/27 21:48:15 by msubtil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULLPTR || lst == NULLPTR)
		return ;
	if (*lst == NULLPTR)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	cpystr(char *dst, const char *src, size_t dstsize)
{
	size_t	src_i;

	src_i = 0;
	while (src_i < dstsize && *src != '\0')
	{
		*dst++ = *src++;
		src_i++;
	}
	if (src_i < dstsize)
	{
		*dst = '\0';
	}
}

int	parse_for_newline(t_file *fdata)
{
	int	byte_count;

	byte_count = 0;
	if (fdata->newline_flg == TRUE)
		fdata->newline_flg = FALSE;
	while (fdata->idx < fdata->read_bytes)
	{
		if (fdata->buf[fdata->idx] == '\0')
			break ;
		byte_count++;
		if (fdata->buf[fdata->idx++] == '\n')
		{
			fdata->newline_flg = TRUE;
			break ;
		}
	}
	return (byte_count);
}

void	allocate_and_cpy(t_list **outlst, size_t bytes, t_file *fdata)
{
	t_list	*new_node;

	if (bytes == 0)
		return ;
	new_node = (t_list *) malloc(sizeof(t_list));
	cpystr(new_node->substr, fdata->buf + fdata->idx - bytes, bytes);
	new_node->next = NULLPTR;
	new_node->bytes = bytes;
	lstadd_front(outlst, new_node);
}

char	*lstjoin(t_list *curr, size_t total_bytes)
{
	t_list	*prev;
	t_list	*next;
	char	*output_str;

	if (curr == NULLPTR || total_bytes == 0)
		return (NULLPTR);
	prev = NULLPTR;
	while (curr != NULLPTR)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	output_str = (char *) malloc(sizeof(char) * (total_bytes + 1));
	while (prev != NULLPTR)
	{
		next = prev->next;
		cpystr(output_str, prev->substr, prev->bytes);
		output_str += prev->bytes;
		free(prev);
		prev = next;
	}
	*output_str = '\0';
	return (output_str - total_bytes);
}
