#include <Framework/Color.h>

namespace bon
{
	namespace framework
	{
		// define built-in colors
		const Color& Color::Black = Color(0,0,0,1);
		const Color& Color::White = Color(1, 1, 1, 1);
		const Color& Color::Transparent = Color(1, 1, 1, 0);
		const Color& Color::TransparentBlack = Color(0, 0, 0, 0);
		const Color& Color::HalfTransparent = Color(1, 1, 1, 0.5f);
		const Color& Color::Gray = Color(0.5f, 0.5f, 0.5f, 1);
		const Color& Color::Red = Color(1, 0, 0, 1);
		const Color& Color::Green = Color(0, 1, 0, 1);
		const Color& Color::Blue = Color(0, 0, 1, 1);
		const Color& Color::Yellow = Color(1, 1, 0, 1);
		const Color& Color::Purple = Color(1, 0, 1, 1);
		const Color& Color::Teal = Color(0, 1, 1, 1);
	}
}