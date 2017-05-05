#ifndef NODE_HEADERS_H
#define NODE_HEADERS_H

#if !defined(WIN32) && !defined(ENABLE_DFB)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <v8-util.h>
#include <uv.h>
#if !defined(WIN32) && !defined(ENABLE_DFB)
#pragma GCC diagnostic pop
#endif

namespace node {

NODE_EXTERN extern v8::Isolate* node_isolate;
NODE_EXTERN extern bool node_is_initialized;

NODE_EXTERN void StartDebug(Environment* env, const char* path,bool wait);
NODE_EXTERN void EnableDebug(Environment* env);
NODE_EXTERN v8::Isolate* CreateIsolate();
NODE_EXTERN bool ShouldAbortOnUncaughtException(v8::Isolate* isolate);

}

#ifdef WIN32
#define USE_STD_THREADS
#include <mutex>
#include <condition_variable>
#endif

#endif

