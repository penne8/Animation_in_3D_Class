#pragma once
#include <Eigen/core>
#include <Eigen/Geometry>
#include <Eigen/dense>


class Movable
{
public:
	Movable();
	Movable(const Movable& mov);
	Eigen::Matrix4f MakeTransScale();
	Eigen::Matrix4d MakeTransd();
	Eigen::Matrix4d MakeTransScaled();
	void MyTranslate(Eigen::Vector3d amt, bool preRotation);
	void TranslateInSystem(Eigen::Matrix3d rot, Eigen::Vector3d amt);
	void Movable::SetCenterOfRotation(Eigen::Vector3d amt);
	void MyRotate(Eigen::Vector3d rotAxis, double angle);
	void RotateInSystem(Eigen::Matrix3d preRot, Eigen::Vector3d rotAxis, double angle);
	void EulerRotation(Eigen::Vector3d rotAxis, double angle, bool limit);
	void MyRotate(const Eigen::Matrix3d &rot);
	void MyScale(Eigen::Vector3d amt);

	Eigen::Matrix3d GetRotation() const{ return Tout.rotation().matrix(); }
	Eigen::Vector3d GetTranslation() const { return Tout.translation(); }

	virtual ~Movable() {}
private:
	Eigen::Affine3d Tout,Tin;
};

