#include "RenderSystem.h"
//#include "Define.h"
#include "World.hpp"
#include "StaticMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "DXSamplerState.hpp"
#include "TransformComponent.h"
#include "Landscape.h"
//#include "DebugCamera.h"

void RenderSystem::Tick(ECS::World* world, float time)
{
	ID3D11RasterizerState* pOldRSState;
	DXDevice::g_pImmediateContext->RSGetState(&pOldRSState);
	DXDevice::g_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSSolid);
	DXDevice::g_pImmediateContext->OMSetBlendState(DXSamplerState::pBlendSamplerState, 0, -1);
	DXDevice::g_pImmediateContext->PSSetSamplers(0, 1, &DXSamplerState::pDefaultSamplerState);

	for (auto& entity : world->GetEntities<Landscape>())
	{
		auto landscape = entity->GetComponent<Landscape>();
		auto transform = entity->GetComponent<TransformComponent>();
		if ((landscape != nullptr) && (transform != nullptr))
		{
			landscape->UpdateTransformMatrix(*transform);
			landscape->Render();
		}
	}

	for (auto& entity : world->GetEntities<SkeletalMeshComponent>())
	{
		auto skeletalMesh = entity->GetComponent<SkeletalMeshComponent>();

	}

	for (auto& entity : world->GetEntities<StaticMeshComponent>())
	{
		auto staticMesh = entity->GetComponent<StaticMeshComponent>();
		auto transform = entity->GetComponent<TransformComponent>();
		
		if ((staticMesh != nullptr) && (transform != nullptr))
		{
			staticMesh->UpdateTransformMatrix(*transform);
			staticMesh->Render();
		}
	}

	DXDevice::g_pImmediateContext->RSSetState(pOldRSState);
	if (pOldRSState != nullptr)
	{
		pOldRSState->Release();
	}
}