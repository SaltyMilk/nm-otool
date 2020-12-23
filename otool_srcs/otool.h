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

#ifndef OTOOL_H
#define OTOOL_H

# include "../libft/libft.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <ar.h>

typedef struct	s_macho_header
{
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;

}				t_macho_header;

typedef struct	s_segment_command
{
	uint32_t		cmd;
	uint32_t		cmdsize;
	char			segname[16];
	uint32_t		vmaddr;
	uint32_t		vmsize;
	uint32_t		fileoff;
	uint32_t		filesize;
	vm_prot_t		maxprot;
	vm_prot_t		initprot;
	uint32_t		nsects;
	uint32_t		flags;
}				t_segm_cmd;

typedef struct	s_section
{
	char			sectname[16];
	char			segname[16];
	uint32_t		addr;
	uint32_t		size;
	uint32_t		offset;
	uint32_t		align;
	uint32_t		reloff;
	uint32_t		nreloc;
	uint32_t		flags;
	uint32_t		reserved1;
	uint32_t		reserved2;
}				t_section;

typedef struct	s_macho_header64
{
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;
	uint32_t		reserved;

}				t_macho_header64;

typedef struct	s_segment_command64
{
	uint32_t		cmd;
	uint32_t		cmdsize;
	char			segname[16];
	uint64_t		vmaddr;
	uint64_t		vmsize;
	uint64_t		fileoff;
	uint64_t		filesize;
	vm_prot_t		maxprot;
	vm_prot_t		initprot;
	uint32_t		nsects;
	uint32_t		flags;
}				t_segm_cmd64;

typedef struct	s_section64
{
	char			sectname[16];
	char			segname[16];
	uint64_t		addr;
	uint64_t		size;
	uint32_t		offset;
	uint32_t		align;
	uint32_t		reloff;
	uint32_t		nreloc;
	uint32_t		flags;
	uint32_t		reserved1;
	uint32_t		reserved2;
	uint32_t		reserved3;
}				t_section64;


typedef struct	s_load_command
{
	uint32_t	cmd;
	uint32_t	cmdsize;	
}				t_load_cmd;

typedef struct	fat_header t_fat_header;
typedef struct	fat_arch t_fat_arch;
typedef struct	ar_hdr t_ar_hdr;

typedef struct	s_macho_file
{
	void				*file;
	t_macho_header		mh;
	t_macho_header64	mh64;
	t_load_cmd			*lc;
	t_fat_header		fh;
	t_ar_hdr			ah;
	char				isfat;
	char				*arg;
	char				*oname;
}				t_macho_file;

int		parse_macho(t_macho_file *mf);
int		parse_macho_header(t_macho_file *mf);
int		parse_magic(t_macho_file *mf);
void	ft_freedptr(char **ptr, uint32_t size);
int		parse_macho_header64(t_macho_file *mf);
int		parse_macho64(t_macho_file *mf);
int		parse_fat(t_macho_file *mf);
int		parse_ar(t_macho_file *mf);

#endif