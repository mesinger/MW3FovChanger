#pragma once

#include <Windows.h>

namespace fov {

	class Changer {

	public:
		Changer(float fov = 90.f);
		virtual ~Changer();

		/*fov changing functions for singleplayer, this method blocks execution*/
		void setfov_sp(const HANDLE hProc) const;
		/*fov changing functions for multiplayer, this method blocks execution*/
		void setfov_mp(const HANDLE hProc) const;

		float getFov() const {
			return fov;
		}

		bool changeFov(float newfov) {
			if (newfov <= 0.f || newfov > 180.f) return false;
			this->fov = newfov;
			return true;
		}

	private:

		float fov;
	};

	void updateConfig(float fov);
}

