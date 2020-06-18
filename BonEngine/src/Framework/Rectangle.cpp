#include <Framework/Rectangle.h>

namespace bon
{
	namespace framework
	{
		RectangleF::operator RectangleI() const { return RectangleI((int)X, (int)Y, (int)Width, (int)Height); }
		RectangleI::operator RectangleF() const { return RectangleF((float)X, (float)Y, (float)Width, (float)Height); }
		RectangleF::operator RectangleI() { return RectangleI((int)X, (int)Y, (int)Width, (int)Height); }
		RectangleI::operator RectangleF() { return RectangleF((float)X, (float)Y, (float)Width, (float)Height); }

		const RectangleI& RectangleI::Zero = RectangleI(0, 0, 0, 0);
		const RectangleF& RectangleF::Zero = RectangleF(0, 0, 0, 0);
	}
}