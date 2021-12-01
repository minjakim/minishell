/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:35:19 by snpark            #+#    #+#             */
/*   Updated: 2021/12/01 18:16:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void
	free_declare(t_hash *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int
	remove_declare(t_hash **head, char *key)
{
	t_hash *back;

	if (*head == NULL || key == NULL)
		return (0);
	if (legal_identifier(key) == 0)
		return (1);
	back = check_declare_key(*head, key);
	if (back == *head && strcmp(key, back->key) == 0)
	{
		*head = back->next;
		free_declare(back);
	}
	if (back->next && strcmp(key, back->next->key) == 0) 
	{
		back->next = back->next->next;
		free_declare(back->next);
	}
	return (0);
}

int
	mini_unset(t_shell *mini)
{
	return (0);
//	remove_declare(&mini->env->declare, argv[1]);
//	replace_envp(mini->env, 1);
}
