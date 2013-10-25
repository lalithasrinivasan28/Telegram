#include "org_telegram_SQLite.h"

void Java_org_telegram_SQLite_SQLiteDatabase_closedb(JNIEnv *env, jobject object, int sqliteHandle) {
	sqlite3 *handle = (sqlite3 *)sqliteHandle;
	int err = sqlite3_close(handle);
	if (SQLITE_OK != err) {
		throw_sqlite3_exception(env, handle, err);
	}
}

void Java_org_telegram_SQLite_SQLiteDatabase_beginTransaction(JNIEnv *env, jobject object, int sqliteHandle) {
    sqlite3 *handle = (sqlite3 *)sqliteHandle;
    sqlite3_exec(handle, "BEGIN", 0, 0, 0);
}

void Java_org_telegram_SQLite_SQLiteDatabase_commitTransaction(JNIEnv *env, jobject object, int sqliteHandle) {
    sqlite3 *handle = (sqlite3 *)sqliteHandle;
    sqlite3_exec(handle, "COMMIT", 0, 0, 0);
}

int Java_org_telegram_SQLite_SQLiteDatabase_opendb(JNIEnv *env, jobject object, jstring fileName) {
    char const *fileNameStr = (*env)->GetStringUTFChars(env, fileName, 0);
    sqlite3 *handle = 0;
    int err = sqlite3_open(fileNameStr, &handle);
    if (SQLITE_OK != err) {
    	throw_sqlite3_exception(env, handle, err);
    }
    if (fileNameStr != 0) {
        (*env)->ReleaseStringUTFChars(env, fileName, fileNameStr);
    }
    return (int)handle;
}
