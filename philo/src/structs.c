/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 17:16:11 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 13:19:35 by jde-baai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief	clean up mutexes
 * @param	meal whether to clean up meal_lock
 */
void	c_mutex(t_program *p, int i, bool meal)
{
	if (meal)
		pthread_mutex_destroy(&p->m_data->philos[i].meal_lock);
	i--;
	while (i < 0)
	{
		pthread_mutex_destroy(&p->m_data->philos[i].fork_left);
		pthread_mutex_destroy(&p->m_data->philos[i].meal_lock);
		i--;
	}
}

static bool	init_philo(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		p->m_data->philos[i].id = i + 1;
		p->m_data->philos[i].last_ate = 0;
		p->m_data->philos[i].eating = false;
		if (pthread_mutex_init(&p->m_data->philos[i].meal_lock, NULL) != 0)
			return (c_mutex(p, i, false), false);
		if (pthread_mutex_init(&p->m_data->philos[i].fork_left, NULL) != 0)
			return (c_mutex(p, i, true), false);
		if (p->n_philo == 1)
			p->m_data->philos[i].fork_right = &p->m_data->philos[i].fork_left;
		else if (i == 0)
			p->m_data->philos[i].fork_right = &p->m_data->philos[p->n_philo
				- 1].fork_left;
		else
			p->m_data->philos[i].fork_right = &p->m_data->philos[i
				- 1].fork_left;
		p->m_data->philos[i].p_data = p;
		i++;
	}
	return (true);
}

/**
 * @brief	clean up mallocs
 */
static void	c_malloc_m(t_monitor *m_data)
{
	if (m_data->threads)
		free(m_data->threads);
	if (m_data->philos)
		free(m_data->philos);
	free(m_data);
}

/**
 * @brief	initializes the monitor struct
 */
int	init_monitor(t_program *p)
{
	p->m_data = malloc(sizeof(t_monitor));
	if (!p->m_data)
		return (-1);
	p->m_data->threads = malloc(sizeof(pthread_t) * p->n_philo);
	if (!p->m_data->threads)
		return (c_malloc_m(p->m_data), -1);
	p->m_data->philos = malloc(sizeof(t_philo) * p->n_philo);
	if (!p->m_data->philos)
		return (c_malloc_m(p->m_data), -1);
	if (!init_philo(p))
		return (c_malloc_m(p->m_data), -2);
	p->m_data->p_state = GOOD;
	if (pthread_mutex_init(&p->m_data->state_mutex, NULL) != 0)
		return (c_malloc_m(p->m_data), -2);
	if (pthread_mutex_init(&p->m_data->writing, NULL) != 0)
	{
		pthread_mutex_destroy(&p->m_data->state_mutex);
		c_malloc_m(p->m_data);
		return (-2);
	}
	if (!init_philo(p))
		return (c_malloc_m(p->m_data), -2);
	return (0);
}

/**
 * @brief cleans up the monitor struct and destroys mutexes
 */
void	clean_monitor(t_program *p)
{
	int	i;

	i = 0;
	while (i < p->n_philo)
	{
		pthread_mutex_destroy(&p->m_data->philos[i].meal_lock);
		pthread_mutex_destroy(&p->m_data->philos[i].fork_left);
		i++;
	}
	free(p->m_data->philos);
	free(p->m_data->threads);
	pthread_mutex_destroy(&p->m_data->state_mutex);
	pthread_mutex_destroy(&p->m_data->writing);
	free(p->m_data);
}
