#include <cmath>
#include <glm/glm.hpp>

int floatToint(float a)
{
    return static_cast<int>(std::round(a));
}

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

bool cmpVec3(const glm::vec3 &A, const glm::vec3 &B, float epsilon = 0.005f)
{
    return (cmpf(A.x, B.x, epsilon) && cmpf(A.y, B.y, epsilon) && cmpf(A.z, B.z, epsilon));
}