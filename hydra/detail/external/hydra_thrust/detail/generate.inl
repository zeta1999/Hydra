/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file generate.inl
 *  \author Jared Hoberock
 *  \brief Inline file for generate.h.
 */

#include <hydra/detail/external/hydra_thrust/generate.h>
#include <hydra/detail/external/hydra_thrust/iterator/iterator_traits.h>
#include <hydra/detail/external/hydra_thrust/system/detail/generic/select_system.h>
#include <hydra/detail/external/hydra_thrust/system/detail/generic/generate.h>
#include <hydra/detail/external/hydra_thrust/system/detail/adl/generate.h>

namespace hydra_thrust
{


__hydra_thrust_exec_check_disable__
template<typename DerivedPolicy,
         typename ForwardIterator,
         typename Generator>
__host__ __device__
  void generate(const hydra_thrust::detail::execution_policy_base<DerivedPolicy> &exec,
                ForwardIterator first,
                ForwardIterator last,
                Generator gen)
{
  using hydra_thrust::system::detail::generic::generate;
  return generate(hydra_thrust::detail::derived_cast(hydra_thrust::detail::strip_const(exec)), first, last, gen);
} // end generate()


__hydra_thrust_exec_check_disable__
template<typename DerivedPolicy,
         typename OutputIterator,
         typename Size,
         typename Generator>
__host__ __device__
  OutputIterator generate_n(const hydra_thrust::detail::execution_policy_base<DerivedPolicy> &exec,
                            OutputIterator first,
                            Size n,
                            Generator gen)
{
  using hydra_thrust::system::detail::generic::generate_n;
  return generate_n(hydra_thrust::detail::derived_cast(hydra_thrust::detail::strip_const(exec)), first, n, gen);
} // end generate_n()


template<typename ForwardIterator,
         typename Generator>
  void generate(ForwardIterator first,
                ForwardIterator last,
                Generator gen)
{
  using hydra_thrust::system::detail::generic::select_system;

  typedef typename hydra_thrust::iterator_system<ForwardIterator>::type System;

  System system;

  return hydra_thrust::generate(select_system(system), first, last, gen);
} // end generate()


template<typename OutputIterator,
         typename Size,
         typename Generator>
  OutputIterator generate_n(OutputIterator first,
                            Size n,
                            Generator gen)
{
  using hydra_thrust::system::detail::generic::select_system;

  typedef typename hydra_thrust::iterator_system<OutputIterator>::type System;

  System system;

  return hydra_thrust::generate_n(select_system(system), first, n, gen);
} // end generate_n()


} // end hydra_thrust
