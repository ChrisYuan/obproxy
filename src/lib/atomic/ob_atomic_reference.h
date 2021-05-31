/**
 * Copyright (c) 2021 OceanBase
 * OceanBase Database Proxy(ODP) is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OB_ATOMIC_REFERENCE_H_
#define OB_ATOMIC_REFERENCE_H_
#include <stdint.h>

namespace oceanbase
{
namespace common
{

union AtomicInt64
{
  volatile uint64_t atomic;
  struct
  {
    uint32_t buffer;
    uint32_t pairs;
  };
  struct
  {
    uint32_t ref;
    uint32_t seq;
  };
};


class ObAtomicReference
{
public:
  ObAtomicReference();
  virtual ~ObAtomicReference();
  void reset();
  int inc_ref_cnt();
  int check_seq_num_and_inc_ref_cnt(const uint32_t seq_num);
  int check_and_inc_ref_cnt();
  int dec_ref_cnt_and_inc_seq_num(uint32_t &ref_cnt);
  inline uint32_t get_seq_num() const { return atomic_num_.seq; }
private:
  AtomicInt64 atomic_num_;
};

}
}

#endif /* OB_ATOMIC_REFERENCE_H_ */
