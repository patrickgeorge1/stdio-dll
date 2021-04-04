/*
 * Operating System Executable Loader header
 *
 * 2019, Operating Systems
 */

#ifndef SO_STDIO_H
#define SO_STDIO_H

#if defined(__linux__)
#define FUNC_DECL_PREFIX
#elif defined(_WIN32)
#include <Windows.h>

#ifdef DLL_EXPORTS
#define FUNC_DECL_PREFIX __declspec(dllexport)
#else
#define FUNC_DECL_PREFIX __declspec(dllimport)
#endif

#else
#error "Unknown platform"
#endif

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

#define SO_EOF (-1)


#define MOD_READ 0
#define MOD_WRITE 1
#define MOD_APPEND 2
#define MOD_CREATE 3
#define MOD_TRUNCATE 4

#define BUFFER_SIZE 4096
#define PATH_SIZE 100


// HERE
struct _so_file
{
    int fd;
    int errorNo;
    char * path;
    char * buffer;
    long fileCursor;
    long bufferOffset;
    int bufferCursor;
    int writtenIntoFile;
    int readFromFile;
    int mods[5];
};
typedef struct _so_file SO_FILE;



FUNC_DECL_PREFIX SO_FILE *so_fopen(const char *pathname, const char *mode);
FUNC_DECL_PREFIX int so_fclose(SO_FILE *stream);

#if defined(__linux__)
FUNC_DECL_PREFIX int so_fileno(SO_FILE *stream);
#elif defined(_WIN32)
FUNC_DECL_PREFIX HANDLE so_fileno(SO_FILE *stream);
#else
#error "Unknown platform"
#endif


FUNC_DECL_PREFIX int so_fflush(SO_FILE *stream);

FUNC_DECL_PREFIX int so_fseek(SO_FILE *stream, long offset, int whence);
FUNC_DECL_PREFIX long so_ftell(SO_FILE *stream);

FUNC_DECL_PREFIX
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

FUNC_DECL_PREFIX
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

FUNC_DECL_PREFIX int so_fgetc(SO_FILE *stream);
FUNC_DECL_PREFIX int so_fputc(int c, SO_FILE *stream);

FUNC_DECL_PREFIX int so_feof(SO_FILE *stream);
FUNC_DECL_PREFIX int so_ferror(SO_FILE *stream);

FUNC_DECL_PREFIX SO_FILE *so_popen(const char *command, const char *type);
FUNC_DECL_PREFIX int so_pclose(SO_FILE *stream);

char *copyString(const char *string);
int getBufferOffset (SO_FILE * file);
int getInBufferPosition(SO_FILE * file);
#endif /* SO_STDIO_H */
