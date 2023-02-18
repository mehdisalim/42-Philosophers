#include "main.h"

long	ft_atoi(const char *str)
{
	int				i;
	long		    result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	return (result * sign);
}

int main(int ac, char **av)
{
    if (ac != 6)
        return (0);
    int i = -1;
    int arr[6] = {0};
    t_philo philo;
    arr[NUMBER_OF_PHILOSOPHERS] = ft_atoi(av[1]);
    arr[TIME_TO_DIE] = ft_atoi(av[2]);
    arr[TIME_TO_EAT] = ft_atoi(av[3]);
    arr[TIME_TO_SLEEP] = ft_atoi(av[4]);
    arr[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = ft_atoi(av[5]);
    while (++i < 5)
        printf("%d\n", arr[i]);
    return (0);
}
