/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_case_write.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaugusti <aaugusti@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 13:41:34 by aaugusti      #+#    #+#                 */
/*   Updated: 2020/10/29 14:01:44 by aaugusti      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "../parser.h"

bool	parser_case_write(t_mshell *mshell, t_parser *parser, char c)
{
	if (parser->in_squote || parser->in_dquote)
		parser_push(mshell, parser, c);
	else
	{
		if (parser->in_word)
			parser->end_word = true;
		if (parser->redir == true && parser->redir_type == APPEND)
		{
			ms_set_error(mshell, ENO_UNEXTOK, "");
			return (true);
		}
		else if (parser->redir == true)
			parser->redir_type = APPEND;
		else
		{
			parser->redir = true;
			parser->redir_type = WRITE;
		}
	}
	return (false);
}