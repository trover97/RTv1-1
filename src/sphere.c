/*
**	created by eflorean
*/

#include "RTv1.h"

double	IntersectSphere(t_vec d, t_scene *scene, int i, t_vec co)
{
	double m[6];

	m[1] = scene->fig[i].oc_d;
	m[2] = scene->fig[i].oc_oc - scene->fig[i].k_k;
	m[3] = m[1] * m[1] - m[2];
	if (m[3] < 0)
		return (0);
	m[4] = -m[1] + sqrtf(m[3]);
	m[5] = -m[1] - sqrtf(m[3]);
	if (m[4] < 1 && m[5] < 1)
		return (0);
    return (((m[4] < m[5] && m[4] >= 1) || m[5] < 1.0) ? m[4] : m[5]);
}

t_vec   sphere_norm(t_scene *scene)
{
    t_vec vec;
    t_vec p;

    p = vec_scale(scene->d, scene->t);
    p = vec_sum(p, scene->cam.orig);
    vec = vec_sub(scene->fig[scene->cur].c, p);
    vec = vec_norm(vec);
    if (vec_dot(vec, scene->d) < 0)
        return (vec_scale(vec, -1));
    return (vec);
}