#define __CL_ENABLE_EXCEPTIONS

#define CL_HPP_MINIMUM_OPENCL_VERSION 300
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include "Globals.h"
#include "PROGRESS_RENDERER.h"

#include <CL/cl.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <vector>
#include <chrono>
#include <future>


char* loadFile(const char* fileName)
{
	FILE* file = fopen(fileName, "rb");
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = (char*)malloc(file_size + 1);
	fread(data, 1, file_size, file);
	fclose(file);

	data[file_size] = 0;

	return data;
}

int init()
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	if (platforms.size() == 0) {
		printf("Platform size 0\n");
		return -1;
	}
	for (auto platform : platforms) {
		printf("%s\n", platform.getInfo<CL_PLATFORM_NAME>().data());
	}

	{
		std::vector<cl::Device> devices;
		platforms.front().getDevices(CL_DEVICE_TYPE_GPU, &devices);
		if (devices.size() == 0) {
			printf("Device size 0\n");
			return -1;
		}
		for (auto device : devices) {
			printf("%s\n", device.getInfo<CL_DEVICE_NAME>().data());
		}
	}
}

void ExecuteKernel()
{
	char* src = loadFile("OpenCL_src/main.cl");

	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	cl_context_properties properties[] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)(platforms[0])(),
		0
	};

	cl::Context context(CL_DEVICE_TYPE_GPU, properties);

	std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

	cl_int err = CL_SUCCESS;
	try {
		cl::Program::Sources source(1, std::make_pair(src, strlen(src)));

		cl::Program program_1 = cl::Program(context, source);
		program_1.build(devices, "-I \"OpenCL_src\"");

		cl::Kernel kernel(program_1, "main", &err);

		cl::CommandQueue queue(context, devices[0], 0, &err);

		cl_mem_flags flags = CL_MEM_WRITE_ONLY;
		cl::Buffer buf(context, flags, (size_t)image.size(), nullptr, &err);

		kernel.setArg(0, buf);
		kernel.setArg(1, image_width);
		kernel.setArg(2, image_height);

		cl::Event event;
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(image_width, image_height), cl::NDRange(1, 1), NULL, &event);
		event.wait();

		std::vector<cl::Event> events;
		queue.enqueueReadBuffer(buf, CL_TRUE, 0, (size_t)image.size(), (void*)image.data(),&events);
		for (auto event_ : events)
			event_.wait();
	}
	catch (cl::Error err) {
		std::cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << std::endl;
	}
}


int main(void)
{
	if (init() == -1)
		return -1;

	std::future<int> RENDERER;
	char mode = std::cin.get();
	if (mode == '\n')
		RENDERER = std::async(std::launch::async, PROGRESS_WINDOW_RENDER);
	std::cin.get();


	auto start = std::chrono::high_resolution_clock::now();
	std::cerr << image_width << ' ' << image_height << '\n';


	ExecuteKernel();


	std::cerr << "\nDone.\n";
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "Render time: " << duration.count() / 1000 << " sec and " << duration.count() % 1000 << " ms\n";

	if (mode == 'l')
		RENDERER = std::async(std::launch::async, PROGRESS_WINDOW_RENDER);

	PROGRESS_DONE = true;

	return EXIT_SUCCESS;
}