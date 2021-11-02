/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:56:50 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 18:31:25 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <string.h>
#include <errno.h>

// Return EXIT_FAILURE since there was an error.
// I return it here to gain lines in main
int	print_error(void)
{
	ft_putstr_fd("An error occured: ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putchar_fd('\n', 1);
	return (EXIT_FAILURE);
}
