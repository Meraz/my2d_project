#include <Jamgine\Include\JTextureImporter.h>



JTextureImporter::JTextureImporter()
{

}

JTextureImporter::~JTextureImporter()
{

}


void* JTextureImporter::ConvertToSRV(void* p_data, unsigned int p_size)
{
	ID3D11ShaderResourceView* viewOfTheResourceOftheObjectWeWantToPaint;
	DirectX::CreateDDSTextureFromMemory(nullptr, (uint8_t*)p_data, p_size, nullptr /* We don't need this, i think //Kim "The almost human, but not quite 'cause skåningar ain't be right" Hansson*/, &viewOfTheResourceOftheObjectWeWantToPaint);

	return viewOfTheResourceOftheObjectWeWantToPaint;
}