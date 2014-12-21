#include <Jamgine/Include/Shader/ShaderLoader.h>

ShaderLoader::ShaderLoader(void)
{
}

ShaderLoader::~ShaderLoader(void)
{
}

HRESULT ShaderLoader::CreateVertexShaderWithInputLayout(WCHAR* fileName, 
														 LPCSTR entryPoint, 
														 LPCSTR shaderModel, 
														 ID3D11Device* device, 
														 ID3D11VertexShader** shaderOut, 
														 D3D11_INPUT_ELEMENT_DESC* 
														 layout,UINT numElements, 
														 ID3D11InputLayout** layoutOut)
{
	HRESULT hr = S_OK;
	
	//compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pVSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }


	// Create the vertex shader
	hr = device->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, shaderOut );
	if( FAILED( hr ) )
	{	
		pVSBlob->Release();
        return hr;
	}

    
     // Create the input layout
	hr = device->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), layoutOut );

	pVSBlob->Release();
	
    return hr;
}

HRESULT ShaderLoader::CreateHullShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11HullShader** shaderOut)
{
	HRESULT hr = S_OK;

	// Compile the hull shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the hull shader
	hr = device->CreateHullShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, shaderOut );
	pPSBlob->Release();

	return hr;
}
HRESULT ShaderLoader::CreateDomainShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11DomainShader** shaderOut)
{
	HRESULT hr = S_OK;

	// Compile the domain shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the domain shader
	hr = device->CreateDomainShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, shaderOut );
	pPSBlob->Release();

	return hr;
}

HRESULT ShaderLoader::CreateGeometryShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11GeometryShader** shaderOut)
{
	HRESULT hr = S_OK;

	// Compile the geometry shader
	ID3DBlob* pPSBlob = nullptr;

	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the geometry shader
	hr = device->CreateGeometryShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, shaderOut );
	pPSBlob->Release();

    return hr;
}

HRESULT ShaderLoader::CreateGeometryShaderWithOutputDeclaration(WCHAR* fileName, 
														 LPCSTR entryPoint, 
														 LPCSTR shaderModel, 
														 ID3D11Device* device, 
														 ID3D11GeometryShader** shaderOut, 
														 D3D11_SO_DECLARATION_ENTRY* decl,
														 UINT numElements)	
{
	//Create the update Geometry shader for output
	HRESULT hr = S_OK;
	ID3DBlob* pPSBlob = nullptr;

	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }


	hr = device->CreateGeometryShaderWithStreamOutput( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), decl, 
		numElements, NULL, 0, D3D11_SO_NO_RASTERIZED_STREAM, NULL, shaderOut );

	pPSBlob->Release();

	return hr;
}

HRESULT ShaderLoader::CreatePixelShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11PixelShader** shaderOut)
{
	HRESULT hr = S_OK;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the pixel shader
	hr = device->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, shaderOut );
	pPSBlob->Release();

	return hr;
}

HRESULT ShaderLoader::CreateComputeShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11ComputeShader** shaderOut)
{
	HRESULT hr = S_OK;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &pPSBlob );
    if( FAILED( hr ) )
    {
        MessageBox( nullptr,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

	// Create the pixel shader
	hr = device->CreateComputeShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, shaderOut);

	pPSBlob->Release();

	return hr;
}

HRESULT ShaderLoader::CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

	    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif


	ID3DBlob* pErrorBlob = nullptr;
	
    hr = D3DCompileFromFile( szFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE , szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob );
	 
    if( FAILED(hr) )
    {
        if( pErrorBlob )
        {
            OutputDebugStringA( reinterpret_cast<const char*>( pErrorBlob->GetBufferPointer() ) );
            pErrorBlob->Release();
        }
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}