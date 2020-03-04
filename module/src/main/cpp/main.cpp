#include <jni.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include "hook_main.h"

// You can remove functions you don't need

extern "C" {
#define EXPORT __attribute__((visibility("default"))) __attribute__((used))
EXPORT void nativeForkAndSpecializePre(
        JNIEnv *env, jclass clazz, jint *_uid, jint *gid, jintArray *gids, jint *runtimeFlags,
        jobjectArray *rlimits, jint *mountExternal, jstring *seInfo, jstring *niceName,
        jintArray *fdsToClose, jintArray *fdsToIgnore, jboolean *is_child_zygote,
        jstring *instructionSet, jstring *appDataDir, jstring *packageName,
        jobjectArray *packagesForUID, jstring *sandboxId) {
    // packageName, packagesForUID, sandboxId are added from Android Q beta 2, removed from beta 5
        enable_hack = isGame(env, *appDataDir);
}

EXPORT int nativeForkAndSpecializePost(JNIEnv *env, jclass clazz, jint res) {
    if (res == 0) {
        // in app process
        if (enable_hack) {
            int ret;
            pthread_t ntid;
            if ((ret = pthread_create(&ntid, NULL, hack_thread, NULL))) {
                LOGE("can't create thread: %s\n", strerror(ret));
            }
        }
    } else {
        // in zygote process, res is child pid
        // don't print log here, see https://github.com/RikkaApps/Riru/blob/77adfd6a4a6a81bfd20569c910bc4854f2f84f5e/riru-core/jni/main/jni_native_method.cpp#L55-L66
    }
    return 0;
}

EXPORT __attribute__((visibility("default"))) void specializeAppProcessPre(
        JNIEnv *env, jclass clazz, jint *_uid, jint *gid, jintArray *gids, jint *runtimeFlags,
        jobjectArray *rlimits, jint *mountExternal, jstring *seInfo, jstring *niceName,
        jboolean *startChildZygote, jstring *instructionSet, jstring *appDataDir,
        jstring *packageName, jobjectArray *packagesForUID, jstring *sandboxId) {
    // this is added from Android Q beta, but seems Google disabled this in following updates

    // packageName, packagesForUID, sandboxId are added from Android Q beta 2, removed from beta 5
}

EXPORT __attribute__((visibility("default"))) int specializeAppProcessPost(
        JNIEnv *env, jclass clazz) {
    // this is added from Android Q beta, but seems Google disabled this in following updates
    return 0;
}

EXPORT void nativeForkSystemServerPre(
        JNIEnv *env, jclass clazz, uid_t *uid, gid_t *gid, jintArray *gids, jint *runtimeFlags,
        jobjectArray *rlimits, jlong *permittedCapabilities, jlong *effectiveCapabilities) {

}

EXPORT int nativeForkSystemServerPost(JNIEnv *env, jclass clazz, jint res) {
    if (res == 0) {
        // in system server process
    } else {
        // in zygote process, res is child pid
        // don't print log here, see https://github.com/RikkaApps/Riru/blob/77adfd6a4a6a81bfd20569c910bc4854f2f84f5e/riru-core/jni/main/jni_native_method.cpp#L55-L66
    }
    return 0;
}

EXPORT int shouldSkipUid(int uid) {
    // by default, Riru only call module functions in "normal app processes" (10000 <= uid % 100000 <= 19999)
    // false = don't skip
    return false;
}

EXPORT void onModuleLoaded() {
    // called when the shared library of Riru core is loaded
}
}

