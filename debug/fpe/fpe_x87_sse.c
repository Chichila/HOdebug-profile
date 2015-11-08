#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _FENV_H
#include <fenv.h>
#endif

#include "fpe_x87_sse.h"

/* on x86 set_fpe_x87_sse_ enables trapping of OVERFLOW, DIVBYZERO, INVALID
   in x87 FPU and SSE */

int set_fpe_x87_sse_(void)
{
  int retcode;
  
  retcode = feenableexcept(FE_OVERFLOW|FE_DIVBYZERO|FE_INVALID);

  return(retcode);
}

/* on x86 clear_fpe_x87_sse_ disables trapping of OVERFLOW, DIVBYZERO, INVALID
   in x87 FPU and SSE */

int clear_fpe_x87_sse_(void)
{
  int retcode;

  retcode = feclearexcept(FE_ALL_EXCEPT);
  retcode = fedisableexcept(FE_ALL_EXCEPT);

  return(retcode);
}
