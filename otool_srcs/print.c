/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:04:40 by sel-melc          #+#    #+#             */
/*   Updated: 2020/12/23 03:54:04 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int	print_text(t_macho_file *mf, t_section *sect)
{
	void		*text;
	uint32_t	addr;
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

int	print_text64(t_macho_file *mf, t_section64 *sect)
{
	void		*text;
	uint64_t	addr;
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
