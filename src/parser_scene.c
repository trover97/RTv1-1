/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquirrel <wquirrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:17:09 by wquirrel          #+#    #+#             */
/*   Updated: 2020/04/27 18:07:26 by wquirrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	parser_get_type(t_type_l *type, char **tmp)
{
	if(ft_strequ(tmp[1], "Directional"))
		*type = DIRECTIONAL;
	else if(ft_strequ(tmp[1], "Point"))
		*type = POINT;
}

void	parser_light(t_scene *scene, t_light *light, int fd)
{
	char *line;
	char **tmp;

	line = NULL;
	while(get_next_line(fd, &line))
	{
		if(ft_strequ(ft_strtrim(line), "}"))
			break;
		tmp = ft_strsplit(line, ' ');
		free(line);
		if(ft_strequ(ft_strtrim(tmp[0]), "type"))
			parser_get_type(&light->type, tmp + 1);
		else if(ft_strequ(ft_strtrim(tmp[0]), "pos"))
			parser_get_vec(&light->p, tmp + 1);
		else if(ft_strequ(ft_strtrim(tmp[0]), "intensity"))
			light->inst = ft_atof(tmp[2]);
		parser_free_array(tmp);
	}
	if (line)
		free(line);
	parser_free_array(tmp);
}

void 	parser_camera(t_scene *scene, int fd)
{
	char *line;
	char **tmp;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if(ft_strequ(ft_strtrim(line), "}"))
			break;
		tmp = ft_strsplit(line, ' ');
		free(line);
		if (ft_strequ(ft_strtrim(tmp[0]), "pos"))
			parser_get_vec(&scene->cam.orig, tmp + 1);
		else if (ft_strequ(ft_strtrim(tmp[0]), "dir"))
			parser_get_vec(&scene->cam.dir, tmp + 1);
		parser_free_array(tmp);
	}
	if (line)
		free(line);
	parser_free_array(tmp);
}

int 	parser_scene(t_scene *scene, int fd)
{
	char *line;
	int i;

	line = NULL;
	i = 0;
	while(get_next_line(fd, &line))
	{
		if(ft_strequ(line, "};") || i == scene->n_lt)
			break;
		if(ft_strequ(ft_strtrim(line), "camera"))
			parser_camera(scene, fd);
		else if(ft_strequ(ft_strtrim(line), "light"))
		{
			parser_light(scene, &scene->light[i], fd);
			i++;
		}
		free(line);
	}
	if (line)
		free(line);
	return(0);
}