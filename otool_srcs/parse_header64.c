/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:44:26 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int	parse_macho_header64(t_macho_file *mf)
{
	size_t pos;

	pos = sizeof(uint32_t);
	mf->mh64.cputype = *((unsigned char*)mf->file + pos);
	pos += sizeof(cpu_type_t);
	mf->mh64.cpusubtype = *((unsigned char*)mf->file + pos);
	pos += sizeof(cpu_subtype_t);
	mf->mh64.filetype = *((unsigned char*)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh64.ncmds = *((unsigned char*)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh64.sizeofcmds = *((unsigned char *)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh64.flags = *((unsigned char *)mf->file + pos);
	pos += sizeof(uint32_t);
	mf->mh64.reserved = *((unsigned char *)mf->file + pos);
	return (0);
}
