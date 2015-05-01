#include "Stadium.h"

Stadium::Stadium(QString name, QString team, int phoneNumber, int capacity, Address address, Date dateOpened)
	: name(name), team(team), phoneNumber(phoneNumber), capacity(capacity), address(address), dateOpened(dateOpened)
{ }

bool Stadium::LoadFromJson(const QJsonObject &json, bool allowPartial)
{
	if (json.contains("Name"))
		name = json["Name"].toString();
	else if (!allowPartial)
		return false;

	if (json.contains("Team"))
		team = json["Team"].toString();
	else if (!allowPartial)
		return false;

	if (json.contains("PhoneNumber"))
		phoneNumber = json["PhoneNumber"].toInt();
	else if (!allowPartial)
		return false;

	if (json.contains("Capacity"))
		capacity = json["Capacity"].toInt();
	else if (!allowPartial)
		return false;

	if (json.contains("Address"))
	{
		if (!address.LoadFromJson(json["Address"].toObject()))
			return false;
	}
	else if (!allowPartial)
		return false;

	if (json.contains("DateOpened"))
	{
		if (!dateOpened.LoadFromJson(json["DateOpened"].toObject()))
			return false;
	}
	else if (!allowPartial)
		return false;

	return true;
}

QJsonObject Stadium::SaveToJson() const
{
	QJsonObject json;

	json["Name"]        = name;
	json["Team"]        = team;
	json["PhoneNumber"] = phoneNumber;
	json["Capacity"]    = capacity;
	json["Address"]     = address.SaveToJson();
	json["DateOpened"]  = dateOpened.SaveToJson();

	return json;
}