uniform float time

#pragma begin raym

Cube c( vec3(0.0, 1.0, 0.0) );
Sphere sphere( vec3(0.0, 1.5, 0.0), 1.0 );

Object o1;

o1 = c + sphere;        # union op

Object o2 = o1 - c;     # substraction op
Object o3 = o1 / c;     # intersection op

raymarch( 100.0, o ); # comment

#pragma end raym

void main() {
    #pragma raym

    vec4 color;

    // output :
    //  - RM_hit_object : int
    //  - RM_isect_pos : vec3
    //  - RM_normal : vec3

    switch(RM_hit_object) {
        case sphere:
            // lightning code
        break;

        case b:
            // lightning code
        break;

        case o:
            // lightning code
        break;
    }

    gl_fragColor = color;
}

