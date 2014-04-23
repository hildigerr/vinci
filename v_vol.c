#include "mex.h"
//#include "vinci.h"

#include "vinci_lass.c"

void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray *prhs[] )
{
	int mrows, ncols;
	int        i, j, k;
	double 	*volume;
	double	*matrix;

	/* Check for proper number of arguments. */
	if (nrhs != 1)
	{
		mexErrMsgTxt("One input required.");
	} else if (nlhs > 1)
	{
		mexErrMsgTxt("Too many output arguments");
	}

	/* the input must be a non complex m by 4 matrix */
	mrows = mxGetM(prhs[0]);
	ncols = mxGetN(prhs[0]);
	if (ncols != 4 || !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0]))
	{
		mexErrMsgTxt("Input must be a noncomplex m by 4 double matrix");
	}

	/* Set up the return argument matrix */
	plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
	
	/* The output goes in *volume */
	volume = mxGetPr(plhs[0]);

	/* Get pointer to the right hand side */
	matrix = mxGetPr(prhs[0]);

	/* Set global variables */
	G_m = mrows;
	G_d = ncols - 1;
	create_hyperplanes (); // allocates space for hyperplanes
	
	/* needs to be changed to read data from the array, or use the array(better) */
	k=0;
	for (i = 0; i < G_m; i++)
    {
		G_Hyperplanes [i] [G_d] = matrix[k++];
	}
	for (i=0; i < G_m; i++)
	{
		G_Hyperplanes [i] [0] = -matrix[k++];
	}
	for (i=0; i < G_m; i++)
	{
		G_Hyperplanes [i] [1] = -matrix[k++];
	}
	for (i=0; i < G_m; i++)
	{
		G_Hyperplanes [i] [2] = -matrix[k++];
	}

         //for (j = 0; j < G_d; j++)
         //{  G_Hyperplanes [i] [j] = matrix[k++];
         //   /*G_Hyperplanes [i] [j] = - G_Hyperplanes [i] [j];*/
         //}
    
    
    
	if (G_Storage > G_d - 3)
	  G_Storage = G_d - 3;
	  /* necessary to prevent memory waste because in the tree arrays of length */
	  /* G_Storage + 2 are allocated                                          */
	
	pivotrow = (rational *) my_malloc ((G_d + 1) * sizeof (rational));
	All_index = (T_LassInt *) my_malloc ((G_m + 1) * sizeof (T_LassInt));
	Pivot = (T_LassInt *) my_malloc ((G_d + 1) * sizeof (T_LassInt));
	p2c = (int **) my_malloc (G_d * sizeof (int *));
	for (i=0; i<G_d; i++){
	   p2c[i] = (int *) my_malloc (2 * sizeof (int));
	}
	A=compact();
	planescopy=compact();
	tree_volumes = NULL;
	create_key (&key, KEY_PLANES_VAR);
	key.hypervar.hyperplanes [0] = G_m + 1;
	key.hypervar.variables [0] = G_d + 1;
	All_index[0]=G_m+2;  /* initialization (end mark) */
	Pivot[0]=G_m+2;	/* initialization (end mark) */
	*volume = lass (A, G_m-1, G_d);

	/* Deallocate memory */ // didn't work
	free_key (key, KEY_PLANES_VAR);
	my_free(planescopy, G_m*(G_d+1)*sizeof(rational));
	my_free(A, G_m*(G_d+1)*sizeof(rational));
	for (i=0; i<G_d; i++){
		my_free(p2c[i], 2 * sizeof (int));
	}
	my_free(p2c, G_d * sizeof (int *));
	my_free(Pivot, (G_d + 1) * sizeof (T_LassInt));
	my_free(All_index,(G_m + 1) * sizeof (T_LassInt));
	my_free(pivotrow, (G_d + 1) * sizeof (rational));
	free_hyperplanes ();
}
