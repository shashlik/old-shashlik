
// So, here are some hacks we need to make it possible to run certain things on a proper linux. GID and UID are not quite so well defined here

#define AID_SYSTEM getuid()
#define AID_INSTALL AID_SYSTEM
#define AID_MEDIA_RW AID_SYSTEM

#define AGID_SYSTEM getgid()
#define AGID_MEDIA_RW AGID_SYSTEM
// #define AID_SYSTEM        1000  /* system server */
// #define AID_INSTALL       1012  /* group for installing packages */
// #define AID_MEDIA_RW      1023  /* internal media storage write access */
