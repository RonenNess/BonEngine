#include <Framework/Point.h>

namespace bon
{
	namespace framework
	{
		PointF::operator PointI() const { return PointI((int)X, (int)Y); }
		PointI::operator PointF() const { return PointF((float)X, (float)Y); }
		PointF::operator PointI() { return PointI((int)X, (int)Y); }
		PointI::operator PointF() { return PointF((float)X, (float)Y); }
	}
}