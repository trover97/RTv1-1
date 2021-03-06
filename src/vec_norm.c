/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquirrel <wquirrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 16:51:36 by wquirrel          #+#    #+#             */
/*   Updated: 2020/07/10 19:28:24 by wquirrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	vec_norm(t_vec a)
{
	t_vec	vec;
	double	len;

	len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	if (len == 0)
		return (init_vec(0, 0, 0));
	vec.x = a.x / len;
	vec.y = a.y / len;
	vec.z = a.z / len;
	return (vec);
}
