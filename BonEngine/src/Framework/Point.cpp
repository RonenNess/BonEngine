#include <Framework/Point.h>

namespace bon
{
	namespace framework
	{
		PointF::operator PointI() const { return PointI((int)X, (int)Y); }
		PointI::operator PointF() const { return PointF((float)X, (float)Y); }
		PointF::operator PointI() { return PointI((int)X, (int)Y); }
		PointI::operator PointF() { return PointF((float)X, (float)Y); }

		const PointI& PointI::Zero = PointI(0,0);
		const PointI& PointI::One = PointI(1, 1);
		const PointI& PointI::Half = PointI(0, 0);

		const PointF& PointF::Zero = PointF(0, 0);
		const PointF& PointF::One = PointF(1, 1);
		const PointF& PointF::Half = PointF(0.5f, 0.5f);
	}
}