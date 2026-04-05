/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:09:26 by lcamerly          #+#    #+#             */
/*   Updated: 2026/04/05 18:10:26 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

# define HEX_BASE_LOWER "0123456789abcdef"
# define HEX_BASE_UPPER "0123456789ABCDEF"

typedef struct t_flag
{
	ssize_t	hashtag;
	ssize_t	precision;
	ssize_t	plus;
	size_t	justify;
	ssize_t	minus;
	ssize_t	zero;
	ssize_t	space;
	ssize_t	errno;
}			t_flag;

enum		e_err
{
	ALLOC_ERROR = 1,
	WRITE_ERROR = 2
};

int			ft_printf(const char *format, ...) __attribute__((format(printf, 1,
						2)));

ssize_t		ft_write_width(t_flag *flags, ssize_t len, int zero);
ssize_t		ft_print_digits(t_flag *flags, unsigned long arg, char c);
ssize_t		ft_args_process(const char **c, t_flag *flags, va_list args);
size_t		ft_print_str(t_flag *flags, char *arg);
size_t		ft_print_null_char(t_flag *flags);
size_t		ft_print_char(t_flag *flags, int arg);
size_t		ft_print_hexa_digits_lower(t_flag *flags, unsigned int arg);
size_t		ft_print_hexa_digits_upper(t_flag *flags, unsigned int arg);
size_t		ft_print_ptr(t_flag *flags, void *ptr);
ssize_t		ft_print_padded(char *str, t_flag *flags);
ssize_t		ft_write(int __fd, const void *__buf, size_t __n, t_flag *flags);
void		ft_process_type(char c, ssize_t *count, t_flag *flags,
				va_list args);
void		ft_process_width(const char **c, t_flag *flags);
void		ft_procest_flags(const char **c, t_flag *flags);
int			ft_process_precision(const char **c, t_flag *flags);
int			putnbr_base(unsigned long n, char *buffer, int idx,
				const char *base);
char		*ft_itoa_with_sign(long nb);
char		*ft_handle_zero_precision(char *str);
char		*ft_precision_pad(char *str, size_t lead, size_t num, ssize_t prec);
char		*ft_hexa_build_str(t_flag *flags, unsigned long long arg,
				const char *prefix, const char *base);
#endif