// hello.c
#define PY_SSIZE_T_CLEAN
#include <Python.h>

// add(a, b) -> a + b
static PyObject* add(PyObject* self, PyObject* args) {
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) {
        return NULL; // TypeError raised by PyArg_ParseTuple
    }
    return PyLong_FromLong(a + b);
}

// greet(name) -> "Hello, <name>!"
static PyObject* greeting(PyObject* self, PyObject* args) {
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }
    return PyUnicode_FromFormat("Hello, %s!", name);
}

static PyMethodDef DemoMethods[] = {
    {"add",   add,   METH_VARARGS, "Add two integers."},
    {"greet", greeting, METH_VARARGS, "Greet someone by name."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef demomodule = {
    PyModuleDef_HEAD_INIT,
    "add",             // m_name (import name)
    "Example C extension", // m_doc
    -1,                  // m_size
    DemoMethods
};

PyMODINIT_FUNC PyInit_add(void) {
    return PyModule_Create(&demomodule);
}
