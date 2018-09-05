#pragma once

#include "GameModel.h"

class Billboard : public GameModel
{
public:
	Billboard(ExecuteValues* values, 
		wstring shaderFile, wstring diffuseFile);
	~Billboard();

	void FixedY(bool val) { bFixedY = val; }

	void Update();
	void Render();

	bool* GetisDouble() { return &bDouble; }
private:
	ExecuteValues* values;

	RasterizerState* cullMode[2];

	bool bFixedY;
	bool bDouble;

	class MeshQuad* subTree;
};