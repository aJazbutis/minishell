/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexius.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:07:15 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/04/22 19:44:52 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXIUS_H
#define LEXIUS_H

enum e_state
{
	GENERAL,
	IN_ESC_SQ,
	IN_F_NAME,
	IN_Q,
	IN_QQ
};

#endif
