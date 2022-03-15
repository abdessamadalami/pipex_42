/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_42_1337.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-oual <ael-oual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:17:01 by ael-oual          #+#    #+#             */
/*   Updated: 2022/03/14 14:00:40 by ael-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_42_1337.h"

char	*path_chec(char **engvic, char **env)
{
	char	*path;

	path = 0;
	if (access_func(engvic) != 0)
		path = access_func(engvic);
	else
		path = get_path(env, engvic[0]);
	return (path);
}

void	chiled_prossice(int *fd, char *path, char **engvic)
{	
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(path);
	free_function(engvic);
}

void	process_ing(char **argc, char **env, int index_c, int file)
{
	int		fd[2];
	char	**engvic;
	char	*path;
	int		id2;

	pipe(fd);
	engvic = ft_split(argc[index_c], ' ');
	path = path_chec(engvic, env);
	id2 = fork();
	if (id2 == 0)
	{
		if (file == -1 && index_c == 2)
		{
			free(path);
			free_function(engvic);
			close_pipe(fd);
			exit(0);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path, engvic, env);
		failed_function(path, engvic);
	}
	chiled_prossice(fd, path, engvic);
}

void	the_last_cmd(char **argc, char **env, int argv, int i)
{
	int		file2;
	char	**engvic;
	char	*path;

	file2 = open(argc[argv - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(file2, STDOUT_FILENO);
	close(file2);
	engvic = ft_split(argc[i], ' ');
	path = path_chec(engvic, env);
	if (path == 0)
	{
		error_print(engvic);
		free(path);
		free_function(engvic);
		exit(0);
	}
	execve(path, engvic, env);
	error_print(engvic);
	free(path);
	free_function(engvic);
}

void	pipex_42(int argv, char **argc, char **env, int file)
{
	int	i;
	int	id2;

	i = 2;
	id2 = -4;
	if (ft_strncmp(argc[1], "here_doc", 9) != 0 && access(argc[1], R_OK))
		perror(argc[1]);
	file = open(argc[1], O_RDONLY, 0644);
	dup2 (file, STDIN_FILENO);
	if (ft_strncmp(argc[1], "here_doc", 9) == 0)
		i = i + 1;
	while (id2 != 0 && i < argv - 2)
	{
		process_ing(argc, env, i, file);
		i++;
	}
	id2 = fork();
	if (id2 == 0)
		the_last_cmd (argc, env, argv, i);
	if (strncmp(argc[1], "/dev/random", 12) != 0)
	{
		while (wait(0) != -1)
		{
		}
	}
}
