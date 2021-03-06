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

    if (strcmp(mode, "r") == 0)
    {
        file->mods[MOD_READ] = 1;
        file->fd = open(pathname, O_RDONLY, 0644);
    }
    else
    if (strcmp(mode, "r+") == 0)
    {
        file->mods[MOD_READ] = 1;
        file->mods[MOD_WRITE] = 1;
        file->fd = open(pathname, O_RDWR, 0644);
    } else
    if (strcmp(mode, "w") == 0)
    {
        file->mods[MOD_WRITE] = 1;
        file->mods[MOD_CREATE] = 1;
        file->mods[MOD_TRUNCATE] = 1;
        file->fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else
    if (strcmp(mode, "w+") == 0) {
        file->mods[MOD_READ] = 1;
        file->mods[MOD_WRITE] = 1;
        file->mods[MOD_CREATE] = 1;
        file->mods[MOD_TRUNCATE] = 1;
        file->fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
    } else
    if (strcmp(mode, "a") == 0) {
        file->mods[MOD_APPEND] = 1;
        file->mods[MOD_CREATE] = 1;
        file->fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else
    if (strcmp(mode, "a+") == 0)
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
    file->fileCursor = lseek(file->fd, 0, SEEK_CUR);
    file->bufferCursor = getInBufferPosition(file);
    file->bufferOffset = getBufferOffset(file);
    file->path = copyString(pathname);
    if (file->path == NULL)
    {
        free(file);
        return NULL;
    }

    // init buffer
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
    long correspondingBufferOffset = getBufferOffset(stream);
    if (correspondingBufferOffset != stream->bufferOffset || stream->readFromFile == 0)
    {
        // invalidate buffer, maybe fflush
        int byteRead = read(stream->fd, stream->buffer, BUFFER_SIZE);
        if (byteRead < 0)
        {
            stream->errorNo = 1;
            return SO_EOF;
        }
        stream->bufferOffset = getBufferOffset(stream);
        stream->bufferCursor = getInBufferPosition(stream);
        stream->readFromFile = 1;
    }
    int charFromFile = (unsigned char) stream->buffer[stream->bufferCursor];
    stream->fileCursor += 1;
    stream->bufferCursor += 1;
    return charFromFile;
}

int so_fputc(int c, SO_FILE *stream) {
    // TODO
    
    stream->writtenIntoFile = 1;
    long correspondingBufferOffset = getBufferOffset(stream);
    // printf("%d\n", correspondingBufferOffset != stream->bufferOffset);
    if (correspondingBufferOffset != stream->bufferOffset)
    {
        if (so_fflush(stream) == SO_EOF) {
            stream->errorNo = 1;
            return SO_EOF;
        }
        stream->bufferOffset = getBufferOffset(stream);
        stream->bufferCursor = getInBufferPosition(stream);
    }
    stream->bytesWritten += 1;
    stream->buffer[stream->bufferCursor] = c;
    stream->bufferCursor += 1;
    stream->fileCursor += 1;

    return c;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    // TODO
    return 0;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    // TODO
    stream->writtenIntoFile = 1;
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
    if (stream == NULL) return SO_EOF;
    if (stream->writtenIntoFile == 1)
    {
        int bytesWritten = write(stream->fd, stream->buffer, stream->bytesWritten);
        stream->writtenIntoFile = 0;
        stream->bytesWritten = 0;
        if (bytesWritten == -1)
        {
            stream->errorNo = 1;
            return SO_EOF;
        }
    }
    return 0;
}

int so_fclose(SO_FILE *stream)
{
    int flushed = so_fflush(stream);
    if (flushed == SO_EOF) {
        free(stream->buffer);
        free(stream->path);
        free(stream);
        return SO_EOF;
    }

    int closeStatus = close(stream->fd);
    free(stream->buffer);
    free(stream->path);
    free(stream);
    if (closeStatus < 0)
    {
        return SO_EOF;
    }
    return 0;
}

long so_ftell(SO_FILE *stream) {
    if (stream == NULL) return -1;
    return stream->fileCursor;
}

int so_feof(SO_FILE *stream) {
    return stream->errorNo;
}

int so_ferror(SO_FILE *stream) {
    return stream->errorNo;
}

char *copyString(const char *string)
{
	char *copy = (char *)calloc(strlen(string) + 1, sizeof(char));
	if (copy == NULL) return copy;
    strcpy(copy, string);
	return copy;
}

int getBufferOffset (SO_FILE * file) {
    return BUFFER_SIZE * (file->fileCursor / BUFFER_SIZE);
}

int getInBufferPosition(SO_FILE * file) {
    return file->fileCursor % BUFFER_SIZE;
}