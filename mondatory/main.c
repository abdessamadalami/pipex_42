/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-oual <ael-oual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:00:11 by ael-oual          #+#    #+#             */
/*   Updated: 2022/03/14 14:11:37 by ael-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_42_1337.h"

void	parent_prossice(char **env, char **argc, int *fd)
{
	char	**engvic;
	char	*path;
	int		file2;

	engvic = ft_split(argc[3], ' ');
	if (access_func(engvic) != 0)
		path = access_func(engvic);
	else
		path = get_path(env, engvic[0]);
	file2 = open(argc[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	if (execve(path, engvic, NULL) == -1)
	{
		error_print(engvic);
		free(path);
		free_function(engvic);
		exit(0);
	}
}

void	first_child(int *fd, char **argc, char **env)
{
	char	**engvic;
	char	*path;
	int		file;

	file = open(argc[1], O_RDONLY, 0777);
	dup2(file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (access(argc[1], R_OK))
	{
		perror(argc[1]);
		exit(0);
	}
	engvic = ft_split(argc[2], ' ');
	if (access_func(engvic) != 0)
		path = access_func(engvic);
	else
		path = get_path(env, engvic[0]);
	if (execve(path, engvic, env) == -1)
	{
		error_print(engvic);
		free(path);
		free_function(engvic);
		exit(0);
	}
}

int	main(int argv, char **argc, char **env)
{
	int	fd[2];
	int	id2;
	int	id;

	id2 = 0;
	id = 0;
	if (argv != 5)
	{
		write(2, "Error\n", 7);
		exit(0);
	}
	pipe(fd);
	id = fork();
	if (id != 0)
		id2 = fork();
	if (id == 0)
		first_child(fd, argc, env);
	else if (id2 == 0)
		parent_prossice(env, argc, fd);
	close (fd[1]);
	close (fd[0]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
