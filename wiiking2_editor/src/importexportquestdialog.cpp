// This file is part of WiiKing2 Editor.
//
// WiiKing2 Editor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Wiiking2 Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WiiKing2 Editor.  If not, see <http://www.gnu.org/licenses/>

#include "importexportquestdialog.h"
#include "ui_importexportquestdialog.h"
#include "mainwindow.h"
#include "skywardswordfile.h"
#include <ZQuestFile.hpp>
#include <ZQuestFileWriter.hpp>
#include <ZQuestFileReader.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

ImportExportQuestDialog::ImportExportQuestDialog(QWidget *parent, Mode mode) :
    QDialog(parent),
    ui(new Ui::ImportExportQuestDialog),
    m_mode(mode),
    m_quest(NULL)
{
    ui->setupUi(this);
    MainWindow* mw = qobject_cast<MainWindow*>(this->parent());

    if (mw)
    {
        if (mode == Export)
        {
            setWindowTitle("Export Quest");
            ui->nameLineEdit->setText(mw->gameFile()->playerName());
            ui->rupeeSpinBox->setValue(mw->gameFile()->rupees());
            ui->hpCurrentSpinBox->setValue(mw->gameFile()->currentHP());
            ui->hpMaxSpinBox->setValue(mw->gameFile()->totalHP());

            connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), mw->gameFile(), SLOT(setPlayerName(QString)));
            connect(ui->rupeeSpinBox, SIGNAL(valueChanged(int)), mw->gameFile(), SLOT(setRupees(int)));
            connect(ui->hpCurrentSpinBox, SIGNAL(valueChanged(int)), mw->gameFile(), SLOT(setCurrentHP(int)));
            connect(ui->hpMaxSpinBox, SIGNAL(valueChanged(int)), mw->gameFile(), SLOT(setTotalHP(int)));
            ui->compressChkBox->setVisible(true);
            ui->importPathgroup->setVisible(false);
            // Resize the window to hide the gap
            this->resize(this->width(), this->height() - (ui->importPathgroup->height() * 2));
        }
        else
        {
            setWindowTitle("Import Quest");
            ui->compressChkBox->setVisible(false);
            ui->importPathgroup->setVisible(true);

            connect(ui->importPushBtn, SIGNAL(clicked()), this, SLOT(onPathPressed()));
        }
    }
}

ImportExportQuestDialog::~ImportExportQuestDialog()
{
    delete m_quest;
    delete ui;
}

void ImportExportQuestDialog::onPathPressed()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import Quest"), QString(), "ZQuest files (*.zquest)");

    if (!path.isEmpty())
    {
        ui->importLineEdit->setText(path);
        zelda::io::ZQuestFileReader reader(path.toStdString());
        m_quest = reader.read();
        if (m_quest->data() && m_quest->gameString() == "Skyward Sword")
        {
            // NTSCU to be safe (it's temporary anyway)
            SkywardSwordFile game(SkywardSwordFile::NTSCURegion);
            game.setGame(IGameFile::Game1);
            game.setGameData(QByteArray((const char*)m_quest->data(), m_quest->length()));

            ui->nameLineEdit->setText(game.playerName());
            ui->rupeeSpinBox->setValue(game.rupees());
            ui->hpCurrentSpinBox->setValue(game.currentHP());
            ui->hpMaxSpinBox->setValue(game.totalHP());
        }
    }
}

void ImportExportQuestDialog::accept()
{
    MainWindow* mw = qobject_cast<MainWindow*>(parent());

    if (mw)
    {
        if (m_mode == Export)
        {
            QString filename = QFileDialog::getSaveFileName(this, tr("Export Quest"), QString(), "ZQuest files (*.zquest)");
            if (!filename.isEmpty())
            {
                // We're going to have to hard code LOZ:SS for now (I'll have to add a static_cast later)
                zelda::ZQuestFile* zquest = new zelda::ZQuestFile();
                zquest->setData((Uint8*)mw->gameFile()->gameData().data(), mw->gameFile()->gameData().size());

                // LOZ:Skyward Sword
                zquest->setGame(zelda::ZQuestFile::SS);
                // LOZ:Skyward sword is always big endian
                zquest->setEndian(zelda::BigEndian);
                qDebug() << "i'm such a retard >.>";

                zelda::io::ZQuestFileWriter writer(filename.toStdString());
                writer.write(zquest, ui->compressChkBox->isChecked());
                delete zquest;
            }
        }
        else
        {
            if (!ui->importLineEdit->text().isEmpty())
            {
                mw->gameFile()->setGameData(QByteArray((const char*)m_quest->data(), m_quest->length()));
                mw->gameFile()->setPlayerName(ui->nameLineEdit->text());
                mw->gameFile()->setRupees(ui->rupeeSpinBox->value());
                mw->gameFile()->setCurrentHP(ui->hpCurrentSpinBox->value());
                mw->gameFile()->setTotalHP(ui->hpMaxSpinBox->value());
            }
            else
            {
                QMessageBox mbox(QMessageBox::Warning, tr("No file specified"), tr("No file was selected to import"));
                mbox.exec();
            }
        }
    }

    QDialog::accept();
}
