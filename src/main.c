/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaugusti <aaugusti@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/23 13:14:58 by aaugusti      #+#    #+#                 */
/*   Updated: 2020/04/29 19:47:33 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftprintf.h>
#include <minishell.h>
#include <stdlib.h>

int	main(void)
{
	t_mshell	mshell;
	char		*cmd;

	init(&mshell);
	while (1)
	{
		prompt(&mshell);
		cmd = get_cmd(&mshell);
		if (ft_strncmp(cmd, "", 1))
			run_cmd(&mshell, cmd);
	}
}
