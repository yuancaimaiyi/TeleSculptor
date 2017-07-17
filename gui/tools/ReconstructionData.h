/*ckwg +29
 * Copyright 2016 by Kitware, SAS; Copyright 2017 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither the name Kitware, Inc. nor the names of any contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MAPTK_RECONSTRUCTIONDATA_H_
#define MAPTK_RECONSTRUCTIONDATA_H_

// VTK includes
class vtkImageData;
class vtkMatrix3x3;
class vtkMatrix4x4;
class vtkTransform;
class vtkVector3d;

#include <string>

class ReconstructionData
{
public:
  ReconstructionData();
  ReconstructionData(std::string depthPath, std::string matrixPath);
  ~ReconstructionData();

  // GETTERS
  int* GetDepthMapDimensions();
  void GetColorValue(int* pixelPosition, double rgb[3]);
  vtkImageData* GetDepthMap();
  vtkMatrix3x3* Get3MatrixK();
  vtkMatrix4x4* Get4MatrixK();
  vtkMatrix4x4* GetMatrixTR();
  vtkVector3d GetCameraCenter();

  // SETTERS
  void SetDepthMap(vtkImageData* data);
  void SetMatrixK(vtkMatrix3x3* matrix);
  void SetMatrixRT(vtkMatrix4x4* matrix);

  // FUNCTIONS
  void ApplyDepthThresholdFilter(double thresholdBestCost);
  void TransformWorldToDepthMapPosition(const double* worldCoordinate, int pixelCoordinate[2]);

  // STATIC FUNCTIONS
  static void ReadDepthMap(std::string path, vtkImageData* out);

protected:

  // Attributes
  vtkImageData* DepthMap;
  vtkMatrix3x3* MatrixK;
  vtkMatrix4x4* Matrix4K;
  vtkMatrix4x4* MatrixRT;

  vtkTransform* TransformWorldToCamera;
  vtkTransform* TransformCameraToDepthMap;
};

#endif
