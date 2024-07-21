/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:24:48 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/21 13:04:13 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_path_command(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(envp[i], "PATH=", 5) == 0)
	{
		pipex->path_cmd = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	}
	if (envp[i] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_command(t_pipex *pipex)
{
	pipex->splited_path = ft_split(pipex->path_cmd, ':');
	if (pipex->splited_path == NULL)
	{
		free(pipex->path_cmd);
		return (EXIT_FAILURE);
	}
	free(pipex->path_cmd);
	pipex->path_cmd = NULL;
	return (EXIT_SUCCESS);
}

int	init_cmd(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	if (get_path_command(pipex, envp) != 0)
		free_all(*pipex, "Error: No path found", 1);
	if (get_command(pipex) != 0)
		free_all(*pipex, "Error: Command no split", 1);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		free_all(*pipex, "Error: infile isn't open", 1);
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex->outfile == -1)
		free_all(*pipex, "Error: outfile isn't open", 1);
	return (EXIT_SUCCESS);
}
