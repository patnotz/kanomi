#ifndef KANOMI_STENCILS_HPP_
#define KANOMI_STENCILS_HPP_

#include <Kanomi_TypeInfo.hpp>

// Topology Information
struct HEX {
  static const SizeT spatial_dimension = 3;
  static const SizeT num_nodes = 8;
  static const SizeT num_sides = 6;
};
struct TET {
  static const SizeT spatial_dimension = 3;
  static const SizeT num_nodes = 4;
  static const SizeT num_sides = 4;
};
struct QUAD {
  static const SizeT spatial_dimension = 2;
  static const SizeT num_nodes = 4;
  static const SizeT num_sides = 4;
};
struct TRI {
  static const SizeT spatial_dimension = 2;
  static const SizeT num_nodes = 3;
  static const SizeT num_sides = 3;
};

// Quadrature Rule Information
struct HEX_Q8 {
  typedef HEX TopologyT;
  static const SizeT spatial_dimension = TopologyT::spatial_dimension;
  static const SizeT parametric_dimension = 3;
  static const SizeT num_points = 8;
  static const ScalarT points[num_points*parametric_dimension]; // 7
  static const ScalarT weights[num_points];
};

struct TET_Q4 {
  typedef TET TopologyT;
  static const SizeT spatial_dimension = TopologyT::spatial_dimension;
  static const SizeT parametric_dimension = 3;
  static const SizeT num_points = 4;
  static const ScalarT points[num_points*parametric_dimension];
  static const ScalarT weights[num_points];
};

struct QUAD_Q4 {
  typedef QUAD TopologyT;
  static const SizeT spatial_dimension = TopologyT::spatial_dimension;
  static const SizeT parametric_dimension = 2;
  static const SizeT num_points = 4;
  static const ScalarT points[num_points*parametric_dimension];
  static const ScalarT weights[num_points];
};

struct TRI_Q3 {
  typedef TRI TopologyT;
  static const SizeT spatial_dimension = TopologyT::spatial_dimension;
  static const SizeT parametric_dimension = 2;
  static const SizeT num_points = 3;
  static const ScalarT points[num_points*parametric_dimension];
  static const ScalarT weights[num_points];
};

#endif /* KANOMI_STENCILS_HPP_ */
