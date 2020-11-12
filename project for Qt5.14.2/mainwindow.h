#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int keyLength = 0;
    int **letterSequence;

private slots:
    void on_pushButtonEncrypt_clicked();

    void on_lineEdit_Encrypt_textEdited(const QString &arg1);


    void on_pushButtonInputKey_clicked();

    void on_pushButton_Decrypt_clicked();

    void on_lineEdit_Decrypt_textEdited(const QString &arg1);

    void on_pushButton_ResetKey_clicked();
private:
    Ui::MainWindow *ui;
    QString key = "";
};
#endif // MAINWINDOW_H
