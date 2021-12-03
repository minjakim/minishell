/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:43:29 by snpark            #+#    #+#             */
/*   Updated: 2021/12/03 10:01:06 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *체크해야할 것
 * 인자
 * 커맨드
 * 리다이렉션
 * 확장할 게 있는지 여부
 * 현재 디렉토리 기준으로 *이게 있는지
 *
*/

int
	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int
	is_end(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0' || c == '|'\
			|| c == '&' || c == '<' || c == '>');
}

t_word_list
	*make_word_list(void)
{
	t_word_list		*new_unit;

	new_unit = malloc(sizeof(t_word_list));
	if (new_unit == NULL)
		return (NULL);
	new_unit->word = malloc(sizeof(t_word_desc));
	if (new_unit->word == NULL)
	{
		free(new_unit);
		return (NULL);
	}
	return (new_unit);
}

int
	word_start(t_shell *mini)
{
	t_word_list		*handle;
	return (0);
}

int
	parse_line(t_shell *mini)
{
	int	i;
	int	start_idx;
	int	quote;
	t_word_list	*tmp;

	i = -1;
	quote = 0;
	start_idx = -1;
	while (mini->line[++i])
	{
		printf("%c", mini->line[i]);
		if ((mini->line[i] == ';' || mini->line[i] == '\\') && !quote)
			return (1);
		if (mini->line[i] == '\'' || mini->line[i] == '\"')
		{
			quote ^= mini->line[i];
			if (quote == 5)
				quote ^= mini->line[i];
			else if (quote == '\'')
				printf(" quote");
			else if (quote == '\"')
				printf(" dquote");
		}
		if (!is_end(mini->line[i]) && i != start_idx\
				&& (i == 0 || (i > 0 && is_end(mini->line[i - 1]))))
		{
			printf(" strat");
			start_idx = i;
		}
		if (!quote && is_end(mini->line[i + 1]) && !is_end(mini->line[i]))
			printf(" end");
		if (!quote && mini->line[i] == '|' && (i > 0 && mini->line[i - 1] != '|')\
				&& mini->line[i + 1] != '|')
			printf(" pipe");
		if (!quote && (i > 0 && mini->line[i - 1] != '&') && mini->line[i + 2] != '&'\
				&& strncmp(mini->line + i, "&&", 2) == 0) 
			printf(" andand");
		if (!quote && (i > 0 && mini->line[i - 1] != '|') && mini->line[i + 2] != '|'\
				&& strncmp(mini->line + i, "||", 2) == 0) 
			printf(" oror");
		if (!quote && (i > 0 && mini->line[i - 1] != '<') && mini->line[i] == '<'\
				&& mini->line[i + 1] != '<')
			printf(" <");
		if (!quote && (i > 0 && mini->line[i - 1] != '<')\
				&& strncmp(mini->line + i, "<<", 2) == 0\
				&& mini->line[i + 2] != '<')
			printf(" <<");
		if (!quote && (i > 0 && mini->line[i - 1] != '>') && mini->line[i] == '>'\
				&& mini->line[i + 1] != '>')
			printf(" >");
		if (!quote && (i > 0 && mini->line[i - 1] != '>')\
				&& strncmp(mini->line + i, ">>", 2) == 0\
				&& mini->line[i + 2] != '>')
			printf(" >>");
		printf("\n");
	}
	return (0);
}
