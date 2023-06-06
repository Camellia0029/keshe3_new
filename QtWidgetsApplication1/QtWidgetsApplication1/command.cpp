#include "command.h"
#include <QDebug>
//调用第三方库
#include <QPainter>
//#include "D:\QtWidgetsApplication\QtWidgetsApplication1\triangle\triangle.h" 
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
    //执行函数
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

//叠加分析（求交集）函数准备
OverlayCommand::OverlayCommand(QObject* parent) : Command(parent)
{


}

void OverlayCommand::execute()
{
    qDebug() << "Executing Overlay Command";

    // 假设传入的是图层信息，每个图层包含多个几何要素
    QVector<QVector<QPoint>> layer1;
    // 添加第一个图层的几何要素
    layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
    layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

    QVector<QVector<QPoint>> layer2;
    // 添加第二个图层的几何要素
    layer2 << QVector<QPoint> { QPoint(3, 3), QPoint(3, 8), QPoint(8, 8), QPoint(8, 3) };
    layer2 << QVector<QPoint> { QPoint(6, 6), QPoint(6, 9), QPoint(9, 9), QPoint(9, 6) };

    // 获取图层几何要素数量
    int layer1Count = layer1.size();
    int layer2Count = layer2.size();

    // 动态创建几何对象数组
    QVector<QPolygon> polygons1(layer1Count);
    QVector<QPolygon> polygons2(layer2Count);

    // 构建图层的几何要素对象
    for (int i = 0; i < layer1Count; i++)
    {
        polygons1[i] = QPolygon(layer1[i]);
    }

    for (int i = 0; i < layer2Count; i++)
    {
        polygons2[i] = QPolygon(layer2[i]);
    }

    // 计算图层的并集
    QVector<QPolygon> resultPolygons;
    for (const QPolygon& polygon1 : polygons1)
    {
        for (const QPolygon& polygon2 : polygons2)
        {
            QPolygon resultPolygon = polygon1.united(polygon2);
            resultPolygons.append(resultPolygon);
        }
    }

    // 打印并集多边形的顶点坐标
    for (const QPolygon& resultPolygon : resultPolygons)
    {
        for (const QPoint& point : resultPolygon)
        {
            qDebug() << "Point: (" << point.x() << ", " << point.y() << ")";
        }
    }
}

//delaunay三角网函数准备
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


    // 假设传入的是图层信息，每个图层包含多个几何要素
    QVector<QVector<QPoint>> layer1;
    // 添加第一个图层的几何要素
    //假设该图层只有两个矩形，合并时再写一个for循环（图层几何数量已知）获取所有几何点
    layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
    layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

    // 计算每个几何要素的周长
    for (const QVector<QPoint>& geometry : layer1)
    {
        qreal perimeter = 0.0;

        // 计算几何要素的周长
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
    //打印周长
}
    AreaCommand::AreaCommand(QObject * parent) : Command(parent)
    {
    }

    void AreaCommand::execute()
    {

        // 假设传入的是图层信息，每个图层包含多个几何要素
        QVector<QVector<QPoint>> layer1;
        // 添加第一个图层的几何要素
        //假设该图层只有两个矩形，合并时再写一个for循环（图层几何数量已知）获取所有几何点
        layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
        layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

        // 计算每个几何要素的面积
        for (const QVector<QPoint>& geometry : layer1)
        {
            qreal area = 0.0;

            // 计算几何要素的面积
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

            // 假设传入的是图层信息，每个图层包含多个几何要素
            QVector<QVector<QPoint>> layer1;
            // 添加第一个图层的几何要素
            //假设该图层只有两个矩形，合并时再写一个for循环（图层几何数量已知）获取所有几何点
            layer1 << QVector<QPoint> { QPoint(0, 0), QPoint(0, 5), QPoint(5, 5), QPoint(5, 0) };
            layer1 << QVector<QPoint> { QPoint(2, 2), QPoint(2, 7), QPoint(7, 7), QPoint(7, 2) };

            int geometryCount = layer1.size();
            qDebug() << "Geometry Count:" << geometryCount;
        }

