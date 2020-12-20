#include "otool.h"

void ft_freedptr(char **ptr, uint32_t size)
{
	uint32_t i;

	i = 0;
	while (i < size)
		free(ptr[i]);
	free(ptr);	
}