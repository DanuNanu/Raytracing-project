#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include<iostream>
#include <stdexcept>

class vec3 {
    public:
        double elm[3];

        vec3() : elm{0,0,0} {}
        vec3(double e0, double e1, double e2) : elm{e0, e1, e2} {}

        // getters for x,y,z coords
        double x() const {
            return elm[0];
        }

        double y() const {
            return elm[1];
        }

        double z() const {
            return elm[2];
        }

        vec3 operator-() const { return vec3(-elm[0], -elm[1], -elm[2]);}

        double operator[](int i) const {return elm[i];}
        double& operator[](int i) {return elm[i]; }

        vec3& operator+=(const vec3& v2) {
            elm[0] += v2.elm[0];
            elm[1] += v2.elm[1];
            elm[2] += v2.elm[2];
            return *this;
        }

        vec3& operator*= (double c) {
            elm[0] *= c;
            elm[1] *= c;
            elm[2] *= c;
            return *this;
        }

        vec3& operator/=(double c) {
            elm[0] /= c;
            elm[1] /= c;
            elm[2] /= c;
            return *this;

        }

        double norm_sqrd() const {
            return elm[0]*elm[0] + elm[1]*elm[1] + elm[2]*elm[2];
        }

        double norm() const {
            return sqrt(norm_sqrd());
        }

        static vec3 random() {
            return vec3(random_double(),random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
    

};

using coord3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.elm[0] << ' ' << v.elm[1] << v.elm[2];
}

inline vec3 operator+ (const vec3& u, const vec3& v) {
    return vec3(u.elm[0] + v.elm[0], u.elm[1] + v.elm[1], u.elm[2] + v.elm[2]);
}

inline vec3 operator- (const vec3& u, const vec3& v) {
    return vec3(u.elm[0] - v.elm[0], u.elm[1] - v.elm[1], u.elm[2] - v.elm[2]);

}

inline vec3 operator* (const vec3& u, const vec3& v) {
    return vec3(u.elm[0] * v.elm[0], u.elm[1] * v.elm[1], u.elm[2] * v.elm[2]);
}
inline vec3 operator* (double c, const vec3& v) {
    return vec3(c*v.elm[0], c*v.elm[1], c*v.elm[2]);
}

inline vec3 operator*(const vec3& v, double c) {
    return c*v;
}


inline vec3 operator/(const vec3& v, double c) {
    if (c == 0.0) {
        throw std::invalid_argument("Cannot divide by 0");
    }
    return (1/c)*v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.elm[0]*v.elm[0] + u.elm[1]*v.elm[1] + u.elm[2]*v.elm[2]; 
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.elm[1]*v.elm[2] - u.elm[2]*v.elm[1],
     u.elm[2]*v.elm[0]- u.elm[0]*v.elm[2],
      u.elm[0]*v.elm[1] - u.elm[1]*v.elm[0]);
}

inline vec3 unit_vec(const vec3& v) {
    return v/v.norm();
}

inline vec3 random_unit_vector() {
    while(true) {
        auto point = vec3::random(-1,1);
        auto lens = point.norm_sqrd();
        if (1e-160 <lens && lens <=1) {
            return point/sqrt(lens);
        }
    }
}

inline vec3 correct_hem(const vec3& normal) {
    vec3 p_on_unit = random_unit_vector();
    if (dot (p_on_unit, normal) > 0) {
        return p_on_unit;
    } 
    return -p_on_unit;
}

#endif