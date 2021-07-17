#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct window {
	int			wid, hei;
	char		c;
}				window;

typedef struct elem {
	char		type;
	float		x, y, wid, hei;
	char		c;
}				elem;

int			parse_window(FILE *f, window *w)
{
	if (fscanf(f, "%d %d %c\n", &w->wid, &w->hei, &w->c) != 3) { return (1); }
	if (w->wid <= 0 || w->wid > 300 || w->hei <= 0 || w->hei > 300) { return (1); }
	return (0);
}

int			should_draw(float x, float y, float ex, float ey, float ebrx, float ebry, char type)
{
	if (x >= ex && x <= ebrx && y >= ey && y <= ebry)
	{
		if (type == 'R')
			return (1);
		float d = 1.00000000;
		if ((x - ex < d) || (ebrx - x < d) || (y - ey < d) || (ebry - y < d))
			return (1);
	}
	return (0);
}


int			main(int ac, char **av)
{
	if (ac != 2) { printf("Error: argument\n"); return (1); }

	FILE *f;
	if ((f = fopen(av[1], "r")) == NULL) { printf("Error: Operation file corrupted\n"); return (1); }

	window w;
	if (parse_window(f, &w) != 0) { printf("Error: Operation file corrupted\n"); return (1); }

	char buf[w.wid * w.hei];
	for (int i = 0; i < (w.wid * w.hei); ++i) { buf[i] = w.c; }

	elem e; int ret;
	while ((ret = fscanf(f, "%c %f %f %f %f %c\n", &e.type, &e.x, &e.y, &e.wid, &e.hei, &e.c)) == 6)
	{
		if (e.wid <= 0.00000000 || e.hei <= 0.00000000 || (e.type != 'r' && e.type != 'R'))
			{ printf("Error: Operation file corrupted\n"); return (1); }
		float brx = e.x + e.wid; float bry = e.y + e.hei;
		for (int y = 0; y < w.hei; ++y)
		{
			for (int x = 0; x < w.wid; ++x)
			{
				if (should_draw((float)x, (float)y, e.x, e.y, brx, bry, e.type))
					buf[y * w.wid + x] = e.c;
			}
		}
	}
	if (ret != -1) { printf("Error: Operation file corrupted\n"); return (1); }

	for (int y = 0; y < w.hei; ++y)
	{
		write(1, &buf[y * w.wid], w.wid);
		write(1, "\n", 1);
	}

	return (0);
}
