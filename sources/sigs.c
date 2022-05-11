/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:16:02 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/04/21 21:46:15 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cntrl_c(int n)
{
	///kill clear shit??
//	SIGQUIT
//	SIGINT
//	EOF
	rl_on_new_line();
}
