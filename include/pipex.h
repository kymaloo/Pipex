/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 04:28:19 by trgaspar          #+#    #+#             */
/*   Updated: 2024/06/20 04:28:19 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define NOT_COUNT_ARGC "You have the wrong number of arguments"
# define NOT_ENVP "I don't have environment variable"

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*path_cmd;
	char	*file;
	char	**splited_path;
	char	**cmd;
	int		infile;
	int		outfile;
	int		number_command;
	int		index;
	int		pipefd[2];
}					t_pipex;

void	stock_command_pipe(t_pipex *pipex, int argc, char **argv);
int		get_path_command(t_pipex *pipex, char **envp);
void	get_command(t_pipex *pipex);
int		init_cmd(t_pipex *pipex, int argc, char *argv[], char *envp[]);
void	exec(t_pipex *pipex, char **cmd, char **envp, int argc);
void	free_all(t_pipex *pipex);
char	*check_cmd(t_pipex *pipex, char *cmd);
int		child(t_pipex *pipex, int argc);
void	free_all2(char **tab, int i);
void	setup_pid(t_pipex *pipex, char **cmd, int argc);

#endif