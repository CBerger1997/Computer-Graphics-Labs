#include "Scene.h"

int main (int argc, char** argv)
{
	srand (time (NULL));

	Scene scene;

	scene.Init ();

	scene.RunScene ();

	scene.Deinit ();

	return 0;
}