#include <fstream>
#include <iostream>
#include "laux.h"
#include "defaults.h"

#if WIN32
#include <io.h>
#define snprintf sprintf_s
#endif

#define CFG_MAX_SIZ 256
static char config_file[CFG_MAX_SIZ];



const char* config_filename()
{
#if defined(WIN32)
    if (access ("muan_conf.xml", 0 ) != -1) {
      return "muan_conf.xml";
    } else {
      snprintf(config_file, CFG_MAX_SIZ, "%s%s%s", MUAN_ROOT_DIR, "bin\\","muan_conf.xml");
      if (access (config_file, 2 ) == -1 )
       return "none";
    }
#elif defined(__APPLE__)
  snprintf(config_file, CFG_MAX_SIZ, "%s%s%s", MUAN_ROOT_DIR, "share/", "muan_conf.xml");
  if (access (config_file, F_OK ) != 0) 
    return "none";
#else // Linux
  if (access ("./muan_conf.xml", F_OK )==0) {
    return "./muan_conf.xml";
  } else {
    snprintf(config_file, CFG_MAX_SIZ, "%s%s", MUAN_ROOT_DIR, "muan_conf.xml");
    if (access (config_file, F_OK ) != 0) 
     return "none";
  }
#endif
  return config_file;
}

int test_file(const char *fname, const char *mode)
{
  FILE *fp;
  if((fp=fopen(fname, mode)) == NULL)
    return FALSE;
  fclose(fp);
  return TRUE;
}

