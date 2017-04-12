#include <vector>
#include <stdexcept>

/*
Returns the determinant of a 2x2 matrix A

                     |a b|
1. Compute: det(A) = |c d| = ad - bc

*/
float determinant_2x2(std::vector< std::vector<float> > A) {
	if (A.capacity() != 2 || A[0].capacity() != 2) {
		// throw error
	}

	//                     |a b|
    //1. Compute: det(A) = |c d| = ad - bc
	float determinant = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
	
	//	throw error if det(A) evaluates to NaN
	if (isnan(determinant)) {
		// throw error
	}

	return determinant;
}


/*
Returns the determinant of an nxn matrix
*/
float determinant(std::vector< std::vector<float> >& A) {
	if (A.capacity() == 2 && A[0].capacity() == 2) {
		// det(A) = ad - bc
		return determinant_2x2(A);
	}

	// cofactor expansion
	
	return 0;
}

/*
Returns the scalar (dot) product of two vectors
- let * be the dot product operator
- let c be a scalar (constant) value
- let a and d be vectors

1. Compute: c = a * b
2. Return: c

THROWS EXCEPTION

*/
float scalar_product(std::vector<float>& a, std::vector<float>& b) {
	float scalar_prod = 0;
	int a_dimension = a.capacity();
	int b_dimension = b.capacity();
	
	// Throw error if a and b are not of the same dimension
	if (a_dimension != b_dimension) {
		throw std::invalid_argument("scalar_product():\n scalar product will not be computed because vectors a and b are of different dimensions\n");
	}
	
	// 1. Compute: c = a * b
	for (int i = 0; i < a_dimension; i++) {
		scalar_prod += a[i] * b[i];
	}
	
	// If a value came back that is not a number, throw an error
	if (isnan(scalar_prod)) {
		nan_exception nan_except;
		throw nan_except;
	}
	
	// 2. Return: c
	return scalar_prod;
}

/*
Returns the product of a Matrix A multiplied
by a column vector d as a column vector<float>

1. Compute: x = A*d
2. Return: x

THROWS EXCEPTION

*/
std::vector<float> mult_matrix_by_vector(std::vector< std::vector<float> >& A, std::vector<float>& d) {
	int r = A[0].capacity();
	int c = d.capacity();
	float scalar_prod;
	std::vector<float> x;
	
	if (r != c) {
		throw std::invalid_argument("mult_matrix_by_vector():\n Product will not be computed because matrix A's # of columns and vector d's r# of rows are of different\n");
	}

	// 1. Compute: x = A*d
	for (int i = 0; i < r; i++) {
		try {
			
			// A[i] * d
			scalar_prod = scalar_product(A[i], d);
			
		// Exception handling
		} catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			throw std::invalid_argument("mult_matrix_by_vector():\n Product failed to compute because a row in matrix A could not be multiplied by column vector d\n");
		
		} catch (const nan_exception& e) {
			std::cerr << "mult_matrix_by_vector():\n Scalar Product of row " << i << 
						 " of Matrix A and column vector d evaluated to NaN (not a number)" << std::endl << std::endl;
			throw e;
		} catch (...) {
			std::cerr << "mult_matrix_by_vector():\nUnknown error" << std::endl << std::endl;
			std::exception e;
			throw e;
		}
		
		// x[i] = A[i] * d
		x.push_back(scalar_prod);
	}
	
	// 2. Return: x
	return x;
}

/*
Returns the inverse of a matrix in the format of a 2D vector<float>
*/
std::vector< std::vector<float> > inverse(std::vector< std::vector<float> >& mat) {
	int x = 2 * mat[0].capacity();
	float matrix[x][x];
	float ratio;
	float a;
	int i, j, k;
	int n = mat[0].capacity();
	
	// Copy argument matrix into work matrix
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			matrix[i][j] = mat[i][j];
		}
	}
	
	// Compute inverse
	for(i = 0; i < n; i++) {
		for(j = n; j < 2*n; j++) {
			if(i==(j-n))
				matrix[i][j] = 1.0;
			else
				matrix[i][j] = 0.0;
		}
	}
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i!=j){
				ratio = matrix[j][i]/matrix[i][i];
				for(k = 0; k < 2*n; k++){
					matrix[j][k] -= ratio * matrix[i][k];
				}
			}
		}
	}
	
	for(i = 0; i < n; i++) {
		a = matrix[i][i];
		for(j = 0; j < 2*n; j++){
			matrix[i][j] /= a;
		}
	}
	
	// Copy inverse back into 2D vector matrix to return
	for(i = 0; i < n; i++) {
		for(j = n; j < 2*n; j++) {
			mat[i][j-n] = matrix[i][j];
		}
	}
	
	return mat;
}
