#include "Globals.h"
#include "PROGRESS_RENDERER.h"

#include "PCH.h"

#include "Scenes.h" // top half of main.cc from v3/TheNextWeek

#include <iostream>
#include <cstdio>
#include <future>
#include <chrono>

color ray_color(const ray& r, const color& background, const hittable& world, shared_ptr<hittable_list>& lights, int depth)
{
	hit_record rec;

	if (depth <= 0)
		return color(0, 0, 0);

	if (!world.hit(r, 0.001, infinity, rec))
		return background;

	//ray scattered;
	//color attenuation;
	//color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
	//double pdf_val;
	//color albedo;
	//
	//if (!rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf_val))
	//	return emitted;
		//return attenuation * ray_color(scattered, world, depth - 1);


	//auto on_light = point3(random_double(213, 343), 554, random_double(227, 332));
	//auto to_light = on_light - rec.p;
	//auto distance_squared = to_light.length_squared();
	//to_light = unit_vector(to_light);
	//
	//if (dot(to_light, rec.normal) < 0)
	//	return emitted;
	//
	//double light_area = (343 - 213) * (332 - 227);
	//auto light_cosine = fabs(to_light.y());
	//if (light_cosine < 0.000001)
	//	return emitted;
	//pdf = distance_squared / (light_cosine * light_area);
	//scattered = ray(rec.p, to_light, r.time());

	//cosine_pdf p(rec.normal);
	//scattered = ray(rec.p, p.generate(), r.time());
	//pdf_val = p.value(scattered.direction());

	//hittable_pdf light_pdf(lights, rec.p);
	//scattered = ray(rec.p, light_pdf.generate(), r.time());
	//pdf_val = light_pdf.value(scattered.direction());


	//auto p0 = make_shared<hittable_pdf>(lights, rec.p);
	//auto p1 = make_shared<cosine_pdf>(rec.normal);
	//mixture_pdf mixed_pdf(p0, p1);
	//
	//scattered = ray(rec.p, mixed_pdf.generate(), r.time());
	//pdf_val = mixed_pdf.value(scattered.direction());
	//
	//return emitted + albedo * rec.mat_ptr->scattering_pdf(r, rec, scattered) * ray_color(scattered, background, world, lights, depth - 1) / pdf_val;


	scatter_record srec;
	color emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
	if (!rec.mat_ptr->scatter(r, rec, srec))
		return emitted;

	if (srec.is_specular)
	{
		return srec.attenuation
			* ray_color(srec.specular_ray, background, world, lights, depth - 1);
	}

	auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);
	mixture_pdf p(light_ptr, srec.pdf_ptr);

	ray scattered = ray(rec.p, p.generate(), r.time());
	auto pdf_val = p.value(scattered.direction());

	return emitted
		+ srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
		* ray_color(scattered, background, world, lights, depth - 1) / pdf_val;


	//vec3 unit_direction = unit_vector(r.direction());
	//auto t = 0.5 * (unit_direction.y() + 1.0);
	//return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void RenderWorker(const hittable_list& world, const Camera& cam, const color& background, shared_ptr<hittable_list>& lights, int js, int je, int is, int ie)
{
	for (int j = js; j >= je; --j)
	{
		for (int i = is; i <= ie; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, background, world, lights, max_depth);
			}
			write_color(pixel_color, samples_per_pixel, j, i);
		}
	}
}

int main()
{
	std::future<int> RENDERER;
	char mode = std::cin.get();
	if(mode == '\n')
		RENDERER = std::async(std::launch::async, PROGRESS_WINDOW_RENDER);
	std::cin.get();
	//// dielectric spheres that use negative radius have unchanged geometry but the surface normal points inwards
	//// can be used as bubble to make hollow glass sphere
	// subsurface reflection sphere : a volume inside a dielectric is what a subsurface material is
	// The biggest limitation left in the renderer is no shadow rays, but that is why we get caustics and subsurface for free. It�s a double-edged design decision.

	hittable_list world;

	point3 lookfrom;
	point3 lookat;
	auto vfov = 40.0;
	auto aperture = 0.0;
	color background(0, 0, 0);
	auto lights = make_shared<hittable_list>();

	switch (Current_Scene)
	{
	case 1:
		world = random_scene();
		background = color(0.70, 0.80, 1.00);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;
	case 2:
		world = two_spheres();
		background = color(0.70, 0.80, 1.00);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;
	case 3:
		world = two_perlin_spheres();
		background = color(0.70, 0.80, 1.00);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;
	case 4:
		world = earth();
		background = color(0.70, 0.80, 1.00);
		lookfrom = point3(13, 2, 3);
		lookat = point3(0, 0, 0);
		vfov = 20.0;
		break;
	case 5:
		world = simple_light();
		samples_per_pixel = 400;
		background = color(0.0, 0.0, 0.0);
		lookfrom = point3(26, 3, 6);
		lookat = point3(0, 2, 0);
		vfov = 20.0;
		break;
	case 6:
		// Special globals !!!
		world = cronell_box();
		lights->add(make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>()));
		lights->add(make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>()));
		samples_per_pixel = 1000;
		background = color(0, 0, 0);
		lookfrom = point3(278, 278, -800);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;
	case 7:
		world = cornell_smoke();
		samples_per_pixel = 200;
		lookfrom = point3(278, 278, -800);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;
	case 8:
		world = final_scene();
		samples_per_pixel = 10000;
		background = color(0, 0, 0);
		lookfrom = point3(478, 278, -600);
		lookat = point3(278, 278, 0);
		vfov = 40.0;
		break;
	}

	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;

	Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	// RENDER
	auto start = std::chrono::high_resolution_clock::now();
	std::cerr << image_width << ' ' << image_height << '\n';
	
	//PPM
	// 
	//std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	//for (int j = image_height - 1; j >= 0; --j)
	//{
	//	std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
	//	for (int i = 0; i < image_width; ++i)
	//	{
	//		color pixel_color(0, 0, 0);
	//		for (int s = 0; s < samples_per_pixel; ++s) {
	//			auto u = (i + random_double()) / (image_width - 1);
	//			auto v = (j + random_double()) / (image_height - 1);
	//			ray r = cam.get_ray(u, v);
	//			pixel_color += ray_color(r, world, max_depth);
	//		}
	//		write_color(std::cout, pixel_color, samples_per_pixel);
	//	}
	//}

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