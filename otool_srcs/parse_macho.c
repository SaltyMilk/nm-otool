/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:44:56 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int print_text(t_macho_file *mf, t_section *sect)
{
	void		*text;
	uint32_t 	addr;
	size_t		bw;

	bw = 0;
	text = mf->file + sect->offset;
	addr = sect->addr;
	if (!mf->oname)
		ft_printf("%s:\n", mf->arg);
	else
		ft_printf("%s(%s):\n", mf->arg, mf->oname);
	ft_printf("Contents of (__TEXT,__text) section");
	while (bw < sect->size)
	{
		if (!(bw % 16))
			ft_printf(mf->isfat ? "\n%0.16x\t"
			 : "\n%0.8x\t", addr);
		ft_printf("%02x ", *(unsigned char *)text++);
		bw++;
		addr++;
	}
	ft_printf("\n");
	return (0);	
}

int handle_macho_sect(t_macho_file *mf, t_section *sect)
{
	if (!ft_strncmp(SECT_TEXT, sect->sectname, ft_strlen(SECT_TEXT)))
		print_text(mf, sect);
	return (0);
}

int handle_macho_segm(t_macho_file *mf, void *segm_cmd)
{
	void		*section;
	t_segm_cmd	segm;
	uint32_t	i;

	i = 0;
	section = segm_cmd + sizeof(t_segm_cmd);
	segm.nsects = ((t_segm_cmd *)segm_cmd)->nsects;
	while (i < segm.nsects)
	{
		handle_macho_sect(mf, section);
		section += sizeof(t_section);
		i++;
	}
	return (0);
}

int parse_macho_lc(t_macho_file *mf, t_load_cmd *lc)
{
	if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
		handle_macho_segm(mf, lc);
	return (0);
}

int parse_macho_load_cmd(t_macho_file *mf)
{
	uint32_t	i;
	t_load_cmd	*lc;

	i = 0;
	lc = (t_load_cmd *)((unsigned char *)mf->file + sizeof(t_macho_header));
	while (i < mf->mh.ncmds)
	{
		parse_macho_lc(mf, lc);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}	
	return (0);
}

int parse_macho(t_macho_file *mf)
{
	parse_macho_header(mf);
	if (parse_macho_load_cmd(mf))
		return (1);
	return (0);
}

