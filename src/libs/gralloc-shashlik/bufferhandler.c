#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/*
 * Taken from weston shared/os-compatibility.c
 */

static int
set_cloexec_or_close(int fd)
{
    long flags;
    int derp;

    if (fd == -1)
        return -5;

    flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        derp = -6;
        goto err;
    }

    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1) {
        derp = -7;
        goto err;
    }

    return fd;

err:
    close(fd);
    return derp;
}

/*
 * Taken from weston shared/os-compatibility.c
 */

static int
create_tmpfile_cloexec(char *tmpname)
{
    int fd;

#ifdef HAVE_MKOSTEMP
    fd = mkostemp(tmpname, O_CLOEXEC);
    if (fd >= 0)
        unlink(tmpname);
#else
    fd = mkstemp(tmpname);
    if (fd >= 0) {
        fd = set_cloexec_or_close(fd);
        unlink(tmpname);
    }
#endif

    return fd;
}

/*
 * Taken from weston shared/os-compatibility.c
 *
 * Create a new, unique, anonymous file of the given size, and
 * return the file descriptor for it. The file descriptor is set
 * CLOEXEC. The file is immediately suitable for mmap()'ing
 * the given size at offset zero.
 *
 * The file should not have a permanent backing store like a disk,
 * but may have if XDG_RUNTIME_DIR is not properly implemented in OS.
 *
 * The file name is deleted from the file system.
 *
 * The file is suitable for buffer sharing between processes by
 * transmitting the file descriptor over Unix sockets using the
 * SCM_RIGHTS methods.
 *
 * If the C library implements posix_fallocate(), it is used to
 * guarantee that disk space is available for the file at the
 * given size. If disk space is insufficent, errno is set to ENOSPC.
 * If posix_fallocate() is not supported, program may receive
 * SIGBUS on accessing mmap()'ed file contents instead.
 */
int
os_create_anonymous_file(off_t size)
{
    static const char template[] = "/kwayland-gralloc-shared-XXXXXX";
    const char *path;
    char *name;
    int fd;
    int ret;

    path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        errno = ENOENT;
        return -4;
    }

    name = malloc(strlen(path) + sizeof(template));
    if (!name)
        return -3;

    strcpy(name, path);
    strcat(name, template);

    fd = create_tmpfile_cloexec(name);

    free(name);

    if (fd < 0)
        return -2;

    ret = ftruncate(fd, size);
    if (ret < 0) {
        close(fd);
        return -errno;
    }

    return fd;
}
