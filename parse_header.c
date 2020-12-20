#include "otool.h"


int parse_macho_header(t_macho_file *mf)
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