/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:01:38 by adesvall          #+#    #+#             */
/*   Updated: 2021/02/11 16:06:14 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	create_window(t_scn *scn)
{
	int	size_w;
	int	size_h;

	printf("\033[0;32mCreating window...\n\033[0m");
	mlx_get_screen_size(scn->mlx, &size_w, &size_h);
	if (scn->res.w > size_w)
		scn->res.w = size_w;
	if (scn->res.h > size_h)
		scn->res.h = size_h;
	if (!(scn->mlx_win = mlx_new_window(scn->mlx,
										scn->res.w, scn->res.h, "miniRT")))
		handle_error("Fail to create Minilibx window", WINDOW_FAIL, scn);
	create_all_img(scn);
	scn->sl_obj.pos = &((t_cam*)scn->actualcam->content)->origin;
	scn->sl_obj.dir = &((t_cam*)scn->actualcam->content)->dir;
	printf("The actual Camera is selected.\n");
	mlx_mouse_hook(scn->mlx_win, mouse_press, scn);
	mlx_hook(scn->mlx_win, ClientMessage, NoEventMask, exit_and_free, scn);
	mlx_key_hook(scn->mlx_win, get_keypress, scn);
	mlx_put_image_to_window(scn->mlx, scn->mlx_win,
						((t_cam*)scn->actualcam->content)->data.img, 0, 0);
	mlx_loop(scn->mlx);
}

void	create_all_img(t_scn *scn)
{
	t_list	*ite;
	t_cam	*cam;

	ite = scn->cams;
	while (ite)
	{
		cam = (t_cam*)ite->content;
		if (!(cam->data.img = mlx_new_image(scn->mlx, scn->res.w, scn->res.h)))
			handle_error("failed to create img.", IMG_FAIL, scn);
		cam->data.addr = mlx_get_data_addr(cam->data.img,
		&cam->data.bits_per_pixel, &cam->data.line_length, &cam->data.endian);
		create_img(cam, scn);
		ite = ite->next;
	}
}

int		main(int argc, char **argv)
{
	t_scn scn;

	if (argc == 1 || argc > 3)
	{
		printf(argc == 1 ? "No arguments.\n" : "Too many arguments.\n");
		exit(1);
	}
	ft_bzero(&scn, sizeof(t_scn));
	scn.mlx = mlx_init();
	if (!ft_strend_is(scn.filename = argv[1], ".rt"))
		return (handle_error("not a .rt file", OPEN_FAIL, &scn));
	parse_file(&scn);
	printf("\033[0;32mRendering miniRT...\n\033[0m");
	if (argc == 3 && !ft_strcmp(argv[2], "-save"))
	{
		create_all_img(&scn);
		printf("Saving to save.bmp ..\n");
		save_bmp("save.bmp",
				(unsigned char*)((t_cam*)scn.cams->content)->data.addr, &scn);
		exit_and_free(&scn);
	}
	else if (argc == 2)
		create_window(&scn);
	else
		printf("Wrong arguments.\n");
}
