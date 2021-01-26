/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:57:00 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int		parse_line2(char **split, t_scn *scn)
{
	if (strcmp(split[0], "pl") == 0)
		return (add_pln(split, scn));
	if (strcmp(split[0], "sq") == 0)
		return (add_sqr(split, scn));
	if (strcmp(split[0], "cy") == 0)
		return (add_cyl(split, scn, 0));
	if (strcmp(split[0], "cyc") == 0)
		return (add_cyl(split, scn, 1));
	if (strcmp(split[0], "tr") == 0)
		return (add_tri(split, scn));
	if (strcmp(split[0], "cub") == 0)
		return (add_cub(split, scn));
	printf("-line : %s - ignored.\n", split[0]);
	return (0);
}

int		parse_line(char **split, t_scn *scn)
{
	if (strcmp(split[0], "R") == 0)
		return (set_res(split, scn));
	if (strcmp(split[0], "A") == 0)
		return (set_amblum(split, scn));
	if (strcmp(split[0], "skybox") == 0)
		return (set_sky(split, scn));
	if (strcmp(split[0], "antialiasing") == 0)
		return (set_anti(split, scn));
	if (strcmp(split[0], "c") == 0)
		return (add_cam(split, scn));
	if (strcmp(split[0], "l") == 0)
		return (add_lum(split, scn, 0));
	if (strcmp(split[0], "ld") == 0)
		return (add_lum(split, scn, 1));
	if (strcmp(split[0], "sp") == 0)
		return (add_sph(split, scn));
	return (parse_line2(split, scn));
}

void	parse_fd(int fd, t_scn *scn)
{
	int		res;
	int		gnl;
	char	*line;
	char	**split;

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
		res = parse_line(split, scn);
		if (res != 0)
			printf("Wrong line starting with \"%s\".\n", split[0]);
		ft_abort(split);
		free(line);
		if (res != 0)
			handle_error("Parsing error", res, scn);
	}
	close(fd);
}

void	parse_file(t_scn *scn)
{
	int		fd;

	printf("\033[0;32mParsing...\n\033[0m");
	if ((fd = open(scn->filename, O_RDONLY)) < 0)
		handle_error("fail to open .rt file", OPEN_FAIL, scn);
	parse_fd(fd, scn);
	if (scn->cams == NULL)
		handle_error("no camera available", NO_CAMERA, scn);
	if (!scn->res.w || !scn->res.h)
		handle_error("no resolution", NO_RES, scn);
	scn->actualcam = scn->cams;
	scn->actuallum = scn->lums;
}
