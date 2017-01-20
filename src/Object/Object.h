#pragma once
#include "cinder/app/App.h"


class Object
{
public:

	Object() :
		is_active(true)
	{}
	virtual ~Object() {}

	virtual void Delete() {}

	bool GetIsActive() const { return is_active; }
	void SetActive(const bool &is_active_) { is_active = is_active_; }

protected:

	bool is_active;
};