/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjumelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:35:07 by cjumelin          #+#    #+#             */
/*   Updated: 2017/07/27 17:33:47 by cjumelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

static int	ft_check(unsigned long long *t)
{
	while (*t && !(*t & 0x8888))
		*t <<= 1;
	while (*t && !(*t & 0xF000))
		*t <<= 4;
	return (*t == 0x8888 || *t == 0xF000 || *t == 0xCC00 ||
			*t == 0x8E00 || *t == 0x44C0 || *t == 0xE200 || *t == 0xC880 ||
			*t == 0x4E00 || *t == 0x8C80 || *t == 0xE400 || *t == 0x4C40 ||
			*t == 0x2E00 || *t == 0x88C0 || *t == 0xE800 || *t == 0xC440 ||
			*t == 0x4C80 || *t == 0xC600 || *t == 0x8C40 || *t == 0x6C00);
}

static int	ft_wtf(long long *m, unsigned long long *t, long *r, long long w)
{
	long long	x;
	long long	y;
	long long	d;
	int			u;

	y = -1;
	while ((++y < (w - 3) || (y < w && !(*t & (0Xfull << 4 * (3 - w + y))))) &&
		(x = -1))
		while (((++x < (w - 3) || (x < w && !(*t &
			((0x1111ull << (3 - w + x)))))) && !(d = 0)))
		{
			while (!((m[(y + d) / (64 / w)] << ((y + d) % (64 / w) * w + x)) &
				((*t << (d * 4 + 48)) & 0xF000000000000000ll)) && d != 4)
				++d;
			if (d == 4 && !(u = 0))
				while (u < 2 && d-- && ((m[(y + d) / (64 / w)] ^=
					((*t & (0xf000ull >> (d * 4))) <<
					(d * 4 + 48)) >> ((y + d) % (64 / w) * w + x)) || 1))
					if (!d && ((!u && (!t[1] || ft_wtf(m, t + 1, r + 1, w))) ||
						!(++u) || !(d = 4)))
						return ((*r = x + y * w) || 1);
		}
	return (0);
}

static int	ft_wtprint(unsigned long long *t, long *r, long w, char *fd)
{
	char		s[w * w];
	long		i;
	long		b;
	long		d;

	if (!t || (i = 0))
	{
		write(1, "error\n", 6);
		return (close((int)fd) || 1);
	}
	while (i < w * w || !(i -= i + 1) || !(b = -1))
		s[i++] = '.';
	while ((t[++i] && (d = -1)) || !(i -= i + 1))
		while (++d < 4 && (b -= b + 1))
			while (++b < 4)
				if (((t[i] << (4 * d + b)) & 0x8000))
					s[r[i] + d * w + b] = 'A' + i;
	while (++i < w * w)
	{
		write(1, s + i, 1);
		if (i % w == w - 1)
			write(1, "\n", 1);
	}
	return (0);
}

int			main(int e, char **argv)
{
	char				buf;
	long long			m[10000];
	unsigned long long	t[10000];
	long				r[10000];
	int					i;

	if (e != 2 || !(i = -1))
		write(1, "usage: fillit source\n", sizeof("usage: fillit sourcen"));
	if (e != 2 || !(e -= e + 1))
		return (0);
	if (-1 == (int)(argv[2] = (char *)(long long)open(argv[1], O_RDONLY)))
		return (ft_wtprint(0, 0, 0, 0));
	while (++i < 10000 || (i = 0))
		(m[i] = 0) || (t[i] -= t[i]) || (r[i] -= r[i]);
	while ((read((int)argv[2], &buf, 1)) &&
			(++e % 21 != 20 || ft_check(t + i++)))
		if ((e % 21 != 20) && (e % 21 % 5 != 4) ? (buf != '.' && buf != '#') ||
			((t[i] = (t[i] << 1) + (buf == '#')) && 0) : buf != '\n')
			return (ft_wtprint(0, 0, 0, argv[2]));
	if (e % 21 != 19 || !ft_check(t + i++) || (t[i] -= t[i]) || !(e = (int)
	".\2\3\4\4\5\5\6\6\6\7\7\7\10\10\10\10\11\11\11\11\12\12\12\12\12\12"[i]))
		return (ft_wtprint(0, 0, 0, argv[2]));
	while (!ft_wtf(m, t, r, e) && e < 64)
		e++;
	return ((close((int)argv[2]) && 0) || ft_wtprint(t, r, e, 0));
}
