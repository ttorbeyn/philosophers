#include "../includes/philo.h"

static	int	ft_verifyll(unsigned long long a, int sign, int c)
{
	unsigned long long	max;

	max = 9223372036854775807U;
	if (((a > max) || c > 19) && sign > 0)
		return (-1);
	if (((a > (max + 1)) || c > 19) && sign < 0)
		return (0);
	return (1);
}

static	int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int					i;
	unsigned long long	y;
	int					sign;
	int					c;

	sign = 1;
	i = ft_isspace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	y = 0;
	c = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		y *= 10;
		y += str[i] - '0';
		i++;
		c++;
	}
	if (ft_verifyll(y, sign, c) != 1)
		return (ft_verifyll(y, sign, c));
	return (y * sign);
}
