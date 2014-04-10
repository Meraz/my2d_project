#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>

class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);

	//standard compileShaderFromFile, used for all create shaders
	HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut );
	
	//creates a shader with a input layout
	HRESULT CreateVertexShaderWithInputLayout(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, 
		ID3D11VertexShader** shaderOut, D3D11_INPUT_ELEMENT_DESC* layout,UINT numElements, ID3D11InputLayout** layoutOut);
	//creates a hull shader
	HRESULT CreateHullShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11HullShader** shaderOut);
	//creates a domain shader
	HRESULT CreateDomainShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11DomainShader** shaderOut);
	//creates a geometry shader
	HRESULT CreateGeometryShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11GeometryShader** shaderOut);
	//creates a pixel shader
	HRESULT CreatePixelShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11PixelShader** shaderOut);
	//creates a compute shader
	HRESULT CreateComputeShader(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, ID3D11ComputeShader** shaderOut);
	//creates a output geometry shader
	HRESULT CreateGeometryShaderWithOutputDeclaration(WCHAR* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* device, 
		ID3D11GeometryShader** shaderOut, D3D11_SO_DECLARATION_ENTRY* decl, UINT numElements);
};

