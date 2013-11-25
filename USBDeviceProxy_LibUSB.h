/*
 * Copyright 2013 Dominic Spill
 * Copyright 2013 Adam Stasiak
 *
 * This file is part of USB-MitM.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _LibUSBDeviceProxy_
#define _LibUSBDeviceProxy_

#ifndef LIBUSB_HOTPLUG_MATCH_ANY
#define LIBUSB_HOTPLUG_MATCH_ANY -1
#endif

#include <libusb-1.0/libusb.h>
#include "USBDeviceProxy.h"

class USBDeviceProxy_LibUSB:public USBDeviceProxy {
private:
	libusb_context* context;
	libusb_device_handle* dev_handle;
	bool privateContext;
	bool privateDevice;
	int desired_vid;
	int desired_pid;
	bool desired_hubs;

public:
	static int debugLevel;
	USBDeviceProxy_LibUSB(int vendorId=LIBUSB_HOTPLUG_MATCH_ANY,int productId=LIBUSB_HOTPLUG_MATCH_ANY,bool includeHubs=false);
	~USBDeviceProxy_LibUSB();

	int connect();
	int connect(int vendorId,int productId,bool includeHubs);
	int connect(libusb_device* dvc, libusb_context* _context=NULL);
	int connect(libusb_device_handle* devh,libusb_context* _context=NULL);
	void disconnect();
	void reset();
	bool is_connected();

	int control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8* dataptr);
	void send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length);
	void receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length);

	void claim_interface(__u8 interface);
	void release_interface(__u8 interface);

	__u8 get_address();
	const char* toString();
};

#endif