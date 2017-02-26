#include <Python.h>
#include <numpy/arrayobject.h>
#include <fast_wh_core.h>

/* Docstring for the module */
static char module_docstring[] = 
	(" Module for computing fast Walsh Hadamard transform for vectors\n"
	 " and matrices. Implementation of the module is copied from the\n"
	 " matlab implementation of the same.\n"
	 " Methods:\n"
	 " 		fast_wh_trans\n");

/* Docstring for vector method */
static char fast_wh_trans_docstring[] = 
	(" Function to implement fast Walsh Hadamard Transformation.\n"
	 " Inputs:\n"
	 " 		input: Input vector/matrix whose transform is computed.\n"
	 " 		columns: True (default): Compute transform of columns.\n"
	 " 				 False: Compute transform of rows.\n"
	 " 		scale: If True (default), scale the output by sqrt(dimension).\n");

/* Now start the main routine */
static PyObject *fast_wh_trans_fast_wh(PyObject *self, PyObject *args)
{
	/* Three inputs and one output */
	PyObject *X_obj, *output_obj;
	int col, scale;

	/* Default arguments */
	col = TRUE;
	scale = TRUE;

	/* Numpy array for X */
	PyObject *X_array;

	/* Data pointer */
	double *X, *output;

	/* Matrix sizes */
	int m, n;
	npy_intp dims[2];

	/* Parse inputs */
	if (!PyArg_ParseTuple(args, "O|ii", &X_obj, &col, &scale))
	{
		return NULL;
	}

	/* Extract the input matrix */
	X_array = PyArray_FROM_OTF(X_obj, NPY_DOUBLE, NPY_IN_ARRAY);

	/* Throw an error if things aren't successful */
	if (X_array == NULL)
	{
		Py_XDECREF(X_array);
		return NULL;
	}

	/* Extract dimension of the matrices */
	m = (int) PyArray_DIM(X_array, 0);
	n = (int) PyArray_DIM(X_array, 1);
	dims[0] = m;
	dims[1] = n;

	/* Extract data pointers */
	X = (double *) PyArray_DATA(X_array);

	/* Allocate data for output */
	output = (double *) malloc(m*n*sizeof(double));

	/* Call the transform routine now */

	/* If it is a vector, call the vector function which is light weight */
	if (m == 1 || n == 1)
	{
		fast_wh_vec(X, MAX(m, n), output, scale);
	}
	else
	{
		fast_wh_mat(X, m, n, output, col, scale);
	}

	/* Computation done. Clean up the object we used */
	Py_DECREF(X_array);

	/* Build output */
	output_obj = PyArray_SimpleNewFromData(2, dims, NPY_DOUBLE, output);

	/* Return */
	return output_obj;
}

/* Define methods of our module*/
static PyMethodDef module_methods[] = {
	{"fast_wh_trans", (PyCFunction)fast_wh_trans_fast_wh, METH_VARARGS,
	 fast_wh_trans_docstring},
	{NULL, NULL, 0, NULL}
};

/* Module initialization */
PyMODINIT_FUNC initfast_wh(void)
{
	PyObject *m = Py_InitModule3("fast_wh", module_methods, module_docstring);

	/* Make sure output is not null */
	if (m == NULL)
		return;

	/* Load numpy functionality */
	import_array();
}

