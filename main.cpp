#include "camera.h"
#include "hitable_list.h"
#include "material.h"
#include "sphere.h"
#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

vec3 color(const ray& r, hitable* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50
            && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;

    // PPM header information.
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;

    // PPM image pixel values.
    hitable* list[5];
    list[0]
        = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100,
                         new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2]
        = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
    hitable* world = new hitable_list(list, 5);

    vec3 look_from(3, 3, 2);
    vec3 look_at(0, 0, -1);
    float dist_to_focus = (look_from - look_at).length();
    float aperture = 2;
    camera cam(look_from, look_at, vec3(0, 1, 0), 20, float(nx) / float(ny),
               aperture, dist_to_focus);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {

                float u = float(i + distribution(generator)) / float(nx);
                float v = float(j + distribution(generator)) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}
