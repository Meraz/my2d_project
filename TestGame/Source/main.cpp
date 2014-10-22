#include <ziplib/ZipFile.h>
#include <TestGame/Include/Jamgame.h>
#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <Windows.h>
#include <fstream>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	/*
	ZipArchive::Ptr archive = ZipFile::Open("archive.zip");

	ZipArchiveEntry::Ptr entry = archive->GetEntry("file.dat");

	size_t t = entry->GetCompressedSize();
	// if entry is nullptr, it means the file already exists in the archive
	assert(entry != nullptr);

	std::ifstream contentStream("file.dat", std::ios::binary);
	
	entry->SetCompressionStream(contentStream);

	// you may of course save it somewhere else
	// note: the contentStream is pumped when the archive is saved
	// if you want to read the stream before saving of the archive,
	// it is need to set Immediate mode in SetCompressionStream method (see below)
	ZipFile::SaveAndClose(archive, "archive.zip");
	*/

	Jamgame* l_jamgame = new Jamgame();
	l_jamgame->Initialize(hInstance, lpCmdLine, nCmdShow);
	l_jamgame->Run();

	delete l_jamgame;
	return 0;
}


#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
int main()
{
Jamgine::JamgineEngine* a = nullptr;
Jamgine::JamgineEngine::CreateEngine(&a, Jamgine::GraphicalSystem::DIRECTX);
//	Jamgine::JamgineEngine::ReleaseEngine();

//a->Render();
system("pause");


return 0;
}

#else
/* Error, both can't be defined or undefined same time */

#endif