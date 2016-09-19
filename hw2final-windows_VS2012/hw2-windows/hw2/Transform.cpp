// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	vec3 nrml = glm::normalize(axis);
	float rad = degrees * pi / 180.0;
	return cos(rad) * mat3()
		+ (1 - cos(rad)) * mat3(nrml.x * nrml.x,
			nrml.x * nrml.y,
			nrml.x * nrml.z, nrml.x * nrml.y,
			nrml.y * nrml.y,
			nrml.y * nrml.z, nrml.z * nrml.x,
			nrml.y * nrml.z,
			nrml.z * nrml.z)
		+ sin(rad) * mat3(0, nrml.z, -nrml.y, -nrml.z, 0, nrml.x, nrml.y, -nrml.x, 0);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = eye * rotate(-degrees, glm::normalize(up));
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 w = glm::normalize(glm::cross(eye, up));
	eye = eye * rotate(-degrees, w);
	up = up * rotate(-degrees, w);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(glm::normalize(up), eye));
	vec3 v = glm::normalize(glm::cross(w, u));
	glm::mat4 rot = glm::mat4(u.x, u.y, u.z, 0, v.x, v.y, v.z, 0, w.x, w.y, w.z, 0, 0, 0, 0, 1);
	rot = glm::transpose(rot);
	mat4 traslate = glm::mat4(1, 0, 0, -eye.x, 0, 1, 0, -eye.y, 0, 0, 1, -eye.z, 0, 0, 0, 1);
	traslate = glm::transpose(traslate);
	//glm::mat4 returnmat = glm::lookAt(eye,glm::vec3(0,0,0),up);
	glm::mat4 returnmat = rot*traslate;
	// You will change this return call
	return returnmat;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
   
	float theta = glm::radians(fovy) / 2 ;
	float d = 1 / tanf(theta);
	float A = -((zFar + zNear) / (zFar - zNear));
	float B = -((2 * zFar*zNear) / (zFar - zNear));

	glm::mat4 ret = glm::mat4((d /aspect), 0, 0, 0, 0, d, 0, 0, 0, 0, A, -1, 0, 0, B, 0);
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  

	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	mat4 ret = mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 

    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	mat4 ret = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
