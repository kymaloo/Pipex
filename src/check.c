/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:08 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/01 17:10:07 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_cmd(t_pipex *pipex, char *cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (pipex->splited_path[i])
	{
		tmp = ft_strjoin(pipex->splited_path[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, 0) == 0)
			return (path);
		free(path);
		i++;
	}
	if (access(cmd, 0) == 0)
		return (cmd);
	return (NULL);
}

void	exec(t_pipex *pipex, char **cmd, char **envp, int argc)
{
	pid_t	pid;
	char	*str;

	if (pipe(pipex->pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	str = check_cmd(pipex, cmd[pipex->index - 2]);
	if (pid == 0)
	{
		setup_pid(pipex, cmd, argc);
		child(pipex, argc);
		if (execve(str, cmd, envp) == -1)
		{
			write(2, "Execve a echoue", 16);
			free_all(pipex);
		}
	}
	else
	{
		close(pipex->pipefd[1]);
		dup2(pipex->pipefd[0], STDIN_FILENO);
	}
	free(str);
}

int	child(t_pipex *pipex, int argc)
{
	if (pipex->index == 2)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
	}
	else if (pipex->index == argc - 2)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
	}
	return (0);
}

void	setup_pid(t_pipex *pipex, char **cmd, int argc)
{
	if (pipex->index == 2)
	{
		cmd[1] = pipex->file;
		cmd[2] = NULL;
	}
	if (pipex->index != 2)
	{
		cmd[0] = cmd[pipex->index - 2];
		cmd[1] = 0;
	}
	child(pipex, argc);
}
