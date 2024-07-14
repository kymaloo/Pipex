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
	char	**splited_path;
	char	**cmd;
	char	**split_cmd;
	int		infile;
	int		outfile;
	int		number_command;
	int		index;
	int		pipefd[2];
	pid_t	pid;
	t_list	*lst;
}					t_pipex;

int		get_path_command(t_pipex *pipex, char **envp);
int		get_command(t_pipex *pipex);
int		init_cmd(t_pipex *pipex, int argc, char *argv[], char *envp[]);
void	exec(t_pipex pipex, char **argv, char **envp);
char	*check_cmd(t_pipex pipex);
int		child(t_pipex pipex, int argc);
void	ft_pipex(t_pipex pipex, int argc, char **argv, char **envp);
void	fork_free(t_pipex pipex);
void	free_child(t_pipex pipex);
void	error(char *msg, int id);

#endif