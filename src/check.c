/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:08 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/14 22:33:36 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_cmd(t_pipex *pipex)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (pipex->splited_path[i])
	{
		tmp = ft_strjoin(pipex->splited_path[i], "/");
		path = ft_strjoin(tmp, pipex->split_cmd[0]);
		free(tmp);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		i++;
	}
	if (access(pipex->split_cmd[0], 0) == 0)
		return (pipex->split_cmd[0]);
	return (NULL);
}

void	exec(t_pipex *pipex, char **argv, char **envp)
{
	char	*str;

	pipex->split_cmd = ft_split(argv[pipex->index], ' ');
	str = check_cmd(pipex);
	if (str == NULL)
	{
		error("command not found : ", 2);
		error(*pipex->split_cmd, 2);
		error("\n", 2);
		free_child(pipex);
	}
	else if (execve(str, pipex->split_cmd, envp) == -1)
		perror("execve error.");
}

int	child(t_pipex *pipex, int argc)
{
	if (close(pipex->pipefd[0]) == -1)
		return (close(pipex->pipefd[1]), -1);
	if (pipex->index == 2)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			return (close(pipex->pipefd[1]), -1);
	}
	if (pipex->index == argc - 2)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			return (close(pipex->pipefd[1]), -1);
	}
	else
	{
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			return (close(pipex->pipefd[1]), -1);
	}
	return (0);
}

void	error(char *msg, int id)
{
	if (id == 2)
		ft_putstr_fd(msg, 2);
	else
	{
		perror(msg);
		exit(1);
	}
}
