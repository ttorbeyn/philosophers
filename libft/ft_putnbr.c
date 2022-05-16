/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:17:16 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 17:17:17 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putnbr(long long n)
{
	unsigned long long	n2;

	if (n < 0)
	{
		n2 = -n;
		ft_putchar('-');
	}
	else
		n2 = n;
	if (n2 > 9)
	{
		ft_putnbr(n2 / 10);
		ft_putchar((n2 % 10) + '0');
	}
	else
		ft_putchar(n2 + '0');
}
