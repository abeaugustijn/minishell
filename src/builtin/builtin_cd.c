/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaugusti <aaugusti@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:29:40 by aaugusti      #+#    #+#                 */
/*   Updated: 2020/10/29 13:30:14 by aaugusti      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <libft.h>
#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

static bool	builtin_cd_home(t_mshell *mshell, t_string *path)
{
	t_env		*home;

	home = env_get(mshell, "HOME");
	if (!home)
		return (ms_set_error(mshell, ENO_HOME, "cd"));
	if (string_from(home->value.str, path))
		error(E_ALLOC "'builtin_cd_home'", mshell);
	return (false);
}

static bool	builtin_cd_old(t_mshell *mshell, t_string *path)
{
	t_env	*old_pwd;

	old_pwd = env_get(mshell, "OLDPWD");
	if (!old_pwd)
		return (ms_set_error(mshell, ENO_OLDPWD, "cd"));
	if (string_from(old_pwd->value.str, path))
		error(E_ALLOC "'builtin_cd_old'", mshell);
	return (false);
}

static bool	builtin_cd_other(t_mshell *mshell, t_string arg, t_string *path)
{
	if (!ft_strcmp(arg.str, "-"))
		return (builtin_cd_old(mshell, path));
	if (arg.str[0] != '/')
	{
		if (string_from(env_get(mshell, "PWD")->value.str, path))
			error(E_ALLOC "'builtin_cd'", mshell);
		if (path->str[path->len - 1] != '/')
			if (string_pushc(path, '/'))
				error(E_ALLOC "'builtin_cd'", mshell);
		if (string_push(path, arg.str))
			error(E_ALLOC "'builtin_cd'", mshell);
	}
	else if (string_from(arg.str, path))
		error(E_ALLOC "'builtin_cd'", mshell);
	return (false);
}

/*
**	Changes the current working directory.
**
**	@param {t_mshell *} mshell
**	@param {t_cmd} cmd
**
**	@return {bool} - true if there is an error
*/

bool		builtin_cd(t_mshell *mshell, t_cmd cmd)
{
	char		*cwd;
	int			chdir_ret;
	t_string	path;

	if (cmd.argc > 2)
		return (ms_set_error(mshell, ENO_TMA, "cd"));
	if (cmd.argc == 1 || (cmd.argc == 2 &&
		ft_strcmp(cmd.argv[1].str, "~") == 0))
	{
		if (builtin_cd_home(mshell, &path))
			return (true);
	}
	else if (builtin_cd_other(mshell, cmd.argv[1], &path))
		return (true);
	env_set(mshell, "OLDPWD", env_get(mshell, "PWD")->value.str, false);
	chdir_ret = chdir(path.str);
	string_free(&path);
	if (chdir_ret != 0)
		return (ms_set_error_from_no(mshell, "cd", cmd.argv[1].str));
	cwd = get_cwd(mshell);
	env_set(mshell, "PWD", cwd, false);
	free(cwd);
	return (false);
}
