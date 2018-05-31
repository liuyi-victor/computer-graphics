/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld, Material* mat ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	// the above description is for object model space !
	Point3D trans_origin = worldToModel * ray.origin;
	Vector3D trans_dir = worldToModel * ray.dir;
	Ray3D trans_ray(trans_origin, trans_dir);

	if(trans_ray.origin[2] * trans_ray.dir[2] > 0)
	{
		return false;
	}
	double t = (-trans_origin[2]) / trans_dir[2];
	if(t < 1)
	{
		return false;
	}
	else if(ray.intersection.none == false && ray.intersection.t_value < t)
	{
		return false;
	}
	else
	{
		double x_intersection = trans_origin[0] + t * trans_dir[0];
		double y_intersection = trans_origin[1] + t * trans_dir[1];
		if(x_intersection < -0.5 || x_intersection > 0.5 || y_intersection < -0.5 || y_intersection > 0.5)
		{
			return false;
		}
		ray.intersection.none = false;
		ray.intersection.point = modelToWorld * (trans_origin + t * trans_dir);
		ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		ray.intersection.normal = modelToWorld * Vector3D(0,0,1);
		ray.intersection.normal.normalize();
		ray.intersection.mat = mat;
		if(mat->texture != 0)
		{
			ray.intersection.u = (x_intersection + 0.5) * mat->width;
			ray.intersection.v = (y_intersection + 0.5) * mat->height;
			//ray.intersection.obj = this;
		}
		return true;
	}
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld, Material* mat ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	// the above description is for object model space !
	Point3D trans_origin = worldToModel * ray.origin;
	Vector3D trans_dir = worldToModel * ray.dir;
	//Ray3D trans_ray(trans_origin, trans_dir);
	
	Vector3D trans_origin_vector = Vector3D(trans_origin[0], trans_origin[1], trans_origin[2]);
	// from the quadratic formula
	double a = trans_dir.dot(trans_dir);
	double b = 2*trans_origin_vector.dot(trans_dir);
	double c = trans_origin_vector.dot(trans_origin_vector) - 1;
	if((b*b - 4*a*c) < 0.0)
	{
		return false;
	}
	double t1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	double t2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
	if(t1 >= 1.0 && t2 >= 1.0)
	{
		double t = t1 < t2 ? t1 : t2;
		if(ray.intersection.none == false && ray.intersection.t_value < t)
			return false;
		Point3D model_space_poi = trans_origin + (t * trans_dir);
		Point3D world_space_poi = modelToWorld * model_space_poi;
		ray.intersection.point = world_space_poi;
		Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
		world_space_normal.normalize();
		//ray.intersection.normal = world_space_normal;
		ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		ray.intersection.t_value = t;
		ray.intersection.none = false;
		/*
		if(t1 < t2)
		{
			Point3D model_space_poi = trans_origin + (t1 * trans_dir);
			Point3D world_space_poi = modelToWorld * model_space_poi;
			ray.intersection.point = world_space_poi;
			Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
			world_space_normal.normalize();
			ray.intersection.normal = world_space_normal;
			ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		}
		else
		{
			Point3D model_space_poi = trans_origin + (t2 * trans_dir);
			Point3D world_space_poi = modelToWorld * model_space_poi;
			ray.intersection.point = world_space_poi;
			Vector3D world_space_normal = Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
			world_space_normal.normalize();
			ray.intersection.normal = world_space_normal;
			ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		}
	*/
		return true;
	}
	else if(t1 < 1.0 && t2 < 1.0)
	{
		return false;
	}
	else
	{
		double t = t1 > t2 ? t1 : t2;
		if(ray.intersection.none == false && ray.intersection.t_value < t)
			return false;
		Point3D model_space_poi = trans_origin + (t * trans_dir);
		Point3D world_space_poi = modelToWorld * model_space_poi;
		ray.intersection.point = world_space_poi;
		Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
		world_space_normal.normalize();
		ray.intersection.normal = world_space_normal;
		ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		//ray.intersection.t_value = t;
		ray.intersection.none = false;
/*
		if(t1 > t2)
		{
			Point3D model_space_poi = trans_origin + (t1 * trans_dir);
			Point3D world_space_poi = modelToWorld * (trans_origin + (t1 * trans_dir));
			ray.intersection.point = world_space_poi;
			Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
			world_space_normal.normalize();
			ray.intersection.normal = world_space_normal;
			ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		}
		else
		{
			Point3D model_space_poi = trans_origin + (t2 * trans_dir);
			Point3D world_space_poi = modelToWorld * (trans_origin + (t2 * trans_dir));
			ray.intersection.point = world_space_poi;
			Vector3D world_space_normal = Vector3D(2*model_space_poi[0], 2*model_space_poi[1], 2*model_space_poi[2]);
			world_space_normal.normalize();
			ray.intersection.normal = world_space_normal;
			ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		}
*/
		return true;
	}
}


bool UnitHyperboloid::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
			const Matrix4x4& modelToWorld, Material* mat )
{
	Point3D trans_origin = worldToModel * ray.origin;
	Vector3D trans_dir = worldToModel * ray.dir;
	Ray3D trans_ray(trans_origin, trans_dir);

	double vx = ray.dir[0];
	double vy = ray.dir[1];
	double vz = ray.dir[2];

	double ex = ray.origin[0];
	double ey = ray.origin[1];
	double ez = ray.origin[2];

	// from the quadratic formula
	double a = vx*vx + vy*vy - vz*vz;
	double b = 2*(ex*vx + ey*vy - ez*vz);
	double c = (ex*ex + ey*ey - ez*ez) - 1;	

	if((b*b - 4*a*c) < 0.0)
	{
		return false;
	}
	double t1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	double t2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
	if(t1 >= 0.0 && t2 >= 0.0)
	{
		double t = t1 < t2 ? t1 : t2;
		if(ray.intersection.none == false && ray.intersection.t_value < t)
			return false;
		Point3D model_space_poi = trans_origin + (t * trans_dir);
		if(model_space_poi[2] > 2 || model_space_poi[2] < -2)
			return false;
		Point3D world_space_poi = modelToWorld * model_space_poi;
		ray.intersection.point = world_space_poi;
		Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], -2*model_space_poi[2]);
		world_space_normal.normalize();
		ray.intersection.normal = world_space_normal;
		ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];

		return true;
	}
	else if(t1 < 0.0 && t2 < 0.0)
	{
		return false;
	}
	else
	{
		double t = t1 > t2 ? t1 : t2;
		if(ray.intersection.none == false && ray.intersection.t_value < t)
			return false;
		Point3D model_space_poi = trans_origin + (t * trans_dir);
		if(model_space_poi[2] > 2 || model_space_poi[2] < -2)
			return false;
		Point3D world_space_poi = modelToWorld * model_space_poi;
		ray.intersection.point = world_space_poi;
		Vector3D world_space_normal = modelToWorld * Vector3D(2*model_space_poi[0], 2*model_space_poi[1], -2*model_space_poi[2]);
		world_space_normal.normalize();
		ray.intersection.normal = world_space_normal;
		ray.intersection.t_value = (ray.intersection.point[0] - ray.origin[0]) / ray.dir[0];
		ray.intersection.none = false;

		return true;
	}
}
