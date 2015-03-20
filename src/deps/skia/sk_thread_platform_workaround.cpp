#include <stdint.h>

/* Just use the GCC atomic intrinsics. They're supported by the NDK toolchain,
 * have reasonable performance, and provide full memory barriers
 */
int sk_atomic_inc(int *addr) {
    return __sync_fetch_and_add(addr, 1);
}

// static inline __attribute__((always_inline)) int32_t sk_atomic_add(int32_t *addr, int32_t inc) {
//     return __sync_fetch_and_add(addr, inc);
// }

int sk_atomic_dec(int *addr) {
    return __sync_fetch_and_add(addr, -1);
}
void sk_membar_aquire__after_atomic_dec() { }
// 
// static inline __attribute__((always_inline)) int32_t sk_atomic_conditional_inc(int32_t* addr) {
//     int32_t value = *addr;
// 
//     while (true) {
//         if (value == 0) {
//             return 0;
//         }
// 
//         int32_t before = __sync_val_compare_and_swap(addr, value, value + 1);
// 
//         if (before == value) {
//             return value;
//         } else {
//             value = before;
//         }
//     }
// }
// static inline __attribute__((always_inline)) void sk_membar_aquire__after_atomic_conditional_inc() { }
