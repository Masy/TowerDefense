#include "Guardian.h"

int main(const int argc, const char **args) {
	Guardian::getInstance()->start(argc, args);
	return 0;
}
