/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:44:10 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int	parse_macho_header(t_macho_file *mf)
{
	size_t pos;

	pos = sizeof(uint32_t);
	mf->mh.cputype = *((unsigned char*)mf->file + pos);
	pos += sizeof(cpu_type_t);
	mf->mh.cpusubtype = *((unsigned char*)mf->file + pos);
	pos += sizeof(cpu_subtype_t);
	mf->mh.filetype = *((unsigned char*)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh.ncmds = *((unsigned char*)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh.sizeofcmds = *((unsigned char *)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh.flags = *((unsigned char *)mf->file + pos);
	return (0);
}
