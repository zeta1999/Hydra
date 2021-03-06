/******************************************************************************
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the NVIDIA CORPORATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NVIDIA CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
#pragma once

#include <hydra/detail/external/hydra_thrust/detail/config.h>
#include <hydra/detail/external/hydra_thrust/system/cuda/detail/guarded_cuda_runtime_api.h>
#include <hydra/detail/external/hydra_thrust/system/cuda/detail/execution_policy.h>
#include <hydra/detail/external/hydra_thrust/system/cuda/detail/util.h>

#include <hydra/detail/external/hydra_thrust/detail/allocator_aware_execution_policy.h>

#if HYDRA_THRUST_CPP_DIALECT >= 2011
#  include <hydra/detail/external/hydra_thrust/detail/dependencies_aware_execution_policy.h>
#endif


HYDRA_THRUST_BEGIN_NS
namespace cuda_cub {

template <class Derived>
struct execute_on_stream_base : execution_policy<Derived>
{
private:
  cudaStream_t stream;

public:
  __host__ __device__
  execute_on_stream_base(cudaStream_t stream_ = default_stream())
      : stream(stream_) {}

  HYDRA_THRUST_RUNTIME_FUNCTION
  Derived
  on(cudaStream_t const &s) const
  {
    Derived result = derived_cast(*this);
    result.stream  = s;
    return result;
  }

private:
  friend __host__ __device__
  cudaStream_t
  get_stream(const execute_on_stream_base &exec)
  {
    return exec.stream;
  }

  friend __host__ __device__
  cudaError_t
  synchronize_stream(execute_on_stream_base &exec)
  {
    #if   !__CUDA_ARCH__
      cudaStreamSynchronize(exec.stream);
      return cudaGetLastError();
    #elif __HYDRA_THRUST_HAS_CUDART__
      HYDRA_THRUST_UNUSED_VAR(exec);
      cudaDeviceSynchronize();
      return cudaGetLastError();
    #else
      HYDRA_THRUST_UNUSED_VAR(exec);
      return cudaSuccess;
    #endif
  }
};

struct execute_on_stream : execute_on_stream_base<execute_on_stream>
{
  typedef execute_on_stream_base<execute_on_stream> base_t;

  __host__ __device__
  execute_on_stream() : base_t(){};
  __host__ __device__
  execute_on_stream(cudaStream_t stream) : base_t(stream){};
};


struct par_t : execution_policy<par_t>,
  hydra_thrust::detail::allocator_aware_execution_policy<
    execute_on_stream_base>
#if HYDRA_THRUST_CPP_DIALECT >= 2011
, hydra_thrust::detail::dependencies_aware_execution_policy<
    execute_on_stream_base>
#endif
{
  typedef execution_policy<par_t> base_t;

  __host__ __device__
  par_t() : base_t() {}

  typedef execute_on_stream stream_attachment_type;

  HYDRA_THRUST_RUNTIME_FUNCTION
  stream_attachment_type
  on(cudaStream_t const &stream) const
  {
    return execute_on_stream(stream);
  }
};

#ifdef __CUDA_ARCH__
static const __device__ par_t par;
#else
static const par_t par;
#endif
}    // namespace cuda_

namespace system {
namespace cuda {
  using hydra_thrust::cuda_cub::par;
  namespace detail {
    using hydra_thrust::cuda_cub::par_t;
  }
} // namesapce cuda
} // namespace system

namespace cuda {
using hydra_thrust::cuda_cub::par;
} // namespace cuda

HYDRA_THRUST_END_NS

