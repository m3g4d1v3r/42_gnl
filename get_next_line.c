/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msubtil- <msubtil-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:28:54 by msubtil-          #+#    #+#             */
/*   Updated: 2022/06/27 20:47:05 by msubtil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_file	fdata;
	t_list			*outlst;
	size_t			read_bytes;
	size_t			bytes;
	size_t			total_bytes;

	outlst = NULLPTR;
	total_bytes = 0;
	bytes = read(fd, fdata.buf, 0);
	if (fdata.eof == TRUE || bytes != 0)
		return (NULLPTR);
	bytes = parse_for_newline(&fdata);
	total_bytes += bytes;
	allocate_and_cpy(&outlst, bytes, &fdata);
	while (fdata.eof == FALSE && fdata.newline_flg == FALSE)
	{
		read_bytes = read(fd, fdata.buf, BUFFER_SIZE);
		fdata.read_bytes = read_bytes;
		fdata.idx = 0;
		if (!(read_bytes > 0)) {
			fdata.eof = TRUE;
			break ;
		}
		bytes = 1;
		while (fdata.newline_flg == FALSE && bytes > 0)
		{
			bytes = parse_for_newline(&fdata);
			total_bytes += bytes;
			allocate_and_cpy(&outlst, bytes, &fdata);
		}
	}
	return (lstjoin(&outlst, total_bytes));
}
