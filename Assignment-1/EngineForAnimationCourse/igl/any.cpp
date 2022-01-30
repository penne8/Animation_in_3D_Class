// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2016 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "any.h"
#include "redux.h"


template <typename AType, typename DerivedB>
IGL_INLINE void igl::any(
	const Eigen::SparseMatrix<AType>& A,
	const int dim,
	Eigen::PlainObjectBase<DerivedB>& B)
{
	typedef typename DerivedB::Scalar Scalar;
	igl::redux(A, dim, [](Scalar a, Scalar b) { return a || b != 0; }, B);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::any<bool, Eigen::Array<bool, -1, 1, 0, -1, 1> >(Eigen::SparseMatrix<bool, 0, int> const&, int, Eigen::PlainObjectBase<Eigen::Array<bool, -1, 1, 0, -1, 1> >&);
#endif
