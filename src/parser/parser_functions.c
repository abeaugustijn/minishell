/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <aaugusti@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 14:02:02 by aaugusti          #+#    #+#             */
/*   Updated: 2020/03/31 16:15:14 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <minishell.h>

void		parser_push(t_parser *parser, char c)
{
	if (string_pushc(parser->curr_word, c))
		error(E_ALLOC "'parser_case_rest'");
}

void		parser_new_word(t_parser *parser)
{
	t_string	new;
	t_string	*new_loc;

	if (string_init(PARSER_INIT_WORD_CAP, NULL, &new))
		error(E_ALLOC "'parser_new_word'");
	if (vla_push(&parser->result, &new, (void **)&new_loc))
		error(E_ALLOC "'parser_new_word'");
	parser->curr_word = new_loc;
	parser->new_word = false;
}

void		parser_end_word(t_parser *parser)
{
	if (string_shrink(parser->curr_word))
		error(E_ALLOC "'parser_end_word'");
	parser->argc++;
	parser->curr_word = NULL;
	parser->end_word = false;
	parser->in_word = false;
}