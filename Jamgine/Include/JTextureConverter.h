
namespace Jamgine
{
	class JTextureConverter
	{
	public:
		virtual void* Convert(void* p_data, void* p_out, unsigned int p_size) = 0;
	};
}