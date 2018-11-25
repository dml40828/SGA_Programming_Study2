#include "stdafx.h"
#include "Program.h"

#include "./Viewer/Freedom.h"

#include "./Executes/ExportMesh.h"

#include "./Executes/ExTPS.h"
#include "./Executes/TestSmoothFollow.h"
#include "./Executes/TestLookAt.h"
#include "./Executes/TestCollision.h"

#include "./Viewer/Viewport.h"

Program::Program()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	values = new ExecuteValues();
	values->ViewProjection = new ViewProjectionBuffer();
	values->GlobalLight = new LightBuffer();
	values->Perspective = new Perspective(desc.Width, desc.Height);
	values->Viewport = new Viewport(desc.Width, desc.Height);

	values->MainCamera = new Freedom(50, 5.0f);
	// Homework ��
	//values->MainCamera->RotationDegree(20.0f, -92.0f);
	values->MainCamera->Position(0, 30, -30.0f);

	// Ray Capsule Collision ��
	//values->MainCamera->RotationDegree(10.0f, -23.0f);
	//values->MainCamera->Position(12.5f, 4.0f, -10.0f);	

	values->GlobalLight->Data.Direction = D3DXVECTOR3(-1, 0, -1);
	
	//executes.push_back(new ExportMesh(values));
	executes.push_back(new ExTPS(values));
	//executes.push_back(new TestSmoothFollow(values));
	//executes.push_back(new TestLookAt(values));
	//executes.push_back(new TestCollision(values));

	showDebug = true;

	angle1 = Math::ToRadian(270);
	angle2 = Math::ToRadian(20);

	ShowCursor(false);
	ShowCursor(false);
}

Program::~Program()
{
	for (Execute* exe : executes)
		SAFE_DELETE(exe);
	
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values->GlobalLight);
	SAFE_DELETE(values->ViewProjection);
	SAFE_DELETE(values->Perspective);
	SAFE_DELETE(values->Viewport);
	SAFE_DELETE(values);
}

void Program::Update()
{
	//Viewport* vp = values->Viewport;
	//// ȭ�� ������ �˾Ƴ����� -> viewport�� ����
	//D3DXVECTOR2 screenSize;
	//screenSize.x = vp->GetWidth();
	//screenSize.y = vp->GetHeight();

	//{
	//	//ShowCursor(false);

	//	POINT pos;
	//	GetCursorPos(&pos);
	//	if (pos.x < 0 || pos.x > screenSize.x)
	//		SetCursorPos(screenSize.x / 2, pos.y);

	//	if (pos.y < 0 || pos.y > screenSize.y)
	//		SetCursorPos(pos.x, screenSize.y / 2);
	//}

	values->MainCamera->Update();

	for (Execute* exe : executes)
		exe->Update();
}

void Program::PreRender()
{
	D3DXMATRIX view, projection;
	values->MainCamera->Matrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);
	values->ViewProjection->SetVSBuffer(0);

	for (Execute* exe : executes)
		exe->PreRender();
}

void Program::Render()
{
	D3DXMATRIX view, projection;
	values->MainCamera->Matrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);
	values->ViewProjection->SetVSBuffer(0);

	values->GlobalLight->SetPSBuffer(0);
	values->Viewport->RSSetViewport();

	for (Execute* exe : executes)
		exe->Render();
}

void Program::PostRender()
{
	ImGui::Text("FPS : %f", Time::Get()->FPS());

	if (ImGui::Checkbox("Show Debug", &showDebug)) {
		if (showDebug)
			ImGui::SetWindowSize(ImVec2(250, 300));
		else
			ImGui::SetWindowSize(ImVec2(250, 100));
	}

	if (showDebug) {
		// ������ ����
		ImGui::Separator();
		ImGui::SliderFloat3("Direction",
			(float *)&values->GlobalLight->Data.Direction, -1, 1);
		ImGui::Separator();

		D3DXVECTOR3 vec;
		values->MainCamera->Position(&vec);
		//ImGui::LabelText("CameraPos", "%.2f, %.2f, %.2f",
		//	vec.x, vec.y, vec.z);
		if (ImGui::DragFloat3("CamPos", (float*)&vec, 0.1f))
			values->MainCamera->Position(vec.x, vec.y, vec.z);

		D3DXVECTOR2 rot;
		values->MainCamera->RotationDegree(&rot);
		//ImGui::LabelText("CameraRot", "%.2f, %.2f", rot.x, rot.y);
		if (ImGui::DragFloat2("CamRot", (float*)&rot, 0.1f))
			values->MainCamera->RotationDegree(rot.x, rot.y);

		for (Execute* exe : executes)
			exe->PostRender();
	}
}

void Program::ResizeScreen()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	values->Perspective->Set(desc.Width, desc.Height);
	values->Viewport->Set(desc.Width, desc.Height);

	for (Execute* exe : executes)
		exe->ResizeScreen();
}