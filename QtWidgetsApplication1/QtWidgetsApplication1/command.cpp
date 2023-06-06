#include "command.h"
#include <QDebug>
//���õ�������
#include <QPainter>
//#include "D:\QtWidgetsApplication\QtWidgetsApplication1\triangle\triangle.h" 
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
    //ִ�к���
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

//���ӷ������󽻼�������׼��
OverlayCommand::OverlayCommand(QObject* parent) : Command(parent)
{


}

void OverlayCommand::execute()
{
    qDebug() << "Executing Overlay Command";

    // ���贫�����ͼ����Ϣ��ÿ��ͼ������������Ҫ��
    QVector<QVector<QPoint>> layer1;
    // ��ӵ�һ��ͼ��ļ���Ҫ��
    layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
    layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

    QVector<QVector<QPoint>> layer2;
    // ��ӵڶ���ͼ��ļ���Ҫ��
    layer2 << QVector<QPoint> { QPoint(3, 3), QPoint(3, 8), QPoint(8, 8), QPoint(8, 3) };
    layer2 << QVector<QPoint> { QPoint(6, 6), QPoint(6, 9), QPoint(9, 9), QPoint(9, 6) };

    // ��ȡͼ�㼸��Ҫ������
    int layer1Count = layer1.size();
    int layer2Count = layer2.size();

    // ��̬�������ζ�������
    QVector<QPolygon> polygons1(layer1Count);
    QVector<QPolygon> polygons2(layer2Count);

    // ����ͼ��ļ���Ҫ�ض���
    for (int i = 0; i < layer1Count; i++)
    {
        polygons1[i] = QPolygon(layer1[i]);
    }

    for (int i = 0; i < layer2Count; i++)
    {
        polygons2[i] = QPolygon(layer2[i]);
    }

    // ����ͼ��Ĳ���
    QVector<QPolygon> resultPolygons;
    for (const QPolygon& polygon1 : polygons1)
    {
        for (const QPolygon& polygon2 : polygons2)
        {
            QPolygon resultPolygon = polygon1.united(polygon2);
            resultPolygons.append(resultPolygon);
        }
    }

    // ��ӡ��������εĶ�������
    for (const QPolygon& resultPolygon : resultPolygons)
    {
        for (const QPoint& point : resultPolygon)
        {
            qDebug() << "Point: (" << point.x() << ", " << point.y() << ")";
        }
    }
}

//delaunay����������׼��
DelaunayCommand::DelaunayCommand(QObject* parent) : Command(parent)
{
}

void DelaunayCommand::execute()
{
    qDebug() << "Executing Delaunay Command";
    // Perform Delaunay triangulation
}

PerimeterCommand::PerimeterCommand(QObject* parent) : Command(parent)
{
}

void PerimeterCommand::execute()
{


    // ���贫�����ͼ����Ϣ��ÿ��ͼ������������Ҫ��
    QVector<QVector<QPoint>> layer1;
    // ��ӵ�һ��ͼ��ļ���Ҫ��
    //�����ͼ��ֻ���������Σ��ϲ�ʱ��дһ��forѭ����ͼ�㼸��������֪����ȡ���м��ε�
    layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
    layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

    // ����ÿ������Ҫ�ص��ܳ�
    for (const QVector<QPoint>& geometry : layer1)
    {
        qreal perimeter = 0.0;

        // ���㼸��Ҫ�ص��ܳ�
        int pointCount = geometry.size();
        for (int i = 0; i < pointCount; i++)
        {
            const QPoint& currentPoint = geometry[i];
            const QPoint& nextPoint = geometry[(i + 1) % pointCount];

            qreal distance = QLineF(currentPoint, nextPoint).length();
            perimeter += distance;
        }

        qDebug() << "Geometry Perimeter:" << perimeter;
    }
    //��ӡ�ܳ�
}
    AreaCommand::AreaCommand(QObject * parent) : Command(parent)
    {
    }

    void AreaCommand::execute()
    {

        // ���贫�����ͼ����Ϣ��ÿ��ͼ������������Ҫ��
        QVector<QVector<QPoint>> layer1;
        // ��ӵ�һ��ͼ��ļ���Ҫ��
        //�����ͼ��ֻ���������Σ��ϲ�ʱ��дһ��forѭ����ͼ�㼸��������֪����ȡ���м��ε�
        layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
        layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

        // ����ÿ������Ҫ�ص����
        for (const QVector<QPoint>& geometry : layer1)
        {
            qreal area = 0.0;

            // ���㼸��Ҫ�ص����
            int pointCount = geometry.size();
            for (int i = 0; i < pointCount; i++)
            {
                const QPoint& currentPoint = geometry[i];
                const QPoint& nextPoint = geometry[(i + 1) % pointCount];

                area += (currentPoint.x() * nextPoint.y() - currentPoint.y() * nextPoint.x()) / 2.0;
            }

            qDebug() << "Geometry Area:" << qAbs(area);
        }
    }

        CountCommand::CountCommand(QObject * parent) : Command(parent)
        {
        }

        void CountCommand::execute()
        {

            // ���贫�����ͼ����Ϣ��ÿ��ͼ������������Ҫ��
            QVector<QVector<QPoint>> layer1;
            // ��ӵ�һ��ͼ��ļ���Ҫ��
            //�����ͼ��ֻ���������Σ��ϲ�ʱ��дһ��forѭ����ͼ�㼸��������֪����ȡ���м��ε�
            layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
            layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

            int geometryCount = layer1.size();
            qDebug() << "Geometry Count:" << geometryCount;
        }

