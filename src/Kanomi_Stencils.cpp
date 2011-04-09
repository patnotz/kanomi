#include <Kanomi_Stencils.hpp>

namespace kanomi {

const ScalarT HEX_Q8::points[num_points*parametric_dimension] = {
    0, 0, 0,  // 0
    0, 0, 0,  // 1
    0, 0, 0,  // 2
    0, 0, 0,  // 3
    0, 0, 0,  // 4
    0, 0, 0,  // 5
    0, 0, 0,  // 6
    0, 0, 0}; // 7
const ScalarT HEX_Q8::weights[num_points] = {
    0,  // 0
    0,  // 1
    0,  // 2
    0,  // 3
    0,  // 4
    0,  // 5
    0,  // 6
    0}; // 7

const ScalarT TET_Q4::points[num_points*parametric_dimension] = {
    0, 0, 0,  // 0
    0, 0, 0,  // 1
    0, 0, 0,  // 2
    0, 0, 0}; // 3
const ScalarT TET_Q4::weights[num_points] = {
    0,  // 0
    0,  // 1
    0,  // 2
    0}; // 3

const ScalarT QUAD_Q4::points[num_points*parametric_dimension] = {
    0, 0,  // 0
    0, 0,  // 1
    0, 0,  // 2
    0, 0}; // 3
const ScalarT QUAD_Q4::weights[num_points] = {
    0,  // 0
    0,  // 1
    0,  // 2
    0}; // 3

const ScalarT TRI_Q3::points[num_points*parametric_dimension] = {
    0, 0,  // 0
    0, 0,  // 1
    0, 0}; // 2
const ScalarT TRI_Q3::weights[num_points] = {
    0,  // 0
    0,  // 1
    0}; // 2

} // namespace kanomi
