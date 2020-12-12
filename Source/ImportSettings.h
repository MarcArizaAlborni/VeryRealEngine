#pragma once
#ifndef __ImportSettings_H__
#define __ImportSettings_H__

class ImportSettings {

public:

	
	ImportSettings() {
	
		GlobalScale = false;

		Ignore_Culling = false;

		Axis_X = false;
		Axis_Y = false;
		Axis_Z = false;

		

		FlipTexture = false;
		Filter = false;
		Wrapping = false;
	
	};
	~ImportSettings() {};
	
	//MESHES
	bool GlobalScale;
	
	bool Ignore_Culling ;

	bool Axis_X ;
	bool Axis_Y ;
	bool Axis_Z ;

	//TEXTURES

	bool FlipTexture ;
	bool Filter ;
	bool Wrapping ;

	



	

};

#endif