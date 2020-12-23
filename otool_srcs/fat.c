/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:37:04 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int	swap32(int x)
{
	return ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8)
	| (((x) & 0xff00) << 8) | (((x) & 0xff) << 24));
}

int	parse_fat(t_macho_file *mf)
{
	uint32_t	n;
	uint32_t	nfat;
	void		*archs;
	void		*init_file;

	n = 0;
	init_file = mf->file;
	archs = mf->file + sizeof(t_fat_header);
	nfat = swap32(((t_fat_header *)(mf->file))->nfat_arch);
	while (n < nfat)
	{
		mf->file = init_file;
		mf->file += swap32(((t_fat_arch *)archs)->offset);
		mf->isfat = 1;
		if (swap32(((t_fat_arch *)archs)->cputype) == CPU_TYPE_X86_64)
			parse_magic(mf);
		archs += sizeof(t_fat_arch);
		n++;
	}
	return (0);
}
