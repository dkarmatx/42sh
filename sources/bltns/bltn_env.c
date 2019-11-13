/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:52:22 by fnancy            #+#    #+#             */
/*   Updated: 2019/11/13 16:24:57 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bltn.h"

int			bltn_env(char **args, ENV *env)
{
	char	**mas;
	int		i;

	if (!env->globals)
		return (210);
	if (bltn_cd_countargs(args) > 1)
		bltn_setenv(args, env);
	i = -1;	
	if (!(mas = ft_avl_tree_to_warr(env->globals, &avln_todstring_key_val)))
		return (210);
	while (mas[++i])
	{
		ft_putstr(mas[i]);
		ft_putchar('\n');
	}
	et_rm_warr(mas);
	return (0);
}
