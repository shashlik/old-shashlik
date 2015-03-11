project(bionic_libc)

set(BIONIC_LIBC_SRC_DIR ${GENERAL_SOURCE_PATH}/bionic/libc)

# Define the common source files for all the libc instances
# =========================================================
set(libc_common_SRCS
    # $(syscall_src) are below for x86
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/_exit.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/_exit_thread.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__fork.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/_waitpid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__waitid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/wait4.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__sys_clone.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/execve.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__setuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/geteuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getegid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getresuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getresgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/gettid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/readahead.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getgroups.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getpgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getppid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getsid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setsid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__setreuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__setresuid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setresgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__brk.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/kill.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/tkill.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/tgkill.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__ptrace.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__set_thread_area.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__getpriority.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setpriority.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setrlimit.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getrlimit.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getrusage.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setgroups.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setpgid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setregid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/chroot.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/prctl.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/capget.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/capset.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sigaltstack.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/acct.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/read.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/write.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/pread64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/pwrite64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__open.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__openat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/close.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lseek.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__llseek.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getpid.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__mmap2.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/munmap.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mremap.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/msync.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mprotect.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/madvise.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mlock.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/munlock.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mlockall.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/munlockall.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mincore.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__ioctl.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/readv.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/writev.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__fcntl.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/flock.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fchmod.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/dup.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/pipe.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/pipe2.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/dup2.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/select.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/ftruncate.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/ftruncate64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getdents.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fsync.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fdatasync.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fchown.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sync.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__fcntl64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__fstatfs64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sendfile.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fstatat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mkdirat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fchownat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fchmodat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/renameat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fsetxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fgetxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/flistxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fremovexattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/link.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/unlink.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/unlinkat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/chdir.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mknod.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/chmod.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/chown.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lchown.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mount.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/umount2.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fstat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/stat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lstat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/mkdir.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/readlink.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/rmdir.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/rename.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__getcwd.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/access.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/faccessat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/symlink.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/fchdir.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/truncate.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lsetxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lgetxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/listxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/llistxattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/removexattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/lremovexattr.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__statfs64.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/unshare.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/swapon.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/swapoff.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/pause.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/gettimeofday.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/settimeofday.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/times.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/nanosleep.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/clock_gettime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/clock_settime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/clock_getres.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/clock_nanosleep.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getitimer.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setitimer.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__timer_create.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__timer_settime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__timer_gettime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__timer_getoverrun.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__timer_delete.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/utimes.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/utimensat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/timerfd_create.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/timerfd_settime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/timerfd_gettime.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sigaction.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sigprocmask.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__sigsuspend.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__rt_sigaction.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__rt_sigprocmask.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__rt_sigtimedwait.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sigpending.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/signalfd4.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/socket.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/bind.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/connect.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/listen.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/accept.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getsockname.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getpeername.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/socketpair.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sendto.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/recvfrom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/shutdown.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/setsockopt.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/getsockopt.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sendmsg.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/recvmsg.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_setscheduler.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_getscheduler.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_yield.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_setparam.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_getparam.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_get_priority_max.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_get_priority_min.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_rr_get_interval.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sched_setaffinity.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__sched_getaffinity.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__getcpu.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/ioprio_set.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/ioprio_get.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/uname.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/umask.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__reboot.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__syslog.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/init_module.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/delete_module.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/klogctl.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/sysinfo.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/personality.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/perf_event_open.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/futex.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/epoll_create.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/epoll_ctl.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/epoll_wait.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/inotify_init.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/inotify_add_watch.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/inotify_rm_watch.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/poll.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/eventfd.S

# libc_common_src_files :=
    ${BIONIC_LIBC_SRC_DIR}/unistd/alarm.c
    ${BIONIC_LIBC_SRC_DIR}/unistd/exec.c
    ${BIONIC_LIBC_SRC_DIR}/unistd/fnmatch.c
    ${BIONIC_LIBC_SRC_DIR}/unistd/syslog.c
    ${BIONIC_LIBC_SRC_DIR}/unistd/system.c
    ${BIONIC_LIBC_SRC_DIR}/unistd/time.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/asprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fflush.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fgetc.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/findfp.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fputc.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fread.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/freopen.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fscanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fseek.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/ftell.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/fvwrite.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/gets.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/printf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/refill.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/rewind.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/scanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/snprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/sprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/sscanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/stdio.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/ungetc.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vasprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vfprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vfscanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vsnprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vsprintf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vscanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/vsscanf.c
    ${BIONIC_LIBC_SRC_DIR}/stdio/wbuf.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/atexit.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/ctype_.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/exit.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/getenv.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/putenv.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/setenv.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtod.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtoimax.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtol.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtoll.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtoul.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtoull.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/strtoumax.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/tolower_.c
    ${BIONIC_LIBC_SRC_DIR}/stdlib/toupper_.c
    ${BIONIC_LIBC_SRC_DIR}/string/strcasecmp.c
    ${BIONIC_LIBC_SRC_DIR}/string/strcspn.c
    ${BIONIC_LIBC_SRC_DIR}/string/strdup.c
    ${BIONIC_LIBC_SRC_DIR}/string/strpbrk.c
    ${BIONIC_LIBC_SRC_DIR}/string/strsep.c
    ${BIONIC_LIBC_SRC_DIR}/string/strspn.c
    ${BIONIC_LIBC_SRC_DIR}/string/strstr.c
    ${BIONIC_LIBC_SRC_DIR}/string/strtok.c
    ${BIONIC_LIBC_SRC_DIR}/wchar/wcswidth.c
    ${BIONIC_LIBC_SRC_DIR}/wchar/wcsxfrm.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/arc4random.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/atoi.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/atol.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/atoll.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/bindresvport.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/bionic_clone.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/clearenv.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/cpuacct.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/daemon.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/err.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ether_aton.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ether_ntoa.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/fcntl.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/fdprintf.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/flockfile.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/fork.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/fstatfs.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ftime.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ftok.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/fts.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/getdtablesize.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/gethostname.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/getpgrp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/getpriority.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/getpt.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/if_indextoname.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/if_nametoindex.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/initgroups.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ioctl.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/isatty.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/issetugid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ldexp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/lseek64.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/md5.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/memmem.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/memswap.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/name_mem.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/openat.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/open.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pathconf.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/perror.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pread.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pselect.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ptsname.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ptsname_r.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pututline.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pwrite.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/reboot.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/recv.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sched_cpualloc.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sched_cpucount.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sched_getcpu.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/semaphore.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/send.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/setegid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/seteuid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/setpgrp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/setresuid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/setreuid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/setuid.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sigblock.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/siginterrupt.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/siglist.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/signal.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/signame.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sigsetmask.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sigsuspend.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/sleep.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/statfs.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/strndup.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/strntoimax.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/strntoumax.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/strtotimeval.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/system_properties.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/system_properties_compat.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/tcgetpgrp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/tcsetpgrp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/thread_atexit.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/time64.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/umount.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/unlockpt.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/usleep.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/utmp.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/wcscoll.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/gethnamaddr.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/inet/nsap_addr.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/__dn_comp.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/__res_close.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/__res_send.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/herror.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_comp.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_data.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_debug.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_init.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_mkquery.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_query.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_send.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_state.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/resolv/res_cache.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/nsdispatch.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/getaddrinfo.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/getnameinfo.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/getservbyname.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/getservent.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/base64.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/net/getservbyport.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_name.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_parse.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_ttl.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_netint.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_print.c
    ${BIONIC_LIBC_SRC_DIR}/netbsd/nameser/ns_samedomain.c

# Fortify implementations of libc functions.
# libc_common_src_files +=
    ${BIONIC_LIBC_SRC_DIR}/bionic/__fgets_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__memcpy_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__memmove_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__memset_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strcat_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strchr_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strcpy_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strlcat_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strlcpy_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strlen_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strncat_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strncpy_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__strrchr_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__umask_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__vsnprintf_chk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__vsprintf_chk.cpp
)

set(libc_bionic_SRCS)
# libc_bionic_src_files :=
    ${BIONIC_LIBC_SRC_DIR}/bionic/abort.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/assert.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/brk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/dirent.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__errno.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/eventfd_read.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/eventfd_write.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/futimens.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/getauxval.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/getcwd.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/libc_init_common.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/libc_logging.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/libgen.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/mmap.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_attr.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_detach.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_equal.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_getcpuclockid.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_getschedparam.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_internals.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_join.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_kill.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_self.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_setname_np.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_setschedparam.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_sigmask.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/raise.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/sbrk.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/scandir.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/sched_getaffinity.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/__set_errno.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/setlocale.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/signalfd.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/sigwait.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/statvfs.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/strerror.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/strerror_r.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/strsignal.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/stubs.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/sysconf.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/tdestroy.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/tmpfile.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/wait.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/wchar.cpp
)

set(lib_tzcode_SRCS
# libc_tzcode_src_files :=
    ${BIONIC_LIBC_SRC_DIR}/tzcode/asctime.c
    ${BIONIC_LIBC_SRC_DIR}/tzcode/difftime.c
    ${BIONIC_LIBC_SRC_DIR}/tzcode/localtime.c
    ${BIONIC_LIBC_SRC_DIR}/tzcode/strftime.c
    ${BIONIC_LIBC_SRC_DIR}/tzcode/strptime.c
)

set(libc_upstream_freebsd_SRCS
# libc_upstream_freebsd_src_files :=
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/clrerr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fclose.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fdopen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/feof.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/ferror.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fgetln.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fgetpos.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fgets.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fileno.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/flags.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fopen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fpurge.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fputs.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fsetpos.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/funopen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fwalk.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/fwrite.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/getc.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/getchar.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/makebuf.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/mktemp.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/putc.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/putchar.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/puts.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/putw.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/remove.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/rget.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/setbuf.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/setbuffer.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/setvbuf.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/tempnam.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/tmpnam.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdio/wsetup.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/abs.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/getopt_long.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/imaxabs.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/imaxdiv.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/labs.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/llabs.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/qsort.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/stdlib/realpath.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcpcpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcpncpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcscasecmp.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcscspn.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsdup.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcslcat.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcslcpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsncasecmp.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsncat.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsncmp.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsncpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsnlen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcspbrk.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsspn.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsstr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcstok.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wmemchr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wmemcpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wmemmove.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wmemset.c
)

set(libc_upstream_netbsd_SRCS
# libc_upstream_netbsd_src_files :=
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/common/lib/libc/hash/sha1/sha1.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/common/lib/libc/inet/inet_addr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/compat-43/creat.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/ftw.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/nftw.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/nice.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/popen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/psignal.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/setjmperr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/gen/utime.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/inet/inet_ntoa.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/inet/inet_ntop.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/inet/inet_pton.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/isc/ev_streams.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/isc/ev_timers.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/regex/regcomp.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/regex/regerror.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/regex/regexec.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/regex/regfree.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdio/getdelim.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdio/getline.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/bsearch.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/div.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/drand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/erand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/jrand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/ldiv.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/lldiv.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/lrand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/mrand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/nrand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/_rand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/seed48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/srand48.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/tdelete.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/tfind.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/stdlib/tsearch.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/string/memccpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/string/strcasestr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/string/strcoll.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/string/strxfrm.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/unistd/killpg.c
)

set(libc_common_SRCS
    ${libc_common_SRCS}
# libc_common_src_files +=
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread-atfork.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread-rwlocks.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread-timers.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/ptrace.c
)

set(libc_static_common_SRCS
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_create.cpp
    ${BIONIC_LIBC_SRC_DIR}/bionic/pthread_key.cpp
)

# processor variant files
set(_LIBC_ARCH_COMMON_SRC_FILES
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/clone.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/_exit_with_stack_teardown.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/futex_x86.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/__get_sp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/__get_tls.c
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/_setjmp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/setjmp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/__set_tls.c
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/sigsetjmp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/syscall.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/vfork.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ffs.S
)

#ifeq ($(ARCH_X86_HAVE_SSSE3),true)
set(_LIBC_ARCH_COMMON_SRC_FILES
    ${_LIBC_ARCH_COMMON_SRC_FILES}
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-memcpy-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-memmove-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-bcopy-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strncat-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strncpy-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strlcat-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strlcpy-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strcmp-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strncmp-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strcat-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-strcpy-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-memcmp-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-wmemcmp-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-memcmp16-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-wcscat-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/ssse3-wcscpy-atom.S
)
#else
set(_LIBC_ARCH_COMMON_SRC_FILES
    ${_LIBC_ARCH_COMMON_SRC_FILES}
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/memcpy.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/memmove.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/bcopy.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/strcmp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/strncmp.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/strcat.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/memcmp.S
    ${BIONIC_LIBC_SRC_DIR}/string/memcmp16.c
    ${BIONIC_LIBC_SRC_DIR}/string/strcpy.c
    ${BIONIC_LIBC_SRC_DIR}/string/strncat.c
    ${BIONIC_LIBC_SRC_DIR}/string/strncpy.c
    ${BIONIC_LIBC_SRC_DIR}/string/strlcat.c
    ${BIONIC_LIBC_SRC_DIR}/string/strlcpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcscpy.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcscat.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wmemcmp.c
)
#endif

#ifeq ($(ARCH_X86_HAVE_SSE2),true)
set(_LIBC_ARCH_COMMON_SRC_FILES
    ${_LIBC_ARCH_COMMON_SRC_FILES}
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-memset-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-bzero-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-memchr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-memrchr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-strchr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-strrchr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-index-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-strlen-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-strnlen-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-wcschr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-wcsrchr-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-wcslen-atom.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/sse2-wcscmp-atom.S
)
#else
set(_LIBC_ARCH_COMMON_SRC_FILES
    ${_LIBC_ARCH_COMMON_SRC_FILES}
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/memset.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/strlen.S
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/string/bzero.S
    ${BIONIC_LIBC_SRC_DIR}/bionic/memrchr.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/memchr.c
    ${BIONIC_LIBC_SRC_DIR}/string/strchr.cpp
    ${BIONIC_LIBC_SRC_DIR}/string/strrchr.c
    ${BIONIC_LIBC_SRC_DIR}/string/index.c
    ${BIONIC_LIBC_SRC_DIR}/bionic/strnlen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcschr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcsrchr.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcslen.c
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd/lib/libc/string/wcscmp.c
)
#endif

set(_LIBC_ARCH_STATIC_SRC_FILES
    ${BIONIC_LIBC_SRC_DIR}/bionic/dl_iterate_phdr_static.c
)

set(_LIBC_ARCH_DYNAMIC_SRC_FILES
)

set(libc_common_SRCS ${libc_common_SRCS} ${_LIBC_ARCH_COMMON_SRC_FILES})
set(libc_common_SRCS ${libc_common_SRCS} ${_LIBC_ARCH_CPU_VARIANT_SRC_FILES})
set(libc_arch_static_SRCS ${_LIBC_ARCH_STATIC_SRC_FILES})
set(libc_arch_dynamic_SRCS ${_LIBC_ARCH_DYNAMIC_SRC_FILES})

include_directories(${BIONIC_LIBC_SRC_DIR}/private)

set(libc_common_cflags "
    -DWITH_ERRLIST
    -DANDROID_CHANGES
    -D_LIBC=1
    -DFLOATING_POINT
    -DINET6
    -DPOSIX_MISTAKE
    -DLOG_ON_HEAP_ERROR
    -Wall -Wextra")


# ifeq ($(TARGET_ARCH),x86)
  set(libc_common_cflags "${libc_common_cflags} -DSOFTFLOAT")
  set(libc_crt_target_cflags "")
#   ifeq ($(ARCH_X86_HAVE_SSE2),true)
      set(libc_crt_target_cflags "${libc_crt_target_cflags} -DUSE_SSE2=1")
#   endif
#   ifeq ($(ARCH_X86_HAVE_SSSE3),true)
      set(libc_crt_target_cflags "${libc_crt_target_cflags} -DUSE_SSSE3=1")
#   endif
# endif # x86


# Define ANDROID_SMP appropriately.
# ifeq ($(TARGET_CPU_SMP),true)
    set(libc_common_cflags "${libc_common_cflags} -DANDROID_SMP=1")
# else
#     libc_common_cflags += -DANDROID_SMP=0
# endif

set(PLATFORM_SDK_VERSION 19)
# crtbrand.c needs <stdint.h> and a #define for the platform SDK version.
set(libc_crt_target_cflags "${libc_crt_target_cflags}
    -I${BIONIC_LIBC_SRC_DIR}/include
    -DPLATFORM_SDK_VERSION=${PLATFORM_SDK_VERSION}
    ")

set(libc_common_c_includes "
        ${BIONIC_LIBC_SRC_DIR}/stdlib
        ${BIONIC_LIBC_SRC_DIR}/string
        ${BIONIC_LIBC_SRC_DIR}/stdio
        ${GENERAL_SOURCE_PATH}/safe-iop/include")

# Needed to access private/__dso_handle.h from
# crtbegin_xxx.S and crtend_xxx.S
set(libc_crt_target_cflags "
    ${BIONIC_LIBC_SRC_DIR}/private
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/include")


# Define the libc run-time (crt) support object files that must be built,
# which are needed to build all other objects (shared/static libs and
# executables)
# ==========================================================================
# ARM, MIPS, and x86 all need crtbegin_so/crtend_so.
#
# For x86, the .init section must point to a function that calls all
# entries in the .ctors section. (on ARM this is done through the
# .init_array section instead).
#
# For all the platforms, the .fini_array section must point to a function
# that will call __cxa_finalize(&__dso_handle) in order to ensure that
# static C++ destructors are properly called on dlclose().
#
# ifeq ($(TARGET_ARCH),arm)
#     libc_crt_target_so_cflags :=
# endif
# ifeq ($(TARGET_ARCH),mips)
#     libc_crt_target_so_cflags := -fPIC
# endif
# ifeq ($(TARGET_ARCH),x86)
    set(libc_crt_target_so_cflags "-fPIC")
# endif
set(libc_crt_target_so_cflags "${libc_crt_target_so_cflags} ${libc_crt_target_cflags}")
set(libc_crt_target_crtbegin_file "${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/crtbegin.c")
set(libc_crt_target_crtbegin_so_file "${BIONIC_LIBC_SRC_DIR}/arch-x86/bionic/crtbegin_so.c")


set(CRT_INTERMEDIATE_DIR "${CMAKE_CURRENT_BINARY_DIR}/crt_intermediate")
file(MAKE_DIRECTORY ${CRT_INTERMEDIATE_DIR})


# Generate crtbrand.s before crtbrand.o - see crtbrand.c for the reason behind this
add_custom_command(
    OUTPUT ${CRT_INTERMEDIATE_DIR}/crtbrand.s
    COMMAND ${CMAKE_C_COMPILER} ARGS "${libc_crt_target_so_cflags} -S -MD -MF ${CRT_INTERMEDIATE_DIR}/crtbrand.d -o ${CRT_INTERMEDIATE_DIR}/crtbrand.s ${CRT_INTERMEDIATE_DIR}/crtbrand.c"
    COMMAND sed ARGS "-i -e '/\.note\.ABI-tag/s/progbits/note/' ${CRT_INTERMEDIATE_DIR}/crtbrand.s" 
    COMMAND cp ARGS "crtbrand.d crtbrand.P"
    COMMAND sed ARGS "-e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < crtbrand.d >> crtbrand.P"
    COMMAND rm ARGS "crtbrand.d"
    COMMAND ${CMAKE_C_COMPILER} ARGS "${libc_crt_target_so_cflags} -o ${CRT_INTERMEDIATE_DIR}/crtbrand.o ${CRT_INTERMEDIATE_DIR}/crtbrand.s"
)

# See the comment in crtbrand.c for the reason why we need to generate
# crtbrand.s before generating crtbrand.o.
# GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbrand.s
# $(GEN): $(LOCAL_PATH)/bionic/crtbrand.c
#     @mkdir -p $(dir $@)
#     $(hide) $(TARGET_CC) $(libc_crt_target_so_cflags) -S \
#         -MD -MF $(@:%.s=%.d) -o $@ $<
#     $(hide) sed -i -e '/\.note\.ABI-tag/s/progbits/note/' $@
#     $(call transform-d-to-p-args,$(@:%.s=%.d),$(@:%.s=%.P))
# -include $(GEN:%.s=%.P)
# ALL_GENERATED_SOURCES += $(GEN)
# 
# GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbrand.o
# $(GEN): $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbrand.s
#     @mkdir -p $(dir $@)
#     $(hide) $(TARGET_CC) $(libc_crt_target_so_cflags) -o $@ -c $<
# ALL_GENERATED_SOURCES += $(GEN)

add_custom_command(
    OUTPUT ${CRT_INTERMEDIATE_DIR}/crtbegin_so.o
    COMMAND ${CMAKE_C_COMPILER} ARGS "${libc_crt_target_so_cflags} -S -MD -MF ${CRT_INTERMEDIATE_DIR}/crtbegin_so.d -o ${CRT_INTERMEDIATE_DIR}/crtbegin_so.o -c ${CRT_INTERMEDIATE_DIR}/crtbegin_so.c"
    COMMAND cp ARGS "${CRT_INTERMEDIATE_DIR}/crtbegin_so.d ${CRT_INTERMEDIATE_DIR}/crtbegin_so.P"
    COMMAND sed ARGS "-e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < ${CRT_INTERMEDIATE_DIR}/crtbegin_so.d >> ${CRT_INTERMEDIATE_DIR}/crtbegin_so.P"
    COMMAND rm ARGS "${CRT_INTERMEDIATE_DIR}/crtbegin_so.d"
)
# GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_so.o
# $(GEN): $(libc_crt_target_crtbegin_so_file)
#     @mkdir -p $(dir $@)
#     $(hide) $(TARGET_CC) $(libc_crt_target_so_cflags) \
#         -MD -MF $(@:%.o=%.d) -o $@ -c $<
#     $(transform-d-to-p)
# -include $(GEN:%.o=%.P)
# ALL_GENERATED_SOURCES += $(GEN)
# 
# results in the following output when running the build:
# prebuilts/gcc/linux-x86/x86/i686-linux-android-4.7/bin/i686-linux-android-gcc -fPIC  -DUSE_SSE2=1 -Ibionic/libc/include -DPLATFORM_SDK_VERSION=19 -Ibionic/libc/private -Ibionic/libc/arch-x86/include \
#     -MD -MF out/target/product/x86/obj/lib/crtbegin_so.d -o out/target/product/x86/obj/lib/crtbegin_so.o -c bionic/libc/arch-x86/bionic/crtbegin_so.c
# cp out/target/product/x86/obj/lib/crtbegin_so.d out/target/product/x86/obj/lib/crtbegin_so.P;
# sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < out/target/product/x86/obj/lib/crtbegin_so.d >> out/target/product/x86/obj/lib/crtbegin_so.P;
# rm -f out/target/product/x86/obj/lib/crtbegin_so.d

add_custom_command(
    OUTPUT ${CRT_INTERMEDIATE_DIR}/crtend_so.o
    COMMAND ${CMAKE_C_COMPILER} ARGS "${libc_crt_target_so_cflags} -S -MD -MF ${CRT_INTERMEDIATE_DIR}/crtend_so.d -o ${CRT_INTERMEDIATE_DIR}/crtend_so.o -c ${CRT_INTERMEDIATE_DIR}/crtend_so.c"
    COMMAND cp ARGS "${CRT_INTERMEDIATE_DIR}/crtend_so.d ${CRT_INTERMEDIATE_DIR}/crtend_so.P"
    COMMAND sed ARGS "-e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < ${CRT_INTERMEDIATE_DIR}/crtend_so.d >> ${CRT_INTERMEDIATE_DIR}/crtend_so.P"
    COMMAND rm ARGS "${CRT_INTERMEDIATE_DIR}/crtend_so.d"
)
# GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtend_so.o
# $(GEN): $(LOCAL_PATH)/arch-$(TARGET_ARCH)/bionic/crtend_so.S
#     @mkdir -p $(dir $@)
#     $(hide) $(TARGET_CC) $(libc_crt_target_so_cflags) \
#         -MD -MF $(@:%.o=%.d) -o $@ -c $<
#     $(transform-d-to-p)
# -include $(GEN:%.o=%.P)
# ALL_GENERATED_SOURCES += $(GEN)

install(FILES ${CRT_INTERMEDIATE_DIR}/crtbegin_so.o ${CRT_INTERMEDIATE_DIR}/crtend_so.o DESTINATION ${ANDROID_ROOT}/lib)
# The following two are installed to device
# GEN := $(TARGET_OUT_SHARED_LIBRARIES)/crtbegin_so.o
# $(GEN): $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_so.o
#     $(hide) mkdir -p $(dir $@) && cp -f $< $@
# ALL_GENERATED_SOURCES += $(GEN)
# 
# GEN := $(TARGET_OUT_SHARED_LIBRARIES)/crtend_so.o
# $(GEN): $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtend_so.o
#     $(hide) mkdir -p $(dir $@) && cp -f $< $@
# ALL_GENERATED_SOURCES += $(GEN)

add_custom_command(
    OUTPUT ${CRT_INTERMEDIATE_DIR}/crtbegin_so.o
    COMMAND ${CMAKE_C_COMPILER} ARGS "${libc_crt_target_so_cflags} -MD -MF ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.d -o ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.o -c ${libc_crt_target_crtbegin_file}"
    COMMAND cp ARGS "${CRT_INTERMEDIATE_DIR}/crtbegin_static1.d ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.P"
    COMMAND sed ARGS "-e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.d >> ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.P"
    COMMAND rm ARGS "${CRT_INTERMEDIATE_DIR}/crtbegin_static1.d"
    COMMAND ${CMAKE_C_LINK_EXECUTABLE} ARGS -r -o ${CRT_INTERMEDIATE_DIR}/crtbegin_static.o ${CRT_INTERMEDIATE_DIR}/crtbegin_static1.o ${CRT_INTERMEDIATE_DIR}/crtbrand.o
)
GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_static1.o
$(GEN): $(libc_crt_target_crtbegin_file)
    @mkdir -p $(dir $@)
    $(hide) $(TARGET_CC) $(libc_crt_target_cflags) \
        -MD -MF $(@:%.o=%.d) -o $@ -c $<
    $(transform-d-to-p)
-include $(GEN:%.o=%.P)
ALL_GENERATED_SOURCES += $(GEN)

GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_static.o
$(GEN): $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_static1.o $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbrand.o
    @mkdir -p $(dir $@)
    $(hide) $(TARGET_LD) -r -o $@ $^
ALL_GENERATED_SOURCES += $(GEN)

GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_dynamic1.o
$(GEN): $(libc_crt_target_crtbegin_file)
    @mkdir -p $(dir $@)
    $(hide) $(TARGET_CC) $(libc_crt_target_cflags) \
        -MD -MF $(@:%.o=%.d) -o $@ -c $<
    $(transform-d-to-p)
-include $(GEN:%.o=%.P)
ALL_GENERATED_SOURCES += $(GEN)

GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_dynamic.o
$(GEN): $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbegin_dynamic1.o $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtbrand.o
    @mkdir -p $(dir $@)
    $(hide) $(TARGET_LD) -r -o $@ $^
ALL_GENERATED_SOURCES += $(GEN)

# We rename crtend.o to crtend_android.o to avoid a
# name clash between gcc and bionic.
GEN := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)/crtend_android.o
$(GEN): $(LOCAL_PATH)/arch-$(TARGET_ARCH)/bionic/crtend.S
    @mkdir -p $(dir $@)
    $(hide) $(TARGET_CC) $(libc_crt_target_cflags) \
        -MD -MF $(@:%.o=%.d) -o $@ -c $<
    $(transform-d-to-p)
-include $(GEN:%.o=%.P)
ALL_GENERATED_SOURCES += $(GEN)



add_definitions(
    -DWITH_ERRLIST
    -DANDROID_CHANGES
    -D_LIBC=1
    -DFLOATING_POINT
    -DINET6
    -DPOSIX_MISTAKE
    -DLOG_ON_HEAP_ERROR
    -Wall -Wextra
# Try to catch typical 32-bit assumptions that break with 64-bit pointers.
#     -Werror=pointer-to-int-cast
#     -Werror=int-to-pointer-cast
#     -Werror=type-limits
#     -Werror
# using the dl malloc
    -DUSE_DLMALLOC

    -DSOFTFLOAT
    -DUSE_SSE2=1
    -DUSE_SSSE3=1

# Define ANDROID_SMP appropriately.
    -DANDROID_SMP=1

# crtbrand.c needs <stdint.h> and a #define for the platform SDK version.
    -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

    -fpermissive
    -D__USE_BSD
    )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(
    ${BIONIC_LIBC_SRC_DIR}
    ${BIONIC_LIBC_SRC_DIR}/stdlib
    ${BIONIC_LIBC_SRC_DIR}/string
    ${BIONIC_LIBC_SRC_DIR}/stdio
    ${BIONIC_LIBC_SRC_DIR}/include
    ${BIONIC_LIBC_SRC_DIR}/private
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/include
    ${BIONIC_LIBC_SRC_DIR}/kernel/common
    ${BIONIC_LIBC_SRC_DIR}/kernel/arch-x86
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd/libc/include
    ${BIONIC_LIBC_SRC_DIR}/upstream-freebsd
    ${BIONIC_LIBC_SRC_DIR}/upstream-netbsd
    ${GENERAL_SOURCE_PATH}/bionic/libm/include
    ${LIBCUTILS_INCLUDES}
    ${SAFE_IOP_INCLUDES})

add_library(bionic_libc SHARED ${libc_SRCS})
