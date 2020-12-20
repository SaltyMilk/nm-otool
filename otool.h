#ifndef OTOOL_H
#define OTOOL_H

# include "libft/libft.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>

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

typedef struct	s_macho_file
{
	void				*file;
	t_macho_header		mh;
	t_macho_header64	mh64;
	t_load_cmd			*lc;
	char			*arg;
}				t_macho_file;

int		parse_macho(t_macho_file *mf);
int		parse_macho_header(t_macho_file *mf);
int		parse_magic(t_macho_file *mf);
void	ft_freedptr(char **ptr, uint32_t size);
int		parse_macho_header64(t_macho_file *mf);
int		parse_macho64(t_macho_file *mf);

#endif