# Kanomi 
*An experiment in fusion*

## About
There exist software designs for managing complexity in multiphysics 
simulation software. These techniques construct a directed acyclic graph (DAG) view of 
the mathematical subexpressions used in assembling complex systems of PDEs in 
order to allow polymorphic substitution and reuse (among other benefits). One
open source implementation is available in the [Phalanx][] package in 
[Trilinos][].

***Kanomi*** is an attempt to implement this same concept but to do so at 
*compile time* using C++ template meta programming. Of course, for this to be 
useful we need to cross the compile-time / run-time boundary so we utilize the
Boost [Fusion][] library to do that as well as many of the ideas and techniques
outlined in [*Modern C++ Design*][MCPPD] by Andrei Alexandrescu. Ultimately, 
the code will utilize the [Kokkos][] compute node API for deployment to 
various multicore architecutres.

## Build
1. Create a build directory
    <pre><code>
    $ mkdir build
    $ cd build
    </code></pre>
1. Copy and tailor your CMake script
    <pre><code>
    $ cp ../doc/do-cmake
    $ emacs do-cmake # set your trilinos installation location
    </code></pre>
1. Build
    <pre><code>
    $ ./do-cmake
    $ make
    </code></pre>
1. Run it
    <pre><code>
    src/kanomi
    </code></pre>

## TODO
 - Need central memory manager and getters
 - `User_Config.hpp` needs to define root-level dependencies
 - Better compilation errors for missing Factory<FieldT,StencilT> 
 - Switch from `fusion::list<>` to `fusion::cons<>`?
 - Need a strategy for dependencies
 - Populate stencil classes with real quadrature points
 - Choose an array class (`Kokkos::MDArray` ?)
 - Evaluate manager in a Kokkos Node (`parallel_for`)
 - Fix version-gen.sh on rebuilds
 - Doxygen and github-pages
   * main page content
   * copy of source code?
   * version identifier

[Trilinos]: http://trilinos.sandia.gov/
[Phalanx]: http://trilinos.sandia.gov/packages/phalanx/
[Kokkos]: http://trilinos.sandia.gov/packages/kokkos/
[Fusion]: http://www.boost.org/doc%/libs/release/libs/fusion
[MCPPD]: http://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315
