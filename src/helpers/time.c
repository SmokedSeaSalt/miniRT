/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:31:56 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/12 13:32:09 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h> //to use gettimeofday
#include <unistd.h> //to use usleep

//get the current time in ms
long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//get timestamp since start
long long	get_timestamp(long long start_time)
{
	long long	current_time;

	current_time = get_time_in_ms();
	return (current_time - start_time);
}