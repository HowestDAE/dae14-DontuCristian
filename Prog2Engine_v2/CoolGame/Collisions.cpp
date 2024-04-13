#include "pch.h"
#include "Collisions.h"

ColDir Collisions::IsRectInPoly(const Rectf& rect, const std::vector<std::vector<Point2f>>& poly)
{
    for (int idx{}; idx < poly.size(); idx++)
    {
        if (utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom }, poly[idx])
            && utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom }, poly[idx]))
        {
            return ColDir::bottom;
        }
        if (utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom + rect.height }, poly[idx])
            && utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom + rect.height }, poly[idx]))
        {
            return ColDir::top;
        }
        if (utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom }, poly[idx])
            && utils::IsPointInPolygon(Point2f{ rect.left,rect.bottom + rect.height }, poly[idx]))
        {
            return ColDir::left;
        }
        if (utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom }, poly[idx])
            && utils::IsPointInPolygon(Point2f{ rect.left + rect.width,rect.bottom + rect.height }, poly[idx]))
        {
            return ColDir::right;
        }
    }
}
