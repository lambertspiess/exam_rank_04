#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

void putstr(char *s) { int i = 0; while (s[i]) { ++i; } write(1, s, i); write(1, "\n", 1); }

typedef struct window { int wid, hei; char c; } window;

typedef struct elem { char type; float x, y, r; char c; } elem;

int should_draw(float i, float j, float ex, float ey, float r, char type)
{
	float d = sqrt((i - ex) * (i - ex) + (j - ey) * (j - ey));
	if (d <= r)
	{
		if (type == 'C') { return  (1); }
		if ((r - d) < 1.00000000) { return (1); }
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2) { putstr("Error: argument"); return (1); }

	FILE *f = NULL;
	if (!(f = fopen(av[1], "r")))
		{ putstr("Error: Operation file corrupted"); return (1); }

	window w;
	if (fscanf(f, "%d %d %c\n", &w.wid, &w.hei, &w.c) != 3)
		{ putstr("Error: Operation file corrupted"); return (1); }

	if (w.wid < 1 || w.wid > 300 || w.hei < 1 || w.hei > 300)
		{ putstr("Error: Operation file corrupted"); return (1); }

	char buf[w.wid * w.hei]; for (int i = 0; i < w.wid * w.hei; ++i) { buf[i] = w.c; }

	elem e; int ret = -1;
	while ((ret = fscanf(f, "%c %f %f %f %c\n", &e.type, &e.x, &e.y, &e.r, &e.c)) == 5)
	{
		if (e.r < 0.00000000 || (e.type != 'c' && e.type != 'C'))
			{ putstr("Error: Operation file corrupted"); return (1); }
		for (int j = 0; j < w.hei; ++j)
		{
			for (int i = 0; i < w.wid; ++i)
			{
				if (should_draw((float)i, (float)j, e.x, e.y, e.r, e.type))
					buf[j * w.wid + i] = e.c;
			}
		}
	}
	if (ret != -1)
		{ putstr("Error: Operation file corrupted"); return (1); }

	for (int j = 0; j < w.hei; ++j)
	{
		write(1, buf + w.wid * j, w.wid); write(1, "\n", 1);
	}
	return (0);
}
