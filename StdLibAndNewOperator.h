#ifdef _DEBUG

	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>
	#include <crtdbg.h>
	#define LOP_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
	#include <cstdlib>
	#define LOP_NEW new
#endif

