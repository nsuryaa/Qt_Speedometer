#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int iCenterX = 0, iCenterY = 0, iRadius = 0;

    painter.setRenderHint(QPainter::Antialiasing);

    /*center and radius of the speedometer*/
    iCenterX  = (ui->obj_grp_bx_Speedometer->width()) / 2;
    iCenterY  = (ui->obj_grp_bx_Speedometer->height()) / 2;
    iRadius   = qMin(ui->obj_grp_bx_Speedometer->width(), ui->obj_grp_bx_Speedometer->height()) / 2 - 30;

    // Set the dominant background color
    /*
    QColor backgroundColor(0,0,0,255); // Replace with the most dominant color (e.g., dark blue)
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen); // Remove the border for the background circle
    */
    //painter.drawEllipse(QPoint(iCenterX, iCenterY), iRadius + 40, iRadius + 40);

    QRadialGradient gradient(QPointF(iCenterX, iCenterY), iRadius + 40);
    gradient.setColorAt(0, QColor(0, 0, 0, 255));   // Inner color
    gradient.setColorAt(1, QColor(30, 30, 30, 255)); // Outer color
    painter.setBrush(gradient);

    // Define colors for circles
        QColor circleColors[7] = {
            QColor(89,89,89,255),   // dark gray
            QColor(200,200,200,255),   // light gray
            QColor(200,200,200,255), //light gray
            QColor(8,6,9,255),   // outer black color1
            QColor(189,42,34,255), // outer red
            QColor(54,250,249,255),  //outer sky blue
            QColor(0,13,18,255),   // outer black color2
        };

        // Draw the five outer circles
        for (int i = 0; i < 7; ++i)
        {
            QPen pen(circleColors[i], 4); // Different color for each circle
            painter.setPen(pen);
            painter.drawEllipse(QPoint(iCenterX, iCenterY), iRadius, iRadius);
            iRadius -= 4; // Decrease radius for the next circle
        }

        // Draw the inner circle
        iRadius = qMin(ui->obj_grp_bx_Speedometer->width(), ui->obj_grp_bx_Speedometer->height()) / 4 - 20;
        QPen innerPen(QColor(54,250,249,255), 2); // Light blue
        painter.setPen(innerPen);
        painter.drawEllipse(QPoint(iCenterX, iCenterY), iRadius, iRadius);

        // Draw the innermost circle
        iRadius = qMin(ui->obj_grp_bx_Speedometer->width(), ui->obj_grp_bx_Speedometer->height()) / 10 - 20;
        QPen innermostPen(QColor(54,250,249,255), 5); // Light blue
        painter.setPen(innermostPen);
        painter.drawEllipse(QPoint(iCenterX, iCenterY), iRadius, iRadius);

         iRadius   = qMin(ui->obj_grp_bx_Speedometer->width(), ui->obj_grp_bx_Speedometer->height()) / 4 - 22;
        // Draw the 36 rounded small lines
           int numLines = 36;
           float angleStep = 360.0 / numLines;
           float lineLength = 5; // Length of each line
           QPen linePen(QColor(54,250,249,255), 2, Qt::SolidLine, Qt::RoundCap);
           painter.setPen(linePen);

           for (int i = 0; i < numLines; ++i)
           {
               float angle = i * angleStep;
               float radian = qDegreesToRadians(angle);

               // Start and end points of the line
               QPointF startPoint(iCenterX + (iRadius - lineLength) * cos(radian),
                                  iCenterY + (iRadius - lineLength) * sin(radian));
               QPointF endPoint(iCenterX + iRadius * cos(radian),
                                iCenterY + iRadius * sin(radian));

               painter.drawLine(startPoint, endPoint);
           }

           // Radius of the inner circle
           iRadius = qMin(ui->obj_grp_bx_Speedometer->width(), ui->obj_grp_bx_Speedometer->height()) / 4 - 20;

           // Define the rectangle that bounds the circle (arc bounding rectangle)
           QRectF boundingRect(iCenterX - iRadius, iCenterY - iRadius, 2 * iRadius, 2 * iRadius);

           // Adjusted angles for proper positioning
           //int numLines = 36;          // Total number of lines in the inner circle
           float anglePerLine = 360.0 / numLines; // Degrees per line

           // Right arc (red): starts at Line 5.5, ends at Line 14.5
           QPen rightArcPen(QColor(54, 250, 249, 255), 5, Qt::SolidLine, Qt::RoundCap);
           painter.setPen(rightArcPen);

           float rightStartAngle = -(90 + (5.5 * anglePerLine)) * 16; // Adjust start from 3 o'clock
           float rightSpanAngle = -(14.5 - 5.5) * anglePerLine * 16;  // Span between lines 5.5 to 14.5
           painter.drawArc(boundingRect, rightStartAngle, rightSpanAngle);

           // Left arc (light blue): starts at Line 23.5, ends at Line 32.5
           QPen leftArcPen(QColor(249, 22, 5, 255), 5, Qt::SolidLine, Qt::RoundCap);
           painter.setPen(leftArcPen);

           float leftStartAngle = -(90 + (23.5 * anglePerLine)) * 16; // Adjust start from 3 o'clock
           float leftSpanAngle = -(32.5 - 23.5) * anglePerLine * 16;  // Span between lines 23.5 to 32.5
           painter.drawArc(boundingRect, leftStartAngle, leftSpanAngle);


}
