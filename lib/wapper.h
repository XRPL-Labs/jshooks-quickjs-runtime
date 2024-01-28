#include "../quickjs.h"

// quickjs-libc.h
JSModuleDef *js_init_module_std(JSContext *ctx, const char *module_name);
JSModuleDef *js_init_module_os(JSContext *ctx, const char *module_name);
void js_std_add_console(JSContext *ctx);
void js_std_loop(JSContext *ctx);
void js_std_init_handlers(JSRuntime *rt);
void js_std_free_handlers(JSRuntime *rt);
void js_std_dump_error(JSContext *ctx);
uint8_t *js_load_file(JSContext *ctx, size_t *pbuf_len, const char *filename);
int js_module_set_import_meta(JSContext *ctx, JSValueConst func_val,
                              JS_BOOL use_realpath, JS_BOOL is_main);
JSModuleDef *js_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque);
void js_std_eval_binary(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                        int flags);
void js_std_promise_rejection_tracker(JSContext *ctx, JSValueConst promise,
                                      JSValueConst reason,
                                      JS_BOOL is_handled, void *opaque);

//ex
int JS_ValueGetTag_real(JSValue v);

void JS_FreeValue_real(JSContext *ctx, JSValue v);

void JS_FreeValueRT_real(JSRuntime *rt, JSValue v);

JSValue JS_DupValue_real(JSContext *ctx, JSValue v);

JSValue JS_DupValueRT_real(JSRuntime *rt, JSValueConst v);

JSValue JS_NewFloat64_real(JSContext *ctx, double d);

JSValue JS_NewInt32_real(JSContext *ctx, int32_t val);
JSValue JS_NewInt64_real(JSContext *ctx, int64_t val);

JSValue JS_NewBool_real(JSContext *ctx, JS_BOOL val);

JS_BOOL JS_VALUE_IS_NAN_real(JSValue v);

double JS_VALUE_GET_FLOAT64_real(JSValue v);

int JS_VALUE_GET_NORM_TAG_real(JSValue v);

void *JS_VALUE_GET_PTR_real(JSValue v);

JS_BOOL JS_IsNumber_real(JSValueConst v);

JS_BOOL JS_IsBigInt_real(JSContext *ctx, JSValueConst v);

JS_BOOL JS_IsBigFloat_real(JSValueConst v);

JS_BOOL JS_IsBigDecimal_real(JSValueConst v);

JS_BOOL JS_IsBool_real(JSValueConst v);

JS_BOOL JS_IsNull_real(JSValueConst v);

JS_BOOL JS_IsUndefined_real(JSValueConst v);

JS_BOOL JS_IsException_real(JSValueConst v);

JS_BOOL JS_IsUninitialized_real(JSValueConst v);

JS_BOOL JS_IsString_real(JSValueConst v);

JS_BOOL JS_IsSymbol_real(JSValueConst v);

JS_BOOL JS_IsObject_real(JSValueConst v);

int JS_IsPromise(JSContext *ctx, JSValueConst val);

JSValue JS_GetPromiseResult_real(JSContext *ctx, JSValueConst this_val);

int JS_ToUint32_real(JSContext *ctx, uint32_t *pres, JSValueConst val);

int JS_SetProperty_real(JSContext *ctx, JSValueConst this_obj, JSAtom prop, JSValue val);

JSValue JS_NewCFunction_real(JSContext *ctx, JSCFunction *func, const char *name,int length);

JSValue JS_NewCFunctionMagic_real(JSContext *ctx, JSCFunctionMagic *func, const char *name, int length, JSCFunctionEnum cproto, int magic);

int js_eval_buf(JSContext *ctx, const void *buf, int buf_len, const char *filename, int eval_flags);

void *memcpy(void *str1, const void *str2, size_t n);

JSValue js_undefined();

JSValue js_exception();

JSValue js_null();