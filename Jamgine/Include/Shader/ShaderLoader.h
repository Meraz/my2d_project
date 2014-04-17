#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>

class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);

	// Standard compileShaderFromFile, used for all create shaders
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
	
	// Creates a shader with a input layout
	HRESULT CreateVertexShaderWithInputLayout(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, 
		ID3D11VertexShader** shaderOut, D3D11_INPUT_ELEMENT_DESC* layout,UINT numElements, ID3D11InputLayout** layoutOut);

	// Creates a hull shader
	HRESULT CreateHullShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11HullShader** shaderOut);

	// Creates a domain shader
	HRESULT CreateDomainShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11DomainShader** shaderOut);

	// Creates a geometry shader
	HRESULT CreateGeometryShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11GeometryShader** shaderOut);

	// Creates a pixel shader
	HRESULT CreatePixelShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11PixelShader** shaderOut);

	// Creates a compute shader
	HRESULT CreateComputeShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11ComputeShader** shaderOut);

	// Creates a output geometry shader
	HRESULT CreateGeometryShaderWithOutputDeclaration(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, 
		ID3D11GeometryShader** shaderOut, D3D11_SO_DECLARATION_ENTRY* decl, UINT numElements);
};

