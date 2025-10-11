# Python C Extensions Tutorial

A comprehensive guide to creating Python C extensions for performance-critical code.

## Overview

This tutorial demonstrates how to extend Python with C/C++ code to improve performance for computationally intensive tasks. Python C extensions allow you to write critical code sections in C while maintaining a Python interface.

## Prerequisites

- Python 3.6 or higher
- C compiler (GCC on Linux, Clang on macOS, Visual Studio on Windows)
- Python development headers
- Basic knowledge of C and Python

### Installing Development Headers

**Ubuntu/Debian:**
```bash
sudo apt-get install python3-dev build-essential
```

**macOS:**
```bash
xcode-select --install
```

**Windows:**
Install Visual Studio Build Tools or Visual Studio with C++ support.

## Project Structure

```
python-c-extensions/
├── setup.py
├── src/
│   ├── example_module.c
│   ├── math_operations.c
│   └── math_operations.h
├── tests/
│   └── test_example.py
└── README.md
```

## Basic Example

### 1. Simple C Extension

**src/example_module.c:**
```c
#include <Python.h>

static PyObject* hello_world(PyObject* self, PyObject* args) {
    return PyUnicode_FromString("Hello from C!");
}

static PyObject* add_numbers(PyObject* self, PyObject* args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    return PyLong_FromLong(a + b);
}

static PyMethodDef ExampleMethods[] = {
    {"hello_world", hello_world, METH_NOARGS, "Return a hello world message"},
    {"add_numbers", add_numbers, METH_VARARGS, "Add two integers"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef examplemodule = {
    PyModuleDef_HEAD_INIT,
    "example",
    "Example C extension module",
    -1,
    ExampleMethods
};

PyMODINIT_FUNC PyInit_example(void) {
    return PyModule_Create(&examplemodule);
}
```

### 2. Setup Script

**setup.py:**
```python
from setuptools import setup, Extension

example_module = Extension(
    'example',
    sources=['src/example_module.c'],
    include_dirs=['src'],
)

setup(
    name='python-c-extensions',
    version='1.0.0',
    description='Python C Extensions Tutorial',
    ext_modules=[example_module],
    packages=[],
)
```

## Building the Extension

```bash
python setup.py build_ext --inplace
```

This will compile the C code and create a shared object file (`.so` on Linux/macOS, `.pyd` on Windows) that can be imported directly in Python.

## Using the Extension

```python
import example

print(example.hello_world())  # Output: Hello from C!
print(example.add_numbers(5, 3))  # Output: 8
```

## Advanced Example: Mathematical Operations

### Header File

**src/math_operations.h:**
```c
#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

double compute_pi(int iterations);
long long fibonacci(int n);

#endif
```

### Implementation

**src/math_operations.c:**
```c
#include <Python.h>
#include "math_operations.h"

double compute_pi(int iterations) {
    double pi = 0.0;
    int sign = 1;
    
    for (int i = 0; i < iterations; i++) {
        pi += sign * (4.0 / (2 * i + 1));
        sign *= -1;
    }
    
    return pi;
}

long long fibonacci(int n) {
    if (n <= 1) return n;
    
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

static PyObject* py_compute_pi(PyObject* self, PyObject* args) {
    int iterations;
    
    if (!PyArg_ParseTuple(args, "i", &iterations)) {
        return NULL;
    }
    
    if (iterations <= 0) {
        PyErr_SetString(PyExc_ValueError, "Iterations must be positive");
        return NULL;
    }
    
    double result = compute_pi(iterations);
    return PyFloat_FromDouble(result);
}

static PyObject* py_fibonacci(PyObject* self, PyObject* args) {
    int n;
    
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;
    }
    
    if (n < 0) {
        PyErr_SetString(PyExc_ValueError, "n must be non-negative");
        return NULL;
    }
    
    long long result = fibonacci(n);
    return PyLong_FromLongLong(result);
}

static PyMethodDef MathMethods[] = {
    {"compute_pi", py_compute_pi, METH_VARARGS, "Compute pi using Leibniz formula"},
    {"fibonacci", py_fibonacci, METH_VARARGS, "Compute nth Fibonacci number"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mathmodule = {
    PyModuleDef_HEAD_INIT,
    "math_ops",
    "Mathematical operations implemented in C",
    -1,
    MathMethods
};

PyMODINIT_FUNC PyInit_math_ops(void) {
    return PyModule_Create(&mathmodule);
}
```

## Testing

**tests/test_example.py:**
```python
import unittest
import example
import math_ops

class TestCExtensions(unittest.TestCase):
    
    def test_hello_world(self):
        self.assertEqual(example.hello_world(), "Hello from C!")
    
    def test_add_numbers(self):
        self.assertEqual(example.add_numbers(2, 3), 5)
        self.assertEqual(example.add_numbers(-1, 1), 0)
    
    def test_compute_pi(self):
        pi_approx = math_ops.compute_pi(1000000)
        self.assertAlmostEqual(pi_approx, 3.14159, places=4)
    
    def test_fibonacci(self):
        self.assertEqual(math_ops.fibonacci(0), 0)
        self.assertEqual(math_ops.fibonacci(1), 1)
        self.assertEqual(math_ops.fibonacci(10), 55)

if __name__ == '__main__':
    unittest.main()
```

## Common Python-C Type Conversions

| Python Type | C Type | Format Code |
|-------------|--------|-------------|
| int | int | "i" |
| int | long | "l" |
| int | long long | "L" |
| float | double | "d" |
| str | char* | "s" |
| tuple | PyObject* | "O" |

## Error Handling

```c
static PyObject* safe_divide(PyObject* self, PyObject* args) {
    double a, b;
    
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;  // TypeError raised automatically
    }
    
    if (b == 0.0) {
        PyErr_SetString(PyExc_ZeroDivisionError, "division by zero");
        return NULL;
    }
    
    return PyFloat_FromDouble(a / b);
}
```

## Best Practices

1. **Always check return values** from Python C API functions
2. **Use proper reference counting** to avoid memory leaks
3. **Handle exceptions** appropriately
4. **Write comprehensive tests**
5. **Document your functions** in the method table
6. **Consider using PyPy or Cython** for simpler cases

## Performance Comparison

Compare the performance of pure Python vs C implementations:

```python
import time
import math_ops

def python_fibonacci(n):
    if n <= 1:
        return n
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

# Benchmark
n = 35
start = time.time()
c_result = math_ops.fibonacci(n)
c_time = time.time() - start

start = time.time()
py_result = python_fibonacci(n)
py_time = time.time() - start

print(f"C extension: {c_time:.6f} seconds")
print(f"Pure Python: {py_time:.6f} seconds")
print(f"Speedup: {py_time/c_time:.2f}x")
```

## Troubleshooting

### Common Issues

1. **Module not found**: Ensure the shared object file is in your Python path
2. **Import errors**: Check for missing dependencies or compilation errors
3. **Segmentation faults**: Usually caused by memory access violations in C code
4. **Type errors**: Verify argument parsing in your C functions

### Debugging

Compile with debug symbols:
```bash
python setup.py build_ext --inplace --debug
```

## Next Steps

- Explore the [Python C API documentation](https://docs.python.org/3/c-api/)
- Learn about [Cython](https://cython.org/) for easier C extensions
- Study [NumPy C extensions](https://numpy.org/doc/stable/reference/c-api/)
- Explore [cffi](https://cffi.readthedocs.io/) for foreign function interface

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Feel free to submit issues and enhancement requests!
