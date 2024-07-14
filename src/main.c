/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:03:28 by trgaspar          #+#    #+#             */
/*   Updated: 2024/06/18 14:03:28 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;

	if (envp == NULL)
		return (EXIT_FAILURE);
	if (argc < 5)
		return (ft_putstr_fd("Error: You don't have enough arguments: ", 1), 1);
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		free_all(pipex);
	if (init_cmd(pipex, argc, argv, envp) != 0)
		free_all(pipex);
	pipex(p, argc, argv, env);
	free_all(pipex);
	return (EXIT_SUCCESS);
}

void	free_all(t_pipex *pipex)
{
	if (pipex->splited_path != NULL)
		free_all2(pipex->splited_path, 0);
	if (pipex->cmd != NULL)
		free_all2(pipex->cmd, 0);
	if (pipex->path_cmd != NULL)
		free(pipex->path_cmd);
	if (pipex->file != NULL)
		free(pipex->file);
	if (pipex != NULL)
		free(pipex);
	exit(1);
}

void	pipex(t_pipex pipex, int argc, char **argv, char **env)
{
	pipex->index = 2;
	while (pipex->index <= argc - 2)
	{
		if (pipe(pipex->tube) < 0)
			perror("pipe");
		pipex->pid = fork();
		if (pipex->pid == -1)
			return ;
		if (pipex->pid == 0)
		{
			if (child(p, argc) == -1)
				return ;
			execute_command(p, argv, env);
			fork_free(p);
			exit(1);
		}
		else
		{
			if ((close(pipex->tube[1]) == -1 || \
			dup2(pipex->tube[0], 0) == -1 || close(pipex->tube[0]) == -1))
				return ;
		}
		pipex->index++;
	}
	wait(NULL);
}
