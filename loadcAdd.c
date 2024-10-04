#include <Python.h>
#include <windows.h>
typedef FARPROC dl_funcptr;
typedef PyObject *(*PyModInitFunction)(void);

#define MODULE_NAME "cAdd"

int main()
{
    Py_Initialize();
    PyObject *module = NULL;
    PyObject *dic = NULL;
    PyObject *add = NULL;
    PyObject *args = NULL;
    PyObject *ret = NULL;
    PyObject *s_main = NULL;
    PyObject *py_main = NULL;

    char *full_path = MYLIBPATH "/" MODULE_NAME Python_SOABI;
    HINSTANCE hDLL = LoadLibraryEx(full_path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (hDLL == NULL)
    {
        printf("dll not find!\n");
        goto final;
    }
    char *funcname = "PyInit_" MODULE_NAME;
    dl_funcptr p = GetProcAddress(hDLL, funcname);
    if (p == NULL)
    {
        printf("function not find!\n");
        goto final;
    }
    module = ((PyModInitFunction)p)();
    // printf("type m is %s\n", Py_TYPE(m)->tp_name);
    // PyObject_Print(m, stdout, 0);
    dic = PyModule_GetDict(module);
    // PyObject_Print(dic, stdout, 0);
    add = PyObject_GetAttrString(module, "add");
    args = Py_BuildValue("(dd)", 2.f, 8.f);
    fprintf(stdout, "call in c  : 2 + 8 = ");
    ret = PyObject_CallObject(add, args);
    PyObject_Print(ret, stdout, 0);
    fprintf(stdout, "\n");

    s_main = PyUnicode_FromString("__main__");
    py_main = PyImport_GetModule(s_main);
    PyObject_SetAttrString(py_main, "cAdd", module);
    if (!PyRun_SimpleString("print('call in python: 2 + 9 = ', cAdd.add(2,9))"))
    {
        PyErr_Print();
        goto final;
    }
    fprintf(stdout, "\n");
final:
    Py_XDECREF(module);
    Py_XDECREF(dic);
    Py_XDECREF(add);
    Py_XDECREF(args);
    Py_XDECREF(ret);
    Py_XDECREF(s_main);
    Py_XDECREF(py_main);
    Py_Finalize();
    return 0;
}