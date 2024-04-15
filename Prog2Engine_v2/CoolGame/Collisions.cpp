#include "pch.h"
#include "Collisions.h"

utils::HitInfo Collisions::m_HitInfo = {};


ColDir Collisions::IsRectInPoly(const Rectf& rect, const std::vector<Point2f>& poly)
{
	int mr{ 3 };
	for (int idx{}; idx < mr; idx++)
	{
		//raycasts to the bottom
		Point2f r1P1{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height / 2 };
		Point2f r1P2{ rect.left + idx * rect.width / (mr - 1),rect.bottom };

		//raycasts to the top
		Point2f r2P1{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height / 2 };
		Point2f r2P2{ rect.left + idx * rect.width / (mr - 1),rect.bottom + rect.height };

		//raycasts to the left
		Point2f r3P1{ rect.left + rect.width / 2,rect.bottom + idx * rect.height / (mr - 1) };
		Point2f r3P2{ rect.left					,rect.bottom + idx * rect.height / (mr - 1) };

		//raycasts to the right
		Point2f r4P1{ rect.left + rect.width / 2,rect.bottom + idx * rect.height / (mr - 1) };
		Point2f r4P2{ rect.left + rect.width,	 rect.bottom + idx * rect.height / (mr - 1) };

		if (utils::Raycast(poly, r1P1, r1P2, m_HitInfo))
			return ColDir::bottom;
		if (utils::Raycast(poly, r2P1, r2P2, m_HitInfo))
			return ColDir::top;
		if (utils::Raycast(poly, r3P1, r3P2, m_HitInfo))
			return ColDir::left;
		if (utils::Raycast(poly, r4P1, r4P2, m_HitInfo))
			return ColDir::right;
	}
   // if (!utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom }, poly)
   //     &&!utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom }, poly))
   // {
   //     m_ColPoint = Point2f{ rect.left + rect.width / 2,rect.bottom };
   //     std::cout << m_ColPoint.y;
   //     return ColDir::bottom;
   // }
   // if (!utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom + rect.height }, poly)
   //     && !utils::IsPointInPolygon(Point2f{rect.left + rect.width,rect.bottom + rect.height }, poly))
   // {
   //     m_ColPoint = Point2f{ rect.left + rect.width / 2,rect.bottom+rect.height };
   //     std::cout << m_ColPoint.y;
   //     return ColDir::top;
   // }
   // if (!utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom }, poly)
   //     && !utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom + rect.height }, poly))
   // {
   //     m_ColPoint = Point2f{ rect.left,rect.bottom + rect.height/2 };
   //     return ColDir::left;
   // }
   // if (!utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom }, poly)
   //     && !utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom + rect.height }, poly))
   // {
   //     m_ColPoint = Point2f{ rect.left + rect.width ,rect.bottom + rect.height / 2 };
   //     return ColDir::right;
   // }
}
