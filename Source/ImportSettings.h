#pragma once
#ifndef __ImportSettings_H__
#define __ImportSettings_H__

class ImportSettings {

public:

	
	ImportSettings() {
	
		GlobalScale = false;

		Ignore_Cameras = false;

		Axis_X = false;
		Axis_Y = false;
		Axis_Z = false;
		DesiredScaleX = 1.0f;
		DesiredScaleY = 1.0f;
		DesiredScaleZ = 1.0f;

		FlipTexture = false;
		Filter = false;
		WrappingS = false;
		WrappingT = true;

		Fill_CLAMP = false;
		Fill_CLAMP_TO_BORDER = false;
		Fill_REPEAT = true;
		Fill_MIRROR_REPEAT = false;
	};
	~ImportSettings() {};
	
	//MESHES
	bool GlobalScale; //d
	float DesiredScaleX; //d
	float DesiredScaleY;//d
	float DesiredScaleZ;//d

	bool Ignore_Cameras;

	bool Axis_X ;
	bool Axis_Y ;
	bool Axis_Z ;

	//TEXTURES

	bool FlipTexture ;
	bool Filter ;
	bool WrappingT ;
	bool WrappingS;

	bool Fill_CLAMP;
	bool Fill_CLAMP_TO_BORDER;
	bool Fill_REPEAT;
	bool Fill_MIRROR_REPEAT;
	
	
	


	

};

#endif