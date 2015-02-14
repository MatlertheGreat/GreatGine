#include "GGGraphics.h"
#include "GGWindow.h"
#include "GGConfig.h"
#include <DirectXMath.h>
using namespace DirectX;
using namespace std;

GGGraphics::GGGraphics( const GGWindow& _window, const GGConfig& _config )
	:
	m_driver( _window, _config.GetInt( "resolutionX" ), _config.GetInt( "resolutionY" ) ),
	m_device( m_driver ),
	m_renderer( m_driver, _config.GetInt( "sync_interval" ) ),
	m_camera( m_device.CreateCamera( XMConvertToRadians( _config.GetFloat( "fov" ) ), _config.GetInt( "resolutionX" ), _config.GetInt( "resolutionY" ) ) ),
	m_basicShader( m_device.CreateShader() ),
	m_mesh( m_device.CreateCubeMesh() )
{}

void GGGraphics::Update( float _frameTime )
{
	m_fpsCounter.Update( _frameTime );

	// Camera update( that code shouldn't really be here, but I'm too lazy )
	float pitch = XMConvertToRadians( m_cameraRot.x );
	float yaw = XMConvertToRadians( m_cameraRot.y );
	float roll = XMConvertToRadians( m_cameraRot.z );
	XMVECTOR rotationQuaterion = XMQuaternionRotationRollPitchYaw( pitch, yaw, roll );

	XMVECTOR velocity = XMLoadFloat3( &m_cameraVelocity );
	velocity = XMVector3Rotate( velocity, rotationQuaterion );
	XMVECTOR position = XMLoadFloat3( &m_cameraPos );
	position = XMVectorAdd( position, XMVectorScale( velocity, _frameTime ) );

	XMStoreFloat3( &m_cameraPos, position );

	XMVECTOR lookDir = XMVector3Rotate( XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ), rotationQuaterion );
	XMVECTOR upDir = XMVectorSet( 0.0f, 1.0f, 0.0f, 1.0f );

	XMFLOAT4X4 viewMatrix;
	XMMATRIX view = XMMatrixLookToLH( position, lookDir, upDir );
	XMStoreFloat4x4( &viewMatrix, XMMatrixTranspose( view ) );

	m_device.UpdateCamera( m_camera, viewMatrix );

	return;
}

void GGGraphics::Render()
{
	m_renderer.ClearScene();

	m_renderer.SetFillType( m_currentFillType );

	m_renderer.SetCamera( m_camera );

	m_renderer.SetShader( m_basicShader );

	m_renderer.SetMesh( m_mesh );
	m_renderer.RenderMesh( m_mesh );

	wstring fpsCount = L"FPS: ";
	fpsCount += to_wstring( m_fpsCounter.GetFPS() );

	m_renderer.RenderIn2D();

	m_renderer.RenderText( fpsCount );

	m_renderer.PresentScene();

	return;
}

void GGGraphics::HandleActionInput( GG_ACTION_INPUT _input, bool _down )
{
	if( _down )
	{
		if( _input == GG_ACTION_INPUT_MOVE_FORWARD )
		{
			m_cameraVelocity.z = 4.0f;
		}
		else if( _input == GG_ACTION_INPUT_MOVE_BACKWARD )
		{
			m_cameraVelocity.z = -4.0f;
		}

		if( _input == GG_ACTION_INPUT_MOVE_RIGHTWARD )
		{
			m_cameraVelocity.x = 4.0f;
		}
		else if( _input == GG_ACTION_INPUT_MOVE_LEFTWARD )
		{
			m_cameraVelocity.x = -4.0f;
		}

		if( _input == GG_ACTION_INPUT_FILL_TYPE )
		{
			SwitchFillType();
		}
	}
	else
	{
		if( _input == GG_ACTION_INPUT_MOVE_FORWARD )
		{
			m_cameraVelocity.z = 0.0f;
		}
		else if( _input == GG_ACTION_INPUT_MOVE_BACKWARD )
		{
			m_cameraVelocity.z = 0.0f;
		}

		if( _input == GG_ACTION_INPUT_MOVE_RIGHTWARD )
		{
			m_cameraVelocity.x = 0.0f;
		}
		else if( _input == GG_ACTION_INPUT_MOVE_LEFTWARD )
		{
			m_cameraVelocity.x = 0.0f;
		}
	}

	return;
}

void GGGraphics::HandleRangeInput( int _x, int _y )
{
	m_cameraRot.x += _y * 0.1f;
	if( m_cameraRot.x >= 89.9f )
	{
		m_cameraRot.x = 89.9f;
	}
	else if( m_cameraRot.x <= -89.9f )
	{
		m_cameraRot.x = -89.9f;
	}

	m_cameraRot.y += _x * 0.1f;

	return;
}

void GGGraphics::SwitchFillType()
{
	if( m_currentFillType == GGRenderer::FILL_TYPE_SOLID )
	{
		m_currentFillType = GGRenderer::FILL_TYPE_WIREFRAME;
	}
	else
	{
		m_currentFillType = GGRenderer::FILL_TYPE_SOLID;
	}

	return;
}