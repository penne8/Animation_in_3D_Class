// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "matlab_format.h"
#include "STR.h"
#include "find.h"

template <typename DerivedM>
IGL_INLINE const Eigen::WithFormat< DerivedM > igl::matlab_format(
	const Eigen::DenseBase<DerivedM>& M,
	const std::string name)
{
	using namespace std;
	string prefix = "";
	if (!name.empty())
	{
		prefix = name + " = ";
	}

	return M.format(Eigen::IOFormat(
		Eigen::FullPrecision,
		0,
		" ",
		"\n",
		"",
		"",
		// This seems like a bit of a hack since I would expect the rows to align
		// with out this extra spacing on the first line
		prefix + "[\n  ",
		"\n];"));
}

template <typename DerivedS>
IGL_INLINE const std::string
igl::matlab_format(
	const Eigen::SparseMatrix<DerivedS>& S,
	const std::string name)
{
	using namespace Eigen;
	using namespace std;
	Matrix<typename Eigen::SparseMatrix<DerivedS>::Scalar, Dynamic, 1> I, J, V;
	Matrix<DerivedS, Dynamic, Dynamic> SIJV;
	find(S, I, J, V);
	I.array() += 1;
	J.array() += 1;
	SIJV.resize(V.rows(), 3);
	SIJV << I, J, V;
	string prefix = "";
	string suffix = "";
	if (!name.empty())
	{
		prefix = name + "IJV = ";
		suffix = "\n" + name + " = sparse(" + name + "IJV(:,1)," + name + "IJV(:,2)," + name + "IJV(:,3)," + std::to_string(S.rows()) + "," + std::to_string(S.cols()) + " );";
	}
	return STR("" <<
		SIJV.format(Eigen::IOFormat(
			Eigen::FullPrecision,
			0,
			" ",
			"\n",
			"",
			"",
			// This seems like a bit of a hack since I would expect the rows to align
			// with out this extra spacing on the first line
			prefix + "[\n  ",
			"\n];")) << suffix);
}

IGL_INLINE Eigen::IOFormat igl::matlab_format()
{
	// M = [1 2 3;4 5 6];
	// M.format(matlab_format()) produces:
	// [
	//   1 2 3
	//   4 5 6
	// ];
	return Eigen::IOFormat(
		Eigen::FullPrecision,
		0,
		" ",
		"\n",
		"",
		"",
		// This seems like a bit of a hack since I would expect the rows to align
		// with out this extra spacing on the first line
		"[\n  ",
		"\n];");
}

IGL_INLINE const std::string igl::matlab_format(
	const double v,
	const std::string name)
{
	using namespace std;
	string prefix = "";
	if (!name.empty())
	{
		prefix = name + " = ";
	}
	return STR(prefix << v << ";");
}

IGL_INLINE const std::string igl::matlab_format(
	const float v,
	const std::string name)
{
	return matlab_format(double(v), name);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template Eigen::WithFormat<Eigen::Matrix<unsigned int, -1, 3, 1, -1, 3> > const igl::matlab_format<Eigen::Matrix<unsigned int, -1, 3, 1, -1, 3> >(Eigen::DenseBase<Eigen::Matrix<unsigned int, -1, 3, 1, -1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const igl::matlab_format<Eigen::Matrix<int, -1, 3, 1, -1, 3> >(Eigen::DenseBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
#if EIGEN_VERSION_AT_LEAST(3,3,0)
#else
template Eigen::WithFormat<Eigen::CwiseUnaryOp<Eigen::internal::scalar_cast_op<bool, int>, Eigen::Matrix<bool, -1, 3, 0, -1, 3> const> > const igl::matlab_format<Eigen::CwiseUnaryOp<Eigen::internal::scalar_cast_op<bool, int>, Eigen::Matrix<bool, -1, 3, 0, -1, 3> const> >(Eigen::DenseBase<Eigen::CwiseUnaryOp<Eigen::internal::scalar_cast_op<bool, int>, Eigen::Matrix<bool, -1, 3, 0, -1, 3> const> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> const> const> > const igl::matlab_format<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> const> const> >(Eigen::DenseBase<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> const> const> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const> > const igl::matlab_format<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const> >(Eigen::DenseBase<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const> > const igl::matlab_format<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const> >(Eigen::DenseBase<Eigen::CwiseUnaryOp<Eigen::internal::scalar_add_op<int>, Eigen::ArrayWrapper<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, 3, 1, 0, 3, 1> > const igl::matlab_format<Eigen::Matrix<float, 3, 1, 0, 3, 1> >(Eigen::DenseBase<Eigen::Matrix<float, 3, 1, 0, 3, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Transpose<Eigen::Block<Eigen::Matrix<float, 4, 4, 0, 4, 4>, -1, -1, false> > > const igl::matlab_format<Eigen::Transpose<Eigen::Block<Eigen::Matrix<float, 4, 4, 0, 4, 4>, -1, -1, false> > >(Eigen::DenseBase<Eigen::Transpose<Eigen::Block<Eigen::Matrix<float, 4, 4, 0, 4, 4>, -1, -1, false> > > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Transpose<Eigen::Matrix<float, 3, 1, 0, 3, 1> > > const igl::matlab_format<Eigen::Transpose<Eigen::Matrix<float, 3, 1, 0, 3, 1> > >(Eigen::DenseBase<Eigen::Transpose<Eigen::Matrix<float, 3, 1, 0, 3, 1> > > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
#endif
template Eigen::WithFormat<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const igl::matlab_format<Eigen::Matrix<float, 1, 3, 1, 1, 3> >(Eigen::DenseBase<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, 4, 1, 0, 4, 1> > const igl::matlab_format<Eigen::Matrix<int, 4, 1, 0, 4, 1> >(Eigen::DenseBase<Eigen::Matrix<int, 4, 1, 0, 4, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template std::basic_string<char, std::char_traits<char>, std::allocator<char> > const igl::matlab_format<double>(Eigen::SparseMatrix<double, 0, int> const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const igl::matlab_format<Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, std::string);
template Eigen::WithFormat<Eigen::Array<int, -1, -1, 0, -1, -1> > const igl::matlab_format<Eigen::Array<int, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Array<int, -1, -1, 0, -1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const igl::matlab_format<Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Matrix<double, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Array<int, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Array<int, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Array<int, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 4, 4, 0, 4, 4> > const igl::matlab_format<Eigen::Matrix<double, 4, 4, 0, 4, 4> >(Eigen::DenseBase<Eigen::Matrix<double, 4, 4, 0, 4, 4> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, 4, 0, -1, 4> > const igl::matlab_format<Eigen::Matrix<double, -1, 4, 0, -1, 4> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 4, 0, -1, 4> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, 2, 0, -1, 2> > const igl::matlab_format<Eigen::Matrix<double, -1, 2, 0, -1, 2> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 2, 0, -1, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 2, 1, 0, 2, 1> > const igl::matlab_format<Eigen::Matrix<double, 2, 1, 0, 2, 1> >(Eigen::DenseBase<Eigen::Matrix<double, 2, 1, 0, 2, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, 1, -1, 1, 1, -1> > const igl::matlab_format<Eigen::Matrix<int, 1, -1, 1, 1, -1> >(Eigen::DenseBase<Eigen::Matrix<int, 1, -1, 1, 1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 1, -1, 1, 1, -1> > const igl::matlab_format<Eigen::Matrix<double, 1, -1, 1, 1, -1> >(Eigen::DenseBase<Eigen::Matrix<double, 1, -1, 1, 1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 3, 3, 0, 3, 3> > const igl::matlab_format<Eigen::Matrix<double, 3, 3, 0, 3, 3> >(Eigen::DenseBase<Eigen::Matrix<double, 3, 3, 0, 3, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 2, 2, 0, 2, 2> > const igl::matlab_format<Eigen::Matrix<double, 2, 2, 0, 2, 2> >(Eigen::DenseBase<Eigen::Matrix<double, 2, 2, 0, 2, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, 2, 2, 0, 2, 2> > const igl::matlab_format<Eigen::Matrix<float, 2, 2, 0, 2, 2> >(Eigen::DenseBase<Eigen::Matrix<float, 2, 2, 0, 2, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 2, 2, 1, 2, 2> > const igl::matlab_format<Eigen::Matrix<double, 2, 2, 1, 2, 2> >(Eigen::DenseBase<Eigen::Matrix<double, 2, 2, 1, 2, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 3, 1, 0, 3, 1> > const igl::matlab_format<Eigen::Matrix<double, 3, 1, 0, 3, 1> >(Eigen::DenseBase<Eigen::Matrix<double, 3, 1, 0, 3, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, 2, 1, 0, 2, 1> > const igl::matlab_format<Eigen::Matrix<float, 2, 1, 0, 2, 1> >(Eigen::DenseBase<Eigen::Matrix<float, 2, 1, 0, 2, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, 2, 2, 1, 2, 2> > const igl::matlab_format<Eigen::Matrix<float, 2, 2, 1, 2, 2> >(Eigen::DenseBase<Eigen::Matrix<float, 2, 2, 1, 2, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, -1, -1, 0, -1, -1> > const igl::matlab_format<Eigen::Matrix<float, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<float, -1, -1, 0, -1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 3, 3, 1, 3, 3> > const igl::matlab_format<Eigen::Matrix<double, 3, 3, 1, 3, 3> >(Eigen::DenseBase<Eigen::Matrix<double, 3, 3, 1, 3, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, -1, 1, -1, -1> > const igl::matlab_format<Eigen::Matrix<double, -1, -1, 1, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<double, -1, -1, 1, -1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, -1, 1, -1, -1> > const igl::matlab_format<Eigen::Matrix<int, -1, -1, 1, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<int, -1, -1, 1, -1, -1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Array<double, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Array<double, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Array<double, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 1, 3, 1, 1, 3> > const igl::matlab_format<Eigen::Matrix<double, 1, 3, 1, 1, 3> >(Eigen::DenseBase<Eigen::Matrix<double, 1, 3, 1, 1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 1, 2, 1, 1, 2> > const igl::matlab_format<Eigen::Matrix<double, 1, 2, 1, 1, 2> >(Eigen::DenseBase<Eigen::Matrix<double, 1, 2, 1, 1, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, 2, 0, -1, 2> > const igl::matlab_format<Eigen::Matrix<int, -1, 2, 0, -1, 2> >(Eigen::DenseBase<Eigen::Matrix<int, -1, 2, 0, -1, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const igl::matlab_format<Eigen::Matrix<int, -1, 3, 0, -1, 3> >(Eigen::DenseBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const igl::matlab_format<Eigen::Matrix<double, -1, 3, 0, -1, 3> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 2, 3, 0, 2, 3> > const igl::matlab_format<Eigen::Matrix<double, 2, 3, 0, 2, 3> >(Eigen::DenseBase<Eigen::Matrix<double, 2, 3, 0, 2, 3> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<double, 3, 2, 0, 3, 2> > const igl::matlab_format<Eigen::Matrix<double, 3, 2, 0, 3, 2> >(Eigen::DenseBase<Eigen::Matrix<double, 3, 2, 0, 3, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Matrix<float, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Matrix<float, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<int, 2, 2, 0, 2, 2> > const igl::matlab_format<Eigen::Matrix<int, 2, 2, 0, 2, 2> >(Eigen::DenseBase<Eigen::Matrix<int, 2, 2, 0, 2, 2> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<float, 4, 4, 0, 4, 4> > const igl::matlab_format<Eigen::Matrix<float, 4, 4, 0, 4, 4> >(Eigen::DenseBase<Eigen::Matrix<float, 4, 4, 0, 4, 4> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
template Eigen::WithFormat<Eigen::Matrix<bool, -1, 1, 0, -1, 1> > const igl::matlab_format<Eigen::Matrix<bool, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Matrix<bool, -1, 1, 0, -1, 1> > const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
#endif
