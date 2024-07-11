/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:08 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/11 18:57:22 by trgaspar         ###   ########.fr       */
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

void	exec(t_pipex *pipex, char **envp, int argc, char **argv)
{
	char	*str;

	if (pipe(pipex->pipefd) == -1)
		perror("pipe");
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror("fork");
	pipex->split_cmd = ft_split(argv[0 + pipex->index], ' ');
	for(int j = 0; pipex->split_cmd[j]; j++)
		printf("%s\n", pipex->split_cmd[j]);
	str = check_cmd(pipex);
	if (pipex->pid == 0)
	{
		if (child(pipex, argc) == -1)
			free_all(pipex);
		if (execve(str, pipex->split_cmd, envp) == -1)
		{
			write(2, "Execve a echoue\n", 17);
			free_all(pipex);
		}
	}
	else
	{
		if ((close(pipex->pipefd[1]) == -1 || \
			dup2(pipex->pipefd[0], 0) == -1 || close(pipex->pipefd[0]) == -1))
				return ;
	}
	free_all2(pipex->split_cmd, 0);
	free(str);
	wait(0);
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
