#include "mlx.h"
#include <stdio.h>

int		key_hook(int keycode, void *param)
{
	printf("Salut");
	printf("Touche %d\n", keycode);
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	void *param;
	int keycode;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	mlx_key_hook(win_ptr, &key_hook, param);
	mlx_loop(mlx_ptr);
	return (0);
}
