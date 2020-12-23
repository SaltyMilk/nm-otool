/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2019/10/20 12:28:12 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int handle_macho_sect64(t_macho_file *mf, t_section64 *sect)
{
	if (!ft_strncmp(SECT_TEXT, sect->sectname, ft_strlen(SECT_TEXT)))
		print_text64(mf, sect);
	return (0);
}

int handle_macho_segm64(t_macho_file *mf, void *segm_cmd)
{
	void		*section;
	t_segm_cmd64	segm;
	uint32_t	i;

	i = 0;
	section = segm_cmd + sizeof(t_segm_cmd64);
	segm.nsects = ((t_segm_cmd64 *)segm_cmd)->nsects;
	while (i < segm.nsects)
	{
		handle_macho_sect64(mf, section);
		section += sizeof(t_section64);
		i++;
	}
	return (0);
}

int parse_macho_lc64(t_macho_file *mf, t_load_cmd *lc)
{
	if (lc->cmd == LC_SEGMENT_64)
		handle_macho_segm64(mf, lc);
	return (0);
}

int parse_macho_load_cmd64(t_macho_file *mf)
{
	uint32_t	i;
	t_load_cmd	*lc;

	i = 0;
	lc = (t_load_cmd *)((unsigned char *)mf->file + sizeof(t_macho_header64));
	while (i < mf->mh64.ncmds)
	{
		parse_macho_lc64(mf, lc);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}	
	return (0);
}

int parse_macho64(t_macho_file *mf)
{
	parse_macho_header64(mf);
	parse_macho_load_cmd64(mf);
	return (0);
}

