/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:14:18 by pjerddee          #+#    #+#             */
/*   Updated: 2023/05/28 16:14:20 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_mrt	mrt;

	if (argc == 1)
		return (elog("Usage: ./minirt [file]", 1));
	mrt.qcode = 0;
	mrt.ambt = 0;
	mrt.cam = 0;
	mrt.lght = 0;
	mrt.obj = 0;
	if (parsing(&mrt, argv[1]) != 0)
		return (clean(&mrt, 1));
	setup(&mrt);
	camera(&mrt);
	render(&mrt);
	return (0);
}

// to do //
// check input value in each item => done
// check multiple item add if have to be single
// multiple light idea
// keycode
// cylinder

// bug //
// shadow have something wrong => fixed maybe
// rotation, it should be with up first, then rotatage

// define hwidth height
// normalise input
