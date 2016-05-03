#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

int main() {
  cl_platform_id platform;
  cl_device_id *devices;
  cl_uint num_devices, addr_data;
  cl_int i, err;
  char name_data[48], ext_data[4096];
  // Access first platform
  err = clGetPlatformIDs(1, &platform, NULL);
  if(err < 0) {
    perror("Couldn't find any platforms");
    exit(1);
  }
  // Determine number of devices
  err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, NULL, &num_devices);
  if(err < 0) {
    perror("Couldn't find any devices");
    exit(1);
  }
  // Allocate device memory
  devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);
  // Populate device memory
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);
  for(i=0; i<num_devices; i++) {
    // Get device name
    err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(name_data), name_data, NULL);
    if(err < 0) {
      perror("Couldn't read extension data");
      exit(1);
    }
    // Get device address width
    clGetDeviceInfo(devices[i], CL_DEVICE_ADDRESS_BITS, sizeof(ext_data), &addr_data, NULL);
    // Get device extensions
    clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS, sizeof(ext_data), ext_data, NULL);
    printf("NAME: %s\nADDRESS_WIDTH: %u\nEXTENSIONS: %s\n", name_data, addr_data, ext_data);
  }
  free(devices);
  return 0;
}