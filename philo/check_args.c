#include "main.h"

int ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	if (!str || !*str)
		return ERROR;
	if (ft_strlen(str) > 10)
		return ERROR;
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-' )
			sign *= -1;
	while (str[i] && ft_isdigit(str[i]))
		result = (result * 10) + str[i++] - 48;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		return ERROR;
	return (result * sign);
}

int	check_args(int ac, char **av)
{
	int i = 0;
	while (++i < ac)
		if (ft_atoi(av[i]) < 0)
			return ERROR;
	return (0);
}