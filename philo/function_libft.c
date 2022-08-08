/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_libft                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:27:53 by iouazzan          #+#    #+#             */
/*   Updated: 2022/07/18 16:27:57 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	check(size_t sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	size_t				k;
	int					sign;
	unsigned long long	n;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	k = i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - 48;
	k = i - k;
	if (k > 19 || n > 9223372036854775807)
		return (check(sign));
	n = n * sign;
	return ((int)n);
}
