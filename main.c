/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-oual <ael-oual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 08:00:11 by ael-oual          #+#    #+#             */
/*   Updated: 2022/02/17 13:54:06 by ael-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include<sys/wait.h>
#include "libft.h"

char *get_path(char **env,char *cmd)
{
	int i;
	int fd;
	char *str,**str1;
	i = 0;
	str = env[6] + 5;
	//printf("%s\n", str);
	str1 = ft_split(str,':');
	while(str1[i] != 0)
	{
		str1[i] =ft_strjoin(str1[i],"/");
		str1[i] =ft_strjoin(str1[i],cmd);
		fd = access(str1[i],0);
		if (fd == 0)
			return str1[i];
		//printf("%s %d\n",str1[i] ,fd);
		i++;
	}
return 0;	
}

void parent_prossice(char **env, char *argc, int *fd,char *file_name)
{

	    char **engvic;
		char *path;
		int file2;
		
		engvic = ft_split(argc,' ');
		path = get_path(env, engvic[0]); 
		file2 = open(file_name, O_WRONLY | O_CREAT | O_TRUNC , 0777);
		dup2(fd[0], STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		close(fd[1]);
		execve(path, engvic, NULL);
}

int	main(int argv, char **argc,char **env)
{
	int		fd[2];
	int		file;
	int		idf;
	char	**engvic;
	char	*path;
	
	engvic = ft_split(argc[2],' ');
	path = get_path(env, engvic[0]);
	file = open(argc[1], O_CREAT , 0777);
	pipe(fd);
	idf = fork();
	if(idf == 0)
	{
	    if(dup2(file, 0) == -1);
			perror;
		if(dup2(fd[1], 1) == -1)
			perror;
		close(fd[0]);
		if(execve(path, engvic, env)== -1)
			 perror;
	}
	else	
		parent_prossice(env , argc[3], fd, argc[4]);
		return (0);	
}