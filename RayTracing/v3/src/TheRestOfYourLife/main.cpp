// ... includes

#include "Globals.h"
#include "PROGRESS_RENDERER.h"

#include <iostream>
#include <cstdio>
#include <future>
#include <chrono>

// ray_color ...

// cornell_box ...

void RenderWorker(const hittable_list& world, const camera& cam, const color& background, shared_ptr<hittable_list>& lights, int js, int je, int is, int ie)
{
	// Render - MODIFIED
	for (int j = js; j >= je; --j)
	{
		for (int i = is; i <= ie; ++i)
		{
			// color ...
			write_color(pixel_color, samples_per_pixel, j, i);
		}
	}
}

int main() {
	std::future<int> RENDERER;
	char mode = std::cin.get();
	if (mode == '\n')
		RENDERER = std::async(std::launch::async, PROGRESS_WINDOW_RENDER);
	std::cin.get();

	// World ...

	// Camera ...

	// Render
	auto start = std::chrono::high_resolution_clock::now();
	std::cerr << image_width << ' ' << image_height << '\n';

	int max_threads = 16;
	std::vector<std::future<void>> threadPool;
	threadPool.reserve(max_threads);

	int pieces_on_horizontal = 32;
	int piece_size = image_width / pieces_on_horizontal;

	int pieces_left = (1 + (image_width / piece_size) + ((image_width % piece_size) ? 1 : 0)) * ((image_height / piece_size) + ((image_height % piece_size) ? 1 : 0));

	int processed_height = 0;
	int processed_width = 0;

	for (int i = 0; i < max_threads; i++)
	{
		threadPool.push_back(std::async(std::launch::async, []() { return; }));
	}

	while (pieces_left > 0)
	{
		for (int i = 0; i < max_threads; i++)
		{
			if (threadPool[i].wait_for(std::chrono::seconds(0)) != std::future_status::ready)
				continue;

			int js = image_height - 1 - processed_height;
			int is = processed_width;
			int je = js - piece_size;
			int ie = is + piece_size;

			if (js - piece_size < 0)
				je = 0;
			if (is + piece_size >= image_width)
				ie = image_width - 1;

			threadPool[i] = std::async(std::launch::async, RenderWorker, world, cam, background, lights, js, je, is, ie);
			processed_width += piece_size;
			if (processed_width > image_width)
			{
				processed_width = 0;
				processed_height += piece_size;
			}
			if (pieces_left <= 0)
				break;

			pieces_left--;
			std::cerr << "\rSectors remaining: " << pieces_left << ' ' << std::flush;
		}
	}
	for (int i = 0; i < max_threads; i++)
	{
		threadPool[i].wait();
	}

	std::cerr << "\nDone.\n";
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "Render time: " << duration.count() / 1000 << " sec and " << duration.count() % 1000 << " ms\n";

	if (mode == 'l')
		RENDERER = std::async(std::launch::async, PROGRESS_WINDOW_RENDER);

	PROGRESS_DONE = true;
	return 0;
}