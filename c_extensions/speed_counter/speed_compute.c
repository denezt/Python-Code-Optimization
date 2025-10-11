// hello.c
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "math.h"
#include "ctype.h"


static int add(a, b){
	return a + b;
}

static int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
}

// compute(a, b) -> a + b
static PyObject* compute(PyObject* self, PyObject* args) {
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) {
        return NULL; // TypeError raised by PyArg_ParseTuple
    }
    int res = add(a, b);
    return PyLong_FromLong(res);
}

// add(a, b) -> a + b
static PyObject* fcompute(PyObject* self, PyObject* args) {
    unsigned int a;
    if (!PyArg_ParseTuple(args, "i", &a)) {
        return NULL; // TypeError raised by PyArg_ParseTuple
    }
    int res = factorial(a);
    return PyLong_FromLong(res);
}

static PyMethodDef ComputeMethods[] = {
    {"compute",   compute,   METH_VARARGS, "Adding large integers."},
    {"fcompute",   fcompute,   METH_VARARGS, "Factorial large integers."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef compute_module = {
    PyModuleDef_HEAD_INIT,
    "speed_compute",             // m_name (import name)
    "Compute C extension",       // m_doc
    -1,                          // m_size
    ComputeMethods
};

PyMODINIT_FUNC PyInit_speed_compute(void) {
    return PyModule_Create(&compute_module);
}
