#ifndef PGR_SEM_COPAKOND_PGR_PORTABLE_H
#define PGR_SEM_COPAKOND_PGR_PORTABLE_H

// THIS IS USED TO MAKE THIS PROGRAM WORK IN BOTH WINDOWS AND (arch) LINUX

#ifdef _WIN32
    #include "pgr.h"
#else
    #include <pgr/pgr.h>
#endif

#endif //PGR_SEM_COPAKOND_PGR_PORTABLE_H
