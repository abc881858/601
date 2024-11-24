#include "evaluatewidget.h"
#include "ui_evaluatewidget.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

EvaluateWidget::EvaluateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluateWidget)
{
    ui->setupUi(this);
    ui->rightStackedWidget->setCurrentIndex(1);
    ui->tabWidget_2->setCurrentIndex(0);
    ui->stackedWidget_3->setCurrentIndex(0);
}

EvaluateWidget::~EvaluateWidget()
{
    delete ui;
}

void EvaluateWidget::on_pushButton_1_clicked()
{
    ui->rightStackedWidget->setCurrentIndex(0);
}

void EvaluateWidget::on_pushButton_2_clicked()
{
    ui->rightStackedWidget->setCurrentIndex(1);
}

void EvaluateWidget::on_pushButton_3_clicked()
{
    ui->rightStackedWidget->setCurrentIndex(2);
}

void EvaluateWidget::on_detail_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}

void EvaluateWidget::on_export_word_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save as Word", "", "Doc Files (*.doc)");
    if (!filePath.isEmpty())
    {
        QWidget* contentWidget = ui->scrollAreaContent;

        // 创建一个 QPixmap 大小为内容部件的大小
        QPixmap pixmap(contentWidget->size());
        pixmap.fill(Qt::white); // 填充背景为白色（可选）
        // 渲染内容部件到 QPixmap
        contentWidget->render(&pixmap);
        // 保存 QPixmap 为 PNG 文件
        pixmap.save("pixmap.png");

        QString imgPath("pixmap.png");

        QString html;
        //文字部分
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
        html += "<h2 align=\"center\">任务综合评估报告</h2>";
        html += "<h4 align=\"center\">" + current_date + "</h2><br>";
        //图片部分
        html += "<img align=\"middle\" src = \"" + imgPath + "\"  width=\"600\" height=\""+ QString::number(pixmap.height()) + "\"/><br>" ;

        QFile outFile(filePath);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append );
        QTextStream ts(&outFile);
        ts << html;
        outFile.close();
    }
}

void EvaluateWidget::on_export_pdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save as PDF", "", "PDF Files (*.pdf)");
    if (!filePath.isEmpty())
    {
        QWidget* contentWidget = ui->scrollAreaContent;

        // 设置 PDF 文件写入器
        QPdfWriter pdfWriter(filePath);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4)); // 设置为 A4 纸张大小
        pdfWriter.setResolution(300); // 设置分辨率
        QPainter painter(&pdfWriter);

        // 获取内容的总大小和页面的绘制区域大小
        QSize contentSize = contentWidget->size();
        QRect pdfPageRect = pdfWriter.pageLayout().paintRectPixels(pdfWriter.resolution());

        // 计算缩放比例（等比缩放）
        qreal scaleFactor = qMin(
            pdfPageRect.width() / static_cast<qreal>(contentSize.width()),
            pdfPageRect.height() / static_cast<qreal>(contentSize.height())
        );

        // 渲染内容到 PDF，保持等比缩放并靠上对齐
        int yOffset = 0;
        while (yOffset < contentSize.height())
        {
            QRect partRect(0, yOffset, contentSize.width(), pdfPageRect.height() / scaleFactor);

            // 截取当前页的内容
            QPixmap pagePixmap(contentSize);
            contentWidget->render(&pagePixmap, QPoint(0, -yOffset)); // 渲染内容到 Pixmap
            QPixmap currentPage = pagePixmap.copy(partRect);

            // 计算靠上对齐的目标矩形
            QSize scaledSize = QSize(
                static_cast<int>(contentSize.width() * scaleFactor),
                static_cast<int>(contentSize.height() * scaleFactor)
            );
            QRectF targetRect(
                0, // 左对齐
                0, // 上对齐，留白在下方
                scaledSize.width(),
                scaledSize.height()
            );

            // 缩放并绘制到 PDF 页面
            painter.drawPixmap(targetRect, currentPage, QRectF(0, 0, currentPage.width(), currentPage.height()));

            yOffset += partRect.height();
            if (yOffset < contentSize.height()) {
                pdfWriter.newPage(); // 创建新页面
            }
        }

        painter.end();
    }
}

void EvaluateWidget::on_analyze_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(2);
}

void EvaluateWidget::on_subjective_return_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
}
