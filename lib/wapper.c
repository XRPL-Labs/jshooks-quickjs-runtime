#include "wapper.h"
#include "../quickjs.c"

int JS_ValueGetTag_real(JSValue v) {
    return JS_VALUE_GET_TAG(v);
}

void JS_FreeValue_real(JSContext *ctx, JSValue v) {
    JS_FreeValue(ctx, v);
}

void JS_FreeValueRT_real(JSRuntime *rt, JSValue v) {
    return JS_FreeValueRT(rt, v);
}

JSValue JS_DupValue_real(JSContext *ctx, JSValue v) {
    return JS_DupValue(ctx, v);
}

JSValue JS_DupValueRT_real(JSRuntime *rt, JSValueConst v) {
    return JS_DupValueRT(rt, v);
}

JSValue JS_NewFloat64_real(JSContext *ctx, double d) {
    return JS_NewFloat64(ctx, d);
}

JSValue JS_NewInt32_real(JSContext *ctx, int32_t val) {
    return JS_NewInt32(ctx, val);
}

JSValue JS_NewInt64_real(JSContext *ctx, int64_t val) {
    return JS_NewInt64(ctx, val);
}

JSValue JS_NewBool_real(JSContext *ctx, JS_BOOL val) {
    return JS_NewBool(ctx, val) ;
}

JS_BOOL JS_VALUE_IS_NAN_real(JSValue v) {
    return JS_VALUE_IS_NAN(v);
}

double JS_VALUE_GET_FLOAT64_real(JSValue v) {
    return JS_VALUE_GET_FLOAT64(v);
}

int JS_VALUE_GET_NORM_TAG_real(JSValue v) {
    return JS_VALUE_GET_NORM_TAG(v);
}

JS_BOOL JS_IsNumber_real(JSValueConst v) {
    return JS_IsNumber(v);
}

JS_BOOL JS_IsBigInt_real(JSContext *ctx, JSValueConst v) {
    return JS_IsBigInt(ctx, v);
}

JS_BOOL JS_IsBigFloat_real(JSValueConst v) {
    return JS_IsBigFloat(v);
}

JS_BOOL JS_IsBigDecimal_real(JSValueConst v) {
    return JS_IsBigDecimal(v);
}

JS_BOOL JS_IsBool_real(JSValueConst v) {
    return JS_IsBool(v);
}

JS_BOOL JS_IsNull_real(JSValueConst v) {
    return JS_IsNull(v);
}

JS_BOOL JS_IsUndefined_real(JSValueConst v) {
    return JS_IsUndefined(v);
}

JS_BOOL JS_IsException_real(JSValueConst v) {
    return JS_IsException(v);
}

JS_BOOL JS_IsUninitialized_real(JSValueConst v) {
    return JS_IsUninitialized(v);
}

JS_BOOL JS_IsString_real(JSValueConst v) {
    return JS_IsString(v);
}

JS_BOOL JS_IsSymbol_real(JSValueConst v) {
    return JS_IsSymbol(v);
}

JS_BOOL JS_IsObject_real(JSValueConst v) {
    return JS_IsObject(v);
}

int JS_ToUint32_real(JSContext *ctx, uint32_t *pres, JSValueConst val) {
    return JS_ToUint32(ctx, pres, val);
}

int JS_SetProperty_real(JSContext *ctx, JSValueConst this_obj, JSAtom prop, JSValue val) {
    return JS_SetProperty(ctx, this_obj, prop, val);
}

JSValue JS_NewCFunction_real(JSContext *ctx, JSCFunction *func, const char *name,int length) {
    return JS_NewCFunction(ctx, func, name, length);
}

JSValue JS_NewCFunctionMagic_real(JSContext *ctx, JSCFunctionMagic *func, const char *name, int length, JSCFunctionEnum cproto, int magic) {
    return JS_NewCFunctionMagic(ctx, func, name, length, cproto, magic);
}

JSValue JS_GetPromiseResult_real(JSContext *ctx, JSValueConst this_val) {
    return JS_GetPromiseResult(ctx, this_val);
}

int JS_IsPromise(JSContext *ctx, JSValueConst val) {
    JSObject *p;
    if (JS_VALUE_GET_TAG(val) == JS_TAG_OBJECT) {
        p = JS_VALUE_GET_OBJ(val);
        return p->class_id == JS_CLASS_PROMISE;
    } else {
        return FALSE;
    }
}

int js_eval_buf(JSContext *ctx, const void *buf, int buf_len, const char *filename, int eval_flags)
{
    JSValue val;
    int ret;

    if ((eval_flags & JS_EVAL_TYPE_MASK) == JS_EVAL_TYPE_MODULE) {
        /* for the modules, we compile then run to be able to set
           import.meta */
        val = JS_Eval(ctx, buf, buf_len, filename,
                      eval_flags | JS_EVAL_FLAG_COMPILE_ONLY);
        if (!JS_IsException(val)) {
            js_module_set_import_meta(ctx, val, TRUE, TRUE);
            val = JS_EvalFunction(ctx, val);
        }
    } else {
        val = JS_Eval(ctx, buf, buf_len, filename, eval_flags);
    }
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        ret = -1;
    } else {
        ret = 0;
    }
    JS_FreeValue(ctx, val);
    return ret;
}


JSValue js_require(JSContext *ctx, JSValueConst specifier){
    JSAtom atom_basename;
    JSValue basename_val;
    JSModuleDef *m;
    JSValue ret, err, ns;
    const char *basename = NULL, *filename;

    atom_basename = JS_GetScriptOrModuleName(ctx, 0);
    if (atom_basename == JS_ATOM_NULL)
        basename_val = JS_NULL;
    else
        basename_val = JS_AtomToValue(ctx, atom_basename);
    JS_FreeAtom(ctx, atom_basename);
    if (JS_IsException(basename_val))
        return basename_val;

    basename = JS_ToCString(ctx, basename_val);
    filename = JS_ToCString(ctx, specifier);
    JS_FreeValue(ctx, basename_val);

    if (!basename || !filename)
        goto exception;
                     
    m = JS_RunModule(ctx, basename, filename);
    if (!m)
        goto exception;

    /* return the module namespace */
    ns = js_get_module_ns(ctx, m);
    if (JS_IsException(ns))
        goto exception;

    JS_FreeCString(ctx, filename);
    JS_FreeCString(ctx, basename);
    return ns;
exception:
    err = JS_GetException(ctx);
    JS_FreeCString(ctx, filename);
    JS_FreeCString(ctx, basename);
    return err;
}

JSValue js_undefined(){
    return JS_UNDEFINED;
}

JSValue js_exception(){
    return JS_EXCEPTION;
}

JSValue js_null(){
    return JS_NULL;
}