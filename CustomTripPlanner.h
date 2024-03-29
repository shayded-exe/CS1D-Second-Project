#ifndef CUSTOMTRIPPLANNER_H
#define CUSTOMTRIPPLANNER_H

#include "ui_CustomTripPlanner.h"
#include "StadiumListModel.h"
#include "CurrentTrip.h"
#include "Settings.h"

#include <QDialog>
#include <QMessageBox>

class CustomTripPlanner : public QDialog
{
	Q_OBJECT

public:
	CustomTripPlanner(QWidget *parent = 0);

private:
	Ui::CustomTripPlanner ui;

	StadiumList availableStadiums;
	StadiumList chosenStadiums;

	StadiumListModel *availableStadiumsModel = nullptr;
	StadiumListModel *chosenStadiumsModel = nullptr;

	private slots:
	void AddStadium();
	void RemoveStadium();
	void MoveUp();
	void MoveDown();
	void StartTrip();
};

#endif