/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:36:06 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint64_t	get_file_size(char *filename)
{
	int			fd;
	struct stat	buff;

	if ((fd = open(filename, O_RDONLY)) < 0
	|| fstat(fd, &buff) < 0)
		return (0);
	return (buff.st_size);
}

int			parse_ar(t_macho_file *mf)
{
	int		size;
	int		i;
	void	*ar;
	void	*s_ptr;

	ft_printf("Archive : %s\n", mf->arg);
	s_ptr = mf->file;
	ar = mf->file + SARMAG;
	i = 0;
	while (ar < mf->file + get_file_size(mf->arg))
	{
		size = ft_atoi(((t_ar_hdr *)ar)->ar_size);
		mf->oname = ar + sizeof(t_ar_hdr);
		mf->file = mf->oname;
		while (*((char *)mf->file))
			(mf->file)++;
		while (!*((char *)mf->file))
			(mf->file)++;
		if (i++)
			parse_magic(mf);
		ar += size + sizeof(t_ar_hdr);
		mf->file = s_ptr;
	}
	return (0);
}
