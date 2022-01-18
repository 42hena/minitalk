/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:03:46 by hena              #+#    #+#             */
/*   Updated: 2022/01/18 14:08:59 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
int	ft_get_degree(int num)
{
	int	cnt;

	if (num == 0)
		return (1);
	cnt = 0;
	while (num)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

void	recursive(char buf[13], int num, int index)
{
	if (index == -1)
		return ;
	buf[index] = num % 10 + '0';
	recursive(buf, num / 10, index - 1);
}

void	ft_itoa(int pid)
{
	char	buf[13];
	int		size;
    
    size = ft_get_degree(pid);
	buf[size] = 0;
	recursive(buf, pid, size - 1);
	write(1, buf, size);
}

void	handler(int signo, siginfo_t *sf, void *uc)
{
	static int				bit = 7;
	static unsigned char	c = 0;
	static unsigned int		clipid = 0;

	(void)uc;
	if (clipid == 0)
		clipid = sf->si_pid;
	if (signo == SIGUSR1)
		c |= (1 << bit);
	if (bit == 0)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			bit = 7;
			kill(clipid, SIGUSR1);
			clipid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
		bit = 7;
		return ;
	}
	bit--;
}

int	main(void)
{
	struct sigaction	act;

    ft_itoa(getpid());
	write(1, "\n", 1);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, (struct sigaction *) NULL);
	sigaction(SIGUSR2, &act, (struct sigaction *) NULL);
	while (1)
		;
}