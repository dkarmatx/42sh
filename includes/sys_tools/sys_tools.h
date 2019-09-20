/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 08:55:44 by hgranule          #+#    #+#             */
/*   Updated: 2019/09/20 22:10:35 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_TOOLS_H
# define SYS_TOOLS_H

# include <unistd.h>
# include <signal.h>

int			sys_create_pipe(int	*a);
int			sys_destroy_pipe(int p);
int			sys_kill_pipes(void);

int			sys_wait_cp(pid_t childs_pid, int *status);
int			sys_wait_cps(pid_t last_child, int *status);

int			sys_error_message(char *message, size_t len);
int			sys_getch(void);
int			sys_touch_file(const char *path);

#endif
