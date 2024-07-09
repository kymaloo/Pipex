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
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		free_all(pipex);
	if (init_cmd(pipex, argc, argv, envp) != 0)
		free_all(pipex);
	i = 0;
	pipex->index = 0;
	while (i != pipex->number_command)
	{
		exec(pipex, envp, argc, argv);
		i++;
		pipex->index++;
	}
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
