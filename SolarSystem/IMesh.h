#pragma once 
#define _USE_MATH_DEFINES 
#include <cmath> 
#include <vector> 
#include <glm/vec3.hpp> 
#include <glm/glm.hpp> 
 
struct IMesh 
{ 
  std::vector<glm::vec3> vertices; 
  std::vector<uint32_t> triangles; 
 
  uint32_t triangleCount() const { return triangles.size() / 3; } 
 
  void addTriangle(uint32_t a, uint32_t b, uint32_t c) 
  { 
    triangles.emplace_back(a); 
    triangles.emplace_back(b); 
    triangles.emplace_back(c); 
  } 
 
  void addQuad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) 
  { 
    triangles.emplace_back(a); 
    triangles.emplace_back(b); 
    triangles.emplace_back(c); 
    triangles.emplace_back(a); 
    triangles.emplace_back(c); 
    triangles.emplace_back(d); 
  } 
 
  void addQuadAlt(uint32_t a, uint32_t b, uint32_t c, uint32_t d) 
  { 
    triangles.emplace_back(a); 
    triangles.emplace_back(b); 
    triangles.emplace_back(d); 
    triangles.emplace_back(b); 
    triangles.emplace_back(c); 
    triangles.emplace_back(d); 
  } 
 
  void clear() 
  { 
    vertices.clear(); 
    triangles.clear(); 
  } 
 
  double distance(const glm::vec3 &p, uint32_t tidx) const 
  { 
    const uint32_t idx0 = triangles[tidx]; 
    const uint32_t idx1 = triangles[tidx + 1]; 
    const uint32_t idx2 = triangles[tidx + 2]; 
    const glm::vec3 v0 = vertices[idx0]; 
    const glm::vec3 v1 = vertices[idx1]; 
    const glm::vec3 v2 = vertices[idx2]; 
    const glm::vec3 bv = v0; 
    const glm::vec3 e0 = v1 - v0; 
    const glm::vec3 e1 = v2 - v0; 
    const glm::vec3 dv = bv - p; 
    const double a = glm::dot(e0, e0); 
    const double b = glm::dot(e0, e1); 
    const double c = glm::dot(e1, e1); 
    const double d = glm::dot(e0, dv); 
    const double e = glm::dot(e1, dv); 
    const double f = glm::dot(dv, dv); 
 
    const double det = a * c - b * b; 
    double s = b * e - c * d; 
    double t = b * d - a * e; 
 
    if (s + t <= det) 
    { 
      if (s < 0.0) 
      { 
        if (t < 0.0) 
        { 
          // region 4 
          if (d < 0.0) 
          { 
            t = 0.0; 
            s = -d >= a ? 1.0 : -d / a; 
          } 
          else 
          { 
            s = 0.0; 
            t = e >= 0.0 ? 0.0 : (-e >= c ? 1.0 : -e / c); 
          } 
        } 
        else 
        { 
          // region 3 
          s = 0.0; 
          t = e >= 0.0 ? 0.0 : (-e >= c ? 1.0 : -e / c); 
        } 
      } 
      else if (t < 0.0) 
      { 
        // region 5 
        s = d >= 0.0 ? 0.0 : (-d >= a ? 1.0 : -d / a); 
        t = 0.0; 
      } 
      else 
      { 
        // region 0 
        const double invDet = 1.0 / det; 
        s *= invDet; 
        t *= invDet; 
      } 
    } 
    else 
    { 
      if (s < 0.0) 
      { 
        // region 2 
        const double tmp0 = b + d; 
        const double tmp1 = c + e; 
        if (tmp1 > tmp0) 
        { 
          const double numer = tmp1 - tmp0; 
          const double denom = a - 2.0 * b + c; 
          s = numer >= denom ? 1.0 : numer / denom; 
          t = 1.0 - s; 
        } 
        else 
        { 
          s = 0.0; 
          t = (tmp1 <= 0.0 ? 1.0 : (e >= 0.0 ? 0.0 : -e / c)); 
        } 
      } 
      else if (t < 0.0) 
      { 
        // region 6 
        const double tmp0 = b + e; 
        const double tmp1 = a + d; 
        if (tmp1 > tmp0) 
        { 
          const double numer = tmp1 - tmp0; 
          const double denom = a - 2.0 * b + c; 
          t = numer >= denom ? 1.0 : numer / denom; 
          s = 1.0 - t; 
        } 
        else 
        { 
          s = (tmp1 <= 0.0 ? 1.0 : (d >= 0.0 ? 0.0 : -d / a)); 
          t = 0.0; 
        } 
      } 
      else 
      { 
        // region 1 
        const double numer = c + e - b - d; 
        if (numer <= 0) 
        { 
          s = 0.0; 
        } 
        else 
        { 
          const double denom = a - 2.0 * b + c; 
          s = numer >= denom ? 1.0 : numer / denom; 
        } 
        t = 1.0 - s; 
      } 
    } 
 
    return length(p - (v0 + glm::vec3(s) * e0 + glm::vec3(t) * e1)); 
  } 
 
  double distance(const glm::vec3 &p) const 
  { 
    double min = 10e10; 
    for (uint32_t i = 0; i < triangles.size(); i += 3) 
    { 
      min = std::fmin(min, distance(p, i)); 
    } 
    return min; 
  } 
};