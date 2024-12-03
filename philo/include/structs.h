/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:43:37 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 02:48:31 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_program	t_program;

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"

/**
 * @param GOOD to be checked by philosophers if they can continue
 * @param END to be checked by philosophers if they can continue
 */
typedef enum e_state
{
	GOOD,
	END
}							t_state;

/**
 * @brief each individual philosophers data
 * @param id: the number assigned to the philosopher;
 * @param meal_count: the number of meals the philosopher has eaten;
 * @param last_ate: the time the philosopher last ate;
 * @param eating: whether the philosopher is currently eating;
 * @param alive: whether the philosopher is alive;
 * @param meal_lock: mutex to protect last_ate & meal_count;
 * @param fork_left: mutex to protect the left fork;
 * @param fork_right: mutex reference to left fork of previous philosopher;
 * @param program_data: the general program data;
 */
typedef struct s_philo
{
	int						id;
	int						meal_count;
	unsigned long			last_ate;
	bool					eating;
	pthread_mutex_t			meal_lock;
	pthread_mutex_t			fork_left;
	pthread_mutex_t			*fork_right;
	t_program				*p_data;
}							t_philo;

/**
 * @brief monitoring data
 * @param threads: array of threads;
 * @param philos: array of philosophers;
 * @param p_state: state of the program;
 * @param state_mutex: mutex to protect p_state;
 * @param writing: mutex to protect writing to stdout;
 */
typedef struct s_monitor
{
	pthread_t				*threads;
	t_philo					*philos;
	t_state					p_state;
	pthread_mutex_t			state_mutex;
	pthread_mutex_t			writing;
}							t_monitor;

/**
 * @brief general program data
 */
struct						s_program
{
	int						n_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	unsigned long			start_time;
	t_monitor				*m_data;
};

#endif /* STRUCTS_H */