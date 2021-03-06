#pragma once

#include <vector>
#include <DirectXMath.h>
#include <wrl/client.h>

struct GGMeshData
{
public:
	struct GGVertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT3 color;
	};

	typedef unsigned int GGIndex;

public:
	std::vector<GGVertex> vertices;
	std::vector<GGIndex> indices;
};

GGMeshData GGCubeMeshData( float _dimension );