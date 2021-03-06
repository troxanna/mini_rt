/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 19:10:12 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/23 03:33:10 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# include "mlx.h"

typedef struct				s_vector
{
	float					x;
	float					y;
	float					z;
}							t_vector;

typedef struct				s_rgb
{
	int						r;
	int						g;
	int						b;
}							t_rgb;

typedef struct				s_amb_light
{
	float					ambient;
	t_rgb					color;
}							t_amb_light;

typedef struct				s_point_light
{
	float					brightness;
	t_rgb					color;
	t_vector				point_light;
	struct s_point_light	*next;
}							t_point_light;

typedef struct				s_resolution
{
	int						width;
	int						height;
}							t_resolution;

typedef struct				s_sphere
{
	t_vector				center;
	float					radius;
	struct s_sphere			*next;
	t_rgb					color;
}							t_sphere;

typedef struct				s_triangle
{
	t_vector				first_point;
	t_vector				second_point;
	t_vector				third_point;
	t_rgb					color;
	struct s_triangle		*next;
}							t_triangle;

typedef struct				s_plane
{
	t_vector				point_plane;
	t_vector				direction;
	t_rgb					color;
	struct s_plane			*next;
}							t_plane;

typedef struct				s_square
{
	t_vector				center_square;
	t_vector				direction;
	float					side;
	t_rgb					color;
	struct s_square			*next;
}							t_square;

typedef struct				s_cylinder
{
	t_vector				point_cylinder;
	t_vector				direction;
	float					diameter;
	float					height;
	t_rgb					color;
	struct s_cylinder		*next;
}							t_cylinder;

typedef struct				s_camera
{
	t_vector				origin;
	t_vector				direction;
	float					fov;
	struct s_camera			*next;
}							t_camera;

typedef struct				s_object_params
{
	t_vector				intersect_point;
	t_vector				norm;
	t_rgb					color;
	int						flag;
	float					range[2];
	float					tmp_t[2];
	float					closest_t;
}							t_object_params;

typedef struct				s_object_scene
{
	t_vector				*ray_orig;
	t_sphere				*sphere;
	t_plane					*plane;
	t_triangle				*triangle;
	t_square				*square;
	t_cylinder				*cylinder;
	t_amb_light				*amb_light;
	t_point_light			*point_light;
}							t_object_scene;

typedef struct				s_scene
{
	t_resolution			*resolution;
	t_camera				*camera;
	t_amb_light				*amb_light;
	t_point_light			*point_light;
	t_sphere				*sphere;
	t_plane					*plane;
	t_triangle				*triangle;
	t_square				*square;
	t_cylinder				*cylinder;
}							t_scene;

typedef struct				s_mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*addr;
	t_scene					*scene;
	t_camera				*camera;
	int						res_x;
	int						res_y;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_mlx;

typedef struct				s_tmp
{
	t_vector				*ray_dir;
	t_vector				*ray_orig;
	t_vector				*direction;
	t_vector				x;

}							t_tmp;

void						ft_error(int id_err);
int							close_window(void);
void						ft_bzero(void *s, size_t n);
void						create_bmp(t_mlx *data);
void						while_parse(int *i, char *line);
int							get_line(int fd, char **line);
void						ft_init_scene(t_scene *scene);
int							check_scene(t_scene *scene);
t_rgb						*new_color(int r, int g, int b);
void						init_color(t_rgb *color, int r, int g, int b);
int							create_trgb(int t, int r, int g, int b);
t_resolution				*new_resolution(int width, int height);
void						init_vector(t_vector *result,
									float x, float y, float z);
t_vector					*new_vector(float x, float y, float z);
float						vector_length(t_vector *v);
void						vector_normalize(t_vector *v);
void						scalars_mult_vectors(float scalar,
												t_vector *vector);
void						vector_addition(t_vector *result,
										t_vector *v1, t_vector *v2);
void						vector_subtraction(t_vector *result,
											t_vector *v1, t_vector *v2);
float						vector_dot_products(t_vector *v1, t_vector *v2);
void						vector_cross_products(t_vector *result,
											t_vector *v1, t_vector *v2);
t_vector					*matrix_to_world(t_vector *ray_dir,
											t_vector *camera_dir);
t_amb_light					*new_ambient_light(float bright_ambient,
														t_rgb color);
t_camera					*new_camera(t_vector origin,
								t_vector direction, float fov);
void						add_camera(t_scene *scene, t_camera *next);
void						switching_between_cameras(t_scene *scene,
										t_mlx *mlx, t_camera *camera_first);
t_point_light				*new_light(t_vector light_point,
											float bright_light, t_rgb color);
void						add_point_light(t_scene *scene,
											t_point_light *next);
t_sphere					*new_sphere(t_vector center,
								float radius, t_rgb color);
void						add_sphere(t_scene *scene, t_sphere *next);
t_plane						*new_plane(t_vector point_plane,
										t_vector direction, t_rgb color);
void						add_plane(t_scene *scene, t_plane *next);
t_triangle					*new_triangle(t_vector first_point,
							t_vector second_point,
								t_vector third_point, t_rgb color);
void						add_triangle(t_scene *scene, t_triangle *next);
t_square					*new_square(t_vector center_square,
												t_vector direction,
												float side, t_rgb color);
void						add_square(t_scene *scene, t_square *next);
t_cylinder					*new_cylinder(t_vector point_cylinder,
													t_vector direction,
													float *dh, t_rgb color);
void						add_cylinder(t_scene *scene, t_cylinder *next);
int							ft_atoi(char *str, int *i);
float						*ft_atof(char *str, int *i, float *result);
int							ft_atorgb(t_rgb *color, char *str, int *i);
int							ft_atovec(t_vector *result, char *str, int *i);
int							ft_atovec_norm(t_vector *result,
											char *str, int *i);
int							parser_object_figure(int i, char *line,
													t_scene *scene);
t_cylinder					*parser_cylinder(char *line,
										int i, t_scene *scene,
										float *tmp);
int							parser_object_scene(char *line, t_scene *scene);
int							parser_rt(char *scene_rt,
								void *mlx_ptr, t_scene *scene);
void						create_bmp(t_mlx *data);
float						s_q(float a, float b, float c, float *t);
float						iterate_object_cylinder(t_cylinder *cy,
										t_object_params *o_p,
											t_vector *r_d, t_vector *r_o);
float						iterate_object_square(t_square *square,
										t_object_params *o_p,
									t_vector *ray_dir, t_vector *ray_orig);
float						iterate_object_triangle(t_triangle *t,
										t_object_params *o_p,
									t_vector *ray_dir, t_vector *ray_orig);
float						iterate_object_sphere(t_sphere *sphere,
										t_object_params *object_params,
									t_vector *ray_dir, t_vector *ray_orig);
float						iterate_object_plane(t_plane *plane,
							t_object_params *o_p, t_vector *r_d, t_vector *r_o);
float						intersect_object(t_object_params *o_p,
									t_object_scene *o_f, t_vector *ray_dir);
int							angle_between_norm_and_light(t_vector *norm,
															t_vector *l_ray);
void						reverse_normal(t_vector *norm);
int							shadow_check(t_object_scene *o_f,
									t_vector *l_ray, t_vector *i_p);
int							get_light_point(t_object_scene *scene,
										t_object_params *obj_params);
void						my_mlx_pixel_put(t_mlx *mlx,
									int x, int y, int color);
void						ray_tracing(t_mlx *mlx, t_scene *scene);

#endif
