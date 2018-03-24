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

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/pair.h>
#include <hydra/detail/external/thrust/iterator/iterator_traits.h>
#include <hydra/detail/external/thrust/detail/type_traits/algorithm/intermediate_type_from_function_and_iterators.h>
#include <hydra/detail/external/thrust/system/detail/sequential/execution_policy.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace system
{
namespace detail
{
namespace sequential
{


__thrust_exec_check_disable__
template<typename DerivedPolicy,
         typename InputIterator1,
         typename InputIterator2,
         typename OutputIterator1,
         typename OutputIterator2,
         typename BinaryPredicate,
         typename BinaryFunction>
__hydra_host__ __hydra_device__
  thrust::pair<OutputIterator1,OutputIterator2>
    reduce_by_key(sequential::execution_policy<DerivedPolicy> &,
                  InputIterator1 keys_first, 
                  InputIterator1 keys_last,
                  InputIterator2 values_first,
                  OutputIterator1 keys_output,
                  OutputIterator2 values_output,
                  BinaryPredicate binary_pred,
                  BinaryFunction binary_op)
{
  typedef typename thrust::iterator_traits<InputIterator1>::value_type  InputKeyType;
  typedef typename thrust::iterator_traits<InputIterator2>::value_type  InputValueType;

  typedef typename thrust::detail::intermediate_type_from_function_and_iterators<
    InputIterator2,
    OutputIterator2,
    BinaryFunction
  >::type TemporaryType;

  if(keys_first != keys_last)
  {
    InputKeyType  temp_key   = *keys_first;
    TemporaryType temp_value = *values_first;

    for(++keys_first, ++values_first;
        keys_first != keys_last;
        ++keys_first, ++values_first)
    {
      InputKeyType    key  = *keys_first;
      InputValueType value = *values_first;

      if(binary_pred(temp_key, key))
      {
        temp_value = binary_op(temp_value, value);
      }
      else
      {
        *keys_output   = temp_key;
        *values_output = temp_value;

        ++keys_output;
        ++values_output;

        temp_key   = key;
        temp_value = value;
      }
    }

    *keys_output   = temp_key;
    *values_output = temp_value;

    ++keys_output;
    ++values_output;
  }

  return thrust::make_pair(keys_output, values_output);
}


} // end namespace sequential
} // end namespace detail
} // end namespace system
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END