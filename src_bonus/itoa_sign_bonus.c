/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_sign_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:28:57 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 07:21:49 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static char	*tab_writing_with_sign(int nb, unsigned int n, int index,
		char *dest)
{
	if (nb < 0)
		dest[0] = '-';
	else
		dest[0] = '+';
	dest[index--] = '\0';
	while (n > 9)
	{
		dest[index--] = n % 10 + '0';
		n = n / 10;
	}
	dest[index] = n % 10 + '0';
	return (dest);
}

static char	*ft_case_zero(char *dest)
{
	dest = malloc(sizeof(char) * 3);
	if (!dest)
		return (NULL);
	dest[0] = '+';
	dest[1] = '0';
	dest[2] = '\0';
	return (dest);
}

char	*ft_itoa_with_sign(long nb)
{
	unsigned int	nb_count;
	unsigned int	n;
	int				i;
	char			*dest;

	i = 1;
	if (nb == 0)
	{
		dest = NULL;
		return (ft_case_zero(dest));
	}
	n = ft_abs(nb);
	nb_count = n;
	while (nb_count > 9)
	{
		nb_count = nb_count / 10;
		i++;
	}
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	return (tab_writing_with_sign(nb, n, i + 1, dest));
}
