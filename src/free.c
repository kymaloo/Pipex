#include "pipex.h"

void	fork_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->pid == 0)
	{
		close(pipex->pipefd[1]);
		close(pipex->pipefd[0]);
	}
	while (pipex->splited_path[i])
	{
		free(pipex->splited_path[i]);
		i++;
	}
	free(pipex->splited_path);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->args[i])
	{
		if (pipex->args[i])
			free(pipex->args[i]);
		i++;
	}
	free(pipex->args);
}