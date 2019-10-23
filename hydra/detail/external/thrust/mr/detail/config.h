/*
 *  Copyright 2018 NVIDIA Corporation
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

#include <cstddef>

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/detail/alignment.h>
#include <hydra/detail/external/thrust/detail/config/cpp_compatibility.h>

#define HYDRA_THRUST_MR_DEFAULT_ALIGNMENT HYDRA_THRUST_ALIGNOF(::HYDRA_EXTERNAL_NS::thrust::detail::max_align_t)

#if __cplusplus >= 201703L
#  if __has_include(<memory_resource>)
#    define HYDRA_THRUST_MR_STD_MR_HEADER <memory_resource>
#    define HYDRA_THRUST_MR_STD_MR_NS std::pmr
#  elif __has_include(<experimental/memory_resource>)
#    define HYDRA_THRUST_MR_STD_MR_HEADER <experimental/memory_resource>
#    define HYDRA_THRUST_MR_STD_MR_NS std::experimental::pmr
#  endif
#endif
