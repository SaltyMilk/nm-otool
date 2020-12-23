#include "otool.h"

int print_text64(t_macho_file *mf, t_section64 *sect)
{
	void		*text;
	uint64_t 	addr;
	uint32_t	addr_s[2];
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
		ft_memcpy(addr_s, &addr, sizeof(addr));
		if (!(bw % 16))
			ft_printf("\n%0.8x%0.8x\t", addr_s[1], addr_s[0]);
		ft_printf("%02x ", *(unsigned char *)text++);
		bw++;
		addr++;
	}
	ft_printf("\n");
	return (0);	
}

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

