/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltkache <oltkache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:51:22 by oltkache          #+#    #+#             */
/*   Updated: 2018/04/20 21:03:38 by oltkache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SSL_DES_H
# define __SSL_DES_H

# define BASE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_elem
{
	int				p;
	int				prev_rd;
	int				rd;
	unsigned char	*str;
	unsigned char	*prev;
	int				b;
}					t_elem;

typedef struct		s_h
{
	int					*f;
	unsigned long long	k;
	unsigned long long	v;
	char				*key;
	char				*iv;
}					t_h;

typedef struct		s_k
{
	unsigned long long	k1;
	unsigned long long	k2;
	unsigned long long	k3;
	char				*keys[3];
}					t_k;

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_memdel(void **ap);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *str, int c, size_t len);
int					ft_isascii(int c);
char				*ft_strdup(const char *s1);
void				base64(unsigned char *str, int fd, int k);
int					ft_flags(char **argv, int *in, int *out);
unsigned char		*reall(unsigned char *str, unsigned char *res);
void				ft_h(int *res, unsigned char **s);
void				rev64(unsigned char **s, unsigned char **r, int *g);
void				ft_64(char **argv);
int					*ft_int_ar(char *file, int n);
unsigned long long	ft_strtol(char *str);
unsigned long long	ft_pc(unsigned long long a, int n);
unsigned long long	ft_ip_p(unsigned long long a, int n);
unsigned long long	ft_e_sel(unsigned long long a);
unsigned long long	*ft_subkeys(unsigned long long k);
unsigned long long	ft_s1(unsigned long long a, unsigned long long res);
unsigned long long	ft_s2(unsigned long long a, unsigned long long res);
unsigned long long	ft_s3(unsigned long long a, unsigned long long res);
unsigned long long	ft_s4(unsigned long long a, unsigned long long res);
unsigned long long	ft_s_modif(unsigned long long a);
unsigned long long	ft_message(unsigned long long m, unsigned long long k1);
void				ft_des_ecb(char **argv, int ch);
void				ft_b64(unsigned char *str, int l, int out, int *b);
void				ft_read_key(char **key);
void				ft_pad_key(char **key);
void				ft_pad_m(unsigned long long *c, int *rd, int t);
int					ft_m(unsigned char *str, int *i, int l,
	unsigned long long *m);
unsigned long long	ft_message(unsigned long long m, unsigned long long k1);
unsigned long long	ft_message_r(unsigned long long m, unsigned long long k1);
void				ft_des_flags(int **f, char **argv, char **key);
void				ft_str_hex(t_elem *new, t_k k);
void				ft_unpad(unsigned char **str, int *rd);
void				ft_close(int in, int out);
void				ft_ecb_out(int prev_rd, unsigned char *str, int *f, int *b);
void				ft_h2(int prev_rd, t_k k,
	unsigned char **str);
void				ft_ecb_h(t_elem *new, int *f, t_k k);
int					ft_break_key(t_k *k, char *key, int ch);
void				des_ecb_d(t_elem *new, t_k k, int f);
void				ft_h1(int *r, unsigned long long c, unsigned char **str,
	t_k k);
void				ft_str_hex_cbc(unsigned long long k, t_elem *new,
	unsigned long long *v, int ch);
void				ft_des_cbc(char **argv);
void				ft_del(t_elem new, int *f);
void				des_cbc_d(t_elem *new, unsigned long long k,
	unsigned long long *v, int ch);
void				ft_h1_cbc(int *r, unsigned long long *c,
	unsigned char **str, unsigned long long k);
void				ft_cbc(t_elem *new, int *f, unsigned long long k,
	unsigned long long *v);
void				ft_pad24(t_elem *new, unsigned long long c,
	unsigned long long *v, unsigned long long k);
void				ft_cpy(unsigned char **dst, unsigned char *src, int len);
int					*d_64(unsigned char *s, int *prev_rd);
void				ft_64d(int *f, t_k k);
void				ft_64d_cbc(t_h h);
void				ft_new(t_elem *new, int *f, int n);
void				ft_des3(char **argv);
int					ft_2(int k, unsigned char **r, unsigned char **buf, int i);
void				ft_read(int *f, int *i);
void				ft_key_iv(char **k, unsigned long long *l, char *argv,
	int ch);
void				ft_des_ecb_h(char **argv, int **f, t_k *k, int ch);
void				ft_cbc_h(t_h *h, char **argv, int ch);
void				ft_b64_d(t_elem *new);
void				ft_cbc_flags(t_h *h, char **argv, int ch);
void				ft_cbc_h2(t_elem new, unsigned long long k,
	unsigned long long v);
void				ft_get_keys(t_k *k, int num_k);
void				ft_cbc_h3(t_h *h, char **argv, t_k *k);
void				des_cbc_d3(t_elem *new, t_k k, unsigned long long *v);
void				ft_h1_cbc3(int *r, unsigned long long *c,
	unsigned char **str, t_k k);

#endif
