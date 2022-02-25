/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-oual <ael-oual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:00:11 by ael-oual          #+#    #+#             */
/*   Updated: 2022/02/19 18:55:34 by ael-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h>
#include "libft.h"
int get_index_of_path(char **env)
{
	int i;
	
	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i],"PATH",4) == 0)
			return i;
	i++;
	}
	return 0;
}
char *get_path(char **env,char *cmd)
{
	int i;
	int fd;
	char *str,**str1;
	i = 0;
	
	str = env[get_index_of_path(env)] + 5;
	//printf("%s %d \n", str , get_index_of_path(env));
	str1 = ft_split(str,':');
	while(str1[i] != 0)
	{
		str1[i] =ft_strjoin(str1[i],"/");
		str1[i] =ft_strjoin(str1[i],cmd);
		fd = access(str1[i], 0);
		if (fd == 0)
			return str1[i];
		//printf("%s %d\n",str1[i] ,fd);
		i++;
	}
return 0;	
}

void parent_prossice(char **env, char **argc, int *fd)
{

	    char **engvic;
		char *path;
		int file2;
	
		engvic = ft_split(argc[3],' ');
		//chec_engvig(engvic);
		path = get_path(env, engvic[0]);
		
		file2 = open(argc[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
		dup2(fd[0], STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, engvic, NULL) == -1)
			ft_putstr_fd ("Command Not Found\n", 2);
}

int	main(int argv, char **argc,char **env)
{
	int		fd[2];
	int		file;
	int		file2;
	char	**engvic;
	char	*path;
	int id2;
	
	engvic = ft_split(argc[2],' ');
	path = get_path(env, engvic[0]);
	file = open(argc[1], O_CREAT , 0777);
	file2 = open(argc[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if(access(argc[4] ,X_OK))
		exit(0);
	pipe(fd);
	int id = fork();
	if(id != 0)
	{
		 id2 = fork();
	}
	 if(id == 0)
	{
	    dup2(file, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		if(execve(path, engvic, env) == -1)
			ft_putstr_fd ("Command Not Found\n", 2);
	}
	else if (id2 == 0)
	{
		parent_prossice(env , argc, fd);
	}
	 wait(0);
	 //waitpid (id2, NULL, 0);
		return (0);	
}