#include "PCH.h"
#include "GGDebugInfo.h"
using namespace DirectX;
using namespace std;

void GGDebugInfo::Update( float _frameTime, const XMFLOAT3& _cameraPos )
{
	m_fpsCounter.Update( _frameTime );

	m_lines[ 0 ] = L"FPS: ";
	m_lines[ 0 ] += to_wstring( m_fpsCounter.GetFPS() );

	m_lines[ 1 ] = L"X/Y/Z: ";
	m_lines[ 1 ] += to_wstring( _cameraPos.x );
	m_lines[ 1 ] += L" / ";
	m_lines[ 1 ] += to_wstring( _cameraPos.y );
	m_lines[ 1 ] += L" / ";
	m_lines[ 1 ] += to_wstring( _cameraPos.z );

	return;
}

const wstring& GGDebugInfo::GetLine( int _lineNumber ) const
{
	return m_lines[ _lineNumber ];
}