cbuffer ProjectionBuffer : register(b0)
{
	matrix projectionMatrix;
}

cbuffer ViewBuffer : register(b1)
{
	matrix viewMatrix;
}

cbuffer WorldBuffer : register(b2)
{
	matrix worldMatrix;
}

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	float4 output = mul( pos, worldMatrix );
	output = mul( output, viewMatrix );
	output = mul( output, projectionMatrix );

	return output;
}