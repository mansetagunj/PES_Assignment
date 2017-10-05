#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef PLATFORM_KL25Z
	int printf(const char *fmt,...){return 0;}
#else
#include <stdio.h>
#endif

#endif

