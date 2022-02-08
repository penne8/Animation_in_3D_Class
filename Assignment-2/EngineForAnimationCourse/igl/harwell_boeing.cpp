// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "harwell_boeing.h"

template <typename Scalar, typename Index>
IGL_INLINE void igl::harwell_boeing(
	const Eigen::SparseMatrix<Scalar>& A,
	int& num_rows,
	std::vector<Scalar>& V,
	std::vector<Index>& R,
	std::vector<Index>& C)
{
	num_rows = A.rows();
	int num_cols = A.cols();
	int nnz = A.nonZeros();
	V.resize(nnz);
	R.resize(nnz);
	C.resize(num_cols + 1);

	// Assumes outersize is columns
	assert(A.cols() == A.outerSize());
	int column_pointer = 0;
	int i = 0;
	int k = 0;
	// Iterate over outside
	for (; k < A.outerSize(); ++k)
	{
		C[k] = column_pointer;
		// Iterate over inside
		for (typename Eigen::SparseMatrix<Scalar>::InnerIterator it(A, k); it; ++it)
		{
			V[i] = it.value();
			R[i] = it.row();
			i++;
			// Also increment column pointer
			column_pointer++;
		}
	}
	// by convention C[num_cols] = nnz
	C[k] = column_pointer;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::harwell_boeing<double, int>(Eigen::SparseMatrix<double, 0, int> const&, int&, std::vector<double, std::allocator<double> >&, std::vector<int, std::allocator<int> >&, std::vector<int, std::allocator<int> >&);
#endif
