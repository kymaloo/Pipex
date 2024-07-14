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
	t_pipex pipex;

	ft_memset(&pipex, 0, sizeof(pipex));
	if (envp == NULL)
		return (EXIT_FAILURE);
	if (argc < 5)
		return (ft_putstr_fd("Error: You don't have enough arguments: ", 1), 1);
	if (init_cmd(&pipex, argc, argv, envp) != 0)
		return (1);
	ft_pipex(pipex, argc, argv, envp);
	pipex.pid = -9;
	fork_free(pipex);
	return (EXIT_SUCCESS);
}

void	ft_pipex(t_pipex pipex, int argc, char **argv, char **envp)
{
	pipex.index = 2;
	while (pipex.index <= argc - 2)
	{
		if (pipe(pipex.pipefd) < 0)
			perror("pipe");
		pipex.pid = fork();
		if (pipex.pid == -1)
			return ;
		if (pipex.pid == 0)
		{
			if (child(pipex, argc) == -1)
				return ;
			exec(pipex, argv, envp);
			exit(1);
		}
		else
		{
			if ((close(pipex.pipefd[1]) == -1 || \
			dup2(pipex.pipefd[0], 0) == -1 || close(pipex.pipefd[0]) == -1))
				return ;
		}
		pipex.index++;
	}
	wait(NULL);
}
