/*
 * c-periphery
 * https://github.com/vsergeev/c-periphery
 * License: MIT
 */

#ifndef _PERIPHERY_VERSION_H
#define _PERIPHERY_VERSION_H

#define PERIPHERY_VERSION_MAJOR 1
#define PERIPHERY_VERSION_MINOR 1
#define PERIPHERY_VERSION_PATCH 1

#ifndef PERIPHERY_VERSION_COMMIT
#define PERIPHERY_VERSION_COMMIT "unknown"
#endif

typedef struct periphery_version {
    unsigned int major;
    unsigned int minor;
    unsigned int patch;
    const char *commit_id;
} periphery_version_t;

const char *periphery_version(void);

const periphery_version_t *periphery_version_info(void);

#endif

