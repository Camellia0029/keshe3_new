#include "command.h"
#include <QDebug>

Command::Command(QObject* parent) : QObject(parent)
{
}

Command::~Command()
{
}

//凸包计算函数准备
bool comparePoints(const QPoint& p1, const QPoint& p2)
{
    if (p1.y() < p2.y())
        return true;
    else if (p1.y() > p2.y())
        return false;
    else
        return p1.x() < p2.x();
}

int orientation(const QPoint& p, const QPoint& q, const QPoint& r)
{//输入三个点坐标作为参数，利用叉积确定方向关系
    int val = (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0)
        return 0;  // 线性排列
    return (val > 0) ? 1 : 2;  // 顺时针或逆时针方向（0为共线，>0说明p,q,r按逆时针方向排列,<0说明p,q,r按照顺时针方向排列）
}

//凸包计算命令
    std::vector<QPoint> ConvexHullCommand::computeConvexHull(const std::vector<QPoint>&points)
    {
        int n = points.size();
        if (n < 3)
            return std::vector<QPoint>(); // 如果点集不足3个点，则没有凸包

        // 寻找最下且最左的点
        int minY = points[0].y(), minX = points[0].x(), minIdx = 0;
        for (int i = 1; i < n; ++i) {
            int y = points[i].y();
            int x = points[i].x();
            if ((y < minY) || (y == minY && x < minX)) {
                minY = y;
                minX = x;
                minIdx = i;
            }
        }

        // 将最下且最左的点放在 points[0] 的位置，便于比较
        std::swap(points[0], points[minIdx]);

        // 对其他点按极角排序
        QPoint p0 = points[0];
        std::sort(points.begin() + 1, points.end(), [p0](const QPoint& p1, const QPoint& p2) {
            int o = orientation(p0, p1, p2);
            if (o == 0)
                return (p1.x() * p1.x() + p1.y() * p1.y()) < (p2.x() * p2.x() + p2.y() * p2.y());
            return (o == 2);
            });

        // 创建一个空的凸包结果向量
        std::vector<QPoint> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);

        // 依次处理剩余的点
        for (int i = 2; i < n; ++i) {
            while (hull.size() >= 2) {
                QPoint p1 = hull[hull.size() - 2];
                QPoint p2 = hull[hull.size() - 1];
                QPoint p3 = points[i];
                if (orientation(p1, p2, p3) != 2)
                    hull.pop_back();
                else
                    break;
            }
            hull.push_back(points[i]);
        }

        return hull;
    } 

void ConvexHullCommand::execute()
{
   
}

BufferCommand::BufferCommand(QObject* parent) : Command(parent)
{
}

void BufferCommand::execute()
{
    qDebug() << "Executing Buffer Command";
    // Perform buffer calculation
}

OverlayCommand::OverlayCommand(QObject* parent) : Command(parent)
{
}

void OverlayCommand::execute()
{
    qDebug() << "Executing Overlay Command";
    // Perform overlay analysis
}

DelaunayCommand::DelaunayCommand(QObject* parent) : Command(parent)
{
}

void DelaunayCommand::execute()
{
    qDebug() << "Executing Delaunay Command";
    // Perform Delaunay triangulation
}

VoronoiCommand::VoronoiCommand(QObject* parent) : Command(parent)
{
}

void VoronoiCommand::execute()
{
    qDebug() << "Executing Voronoi Command";
    // Perform Voronoi diagram calculation
}
