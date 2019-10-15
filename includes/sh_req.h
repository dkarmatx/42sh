/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_req.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 01:34:45 by hgranule          #+#    #+#             */
/*   Updated: 2019/10/16 02:26:35 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_REQ_H
# define SH_REQ_H

# include "libft.h"
# include "ft_avl_tree.h"
# include "env.h"

int			sys_init(int sbh);
int			sys_var_init(ENV *env, char **argv, int argc);
int			sh_launch_system(ENV *env, char **lfs, char *fs, char **argv);
int			sh_launch_file(ENV *env, char *file);
int			sys_core_set_init(ENV *env, char **argv);
void		sh_loop(ENV *env);

#endif
