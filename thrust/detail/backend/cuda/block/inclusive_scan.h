/*
 *  Copyright 2008-2011 NVIDIA Corporation
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

#include <thrust/detail/config.h>

#include <thrust/iterator/iterator_traits.h>

namespace thrust
{
namespace detail
{
namespace backend
{
namespace cuda
{
namespace block
{

template<typename Context,
         typename InputIterator,
         typename BinaryFunction>
__device__ __forceinline__
void inplace_inclusive_scan(Context context,
                            InputIterator first,
                            BinaryFunction binary_op)
{
  // TODO support dynamic block_size
  const unsigned int block_size = Context::ThreadsPerBlock::value;

  typename thrust::iterator_value<InputIterator>::type val = first[context.thread_index()];

  if(block_size >    1) { if (context.thread_index() >=    1) { val = binary_op(first[context.thread_index() -    1], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >    2) { if (context.thread_index() >=    2) { val = binary_op(first[context.thread_index() -    2], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } 
  if(block_size >    4) { if (context.thread_index() >=    4) { val = binary_op(first[context.thread_index() -    4], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >    8) { if (context.thread_index() >=    8) { val = binary_op(first[context.thread_index() -    8], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >   16) { if (context.thread_index() >=   16) { val = binary_op(first[context.thread_index() -   16], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >   32) { if (context.thread_index() >=   32) { val = binary_op(first[context.thread_index() -   32], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >   64) { if (context.thread_index() >=   64) { val = binary_op(first[context.thread_index() -   64], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >  128) { if (context.thread_index() >=  128) { val = binary_op(first[context.thread_index() -  128], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >  256) { if (context.thread_index() >=  256) { val = binary_op(first[context.thread_index() -  256], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size >  512) { if (context.thread_index() >=  512) { val = binary_op(first[context.thread_index() -  512], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
  if(block_size > 1024) { if (context.thread_index() >= 1024) { val = binary_op(first[context.thread_index() - 1024], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); }
} // end inplace_inclusive_scan()


template<typename Context,
         typename InputIterator,
         typename Size,
         typename BinaryFunction>
__device__ __forceinline__
void inplace_inclusive_scan_n(Context context,
                              InputIterator first,
                              Size n,
                              BinaryFunction binary_op)
{
  // TODO generalize to arbitrary n
  typename thrust::iterator_value<InputIterator>::type val = first[context.thread_index()];

  // assume n <= 2048
  if(n >    1) { if (context.thread_index() < n && context.thread_index() >=    1) { val = binary_op(first[context.thread_index() -    1], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >    2) { if (context.thread_index() < n && context.thread_index() >=    2) { val = binary_op(first[context.thread_index() -    2], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; } 
  if(n >    4) { if (context.thread_index() < n && context.thread_index() >=    4) { val = binary_op(first[context.thread_index() -    4], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >    8) { if (context.thread_index() < n && context.thread_index() >=    8) { val = binary_op(first[context.thread_index() -    8], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   16) { if (context.thread_index() < n && context.thread_index() >=   16) { val = binary_op(first[context.thread_index() -   16], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   32) { if (context.thread_index() < n && context.thread_index() >=   32) { val = binary_op(first[context.thread_index() -   32], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   64) { if (context.thread_index() < n && context.thread_index() >=   64) { val = binary_op(first[context.thread_index() -   64], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  128) { if (context.thread_index() < n && context.thread_index() >=  128) { val = binary_op(first[context.thread_index() -  128], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  256) { if (context.thread_index() < n && context.thread_index() >=  256) { val = binary_op(first[context.thread_index() -  256], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  512) { if (context.thread_index() < n && context.thread_index() >=  512) { val = binary_op(first[context.thread_index() -  512], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n > 1024) { if (context.thread_index() < n && context.thread_index() >= 1024) { val = binary_op(first[context.thread_index() - 1024], val); } context.barrier(); first[context.thread_index()] = val; context.barrier(); } else { return; }  
} // end inplace_inclusive_scan()


template<typename Context,
         typename InputIterator1,
         typename InputIterator2,
         typename BinaryFunction>
__device__ __forceinline__
void inplace_inclusive_segscan(Context context,
                               InputIterator1 first1,
                               InputIterator2 first2,
                               BinaryFunction binary_op)
{
  // TODO support dynamic block_size
  const unsigned int block_size = Context::ThreadsPerBlock::value;

  typename thrust::iterator_value<InputIterator1>::type flg = first1[context.thread_index()];
  typename thrust::iterator_value<InputIterator2>::type val = first2[context.thread_index()];

  if(block_size >    1) { if (context.thread_index() >=    1) { if (!flg) { flg |= first1[context.thread_index() -    1]; val = binary_op(first2[context.thread_index() -    1], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >    2) { if (context.thread_index() >=    2) { if (!flg) { flg |= first1[context.thread_index() -    2]; val = binary_op(first2[context.thread_index() -    2], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } 
  if(block_size >    4) { if (context.thread_index() >=    4) { if (!flg) { flg |= first1[context.thread_index() -    4]; val = binary_op(first2[context.thread_index() -    4], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >    8) { if (context.thread_index() >=    8) { if (!flg) { flg |= first1[context.thread_index() -    8]; val = binary_op(first2[context.thread_index() -    8], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >   16) { if (context.thread_index() >=   16) { if (!flg) { flg |= first1[context.thread_index() -   16]; val = binary_op(first2[context.thread_index() -   16], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >   32) { if (context.thread_index() >=   32) { if (!flg) { flg |= first1[context.thread_index() -   32]; val = binary_op(first2[context.thread_index() -   32], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >   64) { if (context.thread_index() >=   64) { if (!flg) { flg |= first1[context.thread_index() -   64]; val = binary_op(first2[context.thread_index() -   64], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >  128) { if (context.thread_index() >=  128) { if (!flg) { flg |= first1[context.thread_index() -  128]; val = binary_op(first2[context.thread_index() -  128], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >  256) { if (context.thread_index() >=  256) { if (!flg) { flg |= first1[context.thread_index() -  256]; val = binary_op(first2[context.thread_index() -  256], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size >  512) { if (context.thread_index() >=  512) { if (!flg) { flg |= first1[context.thread_index() -  512]; val = binary_op(first2[context.thread_index() -  512], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
  if(block_size > 1024) { if (context.thread_index() >= 1024) { if (!flg) { flg |= first1[context.thread_index() - 1024]; val = binary_op(first2[context.thread_index() - 1024], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); }
} // end inplace_inclusive_segscan()


template<typename Context,
         typename InputIterator1,
         typename InputIterator2,
         typename Size,
         typename BinaryFunction>
__device__ __forceinline__
void inplace_inclusive_segscan_n(Context context,
                                 InputIterator1 first1,
                                 InputIterator2 first2,
                                 Size n,
                                 BinaryFunction binary_op)
{
  // TODO generalize to arbitrary n
  typename thrust::iterator_value<InputIterator1>::type flg = first1[context.thread_index()];
  typename thrust::iterator_value<InputIterator2>::type val = first2[context.thread_index()];

  // assume n <= 2048
  if(n >    1) { if (context.thread_index() < n && context.thread_index() >=    1) { if (!flg) { flg |= first1[context.thread_index() -    1]; val = binary_op(first2[context.thread_index() -    1], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }  
  if(n >    2) { if (context.thread_index() < n && context.thread_index() >=    2) { if (!flg) { flg |= first1[context.thread_index() -    2]; val = binary_op(first2[context.thread_index() -    2], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; } 
  if(n >    4) { if (context.thread_index() < n && context.thread_index() >=    4) { if (!flg) { flg |= first1[context.thread_index() -    4]; val = binary_op(first2[context.thread_index() -    4], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >    8) { if (context.thread_index() < n && context.thread_index() >=    8) { if (!flg) { flg |= first1[context.thread_index() -    8]; val = binary_op(first2[context.thread_index() -    8], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   16) { if (context.thread_index() < n && context.thread_index() >=   16) { if (!flg) { flg |= first1[context.thread_index() -   16]; val = binary_op(first2[context.thread_index() -   16], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   32) { if (context.thread_index() < n && context.thread_index() >=   32) { if (!flg) { flg |= first1[context.thread_index() -   32]; val = binary_op(first2[context.thread_index() -   32], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >   64) { if (context.thread_index() < n && context.thread_index() >=   64) { if (!flg) { flg |= first1[context.thread_index() -   64]; val = binary_op(first2[context.thread_index() -   64], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  128) { if (context.thread_index() < n && context.thread_index() >=  128) { if (!flg) { flg |= first1[context.thread_index() -  128]; val = binary_op(first2[context.thread_index() -  128], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  256) { if (context.thread_index() < n && context.thread_index() >=  256) { if (!flg) { flg |= first1[context.thread_index() -  256]; val = binary_op(first2[context.thread_index() -  256], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n >  512) { if (context.thread_index() < n && context.thread_index() >=  512) { if (!flg) { flg |= first1[context.thread_index() -  512]; val = binary_op(first2[context.thread_index() -  512], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
  if(n > 1024) { if (context.thread_index() < n && context.thread_index() >= 1024) { if (!flg) { flg |= first1[context.thread_index() - 1024]; val = binary_op(first2[context.thread_index() - 1024], val); } } context.barrier(); first1[context.thread_index()] = flg; first2[context.thread_index()] = val; context.barrier(); } else { return; }
} // end inplace_inclusive_segscan()

} // end namespace block
} // end namespace cuda
} // end namespace backend
} // end namespace detail
} // end namespace thrust

