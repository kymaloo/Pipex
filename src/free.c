/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:34:28 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/14 22:34:28 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_free(t_pipex pipex)
{
	int	i;

	i = 0;
	close(pipex.infile);
	close(pipex.outfile);
	if (pipex.pid == 0)
	{
		close(pipex.pipefd[1]);
		close(pipex.pipefd[0]);
	}
	while (pipex.splited_path[i])
	{
		free(pipex.splited_path[i]);
		i++;
	}
	free(pipex.splited_path);
}

void	free_child(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.splited_path[i])
	{
		if (pipex.splited_path[i])
			free(pipex.splited_path[i]);
		i++;
	}
	free(pipex.splited_path);
}

void	free_all(t_pipex pipex, char *er, int ex)
{
	if (ex == EXIT_SUCCESS)
	{
		fork_free(pipex);
		exit(ex);
	}
	else
	{
		fork_free(pipex);
		error(er, 2);
		exit(ex);
	}
}