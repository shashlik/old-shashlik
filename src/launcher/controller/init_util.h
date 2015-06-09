#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#include <sys/socket.h>
#define ANDROID_SOCKET_DIR "/tmp/shashlik-socket"
int create_socket(const char *name, int type, mode_t perm, uid_t uid, gid_t gid);
#ifdef __cplusplus
}
#endif
