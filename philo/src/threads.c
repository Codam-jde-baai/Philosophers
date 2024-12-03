/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/22 16:57:37 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/10/06 23:38:38 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#define EAT_FUNC 0
#define SLEEP_FUNC 1
#define THINK_FUNC 2

bool	continue_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data->m_data->state_mutex);
	if (philo->p_data->m_data->p_state == END)
		return (pthread_mutex_unlock(&philo->p_data->m_data->state_mutex),
			false);
	pthread_mutex_unlock(&philo->p_data->m_data->state_mutex);
	return (true);
}

static void	*routine(void *arg)
{
	t_philo	*philo;
	int		func;
	bool	success;
	bool	(*func_action[3])(t_philo *);

	philo = (t_philo *)arg;
	func = EAT_FUNC;
	if (philo->id % 2 == 0)
		func = SLEEP_FUNC;
	func_action[EAT_FUNC] = &philo_eat;
	func_action[SLEEP_FUNC] = &philo_sleep;
	func_action[THINK_FUNC] = &philo_think;
	while (continue_routine(philo))
	{
		success = func_action[func](philo);
		if (!success)
			return (NULL);
		func = (func + 1) % 3;
	}
	return (NULL);
}

static void	*solo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->fork_left);
	print_message(philo, FORK_MSG);
	ft_zzz(philo->p_data->time_to_die);
	pthread_mutex_unlock(&philo->fork_left);
	return (NULL);
}

/**
 * @brief create threads
 */
int	create_threads(t_program *p, int *thread_count)
{
	if (p->n_philo == 1)
	{
		if (pthread_create(&p->m_data->threads[0], NULL, &solo_routine,
				&p->m_data->philos[0]) != 0)
			return (write(1, "Error: pthread_join\n", 20), false);
		return (true);
	}
	while ((*thread_count) < p->n_philo)
	{
		if (pthread_create(&p->m_data->threads[(*thread_count)], NULL, &routine,
				&p->m_data->philos[(*thread_count)]) != 0)
			return (false);
		(*thread_count)++;
	}
	return (true);
}

/**
 * @brief join threads
 */
bool	join_threads(t_program *p, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		if (pthread_join(p->m_data->threads[i], NULL) != 0)
		{
			write(1, "Error: pthread_join\n", 20);
			return (false);
		}
		i++;
	}
	return (true);
}
