#include "wrapping_dap_chain_cs.h"

/* Callback created */
static int wrapping_dap_chain_callback_new_cfg(dap_chain_t* chain, dap_config_t* cfg)
{
    PyObject *arglist;
    PyObject *result;
    PyObject *obj_chain= _PyObject_New(&dapChainObject_dapChainType);
    ((PyDapChainObject*)obj_chain)->chain_t = chain;
    arglist = Py_BuildValue("O", obj_chain);
    result = PyObject_CallObject(binded_object_callback_new_cfg, arglist);
    Py_DECREF(arglist);
    int r = -1;
    if (PyLong_Check(result)){
        r = (int)PyLong_AsLong(result);
    }
    Py_DECREF(result);
    return r;
}
/*--------------------------------*/
int dap_chain_cs_init_py(void){
    return dap_chain_cs_init();
}
void dap_chain_cs_deinit_py(void){
    dap_chain_cs_deinit();
}

PyObject *DapChainCSObject_new(PyTypeObject *type_object, PyObject *args, PyObject *kwds)
{
    PyDapChainCsObject *obj = (PyDapChainCsObject*)PyType_GenericNew(type_object, args, kwds);
    obj->callback_new_cfg = wrapping_dap_chain_callback_new_cfg;
    return (PyObject *)obj;
}

PyObject *dap_chain_cs_add_py (PyObject *self, PyObject *args){
    const char* cs_str;
    PyObject *obj_callback_init;
    if (!PyArg_ParseTuple(args, "s|O:set_callback", &cs_str, &obj_callback_init)){
        return NULL;
    } else {
        if (!PyCallable_Check(obj_callback_init))
        {
            PyErr_SetString(PyExc_TypeError, "paramentr must be callable");
            return NULL;
        }
    }
    Py_XINCREF(obj_callback_init);
    Py_XDECREF(binded_object_callback_new_cfg);
    binded_object_callback_new_cfg = obj_callback_init;
    dap_chain_cs_add(cs_str, ((PyDapChainCsObject*)self)->callback_new_cfg);
    return PyLong_FromLong(0);
}
PyObject *dap_chain_cs_create_py(PyObject *self, PyObject *args){
    PyObject *obj_chain;
    if (!PyArg_ParseTuple(args, "O", &obj_chain))
        return NULL;
    int res = dap_chain_cs_create(((PyDapChainObject*)obj_chain)->chain_t, g_config);
    return PyLong_FromLong(res);
}

PyObject *dap_chain_class_add_py (PyObject *self, PyObject *args){
    const char* cs_str;
    PyObject *obj_callback_init;
    if (!PyArg_ParseTuple(args, "s|O:set_callback", &cs_str, &obj_callback_init)){
        return NULL;
    } else {
        if (!PyCallable_Check(obj_callback_init))
        {
            PyErr_SetString(PyExc_TypeError, "paramentr must be callable");
            return NULL;
        }
    }
    Py_XINCREF(obj_callback_init);
    Py_XDECREF(binded_object_callback_new_cfg);
    binded_object_callback_new_cfg = obj_callback_init;
    dap_chain_cs_type_add(cs_str, ((PyDapChainCsObject*)self)->callback_new_cfg);
    return PyLong_FromLong(0);
}
PyObject *dap_chain_class_create_py(PyObject *self, PyObject *args){
    PyObject *obj_chain;
    if (!PyArg_ParseTuple(args, "O", &obj_chain))
        return NULL;
    int res = dap_chain_cs_type_create(((PyDapChainObject*)obj_chain)->chain_t, g_config);
    return PyLong_FromLong(res);
}
