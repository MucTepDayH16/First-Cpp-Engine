#include "execute.h"

int main(int argc, char* argv[]) {
	return Execute( new Start(),
		1280,
		760
	).Run();
}