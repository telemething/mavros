/**
 * @brief Frame conversions helper functions
 * @file uas_frame_conversions.cpp
 * @author Nuno Marques <n.marques21@hotmail.com>
 *
 * @addtogroup nodelib
 * @{
 */
/*
 * Copyright 2015 Nuno Marques.
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */
#include <array>
#include <mavros/mavros_uas.h>
#include <boost/math/constants/constants.hpp>

using namespace mavros;

// Eigen based functions

//! +PI rotation around X (Roll) axis give us ROS or FCU representation
static const Eigen::Quaterniond FRAME_ROTATE_Q = UAS::quaternion_from_rpy(M_PI, 0.0, 0.0);

//! Transform for vector3
static const Eigen::Transform<double, 3, Eigen::Affine> FRAME_TRANSFORM_VECTOR3(FRAME_ROTATE_Q);


Eigen::Quaterniond UAS::quaternion_from_rpy(const Eigen::Vector3d &rpy)
{
#if 0
	// RPY - XYZ
	return Eigen::Quaterniond(
			Eigen::AngleAxisd(rpy.x(), Eigen::Vector3d::UnitX()) *
			Eigen::AngleAxisd(rpy.y(), Eigen::Vector3d::UnitY()) *
			Eigen::AngleAxisd(rpy.z(), Eigen::Vector3d::UnitZ())
			);
#else
	// YPR - ZYX
	return Eigen::Quaterniond(
			Eigen::AngleAxisd(rpy.z(), Eigen::Vector3d::UnitZ()) *
			Eigen::AngleAxisd(rpy.y(), Eigen::Vector3d::UnitY()) *
			Eigen::AngleAxisd(rpy.x(), Eigen::Vector3d::UnitX())
			);
#endif
}

Eigen::Vector3d UAS::quaternion_to_rpy(const Eigen::Quaterniond &q)
{
#if 0
	// RPY - XYZ
	return q.toRotationMatrix().eulerAngles(0, 1, 2);
#else
	// YPR - ZYX
	return q.toRotationMatrix().eulerAngles(2, 1, 0).reverse();
#endif
}

Eigen::Quaterniond UAS::transform_frame(const Eigen::Quaterniond &q)
{
	return FRAME_ROTATE_Q * q * FRAME_ROTATE_Q.inverse();
}

Eigen::Vector3d UAS::transform_frame(const Eigen::Vector3d &vec)
{
	return FRAME_TRANSFORM_VECTOR3 * vec;
}

UAS::Covariance3x3 UAS::transform_frame(const Covariance3x3 &cov)
{
	// not implemented!
}

UAS::Covariance6x6 UAS::transform_frame(const Covariance6x6 &cov)
{
	// not implemented!
}
