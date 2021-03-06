#include "stdafx.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
	: state(NULL)
{
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

	desc.AntialiasedLineEnable = false;
	desc.CullMode = D3D11_CULL_BACK;
	desc.DepthBias = 0;
	desc.DepthBiasClamp = 0.0f;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
	desc.MultisampleEnable = false;
	desc.ScissorEnable = false;
	desc.SlopeScaledDepthBias = 0.0f;

	Changed();
}

RasterizerState::~RasterizerState()
{
	SAFE_RELEASE(state);
}

void RasterizerState::RSSetState()
{
	// 디바이스에 세팅해주는 함수
	D3D::GetDC()->RSSetState(state);
}

void RasterizerState::AntialiasedLineEnable(bool val)
{
	desc.AntialiasedLineEnable = val;

	Changed();
}

void RasterizerState::CullMode(D3D11_CULL_MODE val)
{
	desc.CullMode = val;

	Changed();
}

void RasterizerState::DepthClipEnable(bool val)
{
	desc.DepthClipEnable = val;

	Changed();
}

void RasterizerState::FillMode(D3D11_FILL_MODE val)
{
	desc.FillMode = val;

	Changed();
}

void RasterizerState::FrontCounterClockwise(bool val)
{
	desc.FrontCounterClockwise = val;

	Changed();
}

void RasterizerState::MultisampleEnable(bool val)
{
	desc.MultisampleEnable = val;

	Changed();
}

void RasterizerState::Changed()
{
	// 사실 이렇게 지우고 안해도 되긴함
	// 내부적으로 지워주긴 하는데
	SAFE_RELEASE(state);

	HRESULT hr = D3D::GetDevice()->CreateRasterizerState(&desc, &state);
	assert(SUCCEEDED(hr));
}
