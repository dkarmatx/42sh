/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:36:59 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/11/05 16:37:14 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_readline.h"
#include "sh_termcomand.h"

t_darr			sh_add_path(DSTRING **buf, size_t start_dir)
{
	DSTRING		*str;
	DSTRING		*path;
	t_darr		content;
	t_darr		overlap;

	path = sh_get_path((*buf), start_dir);
	content = sh_dir_content(path->txt);
	str = dstr_serr((*buf), start_dir, (*buf)->strlen);
	overlap = sh_cmp_darr(content, str);
	dstr_del(&str);
	dstr_del(&path);
	correct_namedir_buf(overlap, buf, start_dir);
	free_darr_n(content.strings, content.count);
	return (overlap);
}

t_darr			sh_add_cmd(DSTRING **buf, ENV *env)
{
	t_darr		allcmd;
	t_darr		overlap;
	int			begin_cmd;
	DSTRING		*cmd;

	begin_cmd = ind_begin_cmd((*buf));
	cmd = dstr_slice((*buf), begin_cmd, (*buf)->strlen);
	allcmd = env_get_bins(env);
	overlap = sh_cmp_darr(allcmd, cmd);
	correct_namedir_buf(overlap, &cmd, 0);
	dstr_cutins_dstr(buf, cmd, begin_cmd);
	free_darr_n(allcmd.strings, allcmd.count);
	dstr_del(&cmd);
	return (overlap);
}

int				get_ind_name(DSTRING *buf)
{
	int			rez;
	int			i;
	ssize_t		smcln;
	ssize_t		space;

	smcln = dstrrchr(buf, ';');
	if (smcln != -1 && (i = smcln + 1))
	{
		space = dstrrchr(buf, ' ');
		while (ft_isspace(buf->txt[i]))
			i++;
		if (i >= space + 1)
			return (i);
	}
	if ((rez = dstrrchr(buf, '/')) != -1)
		return (rez + 1);
	else if ((rez = dstrrchr(buf, ' ')) != -1)
		return (rez + 1);
	return (0);
}

int				insert_space(DSTRING **buf)
{
	if (!sh_isdir(*buf, get_ind_name(*buf)))
		dstr_insert_ch(*buf, ' ', (*buf)->strlen);
	return (1);
}

t_indch			insert_space_empty(DSTRING **buf, t_indch indch)
{
	dstr_insert_ch((*buf), ' ', (*buf)->strlen);
	indch.ind++;
	return (indch);
}

t_indch			sh_tab(DSTRING **buf, ENV *env, t_indch indch)
{
	t_darr		overlap;
	int			fl;
	t_name_ind	n_ind;

	fl = 0;
	n_ind.ind = 0;
	n_ind.indch = indch;
	overlap = sh_tab_help(buf, env, &indch);
	if (overlap.count == -1)
		return (insert_space_empty(buf, indch));
	n_ind.ind_name = get_ind_name((*buf));
	sort_darr(&overlap);
	indch.fl = 0;
	while (1)
	{
		n_ind.ind = sh_tab_loop_help(overlap, buf, fl++, n_ind);
		if (overlap.count <= 1 && insert_space(buf))
			break ;
		indch.ch = ft_getch();
		if (indch.ch != TAB && (indch.fl = 1))
			break ;
	}
	free_darr_n(overlap.strings, overlap.count);
	indch.ind = (*buf)->strlen;
	return (indch);
}
