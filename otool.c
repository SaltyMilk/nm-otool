#include "otool.h"

int parse_magic(t_macho_file *mf)
{
	mf->mh.magic = *(uint32_t *)mf->file;
	mf->mh64.magic = *(uint32_t *)mf->file;
	if (mf->mh.magic == MH_MAGIC || mf->mh.magic == MH_CIGAM)
		parse_macho(mf);
	else if (mf->mh.magic == MH_MAGIC_64 || mf->mh.magic == MH_CIGAM_64 || mf->mh.magic == 0xcafebabe)
		parse_macho64(mf);
	else
	{
		ft_printf("%s: is not an object file\n", mf->arg);
		return (1);
	}
	return (0);
}

void *open_file(char ** argv, int file_n)
{
	struct stat	buff;
	int			fd;
	void		*f;

	if ((fd = open(argv[file_n], O_RDONLY)) < 0
	|| fstat(fd, &buff) < 0
	|| !buff.st_size)
		return (NULL);
	f = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	return (f == MAP_FAILED ? NULL : f);
}

int otool(void *file, char **argv, int argn)
{
	t_macho_file	mf;

	mf.file = file;
	mf.arg = argv[argn];
	parse_magic(&mf);
	return (0);
}

int main(int argc, char **argv)
{
	void	*file;
	int		argn;

	if (argc < 2)
	{
		ft_printf("Usage: %s filename\n", argv[0]);
		return (2);
	}
	argn = 1;
	while (argn < argc)
	{
		if (!(file = open_file(argv, argn)))
			return (1);
		if (otool(file, argv, argn))
			return (1);
		argn++;
	}
}