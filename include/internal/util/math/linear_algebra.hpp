#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

float determinant_2x2(std::vector< std::vector<float> > A);
float determinant(std::vector< std::vector<float> >& A);
float scalar_product(std::vector<float>& a, std::vector<float>& b);
std::vector< std::vector<float> > matrix_transpose(std::vector< std::vector<float> >& A);
std::vector<float> mult_matrix_by_vector(std::vector< std::vector<float> >& A, std::vector<float>& d);
std::vector< std::vector<float> > inverse(std::vector< std::vector<float> >& mat);

#endif
