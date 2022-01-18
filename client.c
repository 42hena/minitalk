/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:58:22 by hena              #+#    #+#             */
/*   Updated: 2022/01/18 14:53:06 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void	ft_print_binary(char *str, int pid)
{
	int	bit;
	int	i;

	while (*str)
	{
		bit = 1 << 7;
		while (bit)
		{
			if (*str & bit)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(80);
			bit >>= 1;
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(80);
		i++;
	}
}

int	ft_valid_pid(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	sum;

	if (!ft_valid_pid(str))
		return (-1);
	sum = 0;
	while (*str)
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	return (sum);
}

void	handler(int signo)
{
	write(1, "ACK\n", 4);
	(void)signo;
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;

	signal(SIGUSR1, handler);
	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	ft_print_binary(argv[2], pid);
	pause();
}