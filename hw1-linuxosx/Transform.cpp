// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	mat3 returnmat = (cos(degrees*pi/180.0f)*glm::mat3( 1.0 ))+((1-cos(degrees*pi/180.0f))*glm::outerProduct(axis,axis))+sin(degrees*pi/180.0f)*glm::mat3(0,axis.z,-axis.y,-axis.z,0,axis.x,axis.y,-axis.x,0);
  // You will change this return call
  return returnmat;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	vec3 axis = up;
	eye = Transform::rotate(degrees,axis)*eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 axis = glm::cross(eye,up);
	axis = glm::normalize(axis);
	up = Transform::rotate(degrees, axis) * up;
	eye = Transform::rotate(degrees,axis)*eye;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(glm::normalize(up),eye));
	vec3 v = glm::normalize(glm::cross(w,u));
	glm::mat4 rot = glm::mat4(u.x,u.y,u.z,0,v.x,v.y,v.z,0,w.x,w.y,w.z,0,0,0,0,1);
	rot = glm::transpose(rot);
	mat4 traslate = glm::mat4(1,0,0,-eye.x,0,1,0,-eye.y,0,0,1,-eye.z,0,0,0,1);
	traslate = glm::transpose(traslate);
	//glm::mat4 returnmat = glm::lookAt(eye,glm::vec3(0,0,0),up);
	glm::mat4 returnmat = rot*traslate;
  // You will change this return call
  return returnmat;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
