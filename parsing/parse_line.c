/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:11:21 by mdalloli          #+#    #+#             */
/*   Updated: 2025/11/25 14:29:26 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static char *trim_path(char *str)
{
    char *start;
    char *end;
    char *res;
    size_t len;

    if (!str)
        return NULL;

    // Skippa spazi iniziali
    start = str;
    while (*start && (*start == ' ' || *start == '\t'))
        start++;

    // Trova fine
    end = start + ft_strlen(start);
    while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t' || *(end - 1) == '\n'))
        end--;

    len = end - start;
    res = ft_substr(start, 0, len); // alloca nuova stringa
    return res;
}


/*Estrae il percorso della texture da una linea del tipo
"NO ./path/to/texture.xpm"
Restituisce una copia della stringa del percorso*/
char *get_path(char *line)
{
    char **split;
    char *path;

    split = ft_split(line, ' ');
    if (!split || !split[1])
        print_error("Invalid texture path");

    path = trim_path(split[1]); // ora path è allocato e sicuro
    free_split(split);
    if (!path || !*path)
        print_error("Invalid texture path");
    return path;
}
/* char *get_path(char *line)
{
    char **split;
    char *path;
    int i;

    split = ft_split(line, ' ');
    if (!split || !split[1])
        print_error("Invalid texture path");

    path = trim_path(split[1]); // ora path è allocato e sicuro
    free_split(split);

    if (!path || !*path)
        print_error("Invalid texture path");

    // Stampa il percorso normale
    printf("Path: '%s'\n", path);

    // Stampa ogni carattere in esadecimale
    printf("Hex dump: ");
    i = 0;
    while (path[i])
    {
        printf("%02x ", (unsigned char)path[i]);
        i++;
    }
    printf("\n");

    return path;
} */

static void	check_xpm_extension(char *path)
{
	int	len;

	if (!path)
		print_error("Texture path is NULL");
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		print_error("Texture file must be .xpm");
}

static t_img	*load_texture(void *mlx_ptr, char *path)
{
	t_img	*tex;

	check_xpm_extension(path);
	tex = ft_malloc(sizeof(t_img), 0);
	if (!tex)
		print_error("Failed to allocate texture");
	if(open(path, O_RDONLY) < 0)
		print_error("Failed to open XPM texture");
	else
		printf("opened\n");
	tex->img_w = 64;
	tex->img_h = 64;
	tex->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->img_w, &tex->img_h);
	if (!tex->img)
		print_error("Failed to load XPM texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->l_l, &tex->endian);
	return (tex);
}

/*Analizza una singola linea del file .cub e
aggiorna i campi corrispondenti di t_game
Riconosce texture, colori e inizio della mappa.*/
void	parse_line(char *line, t_game *game)
{
	if (is_empty_line(line))
		return ;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		game->textures.north = load_texture(game->mlx_ptr, get_path(line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->textures.south = load_texture(game->mlx_ptr, get_path(line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->textures.west = load_texture(game->mlx_ptr, get_path(line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->textures.east = load_texture(game->mlx_ptr, get_path(line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling = parse_color(line + 2);
	else
	{
		game->map_started = 1;
		add_map_line(game, line);
	}
}
