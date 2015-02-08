#include "GGGraphics.h"
#include "GGWindow.h"

GGGraphics::GGGraphics( const GGWindow& _window )
	:
	m_driver( _window, 800, 600 ),
	m_device( m_driver ),
	m_renderer( m_driver ),
	m_basicShader( m_device.CreateShader() ),
	m_mesh( m_device.CreateCubeMesh() ),
	m_cameraPos( { 0.0f, 1.5f, 0.0f } )
{
}

void GGGraphics::Update()
{
	m_camera.Update( m_cameraPos, { 0.0f, 0.0f, 0.0f } );

	return;
}

void GGGraphics::Render()
{
	m_renderer.ClearScene();

	m_renderer.SetCamera( &m_camera );

	m_renderer.SetShader( m_basicShader.get() );

	m_renderer.SetMesh( m_mesh.get() );
	m_renderer.RenderMesh( m_mesh.get() );

	m_renderer.PresentScene();

	return;
}

void GGGraphics::HandleActionInput( GG_ACTION_INPUT _input, bool _down )
{
	if( !_down )
	{
		return;
	}

	if( _input == GG_ACTION_INPUT_MOVE_FORWARD )
	{
		m_cameraPos.z += 0.1f;
	}
	else if( _input == GG_ACTION_INPUT_MOVE_BACKWARD )
	{
		m_cameraPos.z -= 0.1f;
	}

	if( _input == GG_ACTION_INPUT_MOVE_RIGHTWARD )
	{
		m_cameraPos.x += 0.1f;
	}
	else if( _input == GG_ACTION_INPUT_MOVE_LEFTWARD )
	{
		m_cameraPos.x -= 0.1f;
	}

	return;
}