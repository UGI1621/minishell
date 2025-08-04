/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:58 by saan              #+#    #+#             */
/*   Updated: 2025/08/05 04:54:20 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wspace(char c)
{
	return (c == 8 || c == 9 || c == 10 || c == 11
		|| c == 12 || c == 13 || c == 32);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_cutsign(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	invalid_token(t_lexer_list *res, char c)
{
	write(2, "bash : syntax error near unexpected token `", 43);
	write(2, &c, 1);
	write(2, "'\n",2);
	add_lexer_node(res, NULL);
	return (1);
}
