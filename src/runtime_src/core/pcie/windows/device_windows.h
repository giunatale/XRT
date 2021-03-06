/**
 * Copyright (C) 2019 Xilinx, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef DEVICE_WINDOWS_H
#define DEVICE_WINDOWS_H

#include "common/device_pcie.h"

namespace xrt_core {

class device_windows : public device_pcie
{
public:
  struct IOCTLEntry {
    std::function<void(const device_windows*, QueryRequest, const std::type_info&, boost::any&)> m_fcn;
  };

  const IOCTLEntry & get_IOCTL_entry( QueryRequest qr) const;

  device_windows(id_type device_id, bool user);
  ~device_windows();

  xclDeviceHandle
  get_mgmt_handle() const
  {
    return m_mgmthdl;
  }

  xclDeviceHandle
  get_user_handle() const
  {
    return get_device_handle();
  }

  // query functions
  virtual void read_dma_stats(boost::property_tree::ptree &_pt) const;
  virtual void query(QueryRequest qr, const std::type_info & tinfo, boost::any& value) const;

  virtual void read(uint64_t addr, void* buf, uint64_t len) const;
  virtual void write(uint64_t addr, const void* buf, uint64_t len) const;

private:
  xclDeviceHandle m_mgmthdl = XRT_NULL_HANDLE;
};

} // xrt_core

#endif
