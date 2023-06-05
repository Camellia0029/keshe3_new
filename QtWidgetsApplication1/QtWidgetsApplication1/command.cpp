#include "command.h"
#include <QDebug>

Command::Command(QObject* parent) : QObject(parent)
{
}

Command::~Command()
{
}

//͹�����㺯��׼��
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
{//����������������Ϊ���������ò��ȷ�������ϵ
    int val = (q.y() - p.y()) * (r.x() - q.x()) - (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0)
        return 0;  // ��������
    return (val > 0) ? 1 : 2;  // ˳ʱ�����ʱ�뷽��0Ϊ���ߣ�>0˵��p,q,r����ʱ�뷽������,<0˵��p,q,r����˳ʱ�뷽�����У�
}

//͹����������
    std::vector<QPoint> ConvexHullCommand::computeConvexHull(const std::vector<QPoint>&points)
    {
        int n = points.size();
        if (n < 3)
            return std::vector<QPoint>(); // ����㼯����3���㣬��û��͹��

        // Ѱ������������ĵ�
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

        // ������������ĵ���� points[0] ��λ�ã����ڱȽ�
        std::swap(points[0], points[minIdx]);

        // �������㰴��������
        QPoint p0 = points[0];
        std::sort(points.begin() + 1, points.end(), [p0](const QPoint& p1, const QPoint& p2) {
            int o = orientation(p0, p1, p2);
            if (o == 0)
                return (p1.x() * p1.x() + p1.y() * p1.y()) < (p2.x() * p2.x() + p2.y() * p2.y());
            return (o == 2);
            });

        // ����һ���յ�͹���������
        std::vector<QPoint> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);

        // ���δ���ʣ��ĵ�
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
