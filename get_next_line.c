/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msubtil- <msubtil-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:28:54 by msubtil-          #+#    #+#             */
/*   Updated: 2022/06/27 21:42:20 by msubtil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_file	fdata;
	t_list			*outlst;
	size_t			bytes;
	size_t			total_bytes;

	outlst = NULLPTR;
	if (read(fd, fdata.buf, 0) != 0)
		return (NULLPTR);
	total_bytes = parse_for_newline(&fdata);
	allocate_and_cpy(&outlst, total_bytes, &fdata);
	while (fdata.newline_flg == FALSE)
	{
		fdata.read_bytes = read(fd, fdata.buf, BUFFER_SIZE);
		fdata.idx = 0;
		if (fdata.read_bytes == 0)
			break ;
		bytes = 1;
		while (fdata.newline_flg == FALSE && bytes > 0)
		{
			bytes = parse_for_newline(&fdata);
			total_bytes += bytes;
			allocate_and_cpy(&outlst, bytes, &fdata);
		}
	}
	return (lstjoin(outlst, total_bytes));
}
