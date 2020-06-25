/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquirrel <wquirrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:41:51 by wquirrel          #+#    #+#             */
/*   Updated: 2020/06/25 16:37:52 by wquirrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


void	parser_count_obj(t_scene *scene)
{
	char *line;
	int fd;

	fd = open(scene->file, O_RDONLY);
	while(get_next_line(fd, &line))
	{
		if(ft_str1trim_equ(line, "sphere") || ft_str1trim_equ(line, "plane")
		   || ft_str1trim_equ(line, "cylinder") || ft_str1trim_equ(line, "cone"))
			scene->n_obj++;
		else if(ft_str1trim_equ(line, "light"))
			scene->n_lt++;
		free(line);
	}
	scene->fig = ft_memalloc(sizeof(t_figure) * scene->n_obj);
	scene->light = ft_memalloc(sizeof(t_figure) * scene->n_lt);
	close(fd);
}


void	parser(t_scene *scene, int ac)
{
	int fd;

	scene->n_lt = 0;
	scene->n_obj = 0;
	parser_file(scene->file, &scene->cam_flag, ac);
	if (scene->cam_flag == FALSE)
		ft_putstr("Camera on default");
	parser_count_obj(scene);
	fd = open(scene->file, O_RDONLY);
	parser_scene(scene, fd);
	parser_objects(scene, fd);
	close(fd);
}