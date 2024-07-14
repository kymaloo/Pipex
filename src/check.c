/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:08 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/14 18:13:58 by trgaspar         ###   ########.fr       */
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
	pipex->split_cmd = ft_split(argv[pipex->index], ' ');
	str = check_cmd(pipex);
	if (str == NULL)
	{
		error("command not found : ", 2);
		error(pipex->args[0], 2);
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
		puts("1");
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			return (close(pipex->pipefd[1]), -1);
	}
	if (pipex->index == argc - 2)
	{
		puts("2");
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		{
			puts("test");
			return (close(pipex->pipefd[1]), -1);
		}
		ft_putstr_fd("machin", 2);
	}
	else
	{
		puts("3");
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			return (close(pipex->pipefd[1]), -1);
	}
	return (0);
}
