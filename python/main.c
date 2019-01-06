#include <stdio.h>
#include <Python.h>

int main() {
  Py_Initialize();
  FILE *file = _Py_fopen("projekt.py", "r+");
  if(file != NULL) {
    PyRun_SimpleFile(file, "projekt.py");
  }
  Py_Finalize();
  return 0;
}
