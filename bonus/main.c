/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-oual <ael-oual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:56:01 by ael-oual          #+#    #+#             */
/*   Updated: 2022/02/25 10:00:18 by ael-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h>
#include "libft.h"
#include"get_next_line.h"

void pipex_42(int argv, char **argc,char **env,int file);
void free_function(char **str)
{
	int i;
	 
	 i = 0;
		while(str[i] != 0)
		{
			free(str[i]);
			i++;
		}
}

void print_pointer(char **str)
{
	int i;
	 
	 i = 0;
		while(str[i] != 0)
		{
			printf(" str 1 %p content %c " ,str[i],str[i][0]);
			i++;
		}
}

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
	
	str = env[get_index_of_path(env)] + 5; //unlonk
	//printf("%s %d \n", str , get_index_of_path(env));
	str1 = ft_split(str,':');
	while(str1[i] != 0)
	{
		str1[i] = ft_strjoin(str1[i],"/");
		str1[i] = ft_strjoin(str1[i],cmd);
		fd = access(str1[i], 0);
		if (fd == 0)
		{
			str = str1[i];
			free(str1);
			return (str);
		}
		//printf("%s %d\n",str1[i] ,fd);
		i++;
	}
return 0;	
}

void process_ing (char **argc,char **env,int index_c,int **m_pipes)
{
	int		fd[2];
	char	**engvic;
	char	*path;
	int id2;

	pipe(fd);
	//printf("index of cmd %d ",index_c);
	id2 = fork();
	engvic = ft_split(argc[index_c],' ');
	path = get_path(env, engvic[0]);
	if(id2 == 0)
	{
		//close(fd[0]);
		if (path == 0)
		{
			write(2,"Command not found \n",sizeof("Command not found \n"));
			exit(0);
		}
		dup2(fd[0], STDOUT_FILENO);
		execve(path, engvic, env);
		write(1,"Excusion failed\n",6);
		free(path);
		free_function(engvic);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(id2, NULL, 0);
		free(path);
		free_function(engvic);
	}
}

void the_last_cmd(char **argc ,char **env,int argv,int i)
{
	int		file2;
	char	**engvic;
	char	*path;

	
	file2 = open(argc[argv - 1], O_WRONLY | O_CREAT | O_TRUNC ,0777);
	dup2(file2, STDOUT_FILENO);
	engvic = ft_split(argc[i], ' ');
	path = get_path(env, engvic[0]);
	
	path = get_path(env, engvic[0]);
	if (path == 0)
		{
			write(2 ,"Command no found \n",sizeof("Command not found \n"));
			exit(1);
		}
		execve(path, engvic, env);
}

void here_doc_function(int argv, char **argc,char **env)
{
	char *line;
	char *limtter;
	char *content;
	int file;
	
	file = open ("13", O_RDWR | O_CREAT | O_TRUNC ,0777);
	limtter = ft_strjoin(argc[2],"\n");
	while (1)
	{	
		line = get_next_line(0);
		if (ft_strncmp(limtter, line, ft_strlen(limtter)) == 0)
			break;
		ft_putstr_fd(line, file);
	}
	close(file);
	file = open ("13", O_RDWR ,0644);
	pipex_42( argv, argc, env, file);
}
void make_open_pipes(int **multiple_pipes,int length)
{
	int i;
	
	i = 0;
	multiple_pipes = (int **)malloc(sizeof(length));
	 while(i < length)
	 {
		multiple_pipes[i] = (int *)malloc(8);
	 	pipe(multiple_pipes[i]);
	// printf("write %d  read %d \n",multiple_pipes[i][0],multiple_pipes[i][1]);
	 	i++;
	 }
}
void pipex_42(int argv, char **argc,char **env,int file)
{
	int i;
	int **m_pipes;
	i = 2;
	make_open_pipes(m_pipes ,argv - 4);
	if (ft_strncmp(argc[1],"here_doc",sizeof("here_doc")) == 0)
		i = i + 1;
	dup2(file, STDIN_FILENO);
	while(i < argv - 2)
	{
		process_ing (argc, env, i, m_pipes);
	 	i++;
	}
	the_last_cmd(argc, env, argv, i);
}

int	main(int argv, char **argc,char **env)
{
	int		file;
	int		i;
	if (argv < 5)
	{
		write(1 ,"Error\n", 6);
		exit(0);
	}
	
	if (ft_strncmp(argc[1], "here_doc", sizeof("here_doc")) == 0)
	{
		
			here_doc_function(argv ,argc ,env);
			return (1);
	}
	file = open(argc[1], O_RDONLY ,0777);
	if(access(argc[1], R_OK))
	{
		perror(argc[1]);
		exit(0);
	}
	pipex_42(argv, argc, env, file);
	return (0);	
}