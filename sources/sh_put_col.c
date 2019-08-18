/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_put_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:33:07 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/08/18 17:35:50 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_readline.h"
#include "sh_termcomand.h"
# include <sys/ioctl.h>


// 1. запомнить позицию курсора

// 4. вернуть курсор на мето
// 5. при повторном нажатии дописать путь или комнду

static void		ft_strset(char **str, char c, size_t n)
{
	int		i;

	i = 0;
	(*str) = (char*)malloc(sizeof(char) * n + 1);
	while (i < n)
		(*str)[i++] = c;
	(*str)[i] = '\0';
}

static DSTRING	*sh_get_space(int max, int len)
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

static ushort	get_col(const int lencol)
{
	struct winsize		term;

	ioctl(0, TIOCGWINSZ, &term);
	return (term.ws_col / lencol);
}

static DSTRING	*sh_get_col(t_darr dar, const ushort col, ushort iter)
{
	DSTRING		*colstr;
	DSTRING		*space;
	ushort		nstr;
	uint		ind;
	
	nstr = -1;
	colstr = dstr_new("\n");
	while (++nstr < dar.count / col)
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
			ind += dar.count / col;
		}
		iter = 0;
		dstr_insert_str(colstr, "\n", colstr->strlen);
	}
	return (colstr);
}

void			put_col(t_darr overlap)
{
	ushort		col;
	int			iter;
	DSTRING		*colstr;

	iter = 0;
	col = get_col(overlap.maxlen + 2);
	
	ft_putstr(SAVECAR);
	colstr = sh_get_col(overlap, col, iter);
	ft_putstr(colstr->txt);
	dstr_del(&colstr);
	ft_putstr(LOADCAR);
}