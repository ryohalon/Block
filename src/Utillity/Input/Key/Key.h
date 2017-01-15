#pragma once
#include "cinder/app/KeyEvent.h"
#include <set>
#include <memory>




class Key
{
public:

	Key();
	~Key();

	static Key& Get()
	{
		static Key key;

		return key;
	}

	void PushKey(const ci::app::KeyEvent &key_event);
	void PullKey(const ci::app::KeyEvent &key_event);

	void FlushInput();

	bool IsPushKey(const int &key);
	bool IsPressKey(const int &key);
	bool IsPullKey(const int &key);

private:

	struct KeyStatus
	{
		std::set<int> push_key;
		std::set<int> press_key;
		std::set<int> pull_key;
	};

	std::unique_ptr<KeyStatus> key_status;

};