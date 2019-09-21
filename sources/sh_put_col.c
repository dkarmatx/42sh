/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_put_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:33:07 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/09/21 15:22:20 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_readline.h"
#include "sh_termcomand.h"
#include <sys/ioctl.h>

static void			ft_strset(char **str, char c, size_t n)
{
	size_t		i;

	i = 0;
	(*str) = (char*)malloc(sizeof(char) * n + 1);
	while (i < n)
		(*str)[i++] = c;
	(*str)[i] = '\0';
}

static DSTRING		*sh_get_space(int max, int len)
{
	char	*str;
	int		n;
	DSTRING	*rez;

	n = max - len;
	if (n > 0)
	{
		ft_strset(&str, ' ', n);
		rez = dstr_new(str);
		free(str);
		return (rez);
	}
	return (dstr_new(""));
}

static DSTRING		*sh_get_col(t_darr dar, const ushort col, ushort iter)
{
	DSTRING		*colstr;
	DSTRING		*space;
	ushort		nstr;
	uint		ind;

	nstr = -1;
	colstr = dstr_new("");
	while (++nstr < dar.count / col + 1 && (iter = 0) == 0)
	{
		ind = nstr;
		while (iter++ < col)
		{
			if (ind < dar.count)
			{
				dstr_insert_dstr(colstr, dar.strings[ind], colstr->strlen);
				space = sh_get_space(dar.maxlen + 2, dar.strings[ind]->strlen);
				dstr_insert_dstr(colstr, space, colstr->strlen);
				dstr_del(&space);
			}
			ind += dar.count / col ? dar.count / col + 1 : 1;
		}
		dstr_insert_str(colstr, "\n", colstr->strlen);
	}
	return (colstr);
}

void				free_lines_down(void)
{
	struct winsize		term;
	int					lines;

	ioctl(0, TIOCGWINSZ, &term);
	ft_putstr(SAVECAR);
	lines = term.ws_row;
	while (lines--)
	{
		ft_putstr(NEXTLIN);
		ft_putstr(CLEARL);
	}
	ft_putstr(LOADCAR);
}

void				put_col(t_darr overlap, const DSTRING *buf)
{
	ushort		col;
	int			iter;
	DSTRING		*colstr;

	iter = 0;
	col = get_col(overlap.maxlen + 2);
	ft_putstr(CLRCRBG);
	ft_putstr(MOVEBGN);
	free_lines_down();
	colstr = sh_get_col(overlap, col, iter);
	dstr_cutins_ch(&colstr, '\0', colstr->strlen - 1);
	ft_putstr(colstr->txt);
	ft_putstr("\n");
	sh_rewrite(buf, buf->strlen);
	dstr_del(&colstr);
}
