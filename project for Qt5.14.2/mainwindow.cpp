#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp rx("[A-z 0-9]{1,99}");//----Создание ограничения на ввод
    QValidator *validator = new QRegExpValidator(rx, this);
    QRegExp rx2("[0-1 ]{1,99}");
    QValidator *validator2 = new QRegExpValidator(rx2, this);
    ui->lineEditKey->setValidator(validator);
    ui->lineEdit_Decrypt->setValidator(validator2);
    ui->lineEdit_Encrypt->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonEncrypt_clicked()//---нажатие на кнопку выбора шифрования(шифрование)
{
    ui->pushButtonEncrypt->setChecked(1);
    ui->pushButton_Decrypt->setChecked(0);

    ui->lineEdit_Encrypt->setEnabled(1);
    ui->label_Encrypt->setEnabled(1);
    ui->label_Encrypt->setText("Введите Текст для шифрования(EN):");
    ui->lineEdit_Decrypt->setEnabled(0);
    ui->label_Decrypt->setText("Зашифрованный текст:");
}

void MainWindow::on_pushButton_Decrypt_clicked()//---нажатие на кнопку выбора шифрования(дешифрование)
{
    ui->pushButton_Decrypt->setChecked(1);
    ui->pushButtonEncrypt->setChecked(0);

    ui->lineEdit_Decrypt->setEnabled(1);
    ui->label_Decrypt->setEnabled(1);
    ui->label_Decrypt->setText("Введите Код для дешифрования:");
    ui->lineEdit_Encrypt->setEnabled(0);
    ui->label_Encrypt->setText("Исходный текст:");
}

void MainWindow::on_pushButtonInputKey_clicked()//-----нажатие на кнопку принятия ключа
{
    if(ui->lineEditKey->text().length() == 0){             // Проверка на наличие ключа
        ui->label_Encrypt->setEnabled(1);
        ui->label_Encrypt->setText("Введите Ключ!");
    }
    else{
        key = ui->lineEditKey->text();
        ui->lineEditKey->setEnabled(0);
        ui->pushButtonInputKey->setEnabled(0);
        ui->pushButton_ResetKey->setEnabled(1);
        ui->label_KeyReview->setText("Текущий ключ: " + key);
        ui->pushButtonEncrypt->setEnabled(1);
        ui->pushButton_Decrypt->setEnabled(1);
    }
}

void MainWindow::on_lineEdit_Encrypt_textEdited(const QString &arg1)//---реакция на ввод текста в верхнее поле(шифрование)
{
    QString out_text;
    int pos_key = 0;
    int key_num, input_num, out_num;
    for (int i = 0; i < arg1.length(); i++) {
        key_num = key[pos_key++].unicode();             // Номер символа ключа в кодировке unicode.
        input_num = arg1[i].unicode();            // Номер символа исходного текста в кодировке unicode.
        out_num = key_num ^ input_num;// XOR номеров символов.
        out_text+=QString("%1").arg(out_num, 8, 2, QChar('0'));
//        out_text+=QChar(out_num);                       // Преобразование кода символа в символ.
        out_text+=" ";
        if(pos_key == key.length())
            pos_key = 0;
    }
    ui->lineEdit_Decrypt->clear();
    ui->lineEdit_Decrypt->setText(out_text);
    ui->lineEdit_Decrypt->setEnabled(1);
}





void MainWindow::on_lineEdit_Decrypt_textEdited(const QString &arg1)//---реакция на ввод текста в нижнее поле(дешифрование)
{
    QString Input = ui->lineEdit_Decrypt->text();
    if(Input[Input.length()-1]!= ' ') Input[Input.length()] = ' ';
    QString out_text, texet, text, p;
    bool ok;
    int pos_key = 0;
    int key_num, input_num, out_num;
    for (int i = 0; i < Input.length(); i++) {
        if (Input[i] != " " && i!=Input.length()-1) texet+=Input[i];
    else
        {
            key_num = key[pos_key++].unicode();
            text=texet.toInt(&ok,2);
            p = text;
            input_num = p[0].unicode();
            out_num = key_num ^ input_num;
            out_text+=QChar(out_num);
            if(pos_key == key.length())
                pos_key = 0;
            texet = "";
        }
    }
    ui->lineEdit_Encrypt->clear();
    ui->lineEdit_Encrypt->setText(out_text);
    ui->lineEdit_Encrypt->setEnabled(1);
}

void MainWindow::on_pushButton_ResetKey_clicked()
{
    ui->lineEditKey->setText("");
    ui->lineEdit_Decrypt->setText("");
    ui->lineEdit_Decrypt->setEnabled(0);
    ui->label_Decrypt->setText("");
    ui->lineEdit_Encrypt->setText("");
    ui->lineEdit_Encrypt->setEnabled(0);
    ui->label_Encrypt->setText("");
    ui->lineEditKey->setEnabled(1);
    ui->pushButtonInputKey->setEnabled(1);
    ui->label_KeyReview->setText("");
    ui->pushButtonEncrypt->setEnabled(0);
    ui->pushButton_Decrypt->setEnabled(0);
    ui->pushButton_ResetKey->setEnabled(0);
}
