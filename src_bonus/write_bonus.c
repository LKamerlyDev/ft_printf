/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 06:21:04 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 17:42:31 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_write(int __fd, const void *__buf, size_t __n, t_flag *flags)
{
	ssize_t	count;

	count = write(__fd, __buf, __n);
	if (count == -1)
		flags->errno = WRITE_ERROR;
	return (count);
}

char	*ft_precision_pad(char *str, size_t lead, size_t num, ssize_t prec)
{
	char	*new_str;
	size_t	zeros;

	if (prec <= (ssize_t)num)
		return (str);
	zeros = (size_t)prec - num;
	new_str = malloc(lead + zeros + num + 1);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new_str, str, lead);
	ft_memset(new_str + lead, '0', zeros);
	ft_memcpy(new_str + lead + zeros, str + lead, num);
	new_str[lead + zeros + num] = '\0';
	free(str);
	return (new_str);
}

char	*ft_handle_zero_precision(char *str)
{
	free(str);
	return (ft_strdup(""));
}
