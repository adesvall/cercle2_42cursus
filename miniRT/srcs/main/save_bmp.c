/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:21:27 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

unsigned char	*file_header_bmp(int filesize, t_scn *scn)
{
	unsigned char	*bmpfileheader;

	if (!(bmpfileheader = (unsigned char*)malloc(14 * sizeof(unsigned char))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_memcpy(bmpfileheader, (char[]){'B', 'M', 0, 0, 0, 0, 0,
										0, 0, 0, 54, 0, 0, 0}, 14);
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	return (bmpfileheader);
}

unsigned char	*info_header_bmp(t_couple res, t_scn *scn)
{
	unsigned char	*bmpinfoheader;

	if (!(bmpinfoheader = (unsigned char*)malloc(40 * sizeof(unsigned char))))
		handle_error("Malloc failed", MALLOC_FAIL, scn);
	ft_memcpy(bmpinfoheader, (char[]){40, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 1, 0, 32, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 40);
	bmpinfoheader[4] = (unsigned char)(res.w);
	bmpinfoheader[5] = (unsigned char)(res.w >> 8);
	bmpinfoheader[6] = (unsigned char)(res.w >> 16);
	bmpinfoheader[7] = (unsigned char)(res.w >> 24);
	bmpinfoheader[8] = (unsigned char)(res.h);
	bmpinfoheader[9] = (unsigned char)(res.h >> 8);
	bmpinfoheader[10] = (unsigned char)(res.h >> 16);
	bmpinfoheader[11] = (unsigned char)(res.h >> 24);
	return (bmpinfoheader);
}

void			write_data(int f, const unsigned char *data, t_couple res)
{
	int line;

	line = res.h;
	while (--line + 1)
		write(f, data + res.w * line * 4, res.w * 4);
}

void			save_bmp(const char *fname, unsigned char *data, t_scn *scn)
{
	int				filesize;
	int				f;
	unsigned char	*bmpfileheader;
	unsigned char	*bmpinfoheader;

	filesize = 14 + 40 + 3 * scn->res.w * scn->res.h;
	f = open(fname, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
	bmpfileheader = file_header_bmp(filesize, scn);
	write(f, bmpfileheader, 14);
	free(bmpfileheader);
	bmpinfoheader = info_header_bmp(scn->res, scn);
	write(f, bmpinfoheader, 40);
	free(bmpinfoheader);
	write_data(f, data, scn->res);
	close(f);
}
