/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include <cstdlib>
#include "light_source.h"

void PointLight::shade( Ray3D& ray) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  


/*
// point of intersection
	auto point = ray.intersection.point;
	// point material
	auto material = *(ray.intersection.mat);


	// light direction
	auto lightDir = (_pos - point);
	lightDir.normalize();
	// normal at point
	auto normal =  ray.intersection.normal;
	// diffuse component. FIXME
	auto diffuseLight = std::max(normal.dot(lightDir), 0.0);
	auto diffuseComponent =  material. diffuse * Colour(diffuseLight, diffuseLight, diffuseLight);
	// specular direction
	auto specularDir = (2.0 * lightDir.dot(normal)*normal - lightDir);
	specularDir.normalize();
	// view dir, is the opposite of ray dir
	auto viewDir = -ray.dir;
	// assert(viewDir.length() == 1);
	// specular component
	auto specularLight = std::pow(std::max(specularDir.dot(viewDir), 0.0), material.specular_exp);
	auto specularComponent = material.specular * Colour(specularLight, specularLight, specularLight);
	// final color, should be added to existing color of the ray
	auto finalColor = (material.ambient + diffuseComponent + specularComponent);
	finalColor.clamp();
	ray.col = ray.col + finalColor;
*/


	if(ray.intersection.mat->texture != 0)
	{
		// in scene object.cpp convert the object space intersection point to texture coordinates if(texture == true)
		// then do a texture lookup here	
		Colour lighting(0.0, 0.0, 0.0);
		int u = ray.intersection.u;
		int v = ray.intersection.v;
		unsigned char red = (*ray.intersection.mat->rarray)[v*ray.intersection.mat->width + u];
		unsigned char green = (*ray.intersection.mat->garray)[v*ray.intersection.mat->width + u];
		unsigned char blue = (*ray.intersection.mat->barray)[v*ray.intersection.mat->width + u];
		lighting[0] = ((double)red)/255;
		lighting[1] = ((double)green)/255;
		lighting[2] = ((double)blue)/255;
		ray.col = lighting;
	}
	else
	{
	Vector3D lightvec = _pos - ray.intersection.point;
	Vector3D reflection = 2 * lightvec.dot(ray.intersection.normal) * ray.intersection.normal - lightvec;
	reflection.normalize();
	Vector3D view = -ray.dir;
	view.normalize();
	Colour lighting = _col_ambient * (ray.intersection.mat)->ambient;
	//ray.col.clamp();
	//std::cout<<"colour of ambient: "<<_col_ambient[0]<<", "<<_col_ambient[1]<<" and "<<_col_ambient[2];
	lightvec.normalize();
	double product = fmax(0.0, lightvec.dot(ray.intersection.normal));
	Colour diffuse_colour = _col_diffuse * (ray.intersection.mat)->diffuse;
	//auto diffuse_shading(product*diffuse_colour[0], product*diffuse_colour[1], product*diffuse_colour[2]);
	lighting = lighting + (product * diffuse_colour);
	//lighting = lighting + diffuse_shading;
	//ray.col.clamp();
	product = std::pow(fmax(0.0, reflection.dot(view)), (ray.intersection.mat)->specular_exp);
	Colour specular_colour = _col_specular * (ray.intersection.mat)->specular;
	lighting = lighting + (product * specular_colour);
	lighting.clamp();
	ray.col = ray.col + lighting;
	}

	//	shadeRay(ray, 1.0);

}

void AreaLight::shade( Ray3D& ray) 
{


}
void AreaLight::shadePoint( Ray3D& ray, Point3D& point) 
{
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  

	double factor = 1.0 / (this->width * this->height);
	if(ray.intersection.mat->texture != 0)
	{

		// in scene object.cpp convert the object space intersection point to texture coordinates if(texture == true)

		// then do a texture lookup here	
		Colour lighting(0.0, 0.0, 0.0);
		int u = ray.intersection.u;
		int v = ray.intersection.v;
		unsigned char red = (*ray.intersection.mat->rarray)[v*ray.intersection.mat->width + u];
		unsigned char green = (*ray.intersection.mat->garray)[v*ray.intersection.mat->width + u];
		unsigned char blue = (*ray.intersection.mat->barray)[v*ray.intersection.mat->width + u];
		lighting[0] =  factor * ((double)red)/255;
		lighting[1] =  factor * ((double)green)/255;
		lighting[2] =  factor * ((double)blue)/255;
		ray.col = ray.col + lighting;
	}
	else
	{
		Vector3D lightvec = point - ray.intersection.point;
		Vector3D reflection = 2 * lightvec.dot(ray.intersection.normal) * ray.intersection.normal - lightvec;

		reflection.normalize();
		Vector3D view = -ray.dir;
		view.normalize();
		Colour lighting = this->_col_ambient * (ray.intersection.mat)->ambient;

		lightvec.normalize();
		double product = fmax(0.0, lightvec.dot(ray.intersection.normal));
		Colour diffuse_colour = this->_col_diffuse * (ray.intersection.mat)->diffuse;

		lighting = lighting + (product * diffuse_colour);
		//lighting = lighting + diffuse_shading;
		//ray.col.clamp();
		product = std::pow(fmax(0.0, reflection.dot(view)), (ray.intersection.mat)->specular_exp);
		Colour specular_colour = this->_col_specular * (ray.intersection.mat)->specular;
		lighting = lighting + (product * specular_colour);
		//lighting = factor * lighting;
		lighting.clamp();
		//ray.col = lighting;
		ray.col = ray.col + (factor * lighting);
	}

}












/*
void shadeRay(Ray3D& ray, double factor, Point3D& point)
{
	if(ray.intersection.mat->texture != 0)
	{
		// in scene object.cpp convert the object space intersection point to texture coordinates if(texture == true)
		// then do a texture lookup here	
		Colour lighting(0.0, 0.0, 0.0);
		int u = ray.intersection.u;
		int v = ray.intersection.v;
		unsigned char red = (*ray.intersection.mat->rarray)[v*ray.intersection.mat->width + u];
		unsigned char green = (*ray.intersection.mat->garray)[v*ray.intersection.mat->width + u];
		unsigned char blue = (*ray.intersection.mat->barray)[v*ray.intersection.mat->width + u];
		lighting[0] = factor * ((double)red)/255;
		lighting[1] = factor * ((double)green)/255;
		lighting[2] = factor * ((double)blue)/255;
		ray.col = lighting;
	}
	else
	{
		Vector3D lightvec = point - ray.intersection.point;
		Vector3D reflection = 2 * lightvec.dot(ray.intersection.normal) * ray.intersection.normal - lightvec;
		reflection.normalize();
		Vector3D view = -ray.dir;
		view.normalize();
		Colour lighting = this->_col_ambient * (ray.intersection.mat)->ambient;
		//ray.col.clamp();
		//std::cout<<"colour of ambient: "<<_col_ambient[0]<<", "<<_col_ambient[1]<<" and "<<_col_ambient[2];
		lightvec.normalize();
		double product = fmax(0.0, lightvec.dot(ray.intersection.normal));
		Colour diffuse_colour = this->_col_diffuse * (ray.intersection.mat)->diffuse;
		//auto diffuse_shading(product*diffuse_colour[0], product*diffuse_colour[1], product*diffuse_colour[2]);
		lighting = lighting + (product * diffuse_colour);
		//lighting = lighting + diffuse_shading;
		//ray.col.clamp();
		product = std::pow(fmax(0.0, reflection.dot(view)), (ray.intersection.mat)->specular_exp);
		Colour specular_colour = this->_col_specular * (ray.intersection.mat)->specular;
		lighting = lighting + (product * specular_colour);
		lighting = factor * lighting;
		lighting.clamp();
		//ray.col = lighting;
		ray.col = ray.col + lighting;
	}
}
*/
