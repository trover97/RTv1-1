/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquirrel <wquirrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:31:45 by wquirrel          #+#    #+#             */
/*   Updated: 2020/07/31 15:57:16 by wquirrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	int		check_type_light(char **type)
{
	if (ft_strequ(type[0], "Directional"))
		return (DIRECTIONAL);
	else if (ft_strequ(type[0], "Point"))
		return (POINT);
	else if (ft_strequ(type[0], "Ambient"))
		return (AMBIENT);
	else
		return (0);
}

static	void	check_light_feature(char **tmp, t_bool *features, int *type)
{
	if (ft_strequ(tmp[0], "type") && (*type = check_type_light(tmp + 2)))
		features[0] = TRUE;
	else if (ft_strequ(tmp[0], "pos") && check_vec(tmp + 2))
		features[1] = TRUE;
	else if (ft_strequ(tmp[0], "intensity") && check_float(tmp + 1))
		features[2] = TRUE;
}

static	void	check_lights(int fd)
{
	t_bool	*features;
	char	**tmp;
	char	*line;
	int		type;

	tmp = NULL;
	features = (t_bool[3]){FALSE};
	type = 0;
	while (get_next_line(fd, &line))
	{
		count_brackets(line);
		if (ft_str1trim_equ(line, "}") || !line)
			break ;
		tmp = ft_strtrim_split(line, ' ');
		free(line);
		check_light_feature(tmp, &features[0], &type);
		parser_free_array(tmp);
	}
	free(line);
	if ((type == AMBIENT && features[2] != TRUE) || (type != AMBIENT
	&& (features[0] != TRUE || features[1] != TRUE || features[2] != TRUE)))
		output_error("Check a light");
}

static	t_bool	check_camera(int fd)
{
	char	*line;
	char	**tmp;
	t_bool	coo_state[2];

	tmp = NULL;
	while (get_next_line(fd, &line))
	{
		count_brackets(line);
		if (ft_str1trim_equ(line, "}") || !line)
			break ;
		tmp = ft_strtrim_split(line, ' ');
		free(line);
		if (ft_strequ(tmp[0], "pos") && check_vec(tmp + 2))
			coo_state[0] = TRUE;
		else if (ft_strequ(tmp[0], "dir") && check_vec(tmp + 2))
			coo_state[1] = TRUE;
		parser_free_array(tmp);
	}
	free(line);
	if (coo_state[0] == TRUE && coo_state[1] == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

void			check_scene(int fd, t_bool *cam_flag)
{
	char	*line;
	t_bool	light;

	light = FALSE;
	while (get_next_line(fd, &line))
	{
		count_brackets(line);
		if (ft_str1trim_equ(line, "};") || !line)
			break ;
		if (ft_str1trim_equ(line, "camera"))
			*cam_flag = check_camera(fd);
		else if (ft_str1trim_equ(line, "light"))
		{
			check_lights(fd);
			light = TRUE;
		}
		free(line);
	}
	free(line);
	if (light != TRUE)
		output_error("Add 1 or more source of light");
}
