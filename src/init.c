/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:24:48 by trgaspar          #+#    #+#             */
/*   Updated: 2024/07/11 13:46:43 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	stock_command_pipe(t_pipex *pipex, int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	j = 2;
	pipex->number_command = argc - 3;
	pipex->cmd = malloc(sizeof(char **) * (pipex->number_command + 1));
	if (!pipex->cmd)
		free(pipex->cmd);
	while (i != pipex->number_command)
	{
		pipex->cmd[i] = ft_strdup(argv[j]);
		if (!pipex->cmd[i])
			free_all(pipex);
		i++;
		j++;
	}
	pipex->cmd[i] = NULL;
}

int	get_path_command(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(envp[i], "PATH=", 5) == 0)
	{
		pipex->path_cmd = ft_strdup(envp[i]);
		return (EXIT_SUCCESS);
	}
	free_all(pipex);
	return (EXIT_FAILURE);
}

void	get_command(t_pipex *pipex)
{
	size_t		i;
	size_t		cpt;
	char		*str;

	i = 0;
	cpt = ft_strlen(pipex->path_cmd) - 5;
	str = ft_substr(pipex->path_cmd, 5, cpt);
	if (!str)
		free(str);
	pipex->splited_path = ft_split(str, ':');
	if (!pipex->splited_path)
	{
		free(str);
		free_all(pipex);
	}
	free(str);
	free (pipex->path_cmd);
	pipex->path_cmd = NULL;
}

int	init_cmd(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	stock_command_pipe(pipex, argc, argv);
	if (get_path_command(pipex, envp) != 0)
		return (EXIT_FAILURE);
	get_command(pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		return (EXIT_FAILURE);
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipex->outfile == -1)
		return (EXIT_FAILURE);
	pipex->file = ft_strdup(argv[1]);
	if (pipex->file == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_all2(char **tab, int i)
{
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
