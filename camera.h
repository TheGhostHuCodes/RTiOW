#pragma once

#include "ray.h"

class camera {
  public:
    camera(vec3 look_from, vec3 look_at, vec3 v_up, float vfov,
           float aspect) { // vfov is top to bottom in degrees.
        vec3 u, v, w;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = look_from;
        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(v_up, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * u - half_height * v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }
    ray get_ray(float s, float t) {
        return ray(origin,
                   lower_left_corner + s * horizontal + t * vertical - origin);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
