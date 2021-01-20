/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:13:40 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/18 12:21:11 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
void	check_id(t_scn *scn)
{
	if (ft_strequ(scn->split[0], "R") && !scn->resH && !scn->resW)
		parse_res(scn);
	else if (ft_strequ(scn->split[0], "A") && !scn->ambI)
		parse_ambient(scn);
	else if (ft_strequ(scn->split[0], "c"))
		parse_camera(scn);
	else if (ft_strequ(scn->split[0], "l"))
		parse_light(scn);
	else if (ft_strequ(scn->split[0], "sp"))
		parse_sphere(scn);
	else if (ft_strequ(scn->split[0], "pl"))
		parse_plane(scn);
	else if (ft_strequ(scn->split[0], "sq"))
		parse_square(scn);
	else if (ft_strequ(scn->split[0], "cy"))
		parse_cylindre(scn);
	else if (ft_strequ(scn->split[0], "tr"))
		parse_triangle(scn);
	else if (scn->split[0][0] == '#' || ft_strequ(scn->split[0], "#"))
		;
	else if (check_id_bonus(scn))
		;
	else
		handle_error("parsing error", scn);
}

void	parse_rt_file(char *rt_file, t_scn *scn)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		handle_error("fail to open scn file", scn);
	while (get_next_line(fd, scn->line) > 0)
	{
		scn->split = ft_split(scn->line, " \t\v\n\r\f");
		if (scn->split[0])
			check_id(scn);
		scn->split = free_split(scn->split);
		free(scn->line);
	}
	close(fd);
	if (scn->cam == 0)
		handle_error("no camera available", scn);
	if (!scn->resH || !scn->resH)
		handle_error("no resolution", scn);
}
*/

void	parse_file(t_scn *scn)
{
	char	*line;
	char	**split;
	int		res;
	int		gnl;
	int		fd;
	
	printf("\033[0;32mParsing...\n\033[0m");
	if ((fd = open(scn->filename, O_RDONLY)) < 0)
		handle_error("fail to open .rt file", OPEN_FAIL, scn);
	gnl = 1;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		if (!(split = ft_split(line, " \t")) || !split[0])
		{
			ft_abort(split);
			free(line);
			continue ;
		}
		res = 0;
		if (strcmp(split[0], "R") == 0)
			res = set_res(split, scn);
		else if (strcmp(split[0], "A") == 0)
			res = set_amblum(split, scn);
		else if (strcmp(split[0], "skybox") == 0)
			res = set_sky(split, scn);
		else if (strcmp(split[0], "c") == 0)
			res = add_cam(split, scn);
		else if (strcmp(split[0], "l") == 0)
			res = add_lum(split, scn, 0);
		else if (strcmp(split[0], "ld") == 0)
			res = add_lum(split, scn, 1);
		else if (strcmp(split[0], "sp") == 0)
			res = add_sph(split, scn);
		else if (strcmp(split[0], "pl") == 0)
			res = add_pln(split, scn);
		else if (strcmp(split[0], "sq") == 0)
			res = add_sqr(split, scn);
		else if (strcmp(split[0], "cy") == 0)
			res = add_cyl(split, scn, 0);
		else if (strcmp(split[0], "cyc") == 0)
			res = add_cyl(split, scn, 1);
		else if (strcmp(split[0], "tr") == 0)
			res = add_tri(split, scn);
		else if (strcmp(split[0], "cub") == 0)
			res = add_cub(split, scn);
		else
			printf("-line : %s - ignored.\n", split[0]);
		if (res != 0)
			printf("Wrong line starting with \"%s\".\n", split[0]);
		ft_abort(split);
		free(line);
		if (res != 0)
			handle_error("Parsing error", res, scn);
	}
	close(fd);
	if (scn->cams == NULL)
		handle_error("no camera available", NO_CAMERA, scn);
	if (!scn->res.W || !scn->res.H)
		handle_error("no resolution", NO_RES, scn);
	scn->actualcam = scn->cams;
	scn->actuallum = scn->lums;
}
/*
void	init_scn(t_scn *scn)
{
	scn->res.W = 1920;
	scn->res.H = 1080;
	scn->ambI = 0.05;
	scn->ambCol = (t_vect){255, 255, 255};
	scn->actualcam = 0;
	scn->ncam = 2;

	scn->cam = malloc(3 * sizeof(t_cam));
	scn->cam[0].origin = (t_vect){-300, 0, 200};
	scn->cam[0].dir = (t_vect){1, 0, -0.5};
	scn->cam[0].fov = 90;
	scn->cam[1].origin = (t_vect){0, 0, 500};
	scn->cam[1].dir = (t_vect){0, 0, -1};
	scn->cam[1].fov = 90;
	scn->cam[2].fov = 0;

	scn->sph = malloc(3 * sizeof(t_sph));
	scn->sph[0].center = (t_vect){100, -50, 50};
	scn->sph[0].radius = 30;
	scn->sph[0].color = (t_rgb){0, 140, 140};
	scn->sph[0].reflect = 0.07;
	scn->sph[0].exist = 1;
	scn->sph[1].center = (t_vect){100, -150, 0};
	scn->sph[1].radius = 30; //20
	scn->sph[1].color = (t_rgb){140, 140, 0};
	scn->sph[1].reflect = 0.07;
	scn->sph[1].exist = 1;
	scn->sph[2].exist = 0;

	scn->lum = malloc(3 * sizeof(t_lum));
	scn->lum[0].pos = (t_vect){-200, -300, 100};
	scn->lum[0].I = 0.3;
	scn->lum[0].color = (t_vect){255, 255, 255};
	scn->lum[1].pos = (t_vect){-600, 0, 0.01};
	scn->lum[1].I = 0; //.3;
	scn->lum[1].color = (t_vect){255, 255, 255};
	scn->lum[2].I = 0;
	
	scn->pln = malloc(4 * sizeof(t_pln));
	scn->pln[0].origin = (t_vect){0, 0, -30};
	scn->pln[0].normale = (t_vect){0, 0, 1};
	scn->pln[0].color = (t_rgb){72, 31, 10};
	scn->pln[0].reflect = 0.07;
	scn->pln[0].exist = 1;
	scn->pln[1].origin = (t_vect){200, 0, 0};
	scn->pln[1].normale = (t_vect){-1, 0, 0};
	scn->pln[1].color = (t_rgb){172, 131, 110};
	scn->pln[1].reflect = 0.07;
	scn->pln[1].exist = 1;
	scn->pln[2].origin = (t_vect){0, 150, 0};
	scn->pln[2].normale = (t_vect){0, -1, 0};
	scn->pln[2].color = (t_rgb){172, 131, 110};
	scn->pln[2].reflect = 0.07;
	scn->pln[2].exist = 1;
	scn->pln[3].exist = 0;

	// scn->tri = malloc(2 * sizeof(t_cam));
	// scn->tri[0].p1 = (t_vect){100, 0, 0};
	// scn->tri[0].p2 = (t_vect){100, 0, 100};
	// scn->tri[0].p3 = (t_vect){100, 50, 100};
	// scn->tri[0].color = (t_col){240, 240, 240};
	// scn->tri[0].exist = 1;
	// scn->tri[1].exist = 0;
	
	scn->cyl = malloc(2 * sizeof(t_cam));
	scn->cyl[0].origin = (t_vect){100, -50, 50};
	scn->cyl[0].dir = (t_vect){0, -0.1, 1};
	scn->cyl[0].length = 5;
	scn->cyl[0].color = (t_rgb){50, 50, 99};
	scn->cyl[0].radius = 50;
	scn->cyl[0].reflect = 0.07;
	scn->cyl[1].radius = 0;

	scn->car = malloc(4 * sizeof(t_cam));
	scn->car[0].origin = (t_vect){125, 50, 20};
	scn->car[0].normale = normalize((t_vect){0, 0, 1});
	scn->car[0].side = 50;
	scn->car[0].color = (t_rgb){200, 0, 10};
	scn->car[0].reflect = 0.07;
	scn->car[1].origin = (t_vect){100, 50, -5};
	scn->car[1].normale = normalize((t_vect){1, 0, 0});
	scn->car[1].side = 50;
	scn->car[1].color = (t_rgb){200, 0, 10};
	scn->car[1].reflect = 0.07;
	scn->car[2].origin = (t_vect){125, 25, -5};
	scn->car[2].normale = normalize((t_vect){0, -1, 0});
	scn->car[2].side = 50;
	scn->car[2].color = (t_rgb){200, 0, 10};
	scn->car[2].reflect = 0.07;
	scn->car[3].side = 0;
}*/
