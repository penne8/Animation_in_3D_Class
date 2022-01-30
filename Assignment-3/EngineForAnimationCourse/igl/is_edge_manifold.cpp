// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "is_edge_manifold.h"
#include "oriented_facets.h"
#include "unique_simplices.h"

#include <algorithm>
#include <vector>

template <
    typename DerivedF,
    typename DerivedBF,
    typename DerivedE,
    typename DerivedEMAP,
    typename DerivedBE>
IGL_INLINE bool igl::is_edge_manifold(
    const Eigen::MatrixBase<DerivedF> &F,
    Eigen::PlainObjectBase<DerivedBF> &BF,
    Eigen::PlainObjectBase<DerivedE> &E,
    Eigen::PlainObjectBase<DerivedEMAP> &EMAP,
    Eigen::PlainObjectBase<DerivedBE> &BE)
{
  using namespace Eigen;
  typedef typename DerivedF::Index Index;
  typedef Matrix<typename DerivedF::Scalar, Dynamic, 1> VectorXF;
  typedef Matrix<typename DerivedF::Scalar, Dynamic, 2> MatrixXF2;
  MatrixXF2 allE;
  oriented_facets(F, allE);
  // Find unique undirected edges and mapping
  VectorXF _;
  unique_simplices(allE, E, _, EMAP);
  std::vector<typename DerivedF::Index> count(E.rows(), 0);
  for (Index e = 0; e < EMAP.rows(); e++)
  {
    count[EMAP[e]]++;
  }
  const Index m = F.rows();
  BF.resize(m, 3);
  BE.resize(E.rows(), 1);
  bool all = true;
  for (Index e = 0; e < EMAP.rows(); e++)
  {
    const bool manifold = count[EMAP[e]] <= 2;
    all &= BF(e % m, e / m) = manifold;
    BE(EMAP[e]) = manifold;
  }
  return all;
}

template <typename DerivedF>
IGL_INLINE bool igl::is_edge_manifold(
    const Eigen::MatrixBase<DerivedF> &F)
{
  // TODO: It's bothersome that this is not calling/reusing the code from the
  // overload above. This could result in disagreement.

  // List of edges (i,j,f,c) where edge i<j is associated with corner i of face
  // f
  std::vector<std::vector<int>> TTT;
  for (int f = 0; f < F.rows(); ++f)
    for (int i = 0; i < 3; ++i)
    {
      // v1 v2 f ei
      int v1 = F(f, i);
      int v2 = F(f, (i + 1) % 3);
      if (v1 > v2)
        std::swap(v1, v2);
      std::vector<int> r(4);
      r[0] = v1;
      r[1] = v2;
      r[2] = f;
      r[3] = i;
      TTT.push_back(r);
    }
  // Sort lexicographically
  std::sort(TTT.begin(), TTT.end());

  for (int i = 2; i < (int)TTT.size(); ++i)
  {
    // Check any edges occur 3 times
    std::vector<int> &r1 = TTT[i - 2];
    std::vector<int> &r2 = TTT[i - 1];
    std::vector<int> &r3 = TTT[i];
    if ((r1[0] == r2[0] && r2[0] == r3[0]) &&
        (r1[1] == r2[1] && r2[1] == r3[1]))
    {
      return false;
    }
  }
  return true;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template bool igl::is_edge_manifold<Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1>>(Eigen::MatrixBase<Eigen::Matrix<unsigned int, -1, -1, 1, -1, -1>> const &);
// generated by autoexplicit.sh
// template bool igl::is_edge_manifold<double>(Eigen::Matrix<double, -1, -1, 0, -1, -1> const&, Eigen::Matrix<int, -1, -1, 0, -1, -1> const&);
template bool igl::is_edge_manifold<Eigen::Matrix<int, -1, -1, 0, -1, -1>>(Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1>> const &);
template bool igl::is_edge_manifold<Eigen::Matrix<int, -1, 3, 0, -1, 3>>(Eigen::MatrixBase<Eigen::Matrix<int, -1, 3, 0, -1, 3>> const &);
#endif
