/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_s.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjell <kjell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:18:06 by krenken           #+#    #+#             */
/*   Updated: 2024/12/28 14:46:29 by kjell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_specifier_s(char *str)
{
	int	str_len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	str_len = 0;
	while (*str)
	{
		str_len += ft_printchar((int)*str);
		++str;
	}
	return (str_len);
}
