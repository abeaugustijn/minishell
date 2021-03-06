/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaugusti <aaugusti@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:30:29 by aaugusti      #+#    #+#                 */
/*   Updated: 2020/10/29 13:30:29 by aaugusti      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <libftprintf.h>
#include <minishell.h>

/*
**	Print the current working directory.
**
**	@param {t_mshell *} mshell
**	@param {t_cmd} cmd
**
**	@return {bool}
*/

bool	builtin_pwd(t_mshell *mshell, t_cmd cmd)
{
	t_env	*pwd_env;

	(void)cmd;
	pwd_env = env_get(mshell, "PWD");
	ft_printf("%s\n", pwd_env->value.str);
	return (false);
}
