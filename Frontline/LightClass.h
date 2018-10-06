#pragma once

#include "stdafx.h"

class LightClass {
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetAmbientColor(float, float, float, float);
	void SetDirection(float, float, float);

	DirectX::XMFLOAT4 GetDiffuseColor();
	DirectX::XMFLOAT4 GetAmbientColor();
	DirectX::XMFLOAT3 GetDirection();

private:
	DirectX::XMFLOAT4 m_diffuseColor;
	DirectX::XMFLOAT4 m_ambientColor;
	DirectX::XMFLOAT3 m_direction;
};