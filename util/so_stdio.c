#include "so_stdio.h"

int so_fileno(SO_FILE *stream) {
    return stream->fd;
}


SO_FILE *so_fopen(const char *pathname, const char *mode) {
    SO_FILE * file = calloc(1, sizeof(SO_FILE));
    if (file == NULL)
    {
        return NULL;
    }


    if (strcmp(mode, "r"))
    {
        file->mods[MOD_READ] = 1;
        file->fd = open(pathname, O_RDONLY, 0644);
    }
    else
    if (strcmp(mode, "r+"))
    {
        file->mods[MOD_READ] = 1;
        file->mods[MOD_WRITE] = 1;
        file->fd = open(pathname, O_RDWR, 0644);
    } else
    if (strcmp(mode, "w"))
    {
        file->mods[MOD_WRITE] = 1;
        file->mods[MOD_CREATE] = 1;
        file->mods[MOD_TRUNCATE] = 1;
        file->fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else
    if (strcmp(mode, "w+")) {
        file->mods[MOD_READ] = 1;
        file->mods[MOD_WRITE] = 1;
        file->mods[MOD_CREATE] = 1;
        file->mods[MOD_TRUNCATE] = 1;
        file->fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
    } else
    if (strcmp(mode, "a")) {
        file->mods[MOD_APPEND] = 1;
        file->mods[MOD_CREATE] = 1;
        file->fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else
    if (strcmp(mode, "a+"))
    {
        file->mods[MOD_APPEND] = 1;
        file->mods[MOD_READ] = 1;
        file->mods[MOD_CREATE] = 1;
        file->fd = open(pathname, O_RDWR | O_CREAT | O_APPEND, 0644);
    } else {
        free(file);
        return NULL;
    }


    if (file->fd < 0)
    {
        free(file);
        return NULL;
    }
    file->errorNo = 0;
    file->fileCursor = 0;
    file->bufferCursor = 0;
    file->path = copyString(pathname);
    if (file->path == NULL)
    {
        free(file);
        return NULL;
    }
    file->buffer = (char *) calloc(BUFFER_SIZE, sizeof(char));
    if (file->buffer == NULL)
    {
        free(file->path);
        free(file);
        return NULL;
    }

    return file;
}

int so_fgetc(SO_FILE *stream) {
    // TODO
    return 0;
}

int so_fputc(int c, SO_FILE *stream) {
    // TODO
    return 0;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    // TODO
    return 0;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    // TODO
    return 0;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
    // TODO
    return 0;
}

SO_FILE *so_popen(const char *command, const char *type)
{
    // TODO
    return NULL;
}

int so_pclose(SO_FILE *stream)
{
    // TODO
    return 0;
}

int so_fflush(SO_FILE *stream)
{
    // TODO
    return 0;
}

int so_fclose(SO_FILE *stream)
{
    // TODO
    return 0;
}

long so_ftell(SO_FILE *stream) {
    // TODO
    return 0;
}

int so_feof(SO_FILE *stream) {
    // TODO
    return 0;
}

int so_ferror(SO_FILE *stream) {
    // TODO
    return 0;
}

char *copyString(const char *string)
{
	char *copy = (char *)calloc(strlen(string) + 1, sizeof(char));
	if (copy == NULL) return copy;
    strcpy(copy, string);
	return copy;
}