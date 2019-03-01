#include "execute.h"

int main(int argc, char* argv[]) {
	return Execute( new Start(),
		640,
		480
	).Run();
}