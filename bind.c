#include <Python.h>

double add(double, double);

PyObject *PyAdd(PyObject *Py_UNUSED(module), PyObject *args)
{
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b))
    {
        return NULL;
    }
    a = add(a, b);
    return Py_BuildValue("d", a);
}

static PyMethodDef module_methods[] = {
    {.ml_name = "add",
     .ml_meth = (PyCFunction)PyAdd,
     .ml_flags = METH_VARARGS,
     .ml_doc = "an add function"},
    {NULL, NULL, 0, NULL}};

static PyModuleDef cAdd = {
    PyModuleDef_HEAD_INIT,
    .m_name = "cAdd",
    .m_doc = "a demo program providing add function.",
    .m_size = -1,
    .m_methods = module_methods,
};

PyMODINIT_FUNC PyInit_cAdd(void)
{
    return PyModule_Create(&cAdd);
}