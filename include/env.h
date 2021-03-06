/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaugusti <aaugusti@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/31 17:19:26 by aaugusti      #+#    #+#                 */
/*   Updated: 2020/11/13 10:32:50 by aaugusti      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <minishell.h>

# define ENV_PRINT_INIT_CAP 2000

typedef struct	s_env {
	bool		read_only;
	t_string	name;
	t_string	value;
}				t_env;

bool			env_set(t_mshell *mshell, char *name, char *value,
				bool read_only);
bool			env_unset(t_mshell *mshell, char *name, bool enforce_ro);
char			**env_to_envp(t_mshell *mshell);
t_env			*env_get(t_mshell *mshell, char *name);
void			env_free(t_env *env);
bool			export_single(t_mshell *mshell, char *arg);
void			replace_env(t_mshell *mshell, t_string *str, int32_t start);
int32_t			env_check_name(char *name);
t_env			*env_new(t_mshell *mshell, char *name, char *value,
				bool read_only);

#endif
