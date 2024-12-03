/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-baai <jde-baai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 17:08:58 by jde-baai      #+#    #+#                 */
/*   Updated: 2023/09/29 16:45:57 by jde-baai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* parser */
bool			validate_args(char **argv);
t_program		*parse_args(int argc, char **argv);

/* threads */
bool			continue_routine(t_philo *philo);
int				create_threads(t_program *p, int *thread_count);
bool			join_threads(t_program *p, int thread_count);

/* actions */
bool			print_message(t_philo *philo, char *message);
bool			philo_eat(t_philo *philo);
bool			philo_sleep(t_philo *philo);
bool			philo_think(t_philo *philo);

/* monitor */
void			start_monitor(t_program *p);

/* utils */
unsigned long	get_time(void);
unsigned long	get_time_d(unsigned long start_time);
size_t			ft_strlen(const char *s);
void			ft_zzz(unsigned long time);
void			set_time_last_eat(t_program *p);

/* structs */
int				init_monitor(t_program *p);
void			clean_monitor(t_program *p);

#endif /* PHILO_H */