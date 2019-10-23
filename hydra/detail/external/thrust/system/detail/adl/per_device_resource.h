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

#include <hydra/detail/external/thrust/detail/config.h>

// the purpose of this header is to #include the per_device_resource.h header
// of the sequential, host, and device systems. It should be #included in any
// code which uses adl to dispatch per_device_resource

#include <hydra/detail/external/thrust/system/detail/sequential/per_device_resource.h>

#if 0
#include <hydra/detail/external/thrust/system/cpp/detail/per_device_resource.h>
#include <hydra/detail/external/thrust/system/cuda/detail/per_device_resource.h>
#include <hydra/detail/external/thrust/system/omp/detail/per_device_resource.h>
#include <hydra/detail/external/thrust/system/tbb/detail/per_device_resource.h>
#endif

#define __HYDRA_THRUST_HOST_SYSTEM_PER_DEVICE_RESOURCE_HEADER <__HYDRA_THRUST_HOST_SYSTEM_ROOT/detail/per_device_resource.h>
#include __HYDRA_THRUST_HOST_SYSTEM_PER_DEVICE_RESOURCE_HEADER
#undef __HYDRA_THRUST_HOST_SYSTEM_PER_DEVICE_RESOURCE_HEADER

#define __HYDRA_THRUST_DEVICE_SYSTEM_PER_DEVICE_RESOURCE_HEADER <__HYDRA_THRUST_DEVICE_SYSTEM_ROOT/detail/per_device_resource.h>
#include __HYDRA_THRUST_DEVICE_SYSTEM_PER_DEVICE_RESOURCE_HEADER
#undef __HYDRA_THRUST_DEVICE_SYSTEM_PER_DEVICE_RESOURCE_HEADER
